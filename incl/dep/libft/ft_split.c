/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:16:58 by sjossain          #+#    #+#             */
/*   Updated: 2024/05/27 16:54:41 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static size_t	find_len(const char *s, char c, size_t start)
{
	size_t	len;

	len = 1;
	if (s == (void *)0)
		return (len);
	while (s[start++] != c && s[start] != '\0')
		len++;
	if (s[start] == '\0' && s[start - 1] != c)
		len++;
	return (len);
}

static size_t	count_word(const char *s, char c)
{
	size_t	i;
	size_t	idx;

	i = 0;
	idx = 0;
	if (s[i] != c && s[i] != '\0')
		i++;
	while (s[idx] != '\0')
	{
		if (s[idx] == c && s[idx + 1] != '\0' && s[idx + 1] != c)
			i++;
		idx++;
	}
	return (i);
}

static size_t	find_index(const char *s, char c, size_t set)
{
	size_t	i;
	size_t	check_set;
	size_t	start;

	i = 0;
	start = 0;
	check_set = 0;
	while (s[i] == c)
		i++;
	while (s[i] != '\0')
	{
		if (s[i] != c && check_set == set)
			break ;
		if (s[i] == c && s[i + 1] != c)
			check_set++;
		i++;
	}
	start = i;
	return (start);
}

char	**dest_free(char **dest)
{
	size_t	i;

	i = 0;
	while (dest && dest[i])
	{
		free(dest[i]);
		i++;
	}
	free(dest);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t			i;
	size_t			j;
	size_t			col;
	const size_t	raw = count_word(s, c);
	char			**dest;

	i = 0;
	j = 0;
	col = 0;
	dest = (char **) malloc((raw + 1) * sizeof(char *));
	if (s == NULL || dest == NULL)
		return (NULL);
	while (!(raw == 0 || *s == '\0') && i < raw)
	{
		col = find_len(s, c, find_index(s, c, i));
		dest[i] = (char *) malloc((col) * sizeof(char));
		if (!dest[i])
			return (dest_free(dest));
		while (j++ < col)
			ft_strlcpy(dest[i], &s[find_index(s, c, i)], col);
		dest[i][j] = '\0';
		j = 0;
		i++;
	}
	return (dest[i] = NULL, dest);
}
int	main(void)
{
	size_t i;
 	size_t j;
	size_t k;
 	int m;

 	m = 0;
 	char **str;
 	char *str2 = "&&&&&&&wjhfui&&we&&&g&&&&&&&&&&";
 	char c = '&';
 	str =	ft_split(str2, c);
 	i = count_word(str2, c);
 	j = find_index(str2, c, 0);
 	k = find_len(str2, c, 2);
 	printf("count word: %ld\n", i);
 	printf("word index: %ld\n", j);
 	printf("word len %ld\n", k);
	printf("str ptr: %p\n", str);
 	while (str && str[m])
 	{
 		printf("word: %s\n", str[m]);
 		m++;
 	}
	dest_free(str);
 	return (0);
}
