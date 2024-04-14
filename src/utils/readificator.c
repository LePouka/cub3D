/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readificator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 19:00:16 by rtissera          #+#    #+#             */
/*   Updated: 2024/04/14 17:54:53 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_map	read_map(int fd)
{
	t_map	map;
	char	*line;
	char	*c_map;

	line = get_next_line(fd);
	if (!line)
		close_error(fd, "Cannot Read The Map\n");
	while (line)
	{
		if (!c_map)
			c_map = ft_substr(line, 0, ft_strlen(line));
		else
			c_map = free_strjoin(c_map, line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	map.map = ft_split(c_map, '\n');
	free(c_map);
	return (map);
}
