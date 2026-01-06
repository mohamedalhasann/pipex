/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 18:04:25 by mohamed           #+#    #+#             */
/*   Updated: 2026/01/06 19:02:45 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
void    child_process(int fd[2] ,char *outfile , char *command)
{
    int outfile_fd;
    
    close(fd[0]);
    outfile_fd = open(outfile);
    dup2(outfile,1);
    close (outfile);
    dup2(fd[0],0);
    close(fd[0]);
    execve(command);
}
void    parent_process(int fd[2] ,char *infile , char *command)
{
    int infile_fd;
    
    close (fd[0]);
    infile_fd = open(infile);
    dup2 (infile_fd , 0);
    close (infile_fd);
    dup2 (fd[1],1);
    close (fd[1]);
    execve(command);
}
int main(int argc , char **argv)
{
    //./pipex infile command1 command2 outfile
    int fd[2];
    __pid_t parent;
    
    pipe(fd);
    parent = fork();
    if (parent < 0)
        return (0);
    else if (!parent)
        child_process(fd,argv[1],argv[2]);
    else
        parent_process(fd,argv[4],argv[3]);
    return (0);
}