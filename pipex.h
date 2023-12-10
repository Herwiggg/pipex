/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 22:27:01 by almichel          #+#    #+#             */
/*   Updated: 2023/12/10 00:02:10 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PIPEX_H
# define PIPEX_H

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

typedef struct s_pipes
{
	int	fd1;
	int	fd2;
}	t_pipes;

char	**ft_split(char const *s, char c);
char	**ft_doublefree(char **tab, int k);
char	**ft_strcpy(char **tab, const char *s, char c);
int		ft_count_words(const char *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strlen_space(const char *str);
char	*ft_strdup(const char *s);
int		ft_strlen(const char *str);
void	pipex(t_pipes *pipes, char *cmd1, char *cmd2, char *envp[]);
void	child_process_one(int fd1, char *cmd1, char *envp[], int *end);
void	child_process_two(int fd2, char *cmd2, char *envp[], int *end);
void    ft_putstr_fd(char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
