/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igorlebedev <igorlebedev@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 10:15:32 by igorlebedev       #+#    #+#             */
/*   Updated: 2021/02/01 00:23:14 by igorlebedev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	none(void *ptr)
{
	ptr++;
}

t_list	*get_list(int fd)
{
	t_list	*lines;
	t_list	*tmp;
	char	*line;
	int		flag;

	lines = NULL;
	while ((flag = get_next_line(fd, &line)) != -1)
	{
		if ((tmp = ft_lstnew(line)))
			ft_lstadd_back(&lines, tmp);
		else
			flag = -1;
		if (flag != 1)
			break;
	}
	if (flag == -1)
	{
		ft_lstclear(&lines, free);
		return (NULL);
	}
	return (lines);
}	

char	**get_map(int fd)
{
	t_list	*lines;
	t_list	*tmp;
	char	**map;
	int		length;
	int		i;

	if (!(lines = get_list(fd)))
		return (NULL);
	length = ft_lstsize(lines);
	if (!(map = malloc((length + 1) * sizeof(char *))))
	{
		ft_lstclear(&lines, free);
		return (NULL);
	}
	i = 0;
	tmp = lines;
	while (i < length)
	{
		map[i] = (char *)(tmp->content);
		i++;
		tmp = tmp->next;
	}
	map[length] = NULL;
	ft_lstclear(&lines, none);
	return (map);
}

char	**parser(char *file)
{
	char	**map;
	int		fd;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (NULL);
	if (!(map = get_map(fd)))
		return (NULL);
	close(fd);
	return (map);
}