/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_link.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snassour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 21:05:41 by snassour          #+#    #+#             */
/*   Updated: 2018/09/05 21:05:44 by snassour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	lemin_appendtab(t_node ***new, t_node *old, t_node *added)
{
	int		i;

	i = -1;
	while (++i < old->nb_links)
		(*new)[i] = old->links[i];
	(*new)[i] = added;
	(*new)[i + 1] = NULL;
}

void	set_link_nodes(t_node **n1, t_node **n2, char **s, t_node *og)
{
	if (ft_strcmp(s[0], og->name) == 0)
		*n1 = og;
	if (ft_strcmp(s[1], og->name) == 0)
		*n2 = og;
}

int		add_link(char *line, t_map *map)
{
	char	**s;
	t_node	*n1;
	t_node	*n2;
	int		i;

	n1 = NULL;
	n2 = NULL;
	if (!(s = ft_strsplit(line, '-')))
		return (FALSE);
	if ((i = ft_count_tab_elem((void **)s)) != 2)
	{
		ft_tabstrdel(&s, i);
		return (FALSE);
	}
	i = -1;
	while (++i < map->nb_nde)
		set_link_nodes(&n1, &n2, s, map->tab[i]);
	ft_tabstrdel(&s, ft_count_tab_elem((void **)s));
	if (n1 == NULL || n2 == NULL)
		return (FALSE);
	if ((n1 == map->start && n2 == map->end)
	|| (n1 == map->end && n2 == map->start))
		map->start_end_connected = 1;
	return (create_link(n1, n2) ? 2 : FALSE);
}

int		create_link(t_node *n1, t_node *n2)
{
	int		i;
	t_node	**tmp1;
	t_node	**tmp2;

	i = -1;
	while (++i < n1->nb_links)
		if (!ft_strcmp(n1->links[i]->name, n2->name))
			break ;
	if (i != n1->nb_links)
		return (TRUE);
	if ((tmp1 = (t_node **)ft_memalloc(sizeof(t_node *) * (n1->nb_links + 2)))
	&& (tmp2 = (t_node **)ft_memalloc(sizeof(t_node *) * (n2->nb_links + 2))))
	{
		lemin_appendtab(&tmp1, n1, n2);
		lemin_appendtab(&tmp2, n2, n1);
		lemin_tabnddel(&(n1->links));
		lemin_tabnddel(&(n2->links));
		n1->links = tmp1;
		n2->links = tmp2;
		n1->nb_links += 1;
		n2->nb_links += 1;
	}
	tmp1 && !tmp2 ? lemin_tabnddel(&tmp1) : NULL;
	return (n1->links && n2->links ? TRUE : FALSE);
}
