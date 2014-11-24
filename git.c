#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>

int main(int argc, char** argv)
{
	int des_p[2];
	if(pipe(des_p) == -1) {
	  perror("Pipe failed");
	  exit(1);
	}

	if(fork() == 0)		   //first fork
	{
		close(1);		   //closing stdout
		dup(des_p[1]);	   //replacing stdout with pipe write 
		close(des_p[0]);   //closing pipe read
		close(des_p[1]);
		char *envp[] = {
			"LOGNAME=benjamin",
			"HOME=/Users/benjamin",
			"USER=benjamin"
		};
		
		execve("/usr/local/bin/git", &argv[0], envp);
		perror("execve of git failed");
		exit(1);
	}

	if(fork() == 0)		   //creating 2nd child
	{
		close(0);		   //closing stdin
		dup(des_p[0]);	   //replacing stdin with pipe read
		close(des_p[1]);   //closing pipe write
		close(des_p[0]);

		char* const prog2[] = { "cat", 0};
		execvp(prog2[0], prog2);
		perror("execvp of cat failed");
		exit(1);
	}

	close(des_p[0]);
	close(des_p[1]);
	wait(0);
	wait(0);
	return 0;
}