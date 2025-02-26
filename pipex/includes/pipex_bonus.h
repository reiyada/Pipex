/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:32:40 by ryada             #+#    #+#             */
/*   Updated: 2025/02/26 17:36:22 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
#define PIPEX_BONUS_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include "../libft/libft.h"
#include "../gnl/get_next_line.h"

//execution data structure
typedef struct s_edata
{
	int here_doc;
	int num_cmds;
    char *current_cmd;
    pid_t *pid;
}	t_edata;

//getenv_bonus.c//
char	*ft_getenv(char *key, char **envp);
char	*ft_check_exec_path(char *dir, char *cmd);
char	*ft_get_path(char *cmd, char **envp);

//pipex_bonus.c//
void ft_exec(char *cmd, char **envp, pid_t *pid);
void	ft_first_child(char **argv, int *pipe_fd, char **envp, t_edata edata);
void	ft_middle_child(int *pipe_fd, char **envp, t_edata edata);
void	ft_last_child(int argc, char **argv, int *pipe_fd, char **envp, t_edata edata);
void	ft_handle_here_doc_child(int *pipe_fd, char *limiter);
void ft_here_doc(int argc, char *limiter);

//process_bonus.c//
void	ft_create_process(int argc, char **argv, int *pipe_fd, char **envp, t_edata edata);
int	ft_wait_children(t_edata edata);

//utils_bonus.c//
void	ft_free_tab(char **tab);
int ft_open_file(char *filename, int mode, pid_t *pid);
void	ft_error_handler(int type, char **cmd_tab, char *cmd_path, pid_t *pid);
void ft_error_exit(char *msg);

#endif