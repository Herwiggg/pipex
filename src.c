/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 22:10:48 by almichel          #+#    #+#             */
/*   Updated: 2023/12/12 00:28:56 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(t_pipes *pipes, char *cmd1, char *cmd2, char **envp, int *error)
{
	int		end[2];
	pid_t	child;

	if (pipe(end) == -1)
		return ((perror("pipe")));
	child = fork();
	if (child == -1)
		return (perror("fork"));
	while (*error == 1)
	{
		if (child == 0 && pipes->fd1 > 0)
		{
			child_process(pipes->fd1, cmd1, envp, end, error);
		}
		else
			parent_process(pipes->fd2, cmd2, envp, end, error);
	}
}

void	child_process(int fd1, char *cmd1, char *envp[], int *end, int *error)
{
	char	**good_path;
	char	*good_line_envp;
	char	*good_cmd;
	int		i;

	i = 0;
	if (dup2(end[1], STDOUT_FILENO) == -1)
	{
		*error = -1;
		return (perror("dup2"));
	}
	if (dup2(fd1, STDIN_FILENO) == -1)
	{
		*error = -1;
		return (perror("dup2"));
	}
	close(end[0]);
	close(fd1);
	while (envp[i])
	{
		if (ft_strncmp("PATH", envp[i], 4) == 0)
		{
			good_line_envp = envp[i];
			break ;
		}
		i++;
	}
	good_path = ft_split(&good_line_envp[5], ':');
	i = -1;
	while (good_path[++i])
	{
		good_cmd = ft_strjoin(good_path[i], cmd1);
		if (execve(good_cmd, ft_split(cmd1, ' '), envp) != -1)
			break ;
		free(good_cmd);
	}
}

void	parent_process(int fd2, char *cmd2, char *envp[], int *end, int *error)
{
	int		status;
	char	**good_path;
	char	*good_line_envp;
	char	*good_cmd;
	int		i;

	i = 0;
	waitpid(-1, &status, 0);
	if (dup2(fd2, STDOUT_FILENO) == -1)
	{
		*error = -1;
		return (perror("dup2"));
	}
	if (dup2(end[0], STDIN_FILENO) == -1)
	{
		*error = -1;
		return (perror("dup2"));
	}
	close(end[1]);
	close(fd2);
	while (envp[i])
	{
		if (ft_strncmp("PATH", envp[i], 4) == 0)
		{
			good_line_envp = envp[i];
			break ;
		}
		i++;
	}
	good_path = ft_split(good_line_envp, ':');
	i = -1;
	while (good_path[++i])
	{
		good_cmd = ft_strjoin(good_path[i], cmd2);
		if (execve(good_cmd, ft_split(cmd2, ' '), envp) != -1)
			break ;
		free(good_cmd);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	int		fd1;
	int		fd2;
	t_pipes	pipes;
	int		error;

	error = 1;
	pipes.fd1 = open(argv[1], O_RDONLY);
	if (pipes.fd1 < 0)
		ft_putstr_fd(": No such file or directory\n", 2, argv[1]);
	pipes.fd2 = open(argv[4], O_WRONLY | O_TRUNC, 0644);
	if (pipes.fd2 < 0)
	{
		pipes.fd2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	pipex(&pipes, argv[2], argv[3], envp, &error);
	close(pipes.fd1);
	close(pipes.fd2);
}
