#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main() {
pid_t pid;
int status;
printf("Parent Process: Hello!\n");
 pid = fork();
 if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        printf("Child Process: Hello from the child!\n");
        char *args[] = {"ls", "-l", NULL};
        execvp(args[0], args);
        perror("Exec failed");
        exit(1);
    } else {
        printf("Parent Process: Child process ID is %d\n", pid);
        wait(&status);

        if (WIFEXITED(status)) {
            printf("Parent Process: Child process exited with status %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Parent Process: Child process terminated due to unhandled signal %d\n", WTERMSIG(status));
        }
    }

    printf("Parent Process: END\n");

    return 0;
}
