/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 14:09:47 by mohamed           #+#    #+#             */
/*   Updated: 2026/01/10 16:12:03 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void print_exit(char *message, int exit_value)
{
    ft_printf("%s\n",message);
    exit(exit_value);
}
void execve_handle(char *path , char **cmd_args)
{
    ft_printf("execve error\n");
    free_2d(cmd_args);
    free(path);
    exit(1);
}