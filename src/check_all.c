/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snassour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 21:21:21 by snassour          #+#    #+#             */
/*   Updated: 2018/09/05 21:21:23 by snassour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		check_format_nb(char *line)
{
	if (line[0] == '#')
		return (OTHER);
	return ((ft_isnum(line) && ft_atoi(line) > 0) ? 3 : 0);
}

int		check_comment(char *line, t_map *map)
{
	if (line && line[0] == '#')
	{
		if (ft_strcmp(line, "##start") == 0)
		{
			map->waiting_for_start = WAITING;
			return (1);
		}
		if (ft_strcmp(line, "##end") == 0)
		{
			map->waiting_for_end = WAITING;
			return (2);
		}
		else
			return (OTHER);
	}
	return (0);
}

int		check_links(t_node *m, t_node *n)
{
	int		i;
	int		j;
	t_node	*tmp;

	i = 0;
	j = ERROR;
	tmp = NULL;
	if (m == NULL || m == n)
		return (m == NULL ? -1 : 0);
	while (m->links[i] && j == ERROR && m != n)
	{
		tmp = m->links[i];
		if (tmp->passe_par_la == 1)
			++i;
		else
		{
			tmp->passe_par_la = 1;
			if ((j = check_links(tmp, n)) == ERROR)
				++i;
			else
				return (1);
		}
	}
	return (i == m->nb_links ? ERROR : 1);
}

int		check_map(t_map *map)
{
	if (!map->end || !map->start || map->end == map->start)
		return (ERROR);
	map->start->passe_par_la = 1;
	if (map->start->links == NULL || map->end->links == NULL)
		return (ERROR);
	if (check_links(map->start, map->end) == ERROR)
		return (ERROR);
	return (TRUE);
}
