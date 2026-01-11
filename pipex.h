/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 18:04:43 by mohamed           #+#    #+#             */
/*   Updated: 2026/01/11 18:22:07 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include "libft/libft.h"
typedef struct s_pid
{
    char    *envp_path;
	char	*path1;
	char	*path2;
	int	pid1;
	int pid2;
	int fd[2];
}	t_pid;

void print_exit(char *message, int exit_value);
char *find_full_path(char *envp[]);
char    *find_command_path(char *path, char *cmd);
void    free_2d(char **str);
void execve_handle(char **cmd_args);
void    first_process(t_pid data, char *infile, char *cmd1,char **envp);
void    second_process(t_pid data, char *outfile ,char *cmd2, char **envp);
void    fork_error(t_pid data);
void second_fork_error(t_pid data);