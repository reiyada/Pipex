/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:33:22 by ryada             #+#    #+#             */
/*   Updated: 2025/02/27 16:15:02 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_create_process(int argc, char **argv, int *pipe_fd, char **envp, t_edata edata)
{
	int	i;

	i = 0;
	while (i < edata.num_cmds)
	{
		edata.current_cmd = argv[i + 2];
		edata.pid[i] = fork();
		if (edata.pid[i] == -1)
		{
			free(edata.pid);
			ft_error_exit("[Error] Fork faild!\n");
		}
		if (edata.pid[i] == 0)  // Child process
		{
			if (i == 0)
				ft_first_child(argv, pipe_fd, envp, edata);
			else if (i == edata.num_cmds - 1)
				ft_last_child(argc, argv, pipe_fd, envp, edata);
			else
				ft_middle_child(pipe_fd, envp, edata);
		}
		i++;
	}
	close(pipe_fd[0]);//parent closes these pipes
	close(pipe_fd[1]);//because we no longer need the pipe after all forks
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

