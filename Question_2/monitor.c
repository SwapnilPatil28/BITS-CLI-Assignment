#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void handle_sigchld(int sig) {
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

int main() {
    signal(SIGCHLD, handle_sigchld);

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        printf("Child process (PID: %d) is running...\n", getpid());
        while(1) {
            sleep(1);
        }
    } else {
        printf("Parent (PID: %d) is monitoring child (PID: %d)...\n", getpid(), pid);
        sleep(3);
        
        printf("Parent: Child process is unresponsive. Terminating...\n");
        kill(pid, SIGKILL);
        
        sleep(1); 
        printf("Parent: Cleanup complete. Exiting.\n");
    }
    return 0;
}