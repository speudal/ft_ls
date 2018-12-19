/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_padding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 18:11:39 by tduval            #+#    #+#             */
/*   Updated: 2018/12/18 06:35:00 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <uuid/uuid.h>
#include <pwd.h>
#include <grp.h>
#include "ft_ls.h"

static int	*one(t_inf *top, int *pad)
{
	struct passwd	*p;
	struct group	*q;

	p = getpwuid(top->buf.st_uid);
	q = getgrgid(top->buf.st_gid);
	if (int_len(top->buf.st_nlink) > pad[0])
		pad[0] = int_len(top->buf.st_nlink);
	if (p && p->pw_name && (int)ft_strlen(p->pw_name) > pad[1])
		pad[1] = ft_strlen(p->pw_name);
	if (q && q->gr_name && (int)ft_strlen(q->gr_name) > pad[2])
		pad[2] = ft_strlen(q->gr_name);
	if ((int)int_len(top->buf.st_size) > pad[3])
		pad[3] = int_len(top->buf.st_size);
	pad[4] += top->buf.st_blocks;
	return (pad);
}

static int	*two(t_inf *top, int *pad)
{
	struct passwd	*p;
	struct group	*q;

	p = getpwuid(top->buf.st_uid);
	q = getgrgid(top->buf.st_gid);
	if (int_len(top->buf.st_nlink) > pad[0])
		pad[0] = int_len(top->buf.st_nlink);
	if (p && p->pw_name && (int)ft_strlen(p->pw_name) > pad[1])
		pad[1] = ft_strlen(p->pw_name);
	if (q && q->gr_name && (int)ft_strlen(q->gr_name) > pad[2])
		pad[2] = ft_strlen(q->gr_name);
	if ((int)int_len(major((top->buf.st_dev))) > pad[3])
		pad[3] = int_len(minor((top->buf.st_rdev)));
	if ((int)int_len(minor((top->buf.st_rdev))) > pad[5])
		pad[5] = int_len(minor((top->buf.st_rdev)));
	pad[4] += top->buf.st_blocks;
	return (pad);
}

int			*get_padding(t_inf *top, char opts)
{
	int				*pad;
	int				i;

	if (!(pad = (int *)malloc(sizeof(int) * 6)))
		return (0);
	i = 0;
	while (i < 6)
	{
		pad[i] = 0;
		i++;
	}
	while (top)
	{
		if (((opts & OPT_A)) || rev_chr(top->path)[0] != '.')
		{
			if (!(S_ISBLK(top->buf.st_mode) || S_ISCHR(top->buf.st_mode)))
				pad = one(top, pad);
			else
				pad = two(top, pad);
		}
		top = top->next;
	}
	return (pad);
}
