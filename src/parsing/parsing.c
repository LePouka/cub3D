/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:20:59 by rtissera          #+#    #+#             */
/*   Updated: 2024/05/26 19:02:01 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	spaceificator(t_world *world, char **line, int i, int j)
{
	if (line[i][j - 1] && line[i][j - 1] != ' ' && line[i][j - 1] != '1')
		ft_error(world, "Map Must Be Surrounded By Walls");
	if (line[i][j + 1] && line[i][j + 1] != ' ' && line[i][j + 1] != '1')
		ft_error(world, "Map Must Be Surrounded By Walls");
	if (i > 6 && line[i - 1] && line[i - 1][j] && line[i - 1][j] != ' ' \
		&& line[i - 1][j] != '1')
		ft_error(world, "Map Must Be Surrounded By Walls");
	if (line[i + 1] && line[i + 1][j] && line[i + 1][j] != ' ' \
		&& line[i + 1][j] != '1')
		ft_error(world, "Map Must Be Surrounded By Walls");
}

void	lineificator(t_world *world, t_map *map, char **line, int i)
{
	int	j;

	j = 0;
	while (line[i][j])
	{
		if (line[i][j] == ' ')
		{
			spaceificator(world, line, i, j);
		}
		else if (line[i][j] == 'N' || line[i][j] == 'S' \
				|| line[i][j] == 'E' || line[i][j] == 'W')
		{
			map->player_x = j;
			map->player_y = i - 6;
			if (map->player_p)
				ft_error(world, "Cannot Have More Than One Player Position");
			map->player_p = line[i][j];
		}
		else if (line[i][j] != '1' && line[i][j] != '0')
			ft_error(world, "Invalid Character");
		j++;
	}
}

void	parsingator(t_world *world, t_map *map)
{
	int	i;

	map->player_p = '\0';
	i = 6;
	while (map->map[i])
	{
		if (!map->map[i][0])
		{
			ft_error(world, "Cannot Have An Empty Line");
		}
		lineificator(world, map, map->map, i);
		i++;
	}
}
