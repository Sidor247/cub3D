/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 20:20:50 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/09 14:15:24 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	fill_buff(int fd, char *buff)
{
	int	read_bytes;

	read_bytes = read(fd, buff, BUFFER_SIZE);
	if (read_bytes != -1)
		buff[read_bytes] = '\0';
	return (read_bytes);
}

char	*find_n(char *buff)
{
	while (*buff != '\0')
	{
		if (*buff == '\n')
			return (buff);
		buff++;
	}
	return (NULL);
}

int	tail_funcs(char **line, char **tail)
{
	char	*n_ptr;
	char	*tmp_tail;
	int		flag;

	flag = 0;
	n_ptr = NULL;
	tmp_tail = NULL;
	n_ptr = find_n(*tail);
	if (n_ptr)
	{
		flag = 1;
		*n_ptr = '\0';
	}
	if (!create_line(line, *tail))
		flag = -1;
	if (flag == 1 && *(++n_ptr))
	{
		tmp_tail = str_dup(n_ptr);
		if (tmp_tail == NULL)
			flag = -1;
	}
	free(*tail);
	*tail = tmp_tail;
	return (flag);
}

int	buff_funcs(char *buff, char **line, char **tail)
{
	char	*n_ptr;

	n_ptr = find_n(buff);
	if (n_ptr)
		*n_ptr = '\0';
	if (!create_line(line, buff))
		return (-1);
	if (n_ptr)
	{
		if (*(++n_ptr))
		{
			*tail = str_dup(n_ptr);
			if (*tail == NULL)
				return (-1);
		}
		return (1);
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char		*tail;
	char			buff[BUFFER_SIZE + 1];
	char			*new_line;
	int				flag;

	flag = 0;
	if (BUFFER_SIZE < 1 || !line || fd < 0)
		return (-1);
	new_line = str_dup("");
	if (new_line == NULL)
		return (-1);
	if (tail)
		flag = tail_funcs(&new_line, &tail);
	while (flag == 0 && fill_buff(fd, buff) > 0)
		flag = buff_funcs(buff, &new_line, &tail);
	if (flag != 1 && fill_buff(fd, buff) == -1)
		flag = -1;
	if (flag == -1)
	{
		*line = NULL;
		free(new_line);
	}
	else
		*line = new_line;
	return (flag);
}
