/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <	almichel@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:52:13 by almichel          #+#    #+#             */
/*   Updated: 2024/04/05 19:21:54 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipes	init_struct(char *argv[])
{
	t_pipes	pipes;

	pipes.cmd1 = argv[2];
	pipes.cmd2 = argv[3];
	pipes.fd1 = -1;
	pipes.fd2 = -1;
	pipes.status = NULL;
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

void	ft_relative_path1(t_pipes *pipes, char **envp, int i)
{
	char **cmd1;

	cmd1 = ft_split(pipes->cmd1, ' ');
	if (envp[0] != NULL)
	{
		while (envp[i])
		{
			if (ft_strncmp("PATH", envp[i], 4) == 0)
				pipes->good_line_envp = envp[i];
			i++;
		}
		if (pipes->good_line_envp != NULL)
		{
			pipes->good_path = ft_split(pipes->good_line_envp, ':');
			i = -1;
			while (pipes->good_path[++i])
			{
				pipes->good_cmd = ft_strjoin(pipes->good_path[i], pipes->cmd1);
				execve(pipes->good_cmd, cmd1, envp);
				free(pipes->good_cmd);
			}
		}
	}
	if (pipes->good_line_envp != NULL)
		double_free_tab(pipes->good_path, i);
	ft_putstr_fd(": command not found\n", 2, pipes->cmd1);
		i = 0;
	while(cmd1[i] != NULL)
	{
		free(cmd1[i]);
		i++;
	}
	free(cmd1);
}

void	ft_relative_path2(t_pipes *pipes, char **envp, int i)
{
	char **cmd2;

	cmd2 = ft_split(pipes->cmd2, ' ');
	if (envp[0] != NULL)
	{
		while (envp[i])
		{
			if (ft_strncmp("PATH", envp[i], 4) == 0)
				pipes->good_line_envp = envp[i];
			i++;
		}
		if (pipes->good_line_envp != NULL)
		{
			pipes->good_path = ft_split(pipes->good_line_envp, ':');
			i = -1;
			while (pipes->good_path[++i])
			{
				pipes->good_cmd = ft_strjoin(pipes->good_path[i], pipes->cmd2);
				execve(pipes->good_cmd, cmd2, envp);
				free(pipes->good_cmd);
			}
		}
	}
	if (pipes->good_line_envp != NULL)
		double_free_tab(pipes->good_path, i);
	ft_putstr_fd(": command not found\n", 2, pipes->cmd2);
	i = 0;
	while(cmd2[i] != NULL)
	{
		free(cmd2[i]);
		i++;
	}
	free(cmd2);
}
