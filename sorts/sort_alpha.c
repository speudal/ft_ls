/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_alpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 23:18:37 by tduval            #+#    #+#             */
/*   Updated: 2018/12/15 23:35:44 by tduval           ###   ########.fr       */
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
		if (ft_strcmp(rev_chr(lst->path), rev_chr(lst->next->path)) > 0)
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
