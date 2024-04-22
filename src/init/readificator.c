/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readificator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 19:00:16 by rtissera          #+#    #+#             */
/*   Updated: 2024/04/22 15:29:38 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	openificator(char *file_name)
{
	int		fd;

	if (file_name == NULL || file_name[0] == 0)
	{
		return (ft_error("Invalid file input"));
	}
	if (ft_strncmp(file_name + ft_strlen(file_name) - 4, ".cub", 4))
	{
		return (ft_error("Invalid file extension"));
	}
	fd = open(file_name, O_RDONLY, 0777);
	if (fd == -1)
	{
		return (ft_error(strerror(errno)));
	}
	return (fd);
}

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

t_map	*readificator(char *file_name)
{
	int		fd;
	char	*line;
	char	*c_map;
	t_map	*map;

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
	map = (t_map *)malloc(sizeof(t_map *));
	map->map = ft_split(c_map, '\n');
	return (free(c_map), map);
}
