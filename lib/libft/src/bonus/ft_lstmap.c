/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:57:54 by rtissera          #+#    #+#             */
/*   Updated: 2023/05/26 16:07:08 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_new;
	t_list	*lst_bank;

	if (!lst || !f || !del)
		return (0);
	lst_new = 0;
	while (lst)
	{
		lst_bank = ft_lstnew((*f)(lst->content));
		if (!lst_bank)
		{
			ft_lstclear(&lst_bank, (*del));
			return (0);
		}
		ft_lstadd_back(&lst_new, lst_bank);
		lst = lst->next;
	}
	return (lst_new);
}
