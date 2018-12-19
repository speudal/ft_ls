/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 17:41:22 by tduval            #+#    #+#             */
/*   Updated: 2018/12/17 02:31:41 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	free_both(char *s1, char *s2, int w)
{
	if (w == 0 || w == 1)
		ft_strdel(&s1);
	if (w == 0 || w == 2)
		ft_strdel(&s2);
}

char		*ft_strfjoin(char *s1, char *s2, int w)
{
	char	*s;
	char	*res;

	if (!s1 || !s2)
		return (0);
	if (!(s = (char *)malloc(sizeof(char) * \
		(ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (0);
	res = s;
	while (*s1)
	{
		*s = *s1;
		s++;
		s1++;
	}
	while (*s2)
	{
		*s = *s2;
		s++;
		s2++;
	}
	*s = '\0';
	free_both(s1, s2, w);
	return (res);
}
