/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttoupper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 14:42:10 by pmigeon           #+#    #+#             */
/*   Updated: 2018/11/06 14:42:21 by pmigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_list	*ft_lsttoupper(t_list *elem)
{
	if (*(char *)elem->content >= 'a' && *(char *)elem->content <= 'z')
		*(char *)elem->content -= 32;
	return (elem);
}
