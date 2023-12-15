/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsv2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 02:43:23 by almichel          #+#    #+#             */
/*   Updated: 2023/12/15 15:52:02 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen_space(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != ' ' && str[i])
		i++;
	return (i);
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

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tab;
	int		len;
	int		i;
	int		j;

	j = 0;
	i = 0;
	len = ft_strlen(s1) + ft_strlen_space(s2) + 1;
	tab = malloc((len + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	while (s1[i])
		tab[j++] = s1[i++];
	tab[j++] = '/';
	i = 0;
	while (s2[i] != ' ' && s2[i])
		tab[j++] = s2[i++];
	tab[j] = '\0';
	return (tab);
}
