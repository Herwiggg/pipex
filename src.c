/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 22:10:48 by almichel          #+#    #+#             */
/*   Updated: 2023/12/10 01:06:02 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(t_pipes *pipes, char *cmd1, char *cmd2, char **envp)
{
	int		end[2];
	pid_t	child1;
	pid_t	child2;
	int 	status;
	
	if (pipe(end) == -1)
		return ((perror("pipe")));
	child1 = fork();
	if (child1 == -1)
		return ((perror("fork")));
	if (child1 == 0)
	{
		child_process_one(pipes->fd1, cmd1, envp, end);
	}
	child2 = fork();
	if (child2 == -1)
		return ((perror("fork")));
	if (child2 == 0)
	{
		child_process_two(pipes->fd2, cmd2, envp, end);
	}
	close(end[0]);
	close(end[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
}

void	child_process_one(int fd1, char *cmd1, char *envp[], int *end)
{
	char	**good_path;
	char	*good_line_envp;
	char	*good_cmd;
	int		i;

	i = 0;
	dup2(end[1], STDOUT_FILENO);
	close(end[0]);
	close(end[1]);
	while (1)
	{
		if (ft_strncmp("PATH", envp[i], 4) ==  0)
			
		{
			good_line_envp = envp[i];
			break;
		}
		i++;
	}
	//printf("good_line du envp : %s\n", good_line_envp);
	good_path = ft_split(good_line_envp, ':');
	int j = -1;
	i = -1;
	while (good_path[++i])
	{
		good_cmd = ft_strjoin(good_path[i], cmd1);		
		if (execve(good_cmd, ft_split(cmd1, ' '), envp) != -1)
			break ;
		free(good_cmd);
	}
}

void	child_process_two(int fd2, char *cmd2, char *envp[], int *end)
{
	int	status;
	char	**good_path;
	char	*good_line_envp;
	char	*good_cmd;
	int		i;
	
	i = 0;
	dup2(end[0], STDIN_FILENO);
	close(end[0]);
	close(end[1]);
	while (1)
	{
		if (ft_strncmp("PATH", envp[i], 4) ==  0)
			
		{
			good_line_envp = envp[i];
			break;
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

	pipes.fd1 = open(argv[1], O_RDONLY);
	if (pipes.fd1 < 0)
		ft_putstr_fd("file1: No such file or directory", 2);
	pipes.fd2 = open(argv[4], O_RDONLY);
	if (pipes.fd2 < 0)
		ft_putstr_fd("file2: No such file or directory", 2);
	pipex(&pipes, argv[2], argv[3], envp);
	close(pipes.fd1);
    close(pipes.fd2);
}
