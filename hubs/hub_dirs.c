/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dirs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <tduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 05:36:16 by tduval            #+#    #+#             */
/*   Updated: 2018/12/16 05:18:22 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"
#include "libft.h"

void		hub_dirs(char *opts, t_inf *dirs, char flag)
{
	DIR			*o;
	t_inf		*or;
	t_inf		*cur;
	t_dirent	*e;

	or = 0;
	if (dirs && dirs->next)
		flag = 1;
	dirs = sort_alpha(dirs);
	if (ft_ami(opts, 't'))
		dirs = sort_time(dirs);
	if (ft_ami(opts, 'r'))
		dirs = sort_reverse(dirs);
	if (ft_ami(opts, 'R'))
	{
		print_br(dirs, opts, 1);
		return ;
	}
	while (dirs)
	{
		if (flag)
			ft_printf("%s:\n", dirs->path);
		if ((o = opendir(dirs->path)))
		{
			cur = 0;
			while ((e = readdir(o)))
			{
				if (!cur)
				{
					cur = any_new(ft_strjoin(ft_strjoin(dirs->path, "/"), e->d_name), opts);
					or = cur;
				}
				else
				{
					cur->next = any_new(ft_strjoin(ft_strjoin(dirs->path, "/"), e->d_name), opts);
					if (cur->next)
						cur = cur->next;
				}
			}
			hub_files(or, opts, 0, 1);
			free_all(0, 0, cur);
		}
		else
			ft_printf("ft_ls: %s: Permission denied\n", dirs->path);
		dirs = dirs->next;
		if (dirs)
			ft_putchar('\n');
	}
}
