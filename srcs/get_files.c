/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 18:31:23 by tduval            #+#    #+#             */
/*   Updated: 2018/12/11 19:21:29 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"
#include "libft.h"

static char	**split(int ac, char **av, char **tab)
{
	t_stat	buf;
	int		i;
	int		j;

	j = 0;
	i = 1;
	while (i < ac)
	{
		if (stat(av[i], &buf) != -1)
		{
			if (!S_ISDIR(buf.st_mode))
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

char		**get_files(int ac, char **av)
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
		{
			if (!S_ISDIR(buf.st_mode))
				j++;
		}
		else
			ft_printf("ft_ls: %s: No such file or directory\n", av[i]);
		i++;
	}
	if (!(tab = malloc(sizeof(char *) * (j + 1))))
		return (0);
	if (!(tab = split(ac, av, tab)))
		return (0);
	return (tab);
}
