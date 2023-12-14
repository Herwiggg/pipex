/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:52:13 by almichel          #+#    #+#             */
/*   Updated: 2023/12/15 00:20:32 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putstr_fd(char *s, int fd, char *str)
{
	int		total;
	char	*error;

	error = ft_strjoin_error(str, s);
	total = ft_strlen(error);
	write(fd, error, total);
	free(error);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}
void	ft_close_all(t_pipes *pipes, int *end)
{
	close(pipes->fd1);
	close(pipes->fd2);
	close(end[0]);
	close(end[1]);
}
void 	ft_putstr_error(char *str)
{
	int total;

	total = ft_strlen(str);
	write(2, str, total);
}
