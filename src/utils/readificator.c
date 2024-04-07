/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readificator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 19:00:16 by rtissera          #+#    #+#             */
/*   Updated: 2024/04/07 19:05:41 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_map	read_map(int fd)
{
	t_map	map;

	line = get_next_line(fd);
	if (!line)
		return (close_error(fd, "Cannot Read The Map\n"))
	map.x = 0;
	map.y = 0;
	while (line)
	{
		if (!map.y && line[0])
			map.y = ft_strlen(line) - 1;
		if (map.x == 0)
			c_map = ft_substr(line, 0, ft_strlen(line));
		else
			c_map = free_strjoin(c_map, line);
		map.x++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (map.x == 0)
		close_free_error(fd, c_map, "Empty Map\n");
	map.map = ft_split(c_map, '\n');
	map.mv_nb = 0;
	return (free(c_map), map);
}
