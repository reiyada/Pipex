#include "includes/pipex.h"

// int main()
// {
//     int pid = fork();  // Create a new process

//     if (pid != 0)
//         wait(NULL);
//     if (pid > 0) 
//         printf("Parent Process: Child PID = %d, My PID = %d\n", pid, getpid());
//     else if (pid == 0)
//         printf("Child Process: My PID = %d, Parent PID = %d\n", getpid(), getppid());
//     else
//         printf("Fork failed!\n");
    
//     return 0;
// }

// int main()
// {
//     printf("Program will sleep for 10 seconds in Linux.\n");
//     sleep(10);
//     printf("This line will be execused after 10 seconds.\n");
//     return (0);
// }

// int main()
// {
//     int fd[2];
//     char message[100];
//     char buffer[100];
//     int pid;

//     if (pipe(fd) == -1)
//     {
//         perror("pipe failed\n");
//         return (1);
//     }
//     pid = fork();
//     if (pid > 0)
//     {
//         close(fd[0]);
//         printf("[Parent] Enter a message :");
//         scanf(" %99[^\n]", message);
//         write(fd[1], &message, strlen(message) + 1);
//         close(fd[1]);
//     }
//     else if (pid == 0)
//     {
//         close(fd[1]);
//         read (fd[0], buffer, sizeof(buffer));
//         printf ("Child received : %s\n", buffer);
//         close(fd[0]);
//     }
//     else
//     {
//         perror ("fork failed\n");
//         return (1);
//     }
//     return (0);
// }


// int main()
// {
//     pid_t pid1 = fork();
//     if (pid1 == 0)
//     {
//         printf("First child running...\n");
//         sleep(1);
//         return (10);
//     }
//     pid_t pid2 = fork();
//     if (pid2 == 0)
//     {
//         printf("Second child running...\n");
//         sleep(2);
//         return (20);
//     }
//     int status;
//     waitpid(pid1, &status, 0);
//     printf("First child exited with status %d\n", WEXITSTATUS(status));
//     waitpid(pid2, &status, 0);
//     printf("Second child exited with status %d\n", WEXITSTATUS(status));
//     return (0);
// }

// int main()
// {
//     char *args[] = {"/bin/ls", "-l", NULL};
//     execve("/bin/ls", args, NULL);
//     return (0);
// }

// int main()
// {
//     pid_t pid;

//     pid = fork();
//     if (pid == 0)
//     {
//         char *args[] = {"ls", "-l", NULL};
//         execve("/bin/ls", args, NULL);
//     }
//     else
//     {
//         int exit_status;

//         waitpid(pid, &exit_status, 0);
//         printf("Child process finished with %d as its status\n", WEXITSTATUS(exit_status));
//     }
//     return (0);
// }


int main()
{
    char *tab[] = {"hello I am rei", "Hello hehe", "rei", NULL};
    printf("%s\n", tab[0] + 6);
}
