/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 03:44:10 by cwhis             #+#    #+#             */
/*   Updated: 2021/04/17 19:05:23 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	file_to_list(t_list **lines, char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (1);
	*lines = get_list(fd);
	close(fd);
	if (*lines == NULL)
		return (1);
	return (0);
}

t_list	*get_list(int fd)
{
	t_list	*lines;
	t_list	*tmp;
	char	*line;
	int		flag;

	flag = 1;
	lines = NULL;
	while (flag == 1)
	{
		flag = get_next_line(fd, &line);
		if (flag != -1)
		{
			tmp = ft_lstnew(line);
			if (tmp != NULL)
				ft_lstadd_back(&lines, tmp);
			else
				flag = -2;
		}
	}
	if (flag < 0)
		ft_lstclear(&lines, free);
	if (flag == -2)
		free(line);
	return (lines);
}

int	parse_and_trim(t_mlx *mlx, char *line)
{
	char	*trim;
	int		code;

	trim = ft_strtrim(line, " ");
	if (trim == NULL)
		return (0);
	if (*trim == '\0')
		code = 1;
	else
		code = parse_something(mlx, trim);
	free(trim);
	return (code);
}
