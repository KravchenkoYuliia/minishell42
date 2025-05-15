#################################
#         readline              #
#################################
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

This is our get_next_line but with leaks and only read from STDIN.

Compile with -lreadline
char *readline (const char *prompt);
Reads a line from the terminal and returns it, using prompt as a prompt. We need to free it at the end.

Example:

	int main()
	{
		char* line = readline("BabyShell: ");
		if (line)
			printf("%s\n", line);
		else
			printf("Fail\n");

	}

################################################################################################
These 3 functions we need to recreate Ctrl-C
Compile with -lreadline -lhistory

	#################################   1
	#           rl_replace_line     #
	#################################
	void rl_replace_line(char* arg1, int arg2);
1 step:
	clean the current line

	#################################  2
	#           rl_on_new_line      #
	#################################
	int rl_on_new_line (void)
2 step:
	Inform readline about new line (jump to the next line)

	#################################  3
	#           rl_rediplay         #
	#################################
	void rl_redisplay (void)
3 step:
	Change whats displayed on the screen to reflect the current contents of rl_line_buffer.



Example:
	while (1)
                {
                        char* line = readline("BabyShell: ");
                        if (line[0] == '\0')
                                break ;
                        while (line[0] == 'C') #this will be Ctr C when Lyes show me how to use signals
                        {
                                rl_replace_line(line, 0);
                                rl_on_new_line();
                                line = readline("BabyShell: ");
                                rl_redisplay();
                                line = readline("BabyShell: ");
                        }
                        add_history(line);
                        printf("%s\n", line);
                        rl_clear_history();
                        free(line);
                }


###############################################################################################

#################################
#           add_history         #
#################################
Save a line in history so user can get at the line later. Avoid to use it for an empty line.

void add_history (const char *string)
Example:
	while (1)
                {
                        char* line = readline("BabyShell: ");
                        if (line[0] == '\0')
                                break ;
                        add_history(line);
                        printf("%s\n", line);
                }
While our program is working we can press ↑ and see previous commands. (if we want to recreate the behaviour of shell command 'history' we can make it manually after using add_history)

#################################
#     rl_clear_history          #
#################################
This function clears the entire command line history.
Has no parameters.

#################################
#        access                 #
#################################
#include <unistd.h>
int access(const char *pathname, int mode)
On success returns 0, error -1.
Access() checks if we can access the file. Useful to check if file exists or has permitions
Example: access("/home/minishell/test.c", F_OK);
F_OK  - mode that tests if file exists
R_OK  - mode that tests if file exists and has read permissions
W_OK  - mode that tests if file exists and has write permissions
X_OK  - mode that tests if file exists and has execute permissions

#################################
#           fork                #
#################################
#include <sys/types.h>
#include <unistd.h>

Creates a child process in our current program. We need it to execute commands in, because every execution exit a program. So we execute it in child program and still have access to the code in parent process.
pid_t fork(void);

Returns pid_t(its the same as int, dont worry) -1 in case of a problem, 0 - in the child process and PID (process id) of a child is return in parent process (can be any number, like 24698)
Example:
	pid_t	i; 
	i = fork(); //creates a child process
	if (i == -1)
		Error
	if (i == 0)
		We are in child process
	We are in parent process

#################################
#           wait                #
#################################
#include <sys/types.h>
#include <sys/wait.h>

pid_t	wait(int status);

wait() is a system call pausing a parent process to wait for the execution of a child process
The child process must be properly exited (with the exit() function) for the parent process to continue its execution
The usage of wait() prevents the creation of zombie processes
//May be used to update the signal in the global variable, still unsure how//

Return values :
	Success = the pid of the terminated child process;
	Fail = -1;

#################################
#           waitpid             #
#################################
#include <sys/types.h>
#include <sys/wait.h>

pid_t waitpid(pid_t pid, int *status, int options);

waitpid() is a system call that have the same uses as wait(); 
the difference being that it takes a pid and a potential option flag
The benefit of having a pid as parameter is the ability to wait for a specific child process to end,
instead of taking the first amongst the child process to finish like the wait() function
With the option flag, it can also wait for another change of state than just the end of the child process

Return values :
	Success = the pid of the child process which changed state;
	Success with WNOHANG option flag = 0 if the child process of which you put the pid in parameter hasnt change state;
	Fail = -1; 
#################################
#           signal              #
#################################
#include <signal.h>

void (*signal(int sig, void (*func)(int)))(int);

Handle asyncronous event (event that happens outside of the program; ex : ctrl-C)
it takes as parameters a type of signal (ex : SIGINT) and a pointer to a function which handle the signal sent in parameter
This function can be custom made by the programmer or taken from a set list of predefined function
It is called signal handler

Return values :
	Success = the previous return value of the signal handler
	Fail = SIG_ERR which must be handled in the signal handler

Exemple :

void sig_handler(int signal)
{
	if (signal == SIGUSR1)
		printf("Success\n");
	else if (signal == SIG_ERR)
		printf("Failure\n");
}
int	main()
{
	signal(SIGUSR1, sig_handler);
	while (1)
		pause;
	return (0);
}

#################################
#           kill                #
#################################
#include <signal.h>

int	kill(pid_t pid, int sig);

This function sends a signal to a running process of which you put the pid as first parameter
kill() must have access rights to the process to successfully send a signal
Pid can be any number above 0 or below -1 (it takes the absolute value) to send to a specific process
If pid is 0, kill() sends a signal to all reachable processes with the same group ID to which it has access rights
If pid is -1, kill() sends a signal to all reachable processes to which it has access rights
kill() can fail if the value of sig doesnt match a valid signal;
if kill() doesnt have access right the process or if nor processes match the pid entered

Return values :
	Success = 0;
	Fail = -1;

#################################
#           getcwd              #
#################################
#include <unistd.h>

char *getcwd(char *buffer, size_t size);

This function stocks in a buffer the abolute path of the current directory
The size parameter needs to be big enough for getcwd() to properly stock the path in the buffer

Return values :
	Success = a char string containing the absolute path to the current directory;
	Fail = NULL;

#################################
#           chdir               #
#################################
#include <unistd.h>

int chdir(const char *path);

This function allows to move to a different directory
It can either take the abolute path to the target directory or the relative path from the current directory to the target directory

Return values : 
	Success = 0;
	Fail = -1

#################################
#           stat                #
#################################
#include <sys/stat.h>

int stat(const char *restrict path, struct stat *restrict buf);

stat() stocks all the information of the targeted file into a stat structure to be used as needed
If the path given lead to a symbolic link, stat() will get the information of the linked file

Return values :
	Success = 0;
	Fail = -1;

#################################
#           lstat               #
#################################
#include <sys/stat.h>

int lstat(const char *restrict path, struct stat *restrict buf);

lstat() functions almost the same as stat(); 
the only difference being, in case of the path leading to a symbolic link, 
lstat() will get the information of the link itself instead of the linked file

Return values :
	Success = 0;
	Fail = -1;

#################################
#           fstat               #
#################################
#include <sys/stat.h>

int fstat(int fildes, struct stat *buf);

fstat() functions almost the same as stat();
the only difference being that it takes a file descriptor as parameters instead of a path to a file

Return values :
	Success = 0;
	Fail = -1;

#################################
#           unlink              #
#################################
#include <unistd.h>

Deletes file

int unlink(const char *path);
Success = 0
Fail = -1
Example:
	unlink("/home/minishell/deleteme.c");

#################################
#           execve              #
#################################
#include <unistd.h>

Fail = -1
Success - just executes command

Example:
	char **args = {"/bin/ls", "-l", NULL};
	
	execve(args[0], args, NULL);
	* Executes "ls" on Terminal, free all mallocs of current process, kill the process*

#################################
#           dup                 #
#################################
#include <unistd.h>
dup  — duplicate an open file descriptor

//I didn't use it in pipex, because dup2 was more useful//

int dup(int fd);
Duplicates fd (for example fd = 3) and returns a new fd (next number that is free, for example new fd will be = 4 which is copy of fd 3)


#################################
#           dup2                #
#################################
#include <unistd.h>
dup2 — same as dup but fd copy is not random, we precise where duplicate

int	dup2(int fd1, int fd2);
Fail = -1
Success = new file descriptor

Example:
	int fd = open("outfile", O_RDWR);
	dup2(fd, STDOUT_FILENO); (stdouta_fileno - macro pour dire au compilateur stdout, terminal)
	
	We duplicated our outfile and put it at the place of STDOUT, so any printf after it will be not at Terminal but in outfile


#################################
#           pipe                #
#################################
#include <unistd.h>
int pipe(int fildes[2]);


Internal file pipe with 2 ends to access it
int pipes[2]; //declaration of 2 ends(2 files)
pipe(pipes); //calling the function pipe
pipe[0] - is used to read from file
pipe[1] - is used to write on file

cmd1 | cmd2

cmd1 is executed, the result is not on terminal, we dont see it because it is written on pipe[1]
cmd2 take the input not from STDIN (from terminal) but from pipe[0] and executes cmd2 on terminal

pipe is used like intermediary between 2 cmd

#################################
#           opendir             #
#################################
#include <sys/types.h>
#include <dirent.h>

  DIR *opendir(const char *name);

Success: return a pointer to the directory stream
Fail: NULL

#################################
#           readdir             #
#################################
 #include <dirent.h>

    struct dirent *readdir(DIR *dirp);

Success: returns a pointer to a dirent structure (no need to free)
Fail: NULL

Example:
	int main()      
	{
        	DIR             *directory = NULL;
	        struct dirent   *dir;

        	directory = opendir("TEST");

	        while((dir = readdir(directory)) != NULL)
        	{
                	printf("%s\n", dir->d_name); #print every file from directory TEST
	        }
	}

#################################
#           closedir            #
#################################
int closedir(DIR *dirp);

DEVINE :)

je sais pas :(

#################################
#           strerror            #
#################################
#include <string.h>

       char *strerror(int errnum);


Parameter 
Success: error message;
Fail: NULL;

#################################
#           perror              #
#################################
#include <stdio.h>

void perror(const char *prefix);

perror() prints on the stderr (the error output, which can be redirected to a file) the current error saved on the errno global variable
The parameter "prefix" can be used to input a custom message to be printed before the error itself
If left empty, no message will appear before the error altought the function will still works normally

#################################
#           isatty              #
#################################
#include <unistd.h>

int isatty(int fildes);

isatty() tests the file descriptor put in parameter to check if it is associated with the terminal
By default fildes == 0(stdin), fildes == 1(stdout) and fildes == 2(stderr) are all associated with the terminal
The function fails if the fildes isnt opened or isnt associated with the terminal

Return values :
	Success = 1;
	Fail = 0;

#################################
#           ttyname             #
#################################
#include <unistd.h>

char *ttyname(int fd);

ttyname() returns the path to the terminal associated with the fd
The fd need to be associated with a terminal or the function will fail (see isatty())

Return values :
	Success = path to the terminal associated with the fd;
	Fail = NULL;

#################################
#           ttyslot             #
#################################
#include <unistd.h>
#include <stdlib.h>

int ttyslot(void);

ttyslot() serve to locate the index of the current users entry in the /etc/utmp file
the function search for terminal associated with the default file descriptors (see isatty())
If none exist the function fails

Return values :
	Success = the index in the /etc/utmp file;
	Fail = 0 or -1 depending on the system;

#################################
#           ioctl               #
#################################
#include <sys/ioctl.h>

int ioctl(int fd, int op, ...);

/!\
//ON HOLD//
//COMPLEX FUNCTION//

#################################
#           getenv              #
#################################
#include <stdlib.h>

char *getenv(const char *varName);

getenv() stocks in a string all the content of the environment variable you put in parameter
If the environment variable doesnt exist, the function fails

Return values :
	Success = a string containing all the content of the environment variable;
	Fail = NULL

####################################################################################################

//All functions below serve for terminal manipulations//
//Its uses are quite complex and not necesseraly mandatory for the minishell projet//
//On hold until proven otherwise//

#################################
#           tcsetattr           #
#################################
#include <termios.h>

int tcsetattr(int fildes, int optional_actions, const struct termios *termios_p);

/!\
/NEEDS DOCUMENTATION/

#################################
#           tcgetattr           #
#################################
#include <termios.h>

int tcgetattr(int fildes, struct termios *termios_p);

/!\
/NEEDS DOCUMENTATION/

#################################
#           tgetent             #
#################################
#include <term.h>

int tgetent(char *bp, const char *name);

/!\
/NEEDS DOCUMENTATION/

#################################
#           tgetflag            #
#################################
#include <term.h>

int tgetflag(char id[2]);

/!\
/NEEDS DOCUMENTATION/

#################################
#           tgetnum             #
#################################
#include <term.h>

int tgetnum(char id[2]);

/!\
/NEEDS DOCUMENTATION/

#################################
#           tgetstr             #
#################################
#include <term.h>

char *tgetstr(char id[2], char **area);

/!\
/NEEDS DOCUMENTATION/

#################################
#           tgoto               #
#################################
#include <term.h>

char *tgoto(char *cap, int col, int row);

/!\
/NEEDS DOCUMENTATION/

#################################
#           tputs               #
#################################
#include <term.h>

int tputs(const char *str, int affcnt, int (*putc)(int));

/!\
/NEEDS DOCUMENTATION/

######################################################################################################