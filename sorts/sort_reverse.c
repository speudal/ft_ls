/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_reverse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 23:19:28 by tduval            #+#    #+#             */
/*   Updated: 2018/12/18 06:55:55 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"

static int	lst_len(t_inf *lst)
{
	int		i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

static int	split(t_inf **s, t_inf **lst)
{
	char	*tmp;
	t_stat	tt;

	if (!(tmp = ft_strdup((*s)->path)))
		return (0);
	tt = (*s)->buf;
	free((*s)->path);
	if (!((*s)->path = ft_strdup((*lst)->path)))
		return (0);
	(*s)->buf = (*lst)->buf;
	free((*lst)->path);
	if (!((*lst)->path = ft_strdup(tmp)))
		return (0);
	(*lst)->buf = tt;
	free(tmp);
	(*s) = (*s)->next;
	return (1);
}

t_inf		*sort_reverse(t_inf *lst)
{
	int		jk[2];
	t_inf	*s;
	t_inf	*o;

	s = lst;
	o = lst;
	jk[1] = lst_len(lst);
	while (jk[1] > lst_len(o) / 2)
	{
		jk[1]--;
		jk[0] = 0;
		while (lst->next && (jk[0] < jk[1]))
		{
			lst = lst->next;
			jk[0]++;
		}
		if (!(split(&s, &lst)))
			return (0);
		lst = o;
	}
	return (o);
}
