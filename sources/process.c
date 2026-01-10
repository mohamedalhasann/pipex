/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 14:50:29 by mohamed           #+#    #+#             */
/*   Updated: 2026/01/10 16:29:35 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
char    *path_handle(char *env_path, char **cmd_args)
{
    char    *path;
    
    path = find_command_path(env_path,cmd_args[0]);
    if (!path)
    {
        free_2d(cmd_args);
        print_exit("command not found \n",1);
    }
    return (path);
}
void    first_process(t_pid data, char *infile, char *cmd1,char **envp)
{
    int infile_fd;    
    char    **cmd1_args;

    close(data.fd[0]);
    infile_fd = open(infile, O_CREAT|O_RDONLY);
    if (infile_fd < 0)
        print_exit("failed to open a file",1);
    if(dup2(infile_fd,0)== -1)
        print_exit("dup2 failed\n",1);
    if (close(infile_fd) == -1)
        print_exit ("close failed\n",1);
    if(dup2(data.fd[1],1) == -1)
        print_exit ("dup2 failed\n",1);
    if (close(data.fd[1]) == -1)
        print_exit ("close failed\n",1);
    cmd1_args = ft_split(cmd1, ' ');
    if (!cmd1_args)
        print_exit("malloc failed",1);
    data.path1 = path_handle(data.envp_path,cmd1_args);
    execve(data.path1,cmd1_args,envp);;
    execve_handle(data.path1,cmd1_args);
}

void    second_process(t_pid data, char *outfile ,char *cmd2, char **envp)
{
    int outfile_fd;
    char    **cmd2_args;
    
    close(data.fd[1]);
    outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outfile_fd < 0)
        print_exit("failed to open a file\n",1);
     if(dup2(outfile_fd,1)== -1)
        print_exit("dup2 failed\n",1);
    if (close(outfile_fd) == -1)
        print_exit ("close failed\n",1);
    if(dup2(data.fd[0],0) == -1)
        print_exit ("dup2 failed\n",1);
    if (close(data.fd[0]) == -1)
        print_exit ("close failed\n",1);
    cmd2_args = ft_split(cmd2,' ');
    if (!cmd2_args)
        print_exit("malloc failed\n",1);
    data.path2 = path_handle(data.envp_path,cmd2_args);
    execve(data.path2,cmd2_args,envp);
    execve_handle(data.path2,cmd2_args);
}
