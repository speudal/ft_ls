/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inf_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <tduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 18:52:39 by tduval            #+#    #+#             */
/*   Updated: 2018/12/15 03:15:58 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "ft_ls.h"

static	char *rev_chr(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i && str[i] != '/')
		i--;
	return (str + i);
}

t_inf	*fil_new(char *path, char *opts)
{
	int		n;
	t_stat	buf;
	t_inf	*new;

	if (!(new = (t_inf *)malloc(sizeof(t_inf))))
		return (0);
	if (lstat(path, &buf) != 0)
		return (0);
	if (S_ISDIR(buf.st_mode))
	{
		free(new);
		return (0);
	}
	if (S_ISLNK(buf.st_mode) && ft_ami(opts, 'l'))
	{
		new->path = ft_strnew(256);
		n = readlink(path, new->path, 255);
		new->path[n] = 0;
		new->path = ft_strjoin(ft_strjoin(rev_chr(path) + 1, " -> "), new->path);
	}
	else
	{
		if (!(new->path = ft_strdup(path)))
			return (0);
	}
	new->buf = buf;
	new->next = 0;
	return (new);
}

t_inf	*dir_new(char *path, char *opts)
{
	int		n;
	t_stat	buf;
	t_inf	*new;

	if (!(new = (t_inf *)malloc(sizeof(t_inf))))
		return (0);
	if (lstat(path, &buf) != 0)
	{
		ft_printf("ft_ls: %s: No such file or directory\n", path);
		free(new);
		return (0);
	}
	if (S_ISDIR(buf.st_mode) == 0)
	{
		free(new);
		return (0);
	}
	if (S_ISLNK(buf.st_mode) && ft_ami(opts, 'l'))
	{
		new->path = ft_strnew(256);
		n = readlink(path, new->path, 255);
		new->path[n] = 0;
		new->path = ft_strjoin(ft_strjoin(rev_chr(path) + 1, " -> "), new->path);
	}
	else
	{	
		if (!(new->path = ft_strdup(path)))
			return (0);
	}
	new->buf = buf;
	new->next = 0;
	return (new);
}

t_inf	*any_new(char *path, char *opts)
{
	int		n;
	t_stat	buf;
	t_inf	*new;

	if (!(new = (t_inf *)malloc(sizeof(t_inf))))
		return (0);
	if (lstat(path, &buf) != 0)
	{
		ft_printf("ft_ls: %s: No such file or directory\n", path);
		free(new);
		return (0);
	}
	if (S_ISLNK(buf.st_mode) && ft_ami(opts, 'l'))
	{
		new->path = ft_strnew(256);
		n = readlink(path, new->path, 255);
		new->path[n] = 0;
		new->path = ft_strjoin(ft_strjoin(rev_chr(path) + 1, " -> "), new->path);
	}
	else
	{
		if (!(new->path = ft_strdup(S_ISDIR(buf.st_mode) ? path : rev_chr(path) + 1)))
			return (0);
	}
	new->buf = buf;
	new->next = 0;
	return (new);
}