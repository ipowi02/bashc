#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
int main() {
     char *token = getenv("DISCORD_TOKEN");
     if (!token) {
	  fprintf(stderr, "DISCORD_TOKEN not set\n");
	  return 1;
     }
     int tokcap = snprintf(NULL, 0, "TOKEN=%s", token) + 1;
     char token_env[tokcap];
     snprintf(token_env, sizeof(token_env), "TOKEN=%s", token);
     char *envp[] = {
	  "ASSUME_NO_MOVING_GC_UNSAFE_RISK_IT_WITH=go1.24",
	  token_env,
	  NULL
     };

     char *argv[] = {
	  "/home/adam/go/bin/gtkcord3",
	  NULL
     };

     execve("/home/adam/go/bin/gtkcord3", argv, envp);
     perror("execve failed");
     return 1; // execve only returns on failure
}
