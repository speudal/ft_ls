/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_alpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 06:45:45 by tduval            #+#    #+#             */
/*   Updated: 2018/12/18 06:50:15 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"

static int	split(t_inf **lst, t_stat *btmp)
{
	*btmp = (*lst)->buf;
	ft_strdel(&((*lst)->path));
	if (!((*lst)->path = ft_strdup((*lst)->next->path)))
		return (0);
	(*lst)->buf = (*lst)->next->buf;
	return (1);
}

t_inf		*sort_alpha(t_inf *lst)
{
	t_stat	btmp;
	t_inf	*or;
	char	*tmp;

	or = lst;
	tmp = 0;
	while (lst && lst->next)
	{
		if (ft_strcmp(rev_chr(lst->path), rev_chr(lst->next->path)) > 0)
		{
			if (!(tmp = ft_strdup(lst->path)))
				return (0);
			if (!(split(&lst, &btmp)))
				return (0);
			ft_strdel(&(lst->next->path));
			if (!(lst->next->path = ft_strdup(tmp)))
				return (0);
			lst->next->buf = btmp;
			lst = or;
		}
		else
			lst = lst->next;
		ft_strdel(&tmp);
	}
	return (or);
}
