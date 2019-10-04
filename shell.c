#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LINE_LEN 1024
#define MAX_COMMAND_LINE_ARGS 128

char prompt[] = "shell > ";
char delimiters[] = " \t\r\n";
char **environ;

int main(){
// Stores the string typed into the command line.
char command_line[MAX_COMMAND_LINE_LEN];
// Stores the tokenized command line input.
char *arguments[MAX_COMMAND_LINE_ARGS];
//parent ID variable
pid_t pid;

while (true){
// Print the shell prompt.	
  printf("%s", prompt);
  fflush(stdout);	
// Read input from stdin and store it in command_line. If there's an
// error, exit immediately. (If you want to learn more about this line,
// you can Google "man fgets")
  if ((fgets(command_line, MAX_COMMAND_LINE_LEN, stdin) == NULL) && ferror(stdin)){
  fprintf(stderr, "fgets error");	
  exit(0);
}

// If the user input was EOF (ctrl+d), exit the shell.
if (feof(stdin)){
  printf("\n");
  fflush(stdout);
  fflush(stderr);
  return 0;	
}
  
// TODO:	
// 1. Tokenize the command line input (split it on whitespace)
int i = 0;    
char *tmpStr = strtok(command_line, delimiters);     
while (tmpStr != NULL){      
  arguments[i++] = tmpStr;
  tmpStr = strtok(NULL, delimiters);      
}

// 2. Create a child process which will execute the command line input	
pid = fork();
if (pid < 0) {		
  fprintf(stderr, "Fork Failed\n");		
  exit(-1);	
} 

else if (pid == 0) {
  printf("This is the child %d\n", pid);
	execve(arguments[0], arguments, environ);	
}
		
// 3. The parent process should wait for the child to complete	
else {
  printf("This is the parent %d\n", pid);
	wait(NULL);			
  printf("Child Complete\n");
	exit(0);
}
	
}
  
// This should never be reached.
return -1;
}
