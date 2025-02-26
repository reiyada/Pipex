/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:33:22 by ryada             #+#    #+#             */
/*   Updated: 2025/02/26 12:03:47 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_create_pipes(int *pipe_fd, int num_cmds)
{
	int	i;

	i = 0;
	while (i < num_cmds - 1)
	{
		if (pipe(pipe_fd + (2 * i)) == -1)//pipe_fd + (2 * i) points the current pipe_fd
			ft_error_exit("[Error] Pipe creation failed!\n");
		i++;
	}
}

// int	ft_create_process(int argc, char **argv, int *pipe_fd, char **envp, int here_doc, pid_t *pid)
// {
// 	int	i;
// 	int	num_cmds;
// 	int status;
	
// 	i = 0;
// 	num_cmds = argc - 3;
// 	if (here_doc)
// 		num_cmds = 2;
// 	while (i < num_cmds)
// 	{
// 		pid[i] = fork();
// 		if (pid[i] == -1)
// 			ft_error_exit("[Error] Fork failed!\n");
// 		if (pid[i] == 0)
// 		{
// 			if (i == 0)
// 				ft_first_child(argv, pipe_fd, envp, here_doc, pid);
// 			else if (i == num_cmds - 1)
// 				ft_last_child(argc, argv, pipe_fd, envp, here_doc, pid);
// 			else
// 				ft_middle_child(argv, pipe_fd, envp, i, num_cmds);
			
// 		}
// 		if (i > 0)
// 			waitpid(pid[i - 1], &status, 0);
// 		i++;
// 	}
// 	return (status);
// }

// void	ft_create_process(int argc, char **argv, int *pipe_fd, char **envp, int here_doc, pid_t *pid)
// {
// 	int	i;
// 	int	num_cmds;
	
// 	i = 0;
// 	num_cmds = argc - 3;
// 	if (here_doc)
// 		num_cmds = 2;
// 	while (i < num_cmds)
// 	{
// 		pid[i] = fork();
// 		if (pid[i] == -1)
// 			ft_error_exit("[Error] Fork failed!\n");
// 		//if (pid[i] == 0)
// 		else if (pid[i] == 0)
// 		{
// 			if (i == 0)
// 				ft_first_child(argv, pipe_fd, envp, here_doc, pid);
// 			else if (i == num_cmds - 1)
// 				ft_last_child(argc, argv, pipe_fd, envp, here_doc, pid);
// 			else
// 				ft_middle_child(argv, pipe_fd, envp, i, num_cmds);
// 		}
// 		if (i > 0 && i < num_cmds - 1)
// 			pid[i + 1] = wait(NULL);
// 		i++;
// 	}
// }

void	ft_create_process(int argc, char **argv, int *pipe_fd, char **envp, int here_doc, pid_t *pid)
{
	int	i;
	int	num_cmds;

	num_cmds = argc - 3;
	if (here_doc)
		num_cmds = 2;
	i = 0;
	while (i < num_cmds)
	{
		pid[i] = fork();
		if (pid[i] == -1)
		{
			perror("Fork failed");
			exit(EXIT_FAILURE);
		}
		if (pid[i] == 0)  // Child process
		{
			//printf("Child process %d created for command: %s\n", getpid(), argv[i + 2]);
			if (i == 0)
				ft_first_child(argv, pipe_fd, envp, here_doc, pid);
			else if (i == num_cmds - 1)
				ft_last_child(argc, argv, pipe_fd, envp, here_doc, pid);
			else
				ft_middle_child(argv, pipe_fd, envp, i, num_cmds);
		}
		i++;
	}
	// Parent closes all pipes
	i = 0;
	while (i < (2 * (num_cmds - 1)))
	{
		close(pipe_fd[i]);
		i++;
	}
	// Parent waits for all children
	i = 0;
	while (i < num_cmds)
	{
		if (i > 0 && i < num_cmds - 1)
			pid[i + 1] = wait(NULL);
		i++;
	}
}






// void	ft_create_process(int argc, char **argv, int *pipe_fd, char **envp, int here_doc, pid_t *pid)
// {
// 	int	i;
// 	int	num_cmds;

// 	i = 0;
// 	num_cmds = argc - 3;
// 	if (here_doc)
// 		num_cmds = 2;

// 	// Fork all processes first
// 	while (i < num_cmds)
// 	{
// 		pid[i] = fork();
// 		if (pid[i] == -1)
// 			ft_error_exit("[Error] Fork failed!\n");
// 		if (pid[i] == 0)  // Child process
// 		{
// 			if (i == 0)
// 				ft_first_child(argv, pipe_fd, envp, here_doc, pid);
// 			else if (i == num_cmds - 1)
// 				ft_last_child(argc, argv, pipe_fd, envp, here_doc, pid);
// 			else
// 				ft_middle_child(argv, pipe_fd, envp, i, num_cmds);
// 		}
// 		i++;
// 	}

// 	// Parent closes all pipes after forking
// 	// i = 0;
// 	// while (i < 2 * (num_cmds - 1))
// 	// {
// 	// 	close(pipe_fd[i]); // Close all pipe file descriptors
// 	// 	i++;
// 	// }

// 	// Parent waits for all child processes to finish
// 	i = 0;
// 	while (i < num_cmds)
// 	{
// 		waitpid(pid[i], NULL, 0);
// 		i++;
// 	}
// }


void	ft_close_pipes(int *pipe_fd, int num_cmds)
{
	int	i;

	i = 0;
	while (i < 2 * (num_cmds - 1))//close all the pipes between each cmds
	{
		close (pipe_fd[i]);
		i++;
	}
	free(pipe_fd);
}

// void	ft_wait_children(pid_t *pid, int num_cmds)
// {
// 	int	i;

// 	i = 0;
// 	while (i < num_cmds)
// 	{
// 		waitpid(pid[i], &status, 0);
// 		i++;
// 	}
// 	free(pid);
// }

int	ft_wait_children(pid_t *pid, int num_cmds)
{
	int	i;
	int status;

	i = 0;
	while (i < num_cmds)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	free(pid);
	return (status);
}

// int ft_wait_children(pid_t *pid, int num_cmds)
// {
//     int i;
//     int status = 0; // Initialize status

//     i = 0;
//     while (i < num_cmds)
//     {
//         if (waitpid(pid[i], &status, 0) == -1)
//             perror("[Error] waitpid failed");

//         // Debugging output to check status values
//         // if (WIFEXITED(status))
//         //     printf("[DEBUG] Child %d exited with status %d\n", pid[i], WEXITSTATUS(status));
//         // else
//         //     printf("[DEBUG] Child %d did not exit normally\n", pid[i]);

//         i++;
//     }
//     free(pid);
//     return status;  // Return properly initialized status
// }
