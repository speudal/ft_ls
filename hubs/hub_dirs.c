/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub_dirs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 23:55:11 by tduval            #+#    #+#             */
/*   Updated: 2018/12/18 06:10:42 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"
#include "libft.h"

static void	split_while(t_dirent *e, t_inf *cor[2], t_inf *dirs, char opts)
{
	char	*tmp;
	char	*tmp2;

	tmp = 0;
	tmp2 = 0;
	if (!(cor[0]))
	{
		tmp = ft_strapp(dirs->path, '/');
		tmp2 = ft_strjoin(tmp, e->d_name);
		cor[0] = any_new(tmp2, opts);
		free(tmp);
		free(tmp2);
		cor[1] = cor[0];
	}
	else
	{
		tmp = ft_strapp(dirs->path, '/');
		tmp2 = ft_strjoin(tmp, e->d_name);
		cor[0]->next = any_new(tmp2, opts);
		free(tmp);
		free(tmp2);
		if (cor[0]->next)
			cor[0] = cor[0]->next;
	}
}

static void	else_split(t_inf *cor[2], t_inf *dirs, char opts, char flag)
{
	DIR			*o;
	t_dirent	*e;

	o = 0;
	if (flag)
		ft_printf("%s:\n", dirs->path);
	if ((o = opendir(dirs->path)))
	{
		cor[0] = 0;
		while ((e = readdir(o)))
			split_while(e, cor, dirs, opts);
		closedir(o);
		hub_files(cor[1], opts, 0);
		free_all(0, cor[1]);
	}
	else
		ft_printf("ft_ls: %s: Permission denied\n", dirs->path);
}

void		hub_dirs(char opts, t_inf *dirs, char flag)
{
	t_inf		*cor[2];

	if (dirs && dirs->next)
		flag = 1;
	dirs = sort_alpha(dirs);
	if (opts & OPT_T)
		dirs = sort_time(dirs);
	if (opts & OPT_SR)
		dirs = sort_reverse(dirs);
	while (dirs)
	{
		if (opts & OPT_BR)
		{
			if (flag)
				ft_printf("%s:\n", dirs->path);
			print_br(dirs, opts, 0);
		}
		else
			else_split(cor, dirs, opts, flag);
		dirs = dirs->next;
		if (dirs)
			ft_putchar('\n');
	}
}
