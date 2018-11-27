/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_lemin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snassour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 22:13:07 by snassour          #+#    #+#             */
/*   Updated: 2018/09/05 22:13:09 by snassour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		lemin_isint(char *str)
{
	int		i;
	char	*num;

	if (!str || !*str)
		return (FALSE);
	i = str[0] == '-' ? 1 : 0;
	while (ft_isdigit(str[i]))
		++i;
	if (str[i] != 0)
		return (FALSE);
	i = ft_atoi(str);
	if (i == 0)
		return (TRUE);
	num = ft_itoa(i);
	if (num)
		i = ft_strcmp(num, str);
	ft_strdel(&num);
	return (i == 0 ? TRUE : FALSE);
}

void	lemin_modify(t_node *lst, char *name, int x, int y)
{
	lst->x = x;
	lst->y = y;
	if (lst->changed == -1)
	{
		ft_strdel(&(lst->name));
		lst->name = ft_strdup(name);
		if (!lst->name)
		{
			write(2, "Error : change name\n", 21);
			return ;
		}
	}
	lst->changed = 1;
}

void	lemin_tabnddel(t_node ***tab)
{
	if (tab)
		if (*tab)
		{
			free(*tab);
			*tab = NULL;
		}
}

int		add_to_map(char *line, t_map *map, int status, int comment)
{
	int		com;

	com = check_comment(line, map);
	if (com)
		return (status);
	if (status == 1)
		status = add_room(line, map, comment);
	if (status == 2)
		status = add_link(line, map);
	if (status == 3)
		status = add_nb_ants(line, map);
	return (status);
}

t_node	*lemin_getnextnde(t_node *tmp)
{
	int	i;

	i = -1;
	while (++i < tmp->nb_links)
	{
		if (tmp->links[i]->index > 0 && tmp->links[i]->index < tmp->index)
			return (tmp->links[i]);
		if (tmp->links[i]->index == -2)
			return (tmp->links[i]);
	}
	return (NULL);
}
