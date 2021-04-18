/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igorlebedev <igorlebedev@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 20:21:27 by cwhis             #+#    #+#             */
/*   Updated: 2021/01/31 10:47:42 by igorlebedev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# define BUFFER_SIZE 64

size_t			str_len(char *str);
char			*str_dup(char *str);
int				create_line(char **line, char *buff);
int				fill_buff(int fd, char *buff);
char			*find_n(char *buff);
int				tail_funcs(char **line, char **tail);
int				buff_funcs(char *buff, char **line, char **tail);
int				get_next_line(int fd, char **line);

#endif
