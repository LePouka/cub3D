/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphael <raphael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:18:17 by rtissera          #+#    #+#             */
/*   Updated: 2023/06/28 17:01:10 by raphael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

t_buff	*ft_bufflast(t_buff *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_buffadd_back(t_buff **lst, t_buff *new)
{
	t_buff	*last_lst;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last_lst = ft_bufflast(*lst);
	last_lst->next = new;
}

void	clear_old_line(t_buff **lst)
{
	int		i;
	int		size_old_line;
	t_buff	*lst_next;

	if (!*lst)
		return ;
	size_old_line = linelen(lst, 2);
	while (size_old_line - BUFFER_SIZE > 0
		|| (*lst)->buf[size_old_line] == '\0')
	{
		lst_next = (*lst)->next;
		free(*lst);
		*lst = lst_next;
		if (!(*lst))
			return ;
		size_old_line = linelen(lst, 2);
	}
	i = -1;
	size_old_line = linelen(lst, 1);
	while ((*lst)->buf[size_old_line + i++])
		(*lst)->buf[i] = (*lst)->buf[i + size_old_line];
	(*lst)->buf[i] = '\0';
}
