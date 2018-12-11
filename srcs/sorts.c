/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 18:57:42 by tduval            #+#    #+#             */
/*   Updated: 2018/12/11 19:00:06 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
