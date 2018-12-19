/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fil_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 04:03:17 by tduval            #+#    #+#             */
/*   Updated: 2018/12/18 05:39:18 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "ft_ls.h"

static void		*free_ret(t_inf *new)
{
	if (new)
		free(new);
	return (0);
}

static t_inf	*case_lnk(t_inf *new, char *path)
{
	char	t[256];
	char	*tmp;
	int		n;
	t_stat	didi;

	n = readlink(path, t, 255);
	stat(t, &didi);
	if (!(tmp = ft_strjoin(rev_chr(path), " -> ")))
		return (free_ret(new));
	if (!(new->path = ft_strjoin(tmp, t)))
		return (free_ret(new));
	ft_strdel((&tmp));
	return (new);
}

static t_inf	*case_lnk2(t_inf *new, char *path)
{
	char	t[256];
	char	*tmp;
	int		n;
	t_stat	didi;

	n = readlink(path, t, 255);
	if (!(tmp = ft_strjoin("/", t)))
		return (free_ret(new));
	stat(tmp, &didi);
	free(tmp);
	if (S_ISDIR(didi.st_mode))
		return (free_ret(new));
	return (new);
}

t_inf			*fil_new(char *path, char opts)
{
	t_stat	buf;
	t_inf	*new;

	if (!(new = (t_inf *)malloc(sizeof(t_inf))))
		return (0);
	new->path = 0;
	if (lstat(path, &buf) != 0 || S_ISDIR(buf.st_mode))
		return (free_ret(new));
	if (S_ISLNK(buf.st_mode) && opts & OPT_L)
		return (case_lnk(new, path));
	else
	{
		if (S_ISLNK(buf.st_mode))
			return (case_lnk2(new, path));
		if (!(new->path = ft_strdup(path)))
			return (free_ret(new));
	}
	new->buf = buf;
	new->next = 0;
	return (new);
}
