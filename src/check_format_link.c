/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_format_link.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snassour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 18:29:47 by snassour          #+#    #+#             */
/*   Updated: 2018/09/05 18:29:49 by snassour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_node	**transform_graph(t_node *begin_list, int nb_nde)
{
	t_node	**new;
	int		i;
	t_node	*tmp;

	i = -1;
	new = (t_node **)ft_memalloc(sizeof(t_node *) * (nb_nde + 1));
	if (!new)
		return (NULL);
	tmp = begin_list;
	while (++i < nb_nde)
	{
		new[i] = tmp;
		tmp = tmp->next;
	}
	new[i] = NULL;
	return (new);
}

int		check_link_name(char *name, t_map *map)
{
	t_node	*tmp;
	int		ret;

	tmp = map->begin_list;
	while (map->begin_list)
	{
		if (ft_strcmp(map->begin_list->name, name) == 0)
			break ;
		map->begin_list = map->begin_list->next;
	}
	ret = (map->begin_list ? TRUE : FALSE);
	map->begin_list = tmp;
	return (ret);
}

int		check_format_link(char *line, t_map *map, int status)
{
	char	**s;
	int		i;
	int		mode;
	char	*s2;

	if (line[0] == '#')
		return (2);
	if (map->start == NULL || map->end == NULL)
		return (FALSE);
	if ((s2 = ft_strchr(line, '-')) == NULL)
		return (FALSE);
	if (s2 + 1 && ft_strchr(s2 + 1, '-') != NULL)
		return (FALSE);
	s = ft_strsplit(line, '-');
	if (!s)
		return (FALSE);
	i = 0;
	mode = FALSE;
	if (s && (i = ft_count_tab_elem((void **)s)) == 2 && ft_strcmp(s[0], s[1]))
		if (check_link_name(s[0], map) && check_link_name(s[1], map))
			mode = 2;
	if (status == FALSE && mode == 2)
		map->tab = transform_graph(map->begin_list, map->nb_nde);
	ft_tabstrdel(&s, i);
	return (mode);
}
