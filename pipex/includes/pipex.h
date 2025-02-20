/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:32:40 by ryada             #+#    #+#             */
/*   Updated: 2025/02/15 12:14:35 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include "../libft/libft.h"

//pipex.c//
void ft_exec(char *cmd, char **envp);
void ft_first_child(char **argv, int *pipe_fd, char **envp);
void ft_second_child(char **argv, int *pipe_fd, char **envp);

//utils.c//
void	ft_free_tab(char **tab);
char *ft_getenv(char *key, char **envp);
char *ft_get_path(char *cmd, char **envp);
int ft_check_argv(char **argv);
//int ft_check_cmd(char **argv, char **envp);

#endif