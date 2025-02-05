#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

size_t	ft_strlen(const char *s)
{
	size_t	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

/*
** Procura o caractere 'c' na string 's'.
*/
char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

/*
** Concatena as strings 's1' e 's2' em uma nova string.
** Libera 's1' para evitar vazamento de memória.
*/
char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i = 0;
	size_t	j = 0;
	size_t	len1 = ft_strlen(s1);
	size_t	len2 = ft_strlen(s2);
	char	*joined;

	joined = malloc(len1 + len2 + 1);
	if (!joined)
		return (NULL);
	while (s1 && s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
		joined[i++] = s2[j++];
	joined[i] = '\0';
	free(s1);
	return (joined);
}

/*
** Extrai da 'stash' a linha completa (até e incluindo o '\n', se houver).
*/
char	*extract_line_from_stash(char *stash)
{
	size_t	i = 0;
	char	*line;

	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;  /* inclui o '\n' */
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

/*
** Remove da 'stash' a parte que já foi retornada.
** Retorna uma nova string contendo o que sobrou.
*/
char	*clean_stash(char *stash)
{
	size_t	i = 0;
	size_t	j = 0;
	char	*new_stash;
	size_t	stash_len;

	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	i++;  /* pula o '\n' */
	stash_len = ft_strlen(stash);
	new_stash = malloc(stash_len - i + 1);
	if (!new_stash)
		return (NULL);
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}
