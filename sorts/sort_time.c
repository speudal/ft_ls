/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 23:19:58 by tduval            #+#    #+#             */
/*   Updated: 2018/12/16 05:31:24 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"

t_inf	*sort_time(t_inf *lst)
{
	t_stat	btmp;
	t_inf	*or;
	char	*tmp;

	or = lst;
	tmp = 0;
	while (lst && lst->next)
	{
		if (lst->buf.st_mtime < lst->next->buf.st_mtime)
		{
			if (!(tmp = ft_strdup(lst->path)))
				return (0);
			btmp = lst->buf;
			ft_strdel(&(lst->path));
			if (!(lst->path = ft_strdup(lst->next->path)))
				return (0);
			lst->buf = lst->next->buf;
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
