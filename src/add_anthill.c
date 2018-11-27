/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_anthill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snassour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 18:15:42 by snassour          #+#    #+#             */
/*   Updated: 2018/09/05 18:15:44 by snassour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		write_start_equals_end(t_map *map, int fd)
{
	write(fd, map->anthill, map->display_len);
	write(fd, "\n", 1);
	write(fd, "Start equals end, no need to move.\n", 35);
	return (0);
}

void	update_anthill1(int *status, int *comment, t_map *map, char **line)
{
	update_status(*line, map, status, comment);
	status ? add_anthill(map, *line) : 0;
	ft_strdel(line);
}

int		add_anthill(t_map *map, char *line)
{
	char	*s;
	int		i;
	int		len;

	len = ft_strlen(line) > 1000 ? ft_strlen(line) + 1000 : 1000;
	if (map->anthill == NULL
		&& (map->anthill = (char *)ft_memalloc(sizeof(char) * len)))
		map->real_len = len;
	else if (map->anthill == NULL)
		return (ERROR);
	if (map->display_len < map->real_len - 10)
	{
		if (!(s = (char *)ft_memalloc(sizeof(char) * (len + map->real_len))))
			return (ERROR);
		ft_strncpy(s, map->anthill, map->real_len);
		ft_strdel(&(map->anthill));
		map->anthill = s;
		map->real_len += len;
	}
	i = -1;
	while (line[++i])
		map->anthill[i + map->display_len] = line[i];
	map->anthill[i + map->display_len] = '\n';
	map->display_len += (i + 1);
	return (TRUE);
}
