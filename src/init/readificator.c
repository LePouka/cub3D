/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readificator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 19:00:16 by rtissera          #+#    #+#             */
/*   Updated: 2024/05/02 15:25:42 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	close_error(int fd, char *s)
{
	close(fd);
	return (ft_error(s));
}

void	close_free_error(int fd, char *s1, char *s2)
{
	free(s1);
	close_error(fd, s2);
}

char	*free_strjoin(char *s1, char *s2)
{
	char	*s3;

	s3 = ft_strjoin(s1, s2);
	free(s1);
	return (s3);
}

t_map	*mapificator(char **c_map)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map *));
	if (!map)
	{
		free(map);
		ft_error(strerror(errno));
		return (NULL);
	}
	map->map = ft_split(c_map, '\n');
	free(c_map);
	map->i_map = char_to_int(map->map, -1, 0);
	return (map);
}

t_map	*readificator(char *file_name)
{
	int		fd;
	char	*line;
	char	*c_map;

	fd = openificator(file_name);
	if (fd == -1)
		return (false);
	line = get_next_line(fd);
	if (!line)
		close_error(fd, strerror(errno));
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
