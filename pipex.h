/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 22:27:01 by almichel          #+#    #+#             */
/*   Updated: 2023/12/07 00:29:32 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PIPEX_H
# define PIPEX_H

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

char	**ft_split(char const *s, char c);
char	**ft_doublefree(char **tab, int k);
char	**ft_strcpy(char **tab, const char *s, char c);
int		ft_count_words(const char *s, char c);

#endif
