#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

int ft_strlen_space(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != ' ')
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
	while (s2[i] && s2[i] != ' ')
		tab[j++] = s2[i++];
	tab[j] = '\0';
	return (tab);
}


void	child_process(int fd1, char *cmd1, char *envp[])
{
	char	**good_path;
	char	*good_line_envp;
	char	*good_cmd;
	int		i;

	i = 0;
	while (1)
	{
		if (ft_strncmp("PATH", envp[i], 4) ==  0)
			
		{
			good_line_envp = envp[i];
			break;
		}
		i++;
	}
	printf("good_line du envp : %s\n", good_line_envp);
	good_path = ft_split(good_line_envp, ':');
	i = -1;
	while (good_path[++i])
	{
		good_cmd = ft_strjoin(good_path[i], cmd1);
		if (execve(good_cmd, ft_split(cmd1, ' '), envp) != -1)
			break ;
		//perror("execve");
		free(good_cmd);
	}
	printf("good_cmd = %s\n", good_cmd);
}
int main(int argc, char *argv[], char *envp[])
{
	int		fd1;

		fd1 = open(argv[1], O_RDONLY);
	if (fd1 < 0)
		printf("stop");
	child_process(fd1, argv[2], envp);
}
