/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 22:10:48 by almichel          #+#    #+#             */
/*   Updated: 2023/12/11 23:23:44 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(t_pipes *pipes, char *cmd1, char *cmd2, char **envp)
{
	int		end[2];
	pid_t	child;
	
	if (pipe(end) == -1)
		return ((perror("pipe")));
	child = fork();
	if (child == -1)
		return (perror("fork"));
	if (child == 0)
	{
		if (pipes->fd1 > 0)
			child_process(pipes->fd1, cmd1, envp, end);
	}
	else 
		parent_process(pipes->fd2, cmd2, envp, end);
}

void	child_process(int fd1, char *cmd1, char *envp[], int *end)
{
	char	**good_path;
	char	*good_line_envp;
	char	*good_cmd;
	int		i;

	i = 0;

	if (dup2(end[1], STDOUT_FILENO) == -1)
		return(perror("dup2"));
	dup2(fd1, STDIN_FILENO);
	close(end[0]);
	close(fd1);

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
	good_path = ft_split(&good_line_envp[5], ':');
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

void	parent_process(int fd2, char *cmd2, char *envp[], int *end)
{
	int	status;
	char	**good_path;
	char	*good_line_envp;
	char	*good_cmd;
	int		i;
	
	i = 0;
	waitpid(-1, &status, 0);
	dup2(fd2, STDOUT_FILENO);
	dup2(end[0], STDIN_FILENO);
	close(end[1]);
	close(fd2);
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
		ft_putstr_fd(": No such file or directory\n", 2, argv[1]);
	pipes.fd2 = open(argv[4], O_WRONLY | O_TRUNC, 0644);
	if (pipes.fd2 < 0)
		{
			pipes.fd2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}

	pipex(&pipes, argv[2], argv[3], envp);
	close(pipes.fd1);
    close(pipes.fd2);
}
