/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitwhitespaces.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snassour <snassour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 17:29:59 by snassour          #+#    #+#             */
/*   Updated: 2016/10/17 15:40:22 by snassour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static size_t	words(char *str)
{
	size_t	nb_words;
	size_t	i;

	i = 0;
	nb_words = 0;
	while (str[i])
	{
		while (ft_isblank(str[i]) && str[i])
			++i;
		if (!ft_isblank(str[i]) && str[i])
			++nb_words;
		while (!ft_isblank(str[i]) && str[i])
			++i;
	}
	return (nb_words);
}

char			**ft_splitwhitespaces(char *s)
{
	char	**tab;
	size_t	len;
	size_t	nw;
	size_t	j;
	char	*str;

	if (s == NULL)
		return (NULL);
	str = s;
	nw = words(str);
	if (!(tab = (char **)ft_memalloc(sizeof(char *) * (nw + 1))))
		return (NULL);
	j = -1;
	while (++j < nw && *str)
	{
		while (ft_isblank(*str) && *str)
			++str;
		len = 0;
		while (!ft_isblank(str[len]) && str[len])
			++len;
		tab[j] = ft_strncpy(ft_strnew(len), str, len);
		str += len;
	}
	return (tab);
}
