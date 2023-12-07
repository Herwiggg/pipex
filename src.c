/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 22:10:48 by almichel          #+#    #+#             */
/*   Updated: 2023/12/07 02:20:05 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(int fd1, char *cmd1, char *cmd2, int fd2)
{
	int		end[2];
	pid_t	child;

	if (pipe(end) == -1)
		return ((perror("pipe")));
	child = fork();
	if (child < 0)
		return ((perror("fork")));
	if (child == 0)
		child_process(fd1, cmd1);
	else
		parent_process(fd2, cmd2);
}

void	child_process(int fd1, char *cmd1)
{
}

void	parent_process(int fd1, char *cmd1)
{
}
int	main(int argc, char *argv[], char *env[])
{
	int	fd1;
	int	fd2;

	fd1 = open(argv[1], O_RDONLY);
	if (fd1 < 0)
		ft_putstr("file1: No such file or directory");
	fd2 = open(argv[4], O_RDONLY);
	if (fd2 < 0)
		ft_putstr("file2: No such file or directory");
	pipex(fd1, argv[2], argv[3], fd2);
}
