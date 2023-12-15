/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:52:13 by almichel          #+#    #+#             */
/*   Updated: 2023/12/15 03:03:49 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipes	init_struct(char *argv[])
{
	t_pipes pipes;
	
	pipes.cmd1 = argv[2];
	pipes.cmd2 = argv[3];
	return (pipes);
}
int	ft_dup2_one(t_pipes *pipes, int *end)
{
	if (dup2(end[1], STDOUT_FILENO) == -1)
	{
		ft_close_all(pipes, end);
		perror("dup2");
		return (-1);
	}
	if (dup2(pipes->fd1, STDIN_FILENO) == -1)
	{
		ft_close_all(pipes, end);
		perror("dup2");
		return (-1);
	}
	return (1);
}

int	ft_dup2_two(t_pipes *pipes, int *end)
{
	if (dup2(pipes->fd2, STDOUT_FILENO) == -1)
	{
		ft_close_all(pipes, end);
		perror("dup2");
		return (-1);
	}
	if (dup2(end[0], STDIN_FILENO) == -1)
	{
		ft_close_all(pipes, end);
		perror("dup2");
		return (-1);
	}
	return (1);
}
