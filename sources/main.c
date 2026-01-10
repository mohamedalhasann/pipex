/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 18:04:25 by mohamed           #+#    #+#             */
/*   Updated: 2026/01/10 22:19:46 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int last_operation(t_pid data)
{
    int status1;
    int status2;
    
    close(data.fd[0]);
    close(data.fd[1]);
    waitpid(data.pid1, &status1, 0);
    waitpid(data.pid2, &status2, 0);
    if (WIFEXITED(status2))
        return (WEXITSTATUS(status2));
    return (1);
}

void    before_fork(int argc , t_pid data, char **argv, char **envp)
{
    if (argc != 5)
        print_exit("wrong input format", 1);
    if (pipe(data.fd) == -1)
        print_exit("pipe error", 1);
    
    data.envp_path = find_full_path(envp);
    if (!data.envp_path)
        print_exit("envp path not found", 1);
    if (!find_command_path(data.envp_path, argv[2]))
        print_exit("command not found", 1);
    if (!find_command_path(data.envp_path, argv[3]))
        print_exit("command not found", 1);
}

int main(int argc, char **argv, char **envp)
{
    t_pid  data;

    before_fork(argc, data, argv, envp);
    data.pid1 = fork();
    if (data.pid1 == -1)
        fork_error(data);
    if (data.pid1 == 0)
        first_process(data, argv[1], argv[2], envp);
    if (data.pid1 > 0)
    {
        data.pid2 = fork();
        if (data.pid2 == -1)
            second_fork_error(data);
        if (data.pid2 == 0)
            second_process(data, argv[4], argv[3], envp);
    }
    return (last_operation(data));
}

