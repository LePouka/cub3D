/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:33:19 by rtissera          #+#    #+#             */
/*   Updated: 2023/05/26 16:07:01 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

t_list	*ft_lstnew(char *content)
{
	int		i;
	t_list	*lst;

	if (!content)
		return (NULL);
	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	i = 0;
	while (content[i])
	{
		lst->content[i] = content[i];
		i++;
	}
	lst->content[i] = '\0';
	lst->next = NULL;
	return (lst);
}
