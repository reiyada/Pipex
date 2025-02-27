/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 08:33:43 by ryada             #+#    #+#             */
/*   Updated: 2025/02/27 15:52:10 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	ft_open_file(char *filename, int mode, pid_t *pid)
{
	int	fd;

	if (mode == 0)//here_doc(append mode)
		fd = open(filename, O_WRONLY | O_CREAT |O_APPEND, 0644);
	else if (mode == 1)//multiple cmds (NOT APPEND)
		fd = open(filename, O_WRONLY | O_CREAT |O_TRUNC, 0644);
	else
		fd = open(filename, O_RDONLY );
	if (fd < 0)
	{
		//printf("DEBUG\n");
		ft_putstr_fd("[Error] Cannot open file: ", 2);
		ft_putendl_fd(filename, 2);
		free(pid);
		exit(1);
	}
	return (fd);
}

void	ft_error_exit(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(1);
}

void	ft_safe_print_error(const char *msg, const char *arg)
{
	write(2, msg, ft_strlen(msg)); // Write the error message to stderr
	if (arg)
	{
		write(2, arg, ft_strlen(arg)); // Write the command name
		write(2, "\n", 1); // Ensure a newline after each message
	}
}

void	ft_error_handler(int type, char **cmd_tab, char *cmd_path, pid_t *pid)
{
	if (type == 1)
		ft_safe_print_error("[Error] Command parsing failed!\n", NULL);
	else if (type == 2)
		ft_safe_print_error("[Error] Command not found! : ", cmd_tab[0]);
	else if (type == 3)
		ft_safe_print_error("[Error] Command execution failed!: ", cmd_tab[0]);

	ft_free_tab(cmd_tab);
	if (cmd_path && cmd_path != cmd_tab[0]) 
		free(cmd_path);
	if (type == 2)
	{
		free(pid);
		exit (127);
	}
	else
	{
		free(pid);
		exit (EXIT_FAILURE);
	}
}

t_edata ft_init_edata(int argc, char **argv)
{
	t_edata edata;

	edata.status = 0;
	edata.current_cmd = NULL;
	edata.pid = NULL;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		edata.here_doc = 1;
		edata.num_cmds = 2;
	}
	else
	{
		edata.here_doc = 0;
		edata.num_cmds = argc -3;
	}
	return (edata);
}
