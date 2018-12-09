/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 12:29:29 by tduval            #+#    #+#             */
/*   Updated: 2018/12/09 13:36:44 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"

int			check_opts(char *options)
{
	int	i;

	i = 0;
	while (options[i])
	{
		if (!(ft_strchr("lRart", options[i])))
		{
			ft_printf("Invalid option : %c\n", options[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

t_params	get_args(int ac, char **av)
{
	t_params	ret;
	int			i;
	int			j;

	ret.opts = 0;
	ret.paths = 0;
	ret.err = 0;
	i = 1;
	j = 0;
	if (*av[i] == '-')
	{	if (!(ret.opts = ft_strdup(av[i] + 1)) || !(check_opts(ret.opts)))
		{
			ret.err = 1;
			return (ret);
		}
		i++;
	}
	if (!(ret.paths = (char **)malloc(sizeof(char *) * (ac - i + 1))))
	{
		ret.err = 1;
		return (ret);
	}
	while (i < ac)
	{
		if (!(ret.paths[j] = ft_strdup(av[i])))
		{
			ret.err = 1;
			return (ret);
		}
		i++;
		j++;
	}
	ret.paths[i] = 0;
	return (ret);
}

int			main(int ac, char **av)
{
	t_params	p;
/*
	if (ac < 2)
		ft_ls_nomod();
	else*/
	p = get_args(ac, av);
	if (p.err)
		return (0);
	return (0);
}
