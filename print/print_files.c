/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <tduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 21:34:34 by tduval            #+#    #+#             */
/*   Updated: 2018/12/15 03:51:04 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <uuid/uuid.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include "ft_ls.h"

static	char *rev_chr(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i && str[i] != '/')
		i--;
	return (str + i + 1);
}

static int	wiwi(int n)
{
	int	i;

	i = 1;
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static int	*get_padding(t_inf *top, char *opts)
{
	int				*pad;
	int				i;
	struct passwd	*p;
	struct group	*q;

	if (!(pad = (int *)malloc(sizeof(int) * 5)))
		return (0);
	i = 0;
	while (i < 5)
	{
		pad[i] = 0;
		i++;
	}
	while (top)
	{
		if (((opts && ft_ami(opts, 'a')) || rev_chr(top->path)[0] != '.'))
		{
			p = getpwuid(top->buf.st_uid);
			q = getgrgid(top->buf.st_gid);
			if (wiwi(top->buf.st_nlink) > pad[0])
				pad[0] = wiwi(top->buf.st_nlink);
			if (ft_strlen(p->pw_name) > pad[1])
				pad[1] = ft_strlen(p->pw_name);
			if (ft_strlen(q->gr_name) > pad[2])
				pad[2] = ft_strlen(q->gr_name);
			if (wiwi(top->buf.st_size) > pad[3])
				pad[3] = wiwi(top->buf.st_size);
			pad[4] += top->buf.st_blocks;
		}
		top = top->next;
	}
	return (pad);
}

void	print_files(t_inf *top, char *opts, char flag)
{
	int		*pad;
	t_inf	*or;
	int		i;

	i = 0;
	top = sort_alpha(top);
	if (opts && ft_ami(opts, 't'))
		top = sort_time(top);
	if (opts && ft_ami(opts, 'r'))
		top = sort_reverse(top);
	if (opts && ft_ami(opts, 'l'))
	{
		if (!(pad = get_padding(top, opts)))
			return ;
		ft_printf("total %d\n", pad[4]);
		while (top)
		{
			if ((opts && ft_ami(opts, 'a')) || rev_chr(top->path)[0] != '.')
			{
				print_l(top, pad);
				ft_putchar('\n');
			}
			top = top->next;
		}
	}
	else
	{
		while (top)
		{
			if ((opts && ft_ami(opts, 'a')) || ft_ami(top->path, '/') ? rev_chr(top->path)[0] != '.' : (top->path)[0] != '.')
				ft_putendl(ft_ami(top->path, '/') ? rev_chr(top->path) : top->path);
			top = top->next;
		}
		if (flag)
			ft_putchar('\n');
	}
}
