#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

int starts_with(const char *pre, const char *str){
	size_t lenpre = strlen(pre);
	size_t lenstr = strlen(str);
	return lenstr < lenpre ? 0 : strncmp(pre, str, lenpre) == 0;
}

int main(int argc, char** argv, char *envp[])
{
	int i = 0;
	int j = 0;
	char** new_env = malloc (ARG_MAX * sizeof(char*));
	
	while (envp[i] != NULL){
		if (!starts_with("DYLD_FORCE_FLAT_NAMESPACE", envp[i]) && 
			!starts_with("DYLD_INSERT_LIBRARIES", envp[i]) && 
			!starts_with("FAKETIME", envp[i])) {
			new_env[j] = envp[i];
			j++ ;
		}
		i++;
	}
	
	execve("/usr/local/bin/git", &argv[0], new_env);
	perror("execve of git failed");
	exit(1);
}