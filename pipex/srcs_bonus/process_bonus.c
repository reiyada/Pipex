/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:33:22 by ryada             #+#    #+#             */
/*   Updated: 2025/02/26 17:35:57 by ryada            ###   ########.fr       */
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
			perror("Fork failed");
			free(edata.pid);
			exit(EXIT_FAILURE);
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
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

int	ft_wait_children(t_edata edata)
{
	int	i;
	int status;

	i = 0;
	status = 0;
	while (i < edata.num_cmds)
	{
		waitpid(edata.pid[i], &status, 0);
		i++;
	}
	free(edata.pid);
	return (status);
}
