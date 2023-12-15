/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:38:06 by almichel          #+#    #+#             */
/*   Updated: 2023/12/15 15:51:50 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin_error(char const *s1, char const *s2)
{
	char	*tab;
	int		len;
	int		i;
	int		j;

	j = 0;
	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	tab = malloc((len + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	while (s1[i])
		tab[j++] = s1[i++];
	i = 0;
	while (s2[i])
		tab[j++] = s2[i++];
	tab[j] = '\0';
	return (tab);
}

void	double_free_tab(char **tab, int k)
{
	int	i;

	i = -1;
	while (++i < k)
		free(tab[i]);
	free(tab);
	return ;
}

void	ft_putstr_fd(char *s, int fd, char *str)
{
	int		total;
	char	*error;

	error = ft_strjoin_error(str, s);
	total = ft_strlen(error);
	write(fd, error, total);
	free(error);
}

void	ft_close_all(t_pipes *pipes, int *end)
{
	close(pipes->fd1);
	close(pipes->fd2);
	close(end[0]);
	close(end[1]);
}

void	ft_putstr_errr(char *str)
{
	int	total;

	total = ft_strlen(str);
	write(2, str, total);
}
