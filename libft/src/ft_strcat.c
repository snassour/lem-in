/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snassour <snassour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 14:57:32 by snassour          #+#    #+#             */
/*   Updated: 2015/11/29 18:38:46 by snassour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	size_t i;
	size_t j;

	i = ft_strlen(s1);
	j = 0;
	while (*(s2 + j))
		*(s1 + i++) = *(s2 + j++);
	*(s1 + i) = 0;
	return (s1);
}
