/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 08:33:43 by ryada             #+#    #+#             */
/*   Updated: 2025/02/24 14:53:48 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

//It will be easier to understand these function with some knowledge about the environmental path

char	*ft_getenv(char *key, char **envp)
{
	int		i;
	size_t	len;

	len = ft_strlen(key);//key can be PATH, USER, SHELL or HOME
	i = 0;
	while (envp[i])// pass all the line to find the key (PATH in our case)
	{
		if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')//if you find the key and the next character is "="
			return(envp[i] + (len + 1));// return the pointer to the first character of the path string (ex) PATH=/home/ryada/bin:/usr/local..... -> we return the pointer to the first "/"
		i++;
	}
	return (NULL);
}

char	*ft_check_exec_path(char *dir, char *cmd)
{
	char	*path;
	char	*exec;

	path = ft_strjoin(dir, "/");
	exec = ft_strjoin(path, cmd);
	free(path);
	if (!access(exec, F_OK) && !access(exec, X_OK))
		return (exec);
	free(exec);
	return (NULL);
}


char	*ft_get_path(char *cmd, char **envp)
{
	int		i;
	char	*exec;
	char	*env_path;
	char	**all_paths;

	env_path = ft_getenv("PATH", envp);//reproducing the behavior of "getenv"
	if (!env_path)
		return (NULL);
	all_paths = ft_split(env_path, ':');//(ex)/home/ryada/bin:/usr/local/sbin:/usr/...... -> all_paths[0] = "/home/ryada/bin"
	if (!all_paths)
		return (NULL);
	i = 0;
	exec = NULL;
	while (all_paths[i] && !exec)// pass all the possible paths until we find the good match with the command
	{
		exec = ft_check_exec_path(all_paths[i], cmd);
		if (!exec)
			free(exec);
		i++;
	}
	ft_free_tab(all_paths);//free the all path tab
	return (exec);
}
