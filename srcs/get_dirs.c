/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dirs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 18:51:28 by tduval            #+#    #+#             */
/*   Updated: 2018/12/11 19:11:52 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"
#include "libft.h"

static char	**split(char **tab, char **av, int ac)
{
	t_stat	buf;
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (i < ac)
	{
		if (stat(av[i], &buf) != -1)
		{
			if (S_ISDIR(buf.st_mode))
			{
				if (!(tab[j] = ft_strdup(av[i])))
					return (0);
				j++;
			}
		}
		i++;
	}
	tab[j] = 0;
	return (tab);
}

char		**get_dirs(int ac, char **av)
{
	t_stat	buf;
	char	**tab;
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (i < ac && (av[i][0] == '-' && av[i][1]))
		i++;
	while (i < ac)
	{
		if (stat(av[i], &buf) != -1)
			if (S_ISDIR(buf.st_mode))
				j++;
		i++;
	}
	if (!(tab = malloc(sizeof(char *) * (j + 1))))
		return (0);
	if (!(tab = split(tab, av, ac)))
		return (0);
	return (tab);
}
