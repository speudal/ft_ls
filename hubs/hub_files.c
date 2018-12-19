/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <tduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 21:34:34 by tduval            #+#    #+#             */
/*   Updated: 2018/12/18 07:24:18 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <uuid/uuid.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include "ft_ls.h"

static t_inf	*sort_opts(t_inf *lst, char opts)
{
	lst = sort_alpha(lst);
	if (opts & OPT_T)
		lst = sort_time(lst);
	if (opts & OPT_SR)
		lst = sort_reverse(lst);
	return (lst);
}

static int		lili_len(t_inf *lst)
{
	int		i;

	i = 0;
	while (lst)
	{
		if (rev_chr(lst->path)[0] != '.')
			i++;
		lst = lst->next;
	}
	return (i);
}

static void		split_while(char opts, t_inf **top, char flag, int f[2])
{
	if (opts & OPT_A || rev_chr((*top)->path)[0] != '.')
	{
		f[0] = 1;
		ft_putstr(ft_ami((*top)->path, '/') && !flag ?
		rev_chr((*top)->path) : (*top)->path);
		f[1] = 1;
	}
	*top = (*top)->next;
	if (*top && (opts & OPT_A || rev_chr((*top)->path)[0] != '.') && f[1])
		ft_putchar('\n');
}

static void		split_while2(char opts, t_inf **top, int *pad, int f[2])
{
	if (rev_chr((*top)->path)[0] != '.' || opts & OPT_A)
		print_l(*top, pad);
	*top = (*top)->next;
	if (*top && ((opts & OPT_A) || rev_chr((*top)->path)[0] != '.') && f[0])
		ft_putchar('\n');
}

void			hub_files(t_inf *top, char opts, char flag)
{
	int		*pad;
	int		f[2];

	f[0] = 0;
	f[1] = 0;
	pad = 0;
	top = sort_opts(top, opts);
	if (opts & OPT_L)
	{
		if (!(pad = get_padding(top, opts)))
			return ;
		if ((opts & OPT_A || lili_len(top)) && flag == 0)
			ft_printf("total %d\n", pad[4]);
		while (top)
			split_while2(opts, &top, pad, f);
		if (pad)
			free(pad);
	}
	else
	{
		while (top)
			split_while(opts, &top, flag, f);
		if (f[0])
			ft_putchar('\n');
	}
}
