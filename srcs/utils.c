/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 08:33:43 by ryada             #+#    #+#             */
/*   Updated: 2025/02/13 17:35:05 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_free_tab(char **tab)
{
	size_t	i;

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

    len = ft_strlen(key);
    i = 0;
    while(envp[i])
    {
        if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
        {
            //printf("DEBUG: Found %s = %s\n", key, envp[i] + (len + 1));
            return(envp[i] + (len + 1));// + 1 for '='
        }
            
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
    char *path_part;

    env_path = ft_getenv("PATH", envp);
    if (!env_path)
    {
        //printf ("DEBUG: PAATH variable not found!\n");
        return (NULL);
    }
    //printf("DEBUG: command is %s\n", cmd);
    all_paths = ft_split(env_path, ':');
    i = 0;
    while(all_paths[i])// pass all the dir until we find the good match with the command
    {
        path_part = ft_strjoin(all_paths[i], "/");//add "/" at the end of the path of a dir
        exec = ft_strjoin(path_part, cmd);// add command name to the path
        free(path_part);
        //printf("DEBUG: Checking %s\n", exec);
        if (access(exec, F_OK) == 0)
        {
            //printf("DEBUG: Found candidate %s\n", exec);
            if (access(exec, X_OK) == 0)
            {
                //printf("DEBUG: Found valid executable %s\n", exec);
                ft_free_tab(all_paths);
                return (exec);
            }
        }
        free (exec);
        i++;
    }
    ft_free_tab(all_paths);
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


// int ft_check_cmd(char **argv, char **envp)
// {
//     char **cmd1;
//     char **cmd2;
//     char *path1;
//     char *path2;

//     cmd1 = ft_split(argv[2], ' ');
//     cmd2 = ft_split(argv[3], ' ');
//     path1 = ft_get_path(cmd1[0], envp);
//     path2 = ft_get_path(cmd2[0], envp);
//     ft_free_tab(cmd1);
//     ft_free_tab(cmd2);
//     if (!path1 | !path2)
//         return (0);
//     return (1);
// }
