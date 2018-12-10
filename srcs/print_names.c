/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_names.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <tduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 19:00:37 by tduval            #+#    #+#             */
/*   Updated: 2018/12/10 20:44:31 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_files(char *name, char *options)
{
	ft_putendl(name);
}

void	sort_alpha(char **lst)
{
	char	*tmp;
	int		i;

	i = 0;
	while (lst[i + 1])
	{
		if (strcmp(lst[i], lst[i + 1]) > 0)
		{
			if (!(tmp = ft_strdup(lst[i])))
				return ;
			if (!(lst[i] = ft_strdup(lst[i + 1])))
				return ;
			if (!(lst[i + 1] = ft_strdup(tmp)))
				return ;
			i = -1;
		}
		i++;
	}
}

void	sort_t(char **lst)
{
	t_stat	buf1;
	t_stat	buf2;
	char	*tmp;
	int		i;

	i = 0;
	while (lst[i + 1])
	{
		stat(lst[i], &buf1);
		stat(lst[i + 1], &buf2);
		if (buf1.st_mtime < buf2.st_mtime)
		{
			if (!(tmp = ft_strdup(lst[i])))
				return ;
			if (!(lst[i] = ft_strdup(lst[i + 1])))
				return ;
			if (!(lst[i + 1] = ft_strdup(tmp)))
				return ;
			i = -1;
		}
		i++;
	}
}

void	sort_r(char **lst)
{
	char	*tmp;
	int		i;
	int		l;

	i = 0;
	l = 0;
	while (lst[l])
		l++;
	l--;
	while (i < l)
	{
		if (!(tmp = ft_strdup(lst[i])))
			return ;
		if (!(lst[i] = ft_strdup(lst[l])))
			return ;
		if (!(lst[l] = ft_strdup(tmp)))
			return ;
		i++;
		l--;
	}
}

void	print_names(char **lstfls, char *options)
{
	t_stat	buf;
	int		i;
	int		padd[2];
	int		max_links;
	int		max_bytes;

	max_links = 0;
	max_bytes = 0;
	i = 0;
	if (!lstfls)
		return ;
	sort_alpha(lstfls);
	if (options && ft_strchr(options, 't'))
		sort_t(lstfls);
	if (options && ft_strchr(options, 'r'))
		sort_r(lstfls);
	if (options && !ft_strchr(options, 'l'))
	{
		while (lstfls[i])
		{
			print_files(lstfls[i], options);
			i++;
		}
	}
	else
	{
		while (lstfls[i])
		{
			stat(lstfls[i], &buf);
			if (buf.st_nlink > max_links)
				max_links = buf.st_nlink;
			if (buf.st_size > max_bytes)
				max_bytes = buf.st_size;
			i++;
		}
		padd[0] = 3;
		padd[1] = 3;
		while (max_links > 9)
		{
			padd[0]++;
			max_links /= 10;
		}
		while (max_bytes > 9)
		{
			padd[1]++;
			max_bytes /= 10;
		}
		i = 0;
		while (lstfls[i])
		{
			stat(lstfls[i], &buf);
			if (S_ISREG(buf.st_mode))
				ft_putchar('-');
			if (S_ISCHR(buf.st_mode))
				ft_putchar('c');
			if (S_ISBLK(buf.st_mode))
				ft_putchar('b');
			i++;
		}
	}
}
