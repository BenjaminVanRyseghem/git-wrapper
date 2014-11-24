#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	char *envp[] = {
		"LOGNAME=benjamin",
		"HOME=/Users/benjamin",
		"USER=benjamin"
	};
	
	execve("/usr/local/bin/git", &argv[0], envp);
	perror("execve of git failed");
	exit(1);
}