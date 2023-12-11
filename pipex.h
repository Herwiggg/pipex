/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 22:27:01 by almichel          #+#    #+#             */
/*   Updated: 2023/12/11 18:10:13 by almichel         ###   ########.fr       */
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
int		ft_strlen(const char *str);
void	pipex(t_pipes *pipes, char *cmd1, char *cmd2, char *envp[]);
void	child_process(int fd1, char *cmd1, char *envp[], int *end);
void	parent_process(int fd2, char *cmd2, char *envp[], int *end);
void    ft_putstr_fd(char *s, int fd, char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin_error(char const *s1, char const *s2);
#endif
