/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 08:33:43 by ryada             #+#    #+#             */
/*   Updated: 2025/02/20 16:49:12 by ryada            ###   ########.fr       */
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

char *ft_getenv(char *key, char **envp)
{
    int i;
    size_t len;

    len = ft_strlen(key);//key can be PATH, USER, SHELL or HOME
    i = 0;
    while(envp[i])// pass all the line to find the key (PATH in our case)
    {
        if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')//if you find the key and the next character is "="
            return(envp[i] + (len + 1));// return the pointer to the first character of the path string (ex) PATH=/home/ryada/bin:/usr/local..... -> we return the pointer to the first "/"
        i++;
    }
    return (NULL);
}

char *ft_get_path(char *cmd, char **envp)
{
    int i;
    char *exec;
    char *env_path;
    char **all_paths;
    char *current_path;

    env_path = ft_getenv("PATH", envp);//reproducing the behavior of "getenv"
    if (!env_path)
        return (NULL);
    all_paths = ft_split(env_path, ':');//(ex)/home/ryada/bin:/usr/local/sbin:/usr/...... -> all_paths[0] = "/home/ryada/bin"
    i = 0;
    while(all_paths[i])// pass all the possible paths until we find the good match with the command
    {
        current_path = ft_strjoin(all_paths[i], "/");//add "/" at the end of the current path
        exec = ft_strjoin(current_path, cmd);// add command name to the current path
        free(current_path);
        if (!access(exec, F_OK) && !access(exec, X_OK))// if the command path exists and is executable
            return (ft_free_tab(all_paths), exec);//return the correct path
        free (exec);
        i++;
    }
    ft_free_tab(all_paths);//free the tab if there is no match
    return (NULL);
}

int ft_check_argv(char **argv)
{
    int i;

    i = 0;
    while (argv[i])
    {
        if (ft_strlen(argv[i]) == 0)
            return (0);
        i++;
    }
    return (1);
}

int ft_open_file(char *filename, int mode)
{
    int fd;

    if (mode == 0)//here_doc(append mode)
        fd = open(filename, O_WRONLY | O_CREAT |O_APPEND, 0644);
    else if (mode == 1)//multiple cmds (NOT OVERWRITE)
        fd = open(filename, O_WRONLY | O_CREAT |O_TRUNC, 0644);
    else
        fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        ft_putstr_fd("[Error] Cannot open file: ", 2);
        ft_putendl_fd(filename, 2);
        exit(1);
    }
    return (fd);
}
