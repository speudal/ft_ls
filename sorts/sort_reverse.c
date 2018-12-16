/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_reverse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 23:19:28 by tduval            #+#    #+#             */
/*   Updated: 2018/12/16 04:03:47 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"

t_inf	*sort_reverse(t_inf *lst)
{
	t_inf	*prev; 
	t_inf	*cur; 
	t_inf	*next; 

	prev = 0;
	cur = lst;
	while (cur) 
	{ 
		next = cur->next;   
		cur->next = prev;    
		prev = cur; 
		cur= next; 
	} 
	lst = prev; 
	return (lst);
}
