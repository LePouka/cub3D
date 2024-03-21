/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:56:16 by rtissera          #+#    #+#             */
/*   Updated: 2024/03/19 21:24:41 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*lst_todel;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		lst_todel = (*lst)->next;
		ft_lstdelone(*lst, del);
		(*lst) = lst_todel;
	}
}
