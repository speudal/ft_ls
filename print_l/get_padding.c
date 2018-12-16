/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_padding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 18:11:39 by tduval            #+#    #+#             */
/*   Updated: 2018/12/15 21:50:44 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <uuid/uuid.h>
#include <pwd.h>
#include <grp.h>
#include "ft_ls.h"

int		*get_padding(t_inf *top, char *opts)
{
	struct passwd	*p;
	struct group	*q;
	int				*pad;
	int				i;

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
			if (int_len(top->buf.st_nlink) > pad[0])
				pad[0] = int_len(top->buf.st_nlink);
			if ((int)ft_strlen(p->pw_name) > pad[1])
				pad[1] = ft_strlen(p->pw_name);
			if ((int)ft_strlen(q->gr_name) > pad[2])
				pad[2] = ft_strlen(q->gr_name);
			if ((int)int_len(top->buf.st_size) > pad[3])
				pad[3] = int_len(top->buf.st_size);
			pad[4] += top->buf.st_blocks;
		}
		top = top->next;
	}
	return (pad);
}
