/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:32:40 by ryada             #+#    #+#             */
/*   Updated: 2025/02/20 16:59:22 by ryada            ###   ########.fr       */
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


// struct t_fork
// {
//     pid_t *pid;
// }s_fork;

//utils_bonus.c//
void	ft_free_tab(char **tab);
char *ft_getenv(char *key, char **envp);
char *ft_get_path(char *cmd, char **envp);
int ft_check_argv(char **argv);
int ft_open_file(char *filename, int mode);
//int ft_check_cmd(char **argv, char **envp);

//pipex_bonus.c//
void ft_exec(char *cmd, char **envp);
void ft_first_child(char **argv, int *pipe_fd, char **envp, int here_doc);
void ft_middle_child(char *cmd, char **envp, int *prev_pipe, int *new_pipe);
void ft_last_child(int argc, char **argv, char **envp, int *pipe_fd, int here_doc);
void ft_here_doc(char *limiter, int argc);

#endif