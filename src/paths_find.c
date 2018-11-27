/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snassour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 22:11:27 by snassour          #+#    #+#             */
/*   Updated: 2018/09/05 22:11:29 by snassour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		get_paths(t_node *end, t_node *st, int depth)
{
	int		i;
	int		ret;
	t_node	*tmp;

	i = 0;
	if (end == st || end == NULL)
		return (end == st ? RPATH : WPATH);
	ret = WPATH;
	while (end != st && end->links[i] && ret == WPATH)
	{
		tmp = end->links[i];
		if (tmp->index == 0)
		{
			tmp->index = depth + 1;
			if ((ret = get_paths(tmp, st, depth + 1)) == WPATH)
				tmp->index = (tmp->status == 0 ? -1 : -2) + 0 * ++i;
			else
				return (1);
		}
		else
			++i;
	}
	return (ret == WPATH ? WPATH : depth);
}

int		save_paths(t_map *map)
{
	t_path	*path;
	int		i;
	int		j;
	t_node	*tmp;

	i = -1;
	j = -1;
	tmp = map->start;
	if (!(path = lemin_createpath(map)))
		return (ERROR);
	while (++j < map->start->nb_links)
	{
		if (tmp->links[j]->index > 0)
			if (add_to_paths(path, ++i, map, j) == ERROR)
			{
				lemin_destroypath(&path);
				return (ERROR);
			}
	}
	i = (map->write == 0 ? 1 : map->fd_write);
	write(i, map->anthill, map->display_len);
	write(i, "\n", 1);
	lemin_playants(map, path);
	lemin_destroypath(&path);
	return (1);
}

int		find_paths(t_map *map)
{
	int		len;
	int		tmp;

	len = map->nb_nde;
	tmp = 0;
	map->end->index = -2;
	map->start->index = 0;
	while ((tmp = get_paths(map->end, map->start, 0)) > 0)
	{
		map->start->index = 0;
		len = tmp < len ? tmp : len;
	}
	tmp = -1;
	map->start->index = 0;
	while (++tmp < map->start->nb_links)
	{
		if (map->start->links[tmp]->index == 0 \
			&& map->start->links[tmp] != map->end)
			map->start->links[tmp]->index = -1;
		else if (map->start->links[tmp]->index >= map->start->index)
			map->start->index = map->start->links[tmp]->index + 1;
	}
	return (tmp);
}

t_path	*lemin_createpath(t_map *map)
{
	t_path	*path;
	int		i;
	int		j;

	if (!(path = (t_path *)ft_memalloc(sizeof(t_path))))
		return (NULL);
	j = -1;
	i = 0;
	while (++j < map->start->nb_links)
		if (map->start->links[j]->index > 0)
			++i;
	path->tab = (t_node ***)ft_memalloc(sizeof(t_node) * (i + 1));
	path->paths_len = (int *)ft_memalloc(sizeof(int) * (i + 1));
	if (!path->tab || !path->paths_len)
	{
		!path->tab ? NULL : ft_memdel((void **)&(path->tab));
		!path->paths_len ? NULL : ft_memdel((void **)&(path->paths_len));
		ft_memdel((void **)&path);
		return (NULL);
	}
	path->tab[i] = NULL;
	path->nb_paths = i;
	path->dependant_paths_index = 0;
	return (path);
}

void	lemin_destroypath(t_path **path)
{
	int	i;

	i = -1;
	if (path)
		if (*path)
		{
			if ((*path)->tab)
			{
				while (++i < (*path)->nb_paths)
					lemin_tabnddel(&((*path)->tab[i]));
				ft_memdel((void **)&(*path)->tab);
			}
			if ((*path)->paths_len)
				ft_memdel((void **)&((*path)->paths_len));
			if ((*path)->dependant_paths_index)
				ft_memdel((void **)&((*path)->dependant_paths_index));
			ft_memdel((void **)path);
		}
}
