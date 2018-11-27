/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snassour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 19:04:31 by snassour          #+#    #+#             */
/*   Updated: 2018/09/05 19:04:34 by snassour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	add_start_end(t_map *map, t_node *n, int comment)
{
	if (comment == 1 ||
	(map->waiting_for_start == WAITING && map->start_set == NOT_SET))
	{
		map->start_set = SET;
		if (map->start)
			return ;
		map->start = n;
		n->status = START;
		map->waiting_for_start = NOT_WAITING;
	}
	if (comment == 2 ||
	(map->waiting_for_end == WAITING && map->end_set == NOT_SET))
	{
		map->end_set = SET;
		if (map->end)
			return ;
		map->end = n;
		n->status = END;
		map->waiting_for_end = NOT_WAITING;
	}
}

void	lemin_delnode(t_node **node)
{
	if (node)
		if (*node)
		{
			ft_strdel(&(*node)->name);
			lemin_tabnddel(&((*node)->links));
			free(*node);
			(*node) = NULL;
		}
}

t_node	*lemin_initnode(char *name, int x, int y)
{
	t_node *ret;

	ret = NULL;
	if (!(ret = (t_node *)ft_memalloc(sizeof(t_node))))
		return (NULL);
	ret->x = x;
	ret->y = y;
	ret->changed = -1;
	ret->name = NULL;
	if (!(ret->name = ft_strdup(name)))
		lemin_delnode(&ret);
	return (ret);
}

t_node	*lemin_createnode(char *name, int x, int y, t_node *lst)
{
	t_node	*ret;

	ret = NULL;
	while (lst && lst->next && ft_strcmp(lst->name, name)
		&& !(x == lst->x && y == lst->y))
		lst = lst->next;
	if (lst->changed == -1
	|| (!ft_strcmp(lst->name, name) && (lst->x == x && lst->y == y)))
	{
		lemin_modify(lst, name, x, y);
		return (lst);
	}
	if (!ft_strcmp(lst->name, name) || (lst->x == x && lst->y == y))
		return (NULL);
	if (!(ret = (t_node *)ft_memalloc(sizeof(t_node))))
		return (NULL);
	ret->x = x;
	ret->y = y;
	if (!(ret->name = ft_strdup(name)))
		lemin_delnode(&ret);
	return (ret);
}

int		add_room(char *line, t_map *map, int comm)
{
	t_node	*n;
	char	**s;
	t_node	*tmp;

	if (!(s = ft_strsplit(line, ' ')))
		return (FALSE);
	if (!(s[0]))
	{
		free(s);
		return (FALSE);
	}
	tmp = map->begin_list;
	n = lemin_createnode(s[0], ft_atoi(s[1]), ft_atoi(s[2]), tmp);
	if (n && n->changed == 0)
	{
		tmp = map->begin_list;
		while (map->begin_list->next)
			map->begin_list = map->begin_list->next;
		map->begin_list->next = n;
		map->begin_list = tmp;
		map->nb_nde += 1;
	}
	n ? add_start_end(map, n, comm) : NULL;
	ft_tabstrdel(&s, 3);
	return (n ? 1 : FALSE);
}
