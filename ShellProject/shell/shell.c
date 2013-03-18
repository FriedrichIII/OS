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
static int inout[2];

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

/* Ctrl-C handler */
void
intHandler(int signalNo)
{
// TODO replace with SIG_IGN
	if (signalNo == SIGINT){
		printf("Ctrl-C recieved, interrupt child process\n");
	}
}

void
jobLauncher(job* jobs)
{
	if (run_builtin()) return;

}

void
storeParsed(job **currentJob, int parsingCommand, int inRedirection, char **parsed )
{
	if (!*currentJob) *currentJob = newJob;

	job *localJob = *currentJob;

	int success = 0;
	if (parsed && parsed[0]) {
		if (parsingCommand) {
			localJob->cmd = parsed;
			success = 1;
		} else if (inRedirection) {
			localJob->in = open(parsed[0], O_RDONLY);
			if (localJob->in < 0) {
				fprintf(stderr, "%s: No such file or directory\n", parsed[0]);
			} else {
				success = 1;
			}
		} else {
			localJob->out = open(parsed[0], O_WRONLY|O_CREAT, 666);
			if (localJob->in < 0) {
				fprintf(stderr, "%s: Unable to open or create\n", parsed[0]);
			} else {
				success = 1;
			}
		}
	}

	localJob->valid &= success;
}

job * newJob(void) {
	job* newJob;
	
	if(!(newJob = malloc(job))) {
		fprintf(stderr, "Memory error, exiting.\n");
		exit(1);
	}
	newJob->condition=NONE;
	newJob->next=NULL;
	newJob->in = STDIN_FILENO;
	newJob->out = STDOUT_FILENO;
	newJob->valid = 1;

	return newJob;
}

job * freeJob(job *oldJob) {
	free(oldJob);
	return NULL;
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

	for (; strchr(" \t;&|><\n", *p) == NULL; p++)
		/* NOTHING */;

	*pp = p;
	return (p != word ? word : NULL);
}

static void
process(char *line)
{
	int ch, ch2;
	char *p, *word;
	char *args[100], **narg;
	job *currentJob, *jobs;
	int pip[2];
	int parsingCommand;
	int inRedirection;

	p = line;

	narg = args;
	*narg = NULL;

	/*initialises new job list*/
	currentJob = NULL;

	jobs = currentJob;

	/*"remebers" if parse a redirection or a command*/
	parsingCommand=1;
	inRedirection = 0;

	for (; *p != 0; p != line && p++) {
		word = parseword(&p);

		ch = *p;
		*p = 0;

		printf("parseword:\nword: '%s'\nend char:'%c'\nline left '%s'\n", word, ch, p + 1);


		if (word != NULL) {
			*narg++ = word;
			*narg = NULL;
		}

		/*
		 * Here you should put your code for processing the commands
		 * Up to this point, pointer word points to the next word,
		 * ch points to the first character after the word
		 * You should process according to what is in the ch.
		 * For example, use switch(). Next example will skip whitespaces
		 * and detect the redirection of the standard output.
		 *

		 * at this point, ch is a character from the string " \t;&|><\n"
		 * p points at the following character of line
		 
		 */
		 
		/* use a command scheduler? -> parse whole line
		 * and then execute all commands rather than executing
		 * commands while parsing.
		 */
		
		switch (ch) {
		case ' ':
		case '\t': break;
		case '>':
			printf("Ah, we have redirection!\n");
			storeParsed(&currentJob, parsingCommand, inRedirection);
			parsingCommand = 0;
			inRedirection = 0;
			/*
			 * RUN_COMMAND() and store ouput in a file;
			 */
			break;
		case ';':

			printf("End of command, running instruction\n");
			storeParsed(&currentJob, parsingCommand, inRedirection);
			currentJob = currentJob->next;
			parsingCommand = 1;
			/*RUN_COMMAND()*/
			break;
		case '&':
			p++;
			ch2 = *p;
			switch (ch2) {
				case '&':
					printf("&& instruction. If run first fail, don't run second and return fail.\n");
					storeParsed(&currentJob, parsingCommand, inRedirection);
					currentJob->condition = AND;
					currentJob = currentJob->next;
					parsingCommand = 1;
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
					storeParsed(&currentJob, parsingCommand, inRedirection);
					currentJob->background = 1;
					parsingCommand = 1;
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
					storeParsed(&currentJob, parsingCommand, inRedirection);
					currentJob->condition = OR;
					/*
					 * if (RUN_COMMAND(first)) {
					 * 		don't run next command and return success;
					 * } else {
					 *		RUN_COMMAND(second);
					 */
					break;
				default:
					printf("Pipe between first and second\n");
					// TODO check in other case if creating a valid empty job
					storeParsed(&currentJob, parsingCommand, inRedirection);
					if (pipe(pip) != 0) {
						fprintf(stderr, "pipe error, commands will be executed independently.\n");
					} else {
						currentJob->out = pip[1];
						currentJob->next = newJob();
						currentJob = currentJob->next;
						currentJob->in = pip[2];
					}
					/*
					 * RUN_COMMAND(first);
					 * RUN_COMMAND(second with output from first);
					 */
					break;
			}
			break;
		case '<':
			printf("Using a file as input for command\n");
			storeParsed(&currentJob, parsingCommand, inRedirection);
			parsingCommand = 0;
			inRedirection = 1;
			/*
			 * RUN_COMMAND(instr with file as input);
			 */
			break;
		case '\n':
			printf("End of line, running command.\n");
			storeParsed(&currentJob, parsingCommand, inRedirection);
			parsingCommand = 1;
			/*RUN_COMMAND();*/
			break;
		default:
			fprintf(stderr, "internal unexpected error, exiting\n");
			exit();
			break;
		}

		/*
		 *
		 * The previous example is broken in many ways, though,
		 * so you should not use it verbatim.
		 *
		 */

		/* add your code here */
		;
	} // end for

	// launchJobs(jobs)
	jobLauncher(jobs);
}

int
main(void)
{
	/* setting signal handler to the kernel */
	if (signal(SIGINT, intHandler) == SIG_ERR) {
		printf("Error while setting Ctrl-C handler\n");
	}


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
