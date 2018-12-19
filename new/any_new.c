/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   any_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 04:05:29 by tduval            #+#    #+#             */
/*   Updated: 2018/12/18 04:35:24 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "ft_ls.h"

static t_inf	*case_lnk(t_inf *new, char *path)
{
	char	*tmp;
	char	*tmp2;
	int		n;

	tmp = 0;
	tmp2 = 0;
	if (!(new->path = ft_strnew(256)))
		return (0);
	n = readlink(path, new->path, 255);
	if (!(tmp = ft_strdup(new->path)))
		return (0);
	ft_strdel(&(new->path));
	if (!(tmp2 = ft_strjoin(rev_chr(path), " -> ")))
		return (0);
	if (!(new->path = ft_strjoin(tmp2, tmp)))
		return (0);
	free(tmp);
	free(tmp2);
	return (new);
}

static char		*regular(t_inf *new, char *path, t_stat buf)
{
	if (!(new->path = ft_strdup(S_ISDIR(buf.st_mode) ?
			path : rev_chr(path))))
	{
		free(new);
		return (0);
	}
	return (new->path);
}

t_inf			*any_new(char *path, char opts)
{
	t_stat	buf;
	t_inf	*new;

	if (!(new = (t_inf *)malloc(sizeof(t_inf))))
		return (0);
	new->path = 0;
	if (lstat(path, &buf) != 0)
	{
		ft_printf("ft_ls: %s: No such file or directory\n", path);
		free(new);
		return (0);
	}
	if (S_ISLNK(buf.st_mode) && opts & OPT_L)
	{
		if (!(new = case_lnk(new, path)))
			return (0);
	}
	else
	{
		if (!(new->path = regular(new, path, buf)))
			return (0);
	}
	new->buf = buf;
	new->next = 0;
	return (new);
}
