/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:18:54 by rtissera          #+#    #+#             */
/*   Updated: 2023/09/01 07:09:33 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*read_error(t_buff **lst)
{
	t_buff	*lst_next;
	t_buff	*lst_current;

	if (!lst || !*lst)
		return (NULL);
	lst_current = *lst;
	while (lst_current)
	{
		lst_next = lst_current->next;
		free(lst_current);
		lst_current = lst_next;
	}
	*lst = NULL;
	return (NULL);
}

int	linelen(t_buff **lst, int boool)
{
	int		i;
	int		size;
	t_buff	*lst_current;

	i = 0;
	size = 0;
	lst_current = *lst;
	while (lst_current && lst_current->buf[i])
	{
		if (lst_current->buf[i] == '\n')
			return (size + 1);
		i++;
		size++;
		if (!lst_current->buf[i] && boool == 2)
			return (size);
		if (!lst_current->buf[i] && lst_current->next)
		{
			lst_current = lst_current->next;
			i = 0;
		}
	}
	return (-size);
}

t_buff	*read_line(t_buff **lst, int fd)
{
	int		bytes;
	t_buff	*new;

	while (linelen(lst, 1) <= 0)
	{
		new = malloc(sizeof(t_buff));
		if (!new)
			return (read_error(lst), NULL);
		new->buf[0] = '\0';
		bytes = read(fd, new->buf, BUFFER_SIZE);
		if (bytes == -1)
			return (free(new), read_error(lst));
		if (bytes == 0)
		{
			free(new);
			break ;
		}
		new->buf[bytes] = '\0';
		new->next = NULL;
		ft_buffadd_back(lst, new);
	}
	return (*lst);
}

char	*put_in_line(t_buff **lst, int i, int j)
{
	int		size;
	char	*line;
	t_buff	*lst_current;

	size = linelen(lst, 1);
	if (size == 0)
		return (read_error(lst));
	else if (size < 0)
		size = size * -1;
	line = malloc(sizeof(char) * size + 1);
	lst_current = *lst;
	while (i < size)
	{
		line[i] = (lst_current)->buf[j];
		i++;
		j++;
		if (!(lst_current)->buf[j])
		{
			lst_current = lst_current->next;
			j = 0;
		}
	}
	return (line[i] = '\0', line);
}

char	*get_next_line(int fd)
{
	char			*line;
	static t_buff	*lst[1024];

	if (fd >= 1024 || fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	lst[fd] = read_line(&lst[fd], fd);
	if (!lst[fd])
		return (NULL);
	line = put_in_line(&lst[fd], 0, 0);
	if (!line)
		return (NULL);
	clear_old_line(&lst[fd]);
	return (line);
}
