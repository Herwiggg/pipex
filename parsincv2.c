/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsincv2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <	almichel@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:38:06 by almichel          #+#    #+#             */
/*   Updated: 2023/12/12 16:53:50 by almichel         ###   ########.fr       */
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
