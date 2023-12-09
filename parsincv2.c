/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsincv2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:38:06 by almichel          #+#    #+#             */
/*   Updated: 2023/12/09 17:50:20 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int ft_strlen_space(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != ' ' && str[i])
		i++;
	return (i);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*s2;
	int		size;

	i = 0;
	size = ft_strlen(s);
	s2 = malloc((size + 1) * sizeof(char));
	if (!s2)
		return (NULL);
	while (s[i])
	{
		s2[i] = s[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tab;
	int		len;
	int		i;
	int		j;

	j = 0;
	i = 5;
	len = ft_strlen(s1) + ft_strlen_space(s2) + 1 - 5;
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
