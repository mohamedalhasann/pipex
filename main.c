/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 18:04:25 by mohamed           #+#    #+#             */
/*   Updated: 2026/01/08 15:38:04 by malhassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void    parent_process(int fd[2] ,char *outfile , char *command)
{
    int outfile_fd;
    
    outfile_fd = open(outfile,O_RDONLY );
    
}
void    child_process(int fd[2] ,char *infile , char *command)
{
    int infile_fd;
    char **cmd;

    cmd = {"ls" ,NULL};
    close(fd[0]);
    infile_fd = open(infile,O_RDONLY);
    dup2(infile_fd,0);
    execve(cmd);
}
int main(int argc , char **argv,char **envp)
{
    //./pipex infile command1 command2 outfile
    int fd[2];
    int pid;
    int i = 0;
    while (envp[i])
    {printf("%s\n",envp[i]);i++;}
    // pipe(fd);
    // pid = fork();

    // if (pid < 0)
    //     return (0);
    // if (pid == 0)
    //     child_process(fd,argv[1],argv[2]);
    // else if ( pid > 0)
    //     parent_process(fd,argv[4],argv[3]);
    // return (0);
}