/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <tduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 21:34:34 by tduval            #+#    #+#             */
/*   Updated: 2018/12/16 05:02:12 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <uuid/uuid.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include "ft_ls.h"

static t_inf	*sort_opts(t_inf *lst, char *opts)
{
	lst = sort_alpha(lst);
	if (opts && ft_ami(opts, 't'))
		lst = sort_time(lst);
	if (opts && ft_ami(opts, 'r'))
		lst = sort_reverse(lst);
	return (lst);
}
void			hub_files(t_inf *top, char *opts, char flag, char flag2)
{
	int		*pad;

	top = sort_opts(top, opts);
	if (opts && ft_ami(opts, 'l'))
	{
		if (!(pad = get_padding(top, opts)))
			return ;
		if (flag2 && top->next->next)
			ft_printf("total %d\n", pad[4]);
		while (top)
		{
			if (rev_chr(top->path)[0] != '.' || ft_ami(opts, 'a'))
				print_l(top, pad);
			top = top->next;
		}
		if (flag)
			ft_putchar('\n');
	}
	else
	{
		while (top)
		{
			if ((opts && ft_ami(opts, 'a')) || rev_chr(top->path)[0] != '.')
				ft_putendl(ft_ami(top->path, '/') ? rev_chr(top->path) : top->path);
			top = top->next;
		}
		if (flag)
			ft_putchar('\n');
	}
}
