/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:32:40 by ryada             #+#    #+#             */
/*   Updated: 2025/02/24 17:20:53 by ryada            ###   ########.fr       */
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

//getenv_bonus.c//
char	*ft_getenv(char *key, char **envp);
char	*ft_check_exec_path(char *dir, char *cmd);
char	*ft_get_path(char *cmd, char **envp);

//pipex_bonus.c//
void ft_exec(char *cmd, char **envp);
void ft_first_child(char **argv, int *pipe_fd, char **envp, int here_doc, pid_t *pid);
void ft_middle_child(char **argv, int *pipe_fd, char **envp, int i, int num_cmds);
void ft_last_child(int argc, char **argv, int *pipe_fd, char **envp, int here_doc, pid_t *pid);
void	ft_handle_here_doc_child(int *pipe_fd, char *limiter);
void ft_here_doc(char *limiter);

//process_bonus.c//
void ft_create_pipes(int *pipe_fd, int num_cmds);
void ft_create_process(int argc, char **argv, int *pipe_fd, char **envp, int here_doc, pid_t *pid);
void ft_close_pipes(int *pipe_fd, int num_cmds);
void ft_wait_children(pid_t *pid, int num_cmds);

//utils_bonus.c//
void	ft_free_tab(char **tab);
int ft_open_file(char *filename, int mode, int *pipe_fd, pid_t *pid);
void	ft_error_handler(int type, char **cmd_tab, char *cmd_path);
void ft_error_exit(char *msg);

#endif