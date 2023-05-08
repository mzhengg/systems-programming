#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char ** argv)
{
    pid_t child1_pid;
    pid_t child2_pid;
    int exitStatus;

    // at least, there should be 3 arguments
    // 2 for the first command, and the rest for the second command
    if (argc < 4) {
        fprintf(stderr, "Usage: %s cmd1 cmd1_arg cmd2 [cmd2_args ..]\n", argv[0]);
        return 1;
    }

    // fork first child
    child1_pid = fork();

    if (child1_pid < 0) { // exit if fork() fails
        perror("fork()");
        exit(1);
    } else if (child1_pid == 0) { // is a child process
        execlp(argv[1], argv[1], argv[2], NULL);
        // if anything is returned, there is an error; otherwise, it STOPS here!
        perror("execlp()");
        exit(1);
    }

    // fork second child
    child2_pid = fork();

    if (child2_pid < 0) { // exit if fork() fails
        perror("fork()");
        exit(1);
    } else if (child2_pid == 0) { // is a child process
        execvp(argv[3], &argv[3]);
        // if anything is returned, there is an error; otherwise, it STOPS here!
        perror("execvp()");
        exit(1);
    }

    // back in the parent process

    // wait for child1 process to terminate
    waitpid(child1_pid, &exitStatus, 0);
    if (WIFEXITED(exitStatus)) {
        printf("exited=%d exitstatus=%d\n", WIFEXITED(exitStatus), WEXITSTATUS(exitStatus));
    }

    // wait for child2 process to terminate
    waitpid(child2_pid, &exitStatus, 0);
    if (WIFEXITED(exitStatus)) {
        printf("exited=%d exitstatus=%d\n", WIFEXITED(exitStatus), WEXITSTATUS(exitStatus));
    }
    
    return 0;
}