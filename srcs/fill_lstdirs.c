/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lstdirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 17:20:18 by tduval            #+#    #+#             */
/*   Updated: 2018/12/10 17:40:11 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_ls.h"

static char	**split(char **paths)
{
	char	**tab;
	t_stat	buf;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (paths[i++])
		if (stat(paths[i], &buf) != -1)
			if (S_ISDIR(buf.st_mode))
				j++;
	if (!(tab = (char **)malloc(sizeof(char *) * (j + 1))))
		return (0);
	tab[j] = 0;
	return (tab);
}

char		**fill_lstdirs(char **paths)
{
	char	**tab;
	t_stat	buf;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(tab = split(paths)))
		return (0);
	while (paths[i])
	{
		if (stat(paths[i], &buf) != -1)
		{
			if (S_ISDIR(buf.st_mode))
			{
				if (!(tab[j] = ft_strdup(paths[i])))
					return (0);
				j++;
			}
		}
		i++;
	}
	return (tab);
}
