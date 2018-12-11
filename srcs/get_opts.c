/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 17:36:27 by tduval            #+#    #+#             */
/*   Updated: 2018/12/11 18:22:03 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	*split(char *av, char *opts)
{
	int		i;

	i = 1;
	while (av[i])
	{
		if (!ft_strchr("Ralrt", av[i]))
		{
			ft_printf("ft_ls: illegal option -- %c\n", av[i]);
			ft_putendl("usage: ft_ls [-Ralrt] [file ...]");
			if (opts)
				free(opts);
			return (0);
		}
		if (!ft_strchr(opts, av[i]))
		{
			if (!(opts = ft_strcat(opts, &av[i])))
			{
				if (opts)
					free(opts);
				return (0);
			}
		}
		i++;
	}
	return (opts);
}

char		*get_opts(int ac, char **av)
{
	char	*opts;
	int		i;

	i = 1;
	opts = 0;
	if (!(opts = ft_strnew(0)))
		return (0);
	while (i < ac && av[i][0] == '-' && av[i][1])
	{
		if (!(opts = split(av[i], opts)))
			return (0);
		i++;
	}
	return (opts);
}
