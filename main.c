/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 18:04:25 by mohamed           #+#    #+#             */
/*   Updated: 2026/01/09 18:17:25 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    first_process(int fd[2], char *infile, char *cmd1,char **envp)
{
    int infile_fd;    
    char    *path;
    char    **cmd1_args;

    close(fd[0]);
    infile_fd = open(infile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    dup2(infile_fd,0);
    close(infile_fd);
    dup2(fd[1],1);
    close(fd[1]);
    cmd1_args = ft_split(cmd1, ' ');
    path = find_command_path(find_full_path(envp),cmd1_args[0]);
    execve(path,cmd1_args,envp);
    exit(1);
}

void    second_process(int fd[2], char *outfile ,char *cmd2, char **envp)
{
    int outfile_fd;
    char    *path;
    char    **cmd2_args;
    
    close(fd[1]);
    outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    dup2(outfile_fd,1);
    close(outfile_fd);
    dup2(fd[0],0);
    close(fd[0]);
    cmd2_args = ft_split(cmd2,' ');
    path = find_command_path(find_full_path(envp),cmd2_args[0]);
    execve(path,cmd2_args,envp);
    exit(1);
}

int main(int argc , char **argv,char **envp)
{
    int fd[2];
    int pid1;
    int pid2;
    
    if (argc != 5)
        return (0);
    pipe(fd);
    pid1 = fork();
    if (!pid1)
        first_process(fd,argv[1],argv[2],envp);
    pid2 = fork();
    if(!pid2)    
        second_process(fd,argv[4],argv[3],envp);
    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    return (0);
}