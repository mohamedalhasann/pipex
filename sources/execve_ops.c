/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:28:12 by mohamed           #+#    #+#             */
/*   Updated: 2026/01/10 16:12:10 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char *find_full_path(char *envp[])
{
    int i;

    i = 0;
    while(envp[i])
    {
        if (!ft_strncmp(envp[i],"PATH=",5))
            return (envp[i] + 5);
        i++;
    }
    return (NULL);
}
void    free_2d(char **str)
{
    int i;

    i = 0;
    while(str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}

char    *find_command_path(char *path, char *cmd)
{
    char    **str;
    char    *temp;
    char    *tmp;
    int     i;

    if (ft_strchr(cmd,'/'))
    {
        if (!access(cmd,X_OK))
            return (ft_strdup(cmd));
        else
            return (NULL);
    }
    str = ft_split(path, ':');
    temp = NULL;
    i = 0;
    while (str[i])
    {
        tmp = ft_strjoin(str[i], "/");
        temp = ft_strjoin(tmp, cmd);
        free(tmp);
        if (!access(temp, X_OK))
        {
            free_2d(str);
            return (temp);
        }
        free(temp);
        i++;
    }
    free_2d(str);
    return (NULL);
}


// int main(int argc , char **argv , char **envp)
// {
//     char    *str = find_full_path(envp);
//     str = find_command_path(str,"ls");
//     printf("%s",str);
//     free(str);
// }
