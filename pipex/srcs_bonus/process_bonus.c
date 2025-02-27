/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rei <rei@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:33:22 by ryada             #+#    #+#             */
/*   Updated: 2025/02/27 23:05:49 by rei              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

// void	ft_create_process(int argc, char **argv, int *pipe_fd, char **envp, t_edata edata)
// {
// 	int	i;

// 	i = 0;
// 	while (i < edata.num_cmds)
// 	{
// 		edata.current_cmd = argv[i + 2];
// 		edata.pid[i] = fork();
// 		if (edata.pid[i] == -1)
// 		{
// 			free(edata.pid);
// 			ft_error_exit("[Error] Fork faild!\n");
// 		}
		
// 		if (edata.pid[i] == 0)  // Child process
// 		{
// 			if (i == 0)
// 			{
// 				ft_first_child(argv, pipe_fd, envp, edata);
// 				close(pipe_fd[1]);
// 			}
				
// 			else if (i == edata.num_cmds - 1)
// 				ft_last_child(argc, argv, pipe_fd, envp, edata);
// 			else
// 			{
// 				ft_middle_child(pipe_fd, envp, edata);
// 				close(pipe_fd[1]);
// 			}
				
// 			// close(pipe_fd[0]);
// 			// close(pipe_fd[1]);
// 		}
// 		i++;
// 	}
// 	close(pipe_fd[0]);//parent closes these pipes
// 	close(pipe_fd[1]);//because we no longer need the pipe after all forks
// }


///will make this  function shorter by using a structure!!!!!!

void	ft_create_process(int argc, char **argv, char **envp, t_edata edata)
{
	int	i;
	int prev_pipe[2] = {-1, -1};
	int next_pipe[2];

	i = 0;
	while (i < edata.num_cmds)
	{
		if (pipe(next_pipe) == -1)
		{
			free(edata.pid);
			ft_error_exit("[Error] Pipe creation failed!\n");
		}
		edata.current_cmd = argv[i + 2];
		edata.pid[i] = fork();
		if (edata.pid[i] == -1)
		{
			free(edata.pid);
			ft_error_exit("[Error] Fork creation failed!\n");
		}
		if (edata.pid[i] == 0)
		{
			if (i == 0)
				ft_first_child(argv, next_pipe, envp, edata);
			else if (i == edata.num_cmds - 1)
				ft_last_child(argc, argv, prev_pipe, envp, edata);
			else
				ft_middle_child(prev_pipe, next_pipe, envp, edata);
			exit(EXIT_SUCCESS);
		}
		if (prev_pipe[0] != -1)
			close(prev_pipe[0]);
		if (prev_pipe[1] != -1)
			close(prev_pipe[1]);
		prev_pipe[0] = next_pipe[0];
		prev_pipe[1] = next_pipe[1];
		i++;
	}
	if (prev_pipe[0] != -1)
		close(prev_pipe[0]);
	if (prev_pipe[1] != -1)
		close(prev_pipe[1]);
}



void	ft_wait_children(t_edata *edata)
{
	int	i;
	int	status;
	int	last_exit = 0; //Store the last exit status

	i = 0;
	while (i < edata->num_cmds)
	{
		waitpid(edata->pid[i], &status, 0);
		if (WIFEXITED(status)) //Ensure the process exited normally
			last_exit = WEXITSTATUS(status);
		i++;
	}
	edata->status = last_exit; //Save the last command's exit status
}

