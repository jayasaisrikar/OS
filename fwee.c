#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    printf("Parent Process: Hello!\n");

    pid = fork(); // Create a child process

    if (pid < 0) {
        // Error occurred while forking
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child Process: Hello from the child!\n");

        // Execute a different program using exec()
        char *args[] = {"ls", "-l", NULL};
        execvp(args[0], args);

        // exec() replaces the current process, so the code below won't be executed unless exec() fails
        perror("Exec failed");
        exit(1);
    } else {
        // Parent process
        printf("Parent Process: Child process ID is %d\n", pid);

        // Wait for the child process to finish
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
