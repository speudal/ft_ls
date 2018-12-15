/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <tduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 04:42:16 by tduval            #+#    #+#             */
/*   Updated: 2018/12/15 03:27:24 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static	char *rev_chr(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i && str[i] != '/')
		i--;
	return (str + i);
}

void	print_rec(t_inf *dir, char *opts, int f)
{
	DIR			*gl;
	t_inf		*dirs;
	t_inf		*cdirs;
	t_inf		*fils;
	t_inf		*cfils;
	t_stat		buf;
	t_dirent	*e;

	cdirs = 0;
	cfils = 0;
	dirs = 0;
	fils = 0;
	if (!dir)
		return ;
	if (f)
		ft_printf("%s:\n", dir->path);
	if ((gl = opendir(dir->path)))
	{
		while ((e = readdir(gl)))
		{
			if (!cfils)
			{
				fils = any_new(ft_strjoin(ft_strjoin(dir->path, "/"), e->d_name), opts);
				cfils = fils;
			}
			else
			{
				fils->next = any_new(ft_strjoin(ft_strjoin(dir->path, "/"), e->d_name), opts);
				if (fils->next)
					fils = fils->next;
			}
		}
		print_files(cfils, opts, 1);
		while (cfils)
		{
			if (S_ISDIR(cfils->buf.st_mode) && strcmp(rev_chr(cfils->path), "/.") && strcmp(rev_chr(cfils->path), "/..") && (rev_chr(cfils->path)[1] != '.' || ft_ami(opts, 'a')))
				print_rec(cfils, opts, 1);
			cfils = cfils->next;
		}
		closedir(gl);
	}
	else
		ft_printf("ft_ls: %s: Permission denied\n\n", dir->path);
}