/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:52:13 by almichel          #+#    #+#             */
/*   Updated: 2023/12/08 15:38:09 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

void    ft_putstr_fd(char *s, int fd)
{
    if (s)
    {
        write(fd, s, ft_strlen(s));
    }
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
