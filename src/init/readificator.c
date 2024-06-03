/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readificator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 19:00:16 by rtissera          #+#    #+#             */
/*   Updated: 2024/06/03 18:38:06 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*sizeificator(t_world *world, char *s1, int len)
{
	char	*s2;
	int		i;

	s2 = (char *)malloc(sizeof(char) * (len + 1));
	if (!s2)
		ft_error(world, strerror(errno));
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	while (i < len)
	{
		s2[i] = ' ';
		i++;
	}
	s2[i] = '\0';
	free(s1);
	return (s2);
}

void	to_rectangle(t_world *world, t_map *map)
{
	int	i;

    map->lig = 0;
	i = 6;
	while (map->map[i])
	{
		if (ft_strlen(map->map[i]) != map->len)
		{
			map->map[i] = sizeificator(world, map->map[i], map->len);
		}
        map->lig++;
		i++;
	}
}

t_map	*mapificator(t_world *world, char *c_map, int i)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
	{
		free(c_map);
		ft_error(world, strerror(errno));
	}
	map->map = ft_split(c_map, '\n');
	if (!map->map || !map->map[6])
		ft_error(world, "Invalid Map Format");
	free(c_map);
	map->len = ft_strlen(map->map[6]);
	while (map->map[++i])
	{
		if (ft_strlen(map->map[i]) > map->len)
			map->len = ft_strlen(map->map[i]);
	}
	to_rectangle(world, map);
	map->i_map = ft_arrtouille(world, map->map, -1, 0, 6);
	//map->i_map = map_rotate(world, map->i_map);
	return (map);
}

t_map	*readificator(t_world *world, char *file_name)
{
	int		fd;
	char	*line;
	char	*c_map;

	fd = openificator(world, file_name);
	if (fd == -1)
		ft_error(world, strerror(errno));
	line = get_next_line(fd);
	if (!line)
		close_error(world, fd, strerror(errno));
	c_map = NULL;
	while (line)
	{
		if (c_map)
			c_map = free_strjoin(c_map, line);
		else
			c_map = ft_substr(line, 0, ft_strlen(line));
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	free(line);
	return (mapificator(world, c_map, 5));
}
