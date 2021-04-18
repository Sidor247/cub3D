/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 20:22:01 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/09 13:59:29 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	str_len(char *str)
{
	size_t	len;

	len = 0;
	while (*(str + len))
		len++;
	return (len);
}

int	create_line(char **line, char *buff)
{
	size_t	i;
	char	*new_line;

	new_line = malloc((str_len(*line) + str_len(buff) + 1) * sizeof(char));
	if (new_line == NULL)
	{
		free(*line);
		return (0);
	}
	i = -1;
	while (*(*line + ++i) != '\0')
		*(new_line + i) = *(*line + i);
	free(*line);
	while (*buff != '\0')
	{
		*(new_line + i) = *buff;
		i++;
		buff++;
	}
	*(new_line + i) = '\0';
	*line = new_line;
	return (1);
}

char	*str_dup(char *str)
{
	size_t	len;
	size_t	i;
	char	*new;

	i = 0;
	len = str_len(str);
	new = malloc((len + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	while (i < len)
	{
		*(new + i) = *(str + i);
		i++;
	}
	*(new + i) = '\0';
	return (new);
}
