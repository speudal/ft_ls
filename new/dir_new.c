/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inf_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <tduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 18:52:39 by tduval            #+#    #+#             */
/*   Updated: 2018/12/18 05:03:13 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "ft_ls.h"

static void		*free_here(t_inf *new, char *tmp, char *tmp2)
{
	if (new)
	{
		ft_strdel(&(new->path));
		free(new);
	}
	if (tmp)
		free(tmp);
	if (tmp2)
		free(tmp2);
	return (0);
}

static t_inf	*lnk_case(t_inf *new, char *path)
{
	char	*tmp;
	char	*tmp2;
	t_stat	didi;
	int		n;

	tmp = 0;
	tmp2 = 0;
	if (!(new->path = ft_strnew(256)))
		return (0);
	n = readlink(path, new->path, 255);
	stat(new->path, &didi);
	if (S_ISDIR(didi.st_mode))
	{
		if (!(tmp = ft_strdup(new->path)))
			return (free_here(new, 0, 0));
		if (!(tmp2 = ft_strjoin(rev_chr(path), " -> ")))
			return (free_here(new, tmp, 0));
		if (!(new->path = ft_strjoin(tmp2, tmp)))
			return (free_here(new, tmp, tmp2));
		free(tmp);
		free(tmp2);
		return (new);
	}
	else
		return (free_here(new, 0, 0));
}

t_inf			*dir_new(char *path, char opts)
{
	t_stat	buf;
	t_inf	*new;

	if (!(new = (t_inf *)malloc(sizeof(t_inf))))
		return (0);
	if (!(new->path = 0) && lstat(path, &buf) != 0)
	{
		ft_printf("ft_ls: %s: No such file or directory\n", path);
		return (free_here(new, 0, 0));
	}
	if (S_ISDIR(buf.st_mode) == 0 && S_ISLNK(buf.st_mode) == 0)
		return (free_here(new, 0, 0));
	if (S_ISLNK(buf.st_mode) && opts & OPT_L)
	{
		if (!(new = lnk_case(new, path)))
			return (0);
	}
	else
	{
		if (!(new->path = ft_strdup(path)))
			return (free_here(new, 0, 0));
	}
	new->buf = buf;
	new->next = 0;
	return (new);
}
