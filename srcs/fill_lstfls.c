/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lstfls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <tduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 17:41:40 by tduval            #+#    #+#             */
/*   Updated: 2018/12/10 19:47:03 by tduval           ###   ########.fr       */
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
	while (paths[i])
	{
		if (stat(paths[i], &buf) != -1)
			if (!S_ISDIR(buf.st_mode))
				j++;
		i++;
	}
	if (!j)
		return (0);
	if (!(tab = (char **)malloc(sizeof(char *) * (j + 1))))
		return (0);
	tab[j] = 0;
	return (tab);
}

char		**fill_lstfls(char **paths)
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
			if (!S_ISDIR(buf.st_mode))
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
