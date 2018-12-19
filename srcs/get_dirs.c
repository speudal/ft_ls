/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dirs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <tduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 18:51:28 by tduval            #+#    #+#             */
/*   Updated: 2018/12/18 04:01:15 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"
#include "libft.h"

t_inf		*get_dirs(char **av, char opts)
{
	t_inf	*beg;
	t_inf	*dirs;
	int		i;

	i = 0;
	beg = 0;
	dirs = 0;
	while (av[i])
	{
		if (!dirs)
		{
			dirs = dir_new(av[i], opts);
			beg = dirs;
		}
		else
		{
			dirs->next = dir_new(av[i], opts);
			if (dirs->next)
				dirs = dirs->next;
		}
		i++;
	}
	beg = sort_alpha(beg);
	return (beg);
}
