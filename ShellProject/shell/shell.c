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
	printf("running cd\n");
	
	int status;
	
	if (argc == 1 && strcmp(argv[0], "cd") == 0) {
		fprintf(stderr, "Not enough argument for command cd.");
		status = 1;
	} else if (argc == 2) {
		if(strchr(argv[1], '~')) {
			/*
			printf("true\n");
			char* rep = str_replace(argv[1], "~", getenv("HOME"));
			status = chdir(rep);
			free(rep);
			rep = NULL;
			*/
		} else {
			status = chdir(argv[1]);
		}
	}
	
	if (status != 0) {
		switch(errno) {
			case ENOENT:
				fprintf (stderr, "%s does not exist.\n", argv[1]);
				break;
			case ENOTDIR:
				fprintf (stderr, "%s is not a directory.\n", argv[1]);
				break;
			default:
				perror("Error ");
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
	printf("Status of the last command executed : %d\n", error);
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

/* Creates a default new job */
job * newJob(void) {
	job* nJob;

	if(!(nJob = malloc(sizeof(job)))) {
		fprintf(stderr, "Memory error, exiting.\n");
		exit(1);
	}
	nJob->condition=NONE;
	nJob->next=NULL;
	nJob->in = STDIN_FILENO;
	nJob->out = STDOUT_FILENO;
	nJob->valid = 1;

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
storeParsed(job **currentJob, int parsingCommand, int inputRedirection, char **parsed )
{
	if (!(*currentJob)) *currentJob = newJob();

	job *localJob = *currentJob;

	int success = 0;
	if (parsed && parsed[0]) {
		if (parsingCommand) {
			localJob->cmd = parsed;
			success = 1;
		} else if (inputRedirection) {
			localJob->in = open(parsed[0], O_RDONLY);
			if (localJob->in < 0) {
				fprintf(stderr, "%s: No such file or directory\n", parsed[0]);
			} else {
				success = 1;
			}
		} else {
			localJob->out = open(parsed[0], O_WRONLY|O_CREAT, 666);
			if (localJob->out < 0) {
				fprintf(stderr, "%s: Unable to open or create\n", parsed[0]);
			} else {
				success = 1;
			}
		}
	}

	localJob->valid &= success;
}

/* Frees the given job.
 * The pointer on job is set to NULL.
 * @param address of the pointer on job
 */
void
freeJob(job **oldJob) {
	/* close fd. referred file is really closed only if it's last fd is closed
	if ((*oldJob)->in!=STDIN_FILENO) close((*oldJob)->in);
	if ((*oldJob)->out!=STDOUT_FILENO) close((*oldJob)->out);
	*/
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

			return;
		}else if(tmpJob->condition == OR && !error){
			return;
		}
		if(!(tmpJob->valid)){
			error=1;
			return;
		}


		if(tmpJob->background){
			printf("We are in background mode! O_o\n");
			if((childPid=fork()) < 0 ){
				printf("JobLauncher failed miserably to fork process O_o\n");
				exit(1);

			}else if(childPid== 0){
				// Code only executed by the child

				dup2(tmpJob->in, STDIN_FILENO);
				dup2(tmpJob->out, STDOUT_FILENO);

				if (run_builtin(tmpJob->cmd)){

					printf("background : builtin executed!\n");

				}else{
					if(execvp(*(tmpJob->cmd), tmpJob->cmd)){
						printf("background : shell function failed!\n");
						error=1;
					}else{
						printf("background : shell function executed!\n");
						error=0;
					}
				}
				exit(error);


			}else{
				// Code only executed by parent process
				//no wait, its in the background!!!
			}
		}else{
			dup2(tmpJob->in, STDIN_FILENO);
			dup2(tmpJob->out, STDOUT_FILENO);

			if (run_builtin(tmpJob->cmd)){

				printf("builtin executed!\n");

			}else{
				if((childPid=fork()) < 0 ){
						printf("JobLauncher failed miserably to fork process O_o\n");
						exit(1);

				}else if(childPid == 0){
					// Code only executed by the child
					//change the handler of the interrup signal
					signal(SIGINT, SIG_DFL);

					if(execvp(*(tmpJob->cmd), tmpJob->cmd)){
						printf("shell function failed!\n");
						error=1;
					}else{

						printf("shell function executed!\n");
						error=0;
					}
					exit(error);
				}else{
					// Code only executed by parent process
					printf("parent waiting on child\n");
					// TODO
					dup2(stdinCopy, STDIN_FILENO);
					dup2(stdoutCopy, STDOUT_FILENO);

					waitpid( childPid, &error, 0 );
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
 * SOLVED (verifiy anyway: >test.txt;status should create test.txt and print status 0)
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
	job *currentJob, *jobs;
	int pip[2];
	/* parsingCommand=1 when parsing a shell command,
	 * parsingCommand=0 when parsing a redirection.*/
	int parsingCommand;

	/* inputRedirection=1 when parsing an input redirection "<"
	 * inputRedireciton=0 when parsing an output redirection ">"
	 * inputRedirection=unspecified when parsing a command*/
	int inputRedirection;

	p = line;

	harg = args;
	narg = args;
	*narg = NULL;

	/*initialises new job list*/
	currentJob = newJob();

	jobs = currentJob;

	/*"remebers" if parse a redirection or a command*/
	parsingCommand=1;
	inputRedirection = 0;

	for (; *p != 0; p != line && p++) {
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

		switch (ch) {
		case ' ':
		case '\t': break;
		case '>':
			printf("Ah, we have redirection!\n");
			storeParsed(&currentJob, parsingCommand, inputRedirection, harg);
			parsingCommand = 0;
			inputRedirection = 0;
			harg=narg;

			/*
			 * RUN_COMMAND() and store ouput in a file;
			 */

			break;
		case ';':

			printf("End of command, running instruction\n");
			storeParsed(&currentJob, parsingCommand, inputRedirection, harg);
			currentJob = currentJob->next;
			parsingCommand = 1;
			harg = narg;
			/*RUN_COMMAND()*/
			break;
		case '&':
			p++;
			ch2 = *p;
			switch (ch2) {
				case '&':
					printf("&& instruction. If run first fail, don't run second and return fail.\n");
					storeParsed(&currentJob, parsingCommand, inputRedirection, harg);
					currentJob->condition = AND;
					currentJob = currentJob->next;
					parsingCommand = 1;
					harg = narg;
					/*
					 * if (RUN_COMMAND(first)) {
					 * 		RUN_COMMAND(second);
					 * } else {
					 *		Not run next command and return an error;
					 * }
					 */
					break;
				default:
					printf("running instruction in background\n");
					storeParsed(&currentJob, parsingCommand, inputRedirection, harg);
					currentJob->background = 1;
					parsingCommand = 1;
					harg = narg;
					/*
					 * RUN_COMMAND() in subshell
					 */
					break;
			}
			break;
		case '|' :
			p++;
			ch2 = *p;
			switch (ch2) {
				case '|':
					printf("|| instruction. if run first succeed, don't run second and return success.\n");
					storeParsed(&currentJob, parsingCommand, inputRedirection, harg);
					currentJob->condition = OR;
					harg = narg;
					/*
					 * if (RUN_COMMAND(first)) {
					 * 		don't run next command and return success;
					 * } else {
					 *		RUN_COMMAND(second);
					 */
					break;
				default:
					printf("Pipe between first and second\n");
					// DONE check in other case if creating a valid empty job
					// storeparsed set valid to 0 if the stored cmd is empty
					storeParsed(&currentJob, parsingCommand, inputRedirection, harg);
					if (pipe(pip) != 0) {
						fprintf(stderr, "pipe error, commands will be executed independently.\n");
						currentJob = currentJob->next;
					} else {
						currentJob->out = pip[1];
						currentJob->next = newJob();
						currentJob = currentJob->next;
						currentJob->in = pip[0];
					}
					parsingCommand = 1;
					harg = narg;
					/*
					 * RUN_COMMAND(first);
					 * RUN_COMMAND(second with output from first);
					 */



					break;
			}
			break;
		case '<':
			printf("Using a file as input for command\n");
			storeParsed(&currentJob, parsingCommand, inputRedirection, harg);
			parsingCommand = 0;
			inputRedirection = 1;
			harg = narg;
			/*
			 * RUN_COMMAND(instr with file as input);
			 */
			break;
		case '\n':
			printf("End of line, running command.\n");
			storeParsed(&currentJob, parsingCommand, inputRedirection, harg);
			parsingCommand = 1;
			harg = narg;
			currentJob = currentJob->next;
			/*RUN_COMMAND();*/
			break;
		case '#':
			*(p+1)=0;
			break;
		case 0:
			printf("empty line.\n");
			freeJob(&jobs);
			currentJob = NULL;
			/*empty line?*/
			break;
		default:
			fprintf(stderr, "internal unexpected error, exiting\n");
			exit(1);
			break;
		}
	} // end for

	// launchJobs(jobs)
	jobLauncher(jobs);

	printf("Jobs executed sucessfully\n");
	// shellcmd | | | | shellcmd
}

int
main(void)
{
	/* setting signal handler to the kernel */
	if (signal(SIGINT, SIG_IGN) == SIG_ERR) {
		printf("Error while setting Ctrl-C handler\n");
	}

	stdinCopy = dup(STDIN_FILENO);
	stdoutCopy = dup(STDOUT_FILENO);

	char line[1000];
	char *res;

	for (;;) {
		printCwd();

		res = fgets(line, sizeof(line), stdin);
		if (res == NULL)
			break;

		process(line);
	}

	return (error);
}
