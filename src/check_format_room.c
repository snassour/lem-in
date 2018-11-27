/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_format_room.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snassour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 18:24:44 by snassour          #+#    #+#             */
/*   Updated: 2018/09/05 18:24:46 by snassour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		lemin_valid_char_name(char c)
{
	if (c >= 33 && c <= 126 && c != '-')
		return (TRUE);
	return (FALSE);
}

int		lemin_valid_name(char *name)
{
	int	i;
	int ret;

	i = -1;
	ret = TRUE;
	if (name[0] != 'L' && name[0] != '#')
		while (name[++i] && ret == TRUE)
			ret = lemin_valid_char_name(name[i]);
	return (ret == TRUE && i != -1 && name[i] == '\0');
}

int		check_format_room(char *line)
{
	char	**s;
	int		i;
	int		mode;

	if (line[0] == '#')
		return (TRUE);
	s = NULL;
	s = ft_strsplit(line, ' ');
	if (!s)
		return (FALSE);
	mode = FALSE;
	i = 0;
	if (s && (i = ft_count_tab_elem((void **)s)) == 3)
		if (lemin_valid_name(s[0]) && lemin_isint(s[1]) && lemin_isint(s[2]))
			mode = TRUE;
	ft_tabstrdel(&s, i);
	return (mode);
}
