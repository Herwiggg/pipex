/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 22:27:01 by almichel          #+#    #+#             */
/*   Updated: 2024/04/10 13:56:16 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipes
{
	pid_t	child1;
	pid_t	child2;
	int		fd1;
	int		fd2;
	int		flag1;
	char	*cmd1;
	char	*cmd2;
	char	**splited_cmd1;
	char	**splited_cmd2;
	char	*good_line_envp;
	char	**good_path;
	char	*good_cmd;
	int		*status;
}			t_pipes;

/*-------Parsing-------*/
t_pipes		init_struct(char *argv[]);
char		**ft_split(char const *s, char c);
char		**ft_doublefree(char **tab, int k);
char		**ft_strcpy(char **tab, const char *s, char c);
int			ft_count_words(const char *s, char c);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_strlen_space(const char *str);
int			ft_strlen(const char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_count_height(char **tab);
void		ft_free_cmd(char **cmd);

/*-------Process functions-------*/
void		pipex(t_pipes *pipes, char *envp[]);
int			child_process1(t_pipes *pipes, char *envp[], int *end);
int			child_process2(t_pipes *pipes, char *envp[], int *end);
int			ft_dup2_one(t_pipes *pipes, int *end);
int			ft_dup2_two(t_pipes *pipes, int *end);
void		ft_relative_path1(t_pipes *pipes, char **envp, int i);
void		ft_relative_path2(t_pipes *pipes, char **envp, int i);
void		init_fd1(char **argv, t_pipes *pipes);

/*-------Error handling-------*/
void		ft_putstr_fd(char *s, int fd, char *str);
char		*ft_strjoin_error(char const *s1, char const *s2);
void		double_free_tab(char **tab, int k);
void		ft_putstr_errr(char *str);
void		ft_close_all(t_pipes *pipes, int *end);

#endif
