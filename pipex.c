/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <	almichel@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 22:10:48 by almichel          #+#    #+#             */
/*   Updated: 2024/04/05 19:30:17 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(t_pipes *pipes, char **envp)
{
	int	end[2];

	if (pipe(end) == -1)
		return ((perror("pipe")));
	if (pipes->fd1 > 0)
	{
		pipes->child1 = fork();
		if (pipes->child1 == -1)
			return (perror("fork"));
		if (pipes->child1 == 0)
			if (child_process1(pipes, envp, end) == -1)
				exit(EXIT_FAILURE);
	}
	pipes->child2 = fork();
	if (pipes->child2 == -1)
		return (perror("fork"));
	if (pipes->child2 == 0)
		if (child_process2(pipes, envp, end) == -1)
			exit(EXIT_FAILURE);
	ft_close_all(pipes, end);
	wait(pipes->status);
	wait(pipes->status);
}

int	child_process1(t_pipes *pipes, char *envp[], int *end)
{
	int		i;
	char	**absolut_path;
	char	**cmd1;
	
	cmd1 = ft_split(pipes->cmd1, ' ');
	i = 0;
	if (ft_dup2_one(pipes, end) == -1)
		return (-1);
	close(end[0]);
	close(end[1]);
	close(pipes->fd1);
	absolut_path = ft_split(pipes->cmd1, ' ');
	execve(absolut_path[0], ft_split(pipes->cmd1, ' '), envp);
	while (absolut_path[i])
		i++;
	double_free_tab(absolut_path, i);
	i = 0;
	ft_relative_path1(pipes, envp, i);
	while(cmd1[i] != NULL)
	{
		free(cmd1[i]);
		i++;
	}
	free(cmd1);
	return (-1);
}

int	child_process2(t_pipes *pipes, char *envp[], int *end)
{
	int		i;
	char	**absolut_path;	
	char **cmd2;

	cmd2 = ft_split(pipes->cmd2, ' ');
	i = 0;
	if (ft_dup2_two(pipes, end) == -1)
		return (-1);
	close(end[1]);
	close(end[0]);
	close(pipes->fd2);
	absolut_path = ft_split(pipes->cmd2, ' ');
	execve(absolut_path[0], cmd2, envp);
	while (absolut_path[i])
		i++;
	double_free_tab(absolut_path, i);
	i = 0;
	ft_relative_path2(pipes, envp, i);
	while(cmd2[i] != NULL)
	{
		free(cmd2[i]);
		i++;
	}
	free(cmd2);
	return (-1);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipes	pipes;

	pipes = init_struct(argv);
	if (argc == 5)
	{
		if (access(argv[1], F_OK) != 0)
			ft_putstr_fd(": No such file or directory\n", 2, argv[1]);
		else
		{
			pipes.fd1 = open(argv[1], O_RDONLY);
			if (access(argv[1], R_OK) != 0)
				ft_putstr_fd(": Permission denied\n", 2, argv[1]);
		}
		pipes.fd2 = open(argv[4], O_WRONLY | O_TRUNC, 0644);
		if (access(argv[4], W_OK) == -1 && access(argv[4], F_OK) == 0)
			ft_putstr_fd(": Permission denied\n", 2, argv[4]);
		if (pipes.fd2 < 0)
			pipes.fd2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		pipex(&pipes, envp);
		close(pipes.fd1);
		close(pipes.fd2);
	}
	else
		ft_putstr_errr("Wrong number of args: <file1> <cmd1> <cmd2> <file2>\n");
}
