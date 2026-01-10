/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 18:04:25 by mohamed           #+#    #+#             */
/*   Updated: 2026/01/10 16:13:03 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"


int main(int argc , char **argv,char **envp)
{
    t_pid data;
    
    if (argc != 5)
        print_exit("wrong input format\n",1);
    if(pipe(data.fd) == -1)
        print_exit("pipe error\n",1);
    data.envp_path = find_full_path(envp);
    data.pid1 = fork();
    if (data.pid1 == -1)
        print_exit ("fork error \n",1);
    else if (data.pid1 == 0)
        first_process(data,argv[1],argv[2],envp);
    data.pid2 = fork();
    if (data.pid2 == -1)
        print_exit("fork error \n",1);
    else if(data.pid2 == 0)    
        second_process(data,argv[4],argv[3],envp);
    close(data.fd[0]);
    close(data.fd[1]);
    wait(NULL);
    wait(NULL);
    return (0);
}
