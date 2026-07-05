/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 14:09:47 by mohamed           #+#    #+#             */
/*   Updated: 2026/01/11 18:21:55 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void print_exit(char *message, int exit_value) 
{
  ft_putendl_fd(message, 2);
  exit(exit_value);
}
void execve_handle(char **cmd_args) 
{
  perror("execve");
  free_2d(cmd_args);
  exit(1);
}
void fork_error(t_pid data) 
{
  if (data.fd[0] > 0)
    close(data.fd[0]);
  if (data.fd[1] > 0)
    close(data.fd[1]);
  print_exit("fork error", 1);
}

void second_fork_error(t_pid data) 
{
  close(data.fd[0]);
  close(data.fd[1]);
  waitpid(data.pid1, NULL, 0);
  print_exit("fork error", 1);
}
