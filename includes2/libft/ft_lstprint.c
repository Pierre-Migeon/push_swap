/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 13:37:50 by pmigeon           #+#    #+#             */
/*   Updated: 2018/11/06 13:39:20 by pmigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_lstprint(t_list *lst)
{
	while (lst)
	{
		write(1, lst->content, lst->content_size);
		lst = lst->next;
	}
	write(1, "\n", 1);
}
