/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <tduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 18:57:42 by tduval            #+#    #+#             */
/*   Updated: 2018/12/15 02:13:56 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"

t_inf	*sort_alpha(t_inf *lst)
{
	t_stat	btmp;
	t_inf	*or;
	char	*tmp;

	or = lst;
	tmp = 0;
	while (lst && lst->next)
	{
		if (strcmp(lst->path, lst->next->path) > 0)
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
		ft_strdel(&tmp);
		lst = lst->next;
	}
	return (or);
}

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
		ft_strdel(&tmp);
		lst = lst->next;
	}
	return (or);
}

t_inf	*sort_reverse(t_inf *lst)
{
	t_inf	*cur;
	t_inf	*next;
	t_inf	*prev;

	cur = lst;
	next = 0;
	prev = 0;
	while (cur)
	{
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	lst = prev;
	return (prev);
}
