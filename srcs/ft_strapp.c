/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strapp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 23:59:56 by tduval            #+#    #+#             */
/*   Updated: 2018/12/17 00:20:18 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strapp(char *str, char c)
{
	char	*new;
	int		i;

	i = 0;
	if (!(new = ft_strnew(sizeof(char) * (ft_strlen(str) + 2))))
		return (0);
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = c;
	new[i + 1] = '\0';
	return (new);
}
