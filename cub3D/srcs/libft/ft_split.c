/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 22:39:02 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/09 14:38:10 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	word_len(char const *s, char c)
{
	size_t		i;

	i = 0;
	while (*(s + i) != c && *(s + i))
		i++;
	return (i);
}

static	size_t	words_count(char const *s, char c)
{
	size_t		i;
	size_t		k;

	i = -1;
	k = 0;
	while (*(s + ++i))
	{
		if (*(s + i) != c)
		{
			k++;
			while (*(s + i) != c && *(s + i))
				i++;
			i--;
		}
	}
	return (k);
}

static	char	*alloc_or_free(char **tmp, size_t i, size_t lnt)
{
	*(tmp + i) = malloc(sizeof(char *) * (lnt + 1));
	if (!*(tmp))
	{
		while ((int)i != -1)
			free(*(tmp + i--));
		free(tmp);
		return (NULL);
	}
	return (*(tmp + i));
}

static	char	*copy_word(char *s, const char *str, size_t ln)
{
	size_t		j;

	j = -1;
	while (++j < ln)
		*(s + j) = *(str + j);
	*(s + j) = '\0';
	return (s);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	p;
	size_t	wcount;
	char	**tmp;

	if (!s)
		return (NULL);
	wcount = words_count(s, c);
	tmp = malloc(sizeof(char *) * (wcount + 1));
	if (tmp)
		return (NULL);
	i = -1;
	p = 0;
	while (++i < wcount)
	{
		while (*(s + p) == c)
			p++;
		*(tmp + i) = alloc_or_free(tmp, i, word_len(s + p, c));
		if (*(tmp + i) == NULL)
			return (NULL);
		*(tmp + i) = copy_word(*(tmp + i), s + p, (word_len(s + p, c)));
		p += word_len(s + p, c);
	}
	*(tmp + i) = NULL;
	return (tmp);
}
