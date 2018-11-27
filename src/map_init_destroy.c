/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snassour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 18:21:51 by snassour          #+#    #+#             */
/*   Updated: 2018/09/05 18:21:53 by snassour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	lemin_initmap(t_map *map)
{
	ft_bzero(map, sizeof(t_map *));
	map->end_set = NOT_SET;
	map->start_set = NOT_SET;
	map->nb_nde = 1;
	map->tab = NULL;
	map->anthill = NULL;
	if (!(map->begin_list = lemin_initnode("", 0, 0)))
		lemin_delmap(&map);
}

void	lemin_lstnddel(t_node **begin_list)
{
	t_node	*nde;

	if (begin_list)
	{
		while (*begin_list)
		{
			nde = (*begin_list)->next;
			lemin_delnode(begin_list);
			*begin_list = nde;
		}
		*begin_list = NULL;
	}
}

void	lemin_delmap(t_map **map)
{
	if (map)
		if (*map)
		{
			(*map)->begin_list ? lemin_lstnddel(&(*map)->begin_list) : NULL;
			(*map)->tab ? lemin_tabnddel(&(*map)->tab) : NULL;
			ft_strdel(&((*map)->anthill));
			free(*map);
			*map = NULL;
		}
}
