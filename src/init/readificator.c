/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readificator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 19:00:16 by rtissera          #+#    #+#             */
/*   Updated: 2024/05/06 15:56:51 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*sizeificator(char *s1, int len)
{
	char	*s2;
	int		i;

	s2 = (char *)malloc(sizeof(char) * len + 1);
	i = 0;
	while (i < len)
	{
		if (s1[i])
			s2[i] = s1[i];
		else
			s2[i] = '1';
		i++;
	}
	s2[i] = '\0';
	free(s1);
	return (s2);
}

void	to_rectangle(t_map *map)
{
	int	i;
	int	j;

	i = 8;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j] && map->map[i][j] == ' ')
		{
			map->map[i][j] = '1';
			j++;
		}
		if (ft_strlen(map->map[i]) != map->len)
		{
			map->map[i] = sizeificator(map->map[i], map->len);
		}
		i++;
	}
}

t_map	*mapificator(char *c_map)
{
	int		i;
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map *));
	if (!map)
	{
		free(c_map);
		return (ft_error(strerror(errno)), NULL);
	}
	map->map = ft_split(c_map, '\n');
	free(c_map);
	map->len = ft_strlen(map->map[8]);
	i = 1;
	while (map->map[i])
	{
		if (i > 8 && ft_strlen(map->map[i]) > map->len)
			map->len = ft_strlen(map->map[i]);
		i++;
	}
	to_rectangle(map);
	map->i_map = ft_arrtouille(map->map + 8, -1, 0);
	return (map);
}

t_map	*readificator(char *file_name)
{
	int		fd;
	char	*line;
	char	*c_map;

	fd = openificator(file_name);
	if (fd == -1)
		return (NULL);
	line = get_next_line(fd);
	if (!line)
		return (close_error(fd, strerror(errno)), NULL);
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
	return (mapificator(c_map));
}
