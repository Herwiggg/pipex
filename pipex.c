/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 22:10:48 by almichel          #+#    #+#             */
/*   Updated: 2023/12/14 03:52:23 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(t_pipes *pipes, char *cmd1, char *cmd2, char **envp)
{
	int		end[2];
	pid_t	child1;
	pid_t	child2;
	int		status;

	if (pipe(end) == -1)
		return ((perror("pipe")));
	if (pipes->fd1 > 0)
	{
		child1 = fork();
		if (child1 == -1)
			return (perror("fork"));
		if (child1 == 0)
		{
				if (child_process1(pipes->fd1, cmd1, envp, end) == -1)
					exit(EXIT_FAILURE);
		}
	}
	child2 = fork();
	if (child2 == -1)
		return (perror("fork"));
	if (child2 == 0)
	{
		if (child_process2(pipes->fd2, cmd2, envp, end) == -1)
			exit(EXIT_FAILURE);
	}
	close(end[0]);
	close(end[1]);
	wait(&status);
	wait(&status);
}

int	child_process1(int fd1, char *cmd1, char *envp[], int *end)
{
	char	**good_path;
	char	*good_line_envp;
	char	*good_cmd;
	int		i;
	char	**absolut_path;

	i = 0;
	if (dup2(end[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return (-1);
	}
	if (dup2(fd1, STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (-1);
	}
	close(end[0]);
	i = 0;
	absolut_path = ft_split(cmd1, ' ');
	execve(absolut_path[0], ft_split(cmd1, ' '), envp);
	if (envp[0] != NULL)
	{
		while (envp[i])
		{
			if (ft_strncmp("PATH", envp[i], 4) == 0)
			{
				good_line_envp = envp[i];
				break ;
			}
			i++;
		}
		if (good_line_envp != NULL)
		{
			good_path = ft_split(&good_line_envp[5], ':');
			i = -1;
			while (good_path[++i])
			{
				good_cmd = ft_strjoin(good_path[i], cmd1);
				execve(good_cmd, ft_split(cmd1, ' '), envp);
				free(good_cmd);
			}
		}
	}
	if (good_line_envp != NULL)
		double_free_tab(good_path, i);
	ft_putstr_fd(": command not found\n", 2, cmd1);
	return (-1);
}

int	child_process2(int fd2, char *cmd2, char *envp[], int *end)
{
	char	**good_path;
	char	*good_line_envp;
	char	*good_cmd;
	int		i;
	char	**absolut_path;

	i = 0;
	if (dup2(fd2, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return (-1);
	}
	if (dup2(end[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (-1);
	}
	close(end[1]);
	close(fd2);
	absolut_path = ft_split(cmd2, ' ');
	execve(absolut_path[0], ft_split(cmd2, ' '), envp);
	if (envp[0] != NULL)
	{
		while (envp[i])
		{
			if (ft_strncmp("PATH", envp[i], 4) == 0)
			{
				good_line_envp = envp[i];
				break ;
			}
			i++;
		}
		if (good_line_envp != NULL)
		{
			good_path = ft_split(good_line_envp, ':');
			i = -1;
			while (good_path[++i])
			{
				good_cmd = ft_strjoin(good_path[i], cmd2);
				execve(good_cmd, ft_split(cmd2, ' '), envp);
				free(good_cmd);
			}
		}
	}
	if (good_line_envp != NULL)
		double_free_tab(good_path, i);
	ft_putstr_fd(": command not found\n", 2, cmd2);
	return (-1);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipes	pipes;

	if (argc == 5)
	{
		pipes.fd1 = open(argv[1], O_RDONLY);
		if (pipes.fd1 < 0)
			ft_putstr_fd(": No such file or directory\n", 2, argv[1]);
		pipes.fd2 = open(argv[4], O_WRONLY | O_TRUNC, 0777);
		if (pipes.fd2 < 0)
		{
			pipes.fd2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		}
		pipex(&pipes, argv[2], argv[3], envp);
		close(pipes.fd1);
		close(pipes.fd2);
	}
}
