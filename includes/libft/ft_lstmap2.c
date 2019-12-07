/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 20:48:05 by pmigeon           #+#    #+#             */
/*   Updated: 2018/11/06 15:42:29 by pmigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap2(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *exit;

	if (lst)
	{
		exit = f(lst);
		exit->next = ft_lstmap2(lst->next, f);
		return (exit);
	}
	return (NULL);
}
