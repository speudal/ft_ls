/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <tduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 18:31:23 by tduval            #+#    #+#             */
/*   Updated: 2018/12/16 04:10:05 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"
#include "libft.h"

t_inf		*get_files(char **av, char *opts)
{
	t_inf	*beg;
	t_inf	*fils;
	int		i;
	int		j;

	i = 0;
	j = 0;
	beg = 0;
	fils = 0;
	while (av[i])
	{
		if (!fils)
		{
			fils = fil_new(av[i], opts );
			beg = fils;
		}
		else
		{
			fils->next = fil_new(av[i], opts);
			if (fils->next)
				fils = fils->next;
		}
		i++;
	}
	beg = sort_alpha(beg);
	return (beg);
}
