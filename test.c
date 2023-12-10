#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	ft_count_words(const char *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] != c && s[i]) && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

char	**ft_strcpy(char **tab, const char *s, char c)
{
	int	j;
	int	k;
	int	i;

	j = 0;
	k = 0;
	i = 0;
	while (k < ft_count_words(s, c))
	{
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i])
			tab[k][j++] = s[i++];
		tab[k][j] = '\0';
		j = 0;
		k++;
	}
	return (tab);
}

char	**ft_doublefree(char **tab, int k)
{
	int	i;

	i = -1;
	while (++i < k)
		free(tab[i]);
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		k;
	int		i;
	int		j;

	i = 0;
	k = 0;
	if (s == NULL)
		return (NULL);
	tab = malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	while (k < ft_count_words(s, c))
	{
		j = 0;
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i++])
			j++;
		tab[k++] = malloc((j + 1) * sizeof(char));
		if (!tab[k - 1])
			return (ft_doublefree(tab, k));
	}
	tab[k] = NULL;
	return (ft_strcpy(tab, s, c));
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
int ft_strlen_space(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != ' ')
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
	len = ft_strlen(s1) + ft_strlen_space(s2);
	tab = malloc((len + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	while (s1[i])
		tab[j++] = s1[i++];
	i = 0;
	while (s2[i] != ' ')
		tab[j++] = s2[i++];
	tab[j] = '\0';
	return (tab);
}
int main ()
{
	char cmd1[] = "cat";
	printf("%s\n", ft_strjoin(ft_strdup("/usr/bin/"), cmd1));
}
