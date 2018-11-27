/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snassour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 20:49:04 by snassour          #+#    #+#             */
/*   Updated: 2018/09/05 20:49:06 by snassour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		add_nb_ants(char *line, t_map *map)
{
	map->nb_ants = ft_atoi(line);
	return (1);
}

void	lemin_finish_ants(t_map *map, int min, t_path *path)
{
	int		i;
	int		j;
	int		fd;

	i = path->paths_len[min];
	j = 0;
	fd = (map->write == 0 ? 1 : map->fd_write);
	while (--i >= 0)
		if (path->tab[min][i]->ant_curr > 0 \
			&& path->tab[min][i]->ant_curr <= map->nb_ants)
		{
			j == 1 ? write(fd, " ", 1) : 0;
			write(fd, "L", 1);
			ft_putnbr_fd(path->tab[min][i]->ant_curr, fd);
			write(fd, "-", 1);
			if (map->color && path->tab[min][i] == map->end)
				write(fd, GREEN, ft_strlen(GREEN));
			ft_putstr_fd(path->tab[min][i]->name, fd);
			if (map->color && path->tab[min][i] == map->end)
				write(fd, RESET, ft_strlen(RESET));
			j = 1;
		}
	j == 1 ? write(fd, "\n", 1) : 0;
}

void	move_ants(int ant, int min, t_path *path)
{
	int		i;

	i = 0;
	while (i < path->paths_len[min] - 1)
	{
		if (path->tab[min][i]->ant_curr == 0)
			break ;
		++i;
	}
	while (i > 0)
	{
		path->tab[min][i]->ant_curr = path->tab[min][i - 1]->ant_curr;
		i--;
	}
	path->tab[min][0]->ant_curr = ant;
}

void	lemin_playants(t_map *m, t_path *path)
{
	int		i;
	int		min;

	min = 0;
	i = -1;
	while (++i < path->nb_paths)
		if (path->paths_len[i] < path->paths_len[min])
			min = i;
	i = 1;
	while (i <= m->nb_ants)
	{
		move_ants(i, min, path);
		lemin_finish_ants(m, min, path);
		++i;
	}
	while (path->tab[min][path->paths_len[min] - 1]->ant_curr < m->nb_ants + 1)
	{
		move_ants(i, min, path);
		lemin_finish_ants(m, min, path);
	}
	move_ants(i, min, path);
	lemin_finish_ants(m, min, path);
	m->path_used == 1 ? lemin_display_path(m, min, path) : NULL;
}
