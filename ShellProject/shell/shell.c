#include <sys/wait.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <sys/param.h>

#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "str_replace.h"
#include <fcntl.h>

static int error;
static int stdinCopy;
static int stdoutCopy;

typedef int (*builtin_cmd)(int, char **);

typedef int cond;

typedef struct job_s{
	char **cmd;
	int in;
	int out;
	int background;
	cond condition;
	int skip;
	int valid;
	struct job_s *next;
} job;

struct builtin {
	const char *name;
	builtin_cmd func;
};
#define	BIN(n)	{ #n, builtin_ ## n }
#define NONE 0
#define AND 1
#define OR 2

int
builtin_cd(int argc, char **argv) {
	
	int status;
	
	if (argc == 1 && strcmp(argv[0], "cd") == 0) {
		fprintf(stderr, "Not enough arguments for command cd.\n");
		status = 1;
		//to return to home directory instead :
		//status = chdir(getenv("HOME"));
	} else if (argc == 2) {
		if(strchr(argv[1], '~')) {

			char* rep = str_replace(argv[1], "~", getenv("HOME"));
			status = chdir(rep);
			free(rep);
			rep = NULL;
		} else {
			status = chdir(argv[1]);
		}
	}
	
	if (status != 0 && errno != 0) {
		switch(errno) {
			case ENOENT:
				fprintf (stderr, "%s does not exist.\n", argv[1]);
				break;
			case ENOTDIR:
				fprintf (stderr, "%s is not a directory.\n", argv[1]);
				break;
			default:
				perror("Error \n");
				break;
		}
		return(1);
	}

	return (0);
}

int builtin_exit(int argc, char **argv) {
	exit(EXIT_SUCCESS);
}

int builtin_status(int argc, char **argv) {
	printf("%d");
	/*int i;
	printf("arglist:\n");
	for (i=0; argv[i]!=NULL; i++){
		printf("%d) %s\n", (i+1), argv[i]);
	}*/
	return (0);
}

static struct builtin builtins[] = {
	BIN(cd),
	BIN(exit),
	BIN(status),
	{ NULL }
};

/*
 * run_builtin handles setting up the handlers for your builtin commands
 *
 * It accepts the array of strings, and tries to match the first argument
 * with the builtin mappings defined in the builtins[].
 * Returns 0 if it did not manage to find builtin command, or 1 if args
 * contained a builtin command
 */
static int
run_builtin(char **args)
{
	int argc;
	struct builtin *b;

	for (b = builtins; b->name != NULL; b++) {
		if (strcmp(b->name, args[0]) == 0) {
			for (argc = 0; args[argc] != NULL; argc++)
				/* NOTHING */;
			error = b->func(argc, args);
			return (1);
		}
	}

	return (0);
}

/* add your code here */



void
printCwd() {
	char cwd[MAXPATHLEN+1];
	getcwd(cwd, sizeof(cwd));
	printf("%s %% ", cwd);
}


/**
 * Creates a new job
 */
job* newJob(cond condition, int inPipe) {
	job* nJob = NULL;
	if (!(nJob = malloc(sizeof(job)))) {
		printf(stderr, "Memory allocation error when creating job, exiting.\n");
		exit(EXIT_FAILURE);
	} else {
		nJob->cmd = NULL;
		nJob->in = inPipe;
		nJob->out = STDOUT_FILENO;
		nJob->background = 0;
		nJob->condition = condition;
		nJob->skip = 0;
		nJob->valid = 0;
		nJob->next = NULL;
	}
	return nJob;
}

job* defaultJob(void) {
	return newJob(NONE, STDIN_FILENO);
}

/* Creates a default new job */
job * defaultJob_old(void) {
	job* nJob;

	if(!(nJob = malloc(sizeof(job)))) {
		fprintf(stderr, "Memory error, exiting.\n");
		exit(1);
	}
	nJob->condition=NONE;
	nJob->next=NULL;
	nJob->in = STDIN_FILENO;
	nJob->out = STDOUT_FILENO;
	nJob->valid = 0;

	return nJob;
}

/* Stores a parsed chain of word in a given job.
 * If currentJob is NULL, then a new default job is created to store the information.
 * When pasingCommand is set to 1, inputRedirection is ignored.
 * In the case of a redirection, only the first word of parsed is used.
 * If any error occurs, the job will still exist but marked as non-valid.
 * @param currentJob job to be updated
 * @param parsingCommand indicates if parsed is a command (1) or a redirection (0)
 * @param inputRedirection indicates if the if the redirection is on the input (1) or the output (0)
 * @param parsed the parsed chain of word to use in the method*/
void
storeParsed(job *givenJob, int parsingCommand, int inputRedirection, char **parsed )
{
	if (parsed && parsed[0]) {
		if (parsingCommand) {
			givenJob->cmd = parsed;
			givenJob->valid = 1;
		} else if (inputRedirection) {
			int fd = fileno(fopen(parsed[0], "r"));
			if (fd < 0) {
				fprintf(stderr, "%s: No such file or directory\n", parsed[0]);
			} else {
				givenJob->in = fd;
			}
		} else {
			int fd = fileno(fopen(parsed[0], "w"));
			if (fd < 0) {
				fprintf(stderr, "%s: Unable to open or create\n", parsed[0]);
				givenJob->valid = 0;
			} else {
				givenJob->out = fd;
			}
		}
	}
}

/* Frees the given job.
 * The pointer on job is set to NULL.
 * @param address of the pointer on job
 */
void
freeJob(job **oldJob) {
	// close fd. referred file is really closed only if it's last fd is closed
	if ((*oldJob)->in!=STDIN_FILENO) close((*oldJob)->in);
	if ((*oldJob)->out!=STDOUT_FILENO) close((*oldJob)->out);
	free(*oldJob);
	*oldJob = NULL;
}

void
popAndFreeJob(job** jobList) {
	job *tail = NULL;
	if (jobList&&*jobList) {
		tail = (*jobList)->next;
		freeJob(jobList);
		*jobList = tail;
	}
}

void
jobLauncher(job* jobs)
{
	job* tmpJob=jobs;
	pid_t childPid;

	for(;tmpJob;popAndFreeJob(&tmpJob)){

		// Test for conditions on previous commands !!! error==0 if no error...
		if(tmpJob->condition  == AND && error){
			continue;
		}else if(tmpJob->condition == OR && !error){
			continue;
		}

		if(tmpJob->skip) {
			error=0;
			continue;
		}

		if(!(tmpJob->valid)){
			error=1;
			continue;
		}

		if(tmpJob->background){
			printf("We are in background mode! O_o\n");
			if((childPid=fork()) < 0 ){
				fprintf(stderr,"JobLauncher failed miserably to fork process O_o\n");
				exit(1);

			}else if(childPid == 0){
				// Code only executed by the child

				dup2(tmpJob->in, STDIN_FILENO);
				dup2(tmpJob->out, STDOUT_FILENO);

				if (run_builtin(tmpJob->cmd)){

					fprintf(stderr,"background : builtin executed!\n");

				}else{
					if(execvp(*(tmpJob->cmd), tmpJob->cmd)){
						fprintf(stderr,"background : shell function failed!\n");
						error=1;


					}else{
						fprintf(stderr,"background : shell function executed!\n");
						error=0;
					}
				}

				fprintf(stderr,"background : child %d", childPid);

				exit(error);


			}else{
				// Code only executed by parent process
				//no wait, its in the background!!!
			}
		}else{

			if (tmpJob->in == STDIN_FILENO && tmpJob->out == STDOUT_FILENO && run_builtin(tmpJob->cmd)){
					fprintf(stderr, "builtin executed!\n");
			}else{
				if((childPid=fork()) < 0 ){
						fprintf(stderr, "JobLauncher failed miserably to fork process O_o\n");
						exit(1);

				}else if(childPid == 0){
					// Code only executed by the child
					//change the handler of the interrup signal
					dup2(tmpJob->in, STDIN_FILENO);
					dup2(tmpJob->out, STDOUT_FILENO);

					// close unused hald of pipe

					//close((tmpJob->in)++);

					signal(SIGINT, SIG_DFL);

					if(run_builtin(tmpJob->cmd)){
						fprintf(stderr, "child %d : builtin executed!\n", childPid);
						error=0;
					}else if(execvp(*(tmpJob->cmd), tmpJob->cmd)){
						fprintf(stderr,"child %d : shell function failed!\n", childPid);
						error=1;
					}else{

						fprintf(stderr,"child %d : shell function executed!\n", childPid);
						error=0;
					}
					fprintf(stderr,"child %d : exiting\n", childPid);
					exit(error);
				}else{
					// Code only executed by parent process

					dup2(stdinCopy, STDIN_FILENO);
					dup2(stdoutCopy, STDOUT_FILENO);

					printf("parent %d : waiting on child %d\n", getpid(),childPid);
					waitpid(childPid, &error, 0 );
					printf("parent %d : finished waiting on child %d\n",getpid(),childPid);
				}
			}
		}
	}
}

/*
 * Takes a pointer to a string pointer and advances this string pointer
 * to the word delimiter after the next word.
 * Returns a pointer to the beginning of the next word in the string,
 * or NULL if there is no more word available.
 */
static char *
parseword(char **pp)
{
	char *p = *pp;
	char *word;

	for (; isspace(*p); p++)
		/* NOTHING */;

	word = p;

	for (; strchr(" \t;&|><\n#", *p) == NULL; p++)
		/* NOTHING */;

	*pp = p;
	return (p != word ? word : NULL);
}

/* Parses an input line of the shell and creates the associated job list, then call jobLauncher(jobs);
 * Known bugs:
 * -	> file.txt will set status at 1 (error) but still creates a file.
 *
 * -	Unvalid syntax as shellCmd & | ; does not throw any error but creates unvalid empty jobs:
 * 		shellCmd & [empty, unvalid] | [empty, unvalid] ;
 * 		thus error status will be set to 1 with no error message
 */
static void
process(char *line)
{
	int ch, ch2;
	char *p, *word;


	/* args: stores all parsed chain of word
	 * narg: points after the last parsed word
	 * harg: points on the first word of the chain that will be stored in currentJob */

	char *args[100], **narg, **harg;
	/* previous: points on last completly created job
	 * currentJob: job being created
	 * jobs: empty job used as head of the list => call jobLauncher(jobs->next);*/
	job *currentJob, *previousJob, *jobs;
	int pip[2];
	/* parsingCommand=1 when parsing a shell command,
	 * parsingCommand=0 when parsing a redirection.*/
	int parsingCommand = 1;

	/* inputRedirection=1 when parsing an input redirection "<"
	 * inputRedireciton=0 when parsing an output redirection ">"
	 * inputRedirection=unspecified when parsing a command*/
	int inputRedirection = 0;

	/* stores the informations to add to the next job*/
	int condition = NONE;
	int inPipe = STDIN_FILENO;

	/* interrupt for loop when comment is seen*/
	int commented = 0;

	p = line;

	harg = args;
	narg = args;
	*narg = NULL;

	/*initialises new job list*/
	jobs = defaultJob();
	previousJob = jobs;
	currentJob = previousJob->next;

	for (; *p != 0 && !commented; p != line && p++) {
		word = parseword(&p);

		ch = *p;
		*p = 0;

//		printf("parseword:\nword: '%s'\nend char:'%c'\nline left '%s'\n", word, ch, p + 1);


		if (word != NULL) {
			*narg++ = word;
			*narg = NULL;
		}

		/*
		 * at this point, ch is a character from the string " \t;&|><\n"
		 * p points at the following character of line
		 */

		if (!isblank(ch)) {
			if(!currentJob) {
				currentJob = newJob(condition, inPipe);
				previousJob->next = currentJob;
				// skip indicates an empty job that produce no error
				if (!(*harg)) currentJob->skip = 1;
				condition = NONE;
				inPipe = STDIN_FILENO;
			}
			narg++;
			*narg=NULL;
			storeParsed(currentJob, parsingCommand, inputRedirection, harg);
			harg = narg;
			switch (ch) {
			case '<':
				parsingCommand = 0;
				inputRedirection = 1;
				break;
			case '>':
				parsingCommand = 0;
				inputRedirection = 0;
				break;
			case 0:
			case EOF:
			case '\n':
			case ';':
				parsingCommand = 1;
				previousJob = currentJob; // <=> previousJob = previousJob->next
				currentJob = currentJob->next; // <=> currentJob = NULL
				break;
			case '&':
				p++;
				ch2 = *p;
				if (ch2=='&') {
					condition = AND;
				} else {
					currentJob->background = 1;
				}
				parsingCommand = 1;
				previousJob = currentJob; // <=> previousJob = previousJob->next
				currentJob = currentJob->next; // <=> currentJob = NULL
				break;
			case '|':
				p++;
				ch2 = *p;
				if (ch2=='|') {
					condition = OR;
				} else {
					if (pipe(pip) != 0) {
						fprintf(stderr, "pipe error, commands will be executed independently.\n");
					} else {
						currentJob->out = pip[1];
						inPipe = pip[0];
					}
				}
				parsingCommand = 1;
				previousJob = currentJob; // <=> previousJob = previousJob->next
				currentJob = currentJob->next; // <=> currentJob = NULL
				break;
			case '#':
				parsingCommand = 1;
				previousJob = currentJob; // <=> previousJob = previousJob->next
				currentJob = currentJob->next; // <=> currentJob = NULL
				commented = 1;
				break;
			default:
				fprintf(stderr, "internal unexpected error, exiting\n");
				exit(1);
				break;
			}
		}
	} // end for

	// launchJobs(jobs)
	jobLauncher(jobs->next);

	freeJob(&jobs);
	currentJob = NULL;
	printf("All command on this line have been executed\n");
	// shellcmd | | | | shellcmd
}

int
main(void)
{
	/* setting signal handler to the kernel */
	if (signal(SIGINT, SIG_IGN) == SIG_ERR) {
		printf("Error while setting Ctrl-C handler\n");
	}

// uncomment to run the testscript
//	int testscriptfd = open("testscript", O_RDONLY);
//	dup2(testscriptfd, STDIN_FILENO);

	char line[1000];
	char *res;

	stdinCopy=dup(STDIN_FILENO);
	stdoutCopy=dup(STDOUT_FILENO);

	for (;;) {
		printCwd();

		res = fgets(line, sizeof(line), stdin);
		if (res == NULL)
			break;

		printf("Executing: %s", line);
		process(line);
	}

	return (error);
}
