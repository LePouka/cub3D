/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorificator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:02:07 by rtissera          #+#    #+#             */
/*   Updated: 2024/05/20 17:59:13 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	is_color_valid(int* color)
{
	int	i;

	i = 0;
	while (color[i])
	{
		if (color[i] < 0 || color[i] > 255)
		{
			return (false);
		}
		i++;
	}
	return (true);
}

bool	put_color(u_int32_t *color, int **rgb)
{
	if (!rgb || !is_color_valid(rgb[0]) || !is_color_valid(rgb[1]) \
		|| is_color_valid(rgb[2]))
	{
		free_int_array(rgb);
		return (false);
	}
	*color = 0;
	*color |= *rgb[0] & 0xFF;
	*color |= (*rgb[1] & 0xFF) << 16;
	*color |= (*rgb[2] & 0xFF) << 8;
	*color |= (0 & 0xFF) << 24;
	free_int_array(rgb);
	return (true);
}

t_color	*colorificator(t_world *world, t_map *map)
{
	t_color	*color;
	char	**map_five;
	char	**map_six;

	if (!map || !map->map)
		return (NULL);
	if (strncmp("F ", map->map[5], 2) || strncmp("C ", map->map[6], 2))
	{
		ft_error(world, "Invalid Color Format");
	}
	color = (t_color *)malloc(sizeof(t_color) * 2);
	if (!color)
		ft_error(world, strerror(errno));
	map_five = ft_split(map->map[5] + 2, ',');
	map_six = ft_split(map->map[6] + 2, ',');
	if (!put_color(&color->floor, ft_arrtouille(world, map_five, -1, 0, 0)) \
		|| !put_color(&color->ceiling, ft_arrtouille(world, map_six, -1, 0, 0)))
	{
		free_array(map_five);
		free_array(map_six);
		ft_error(world, "Invalid Color Format");
	}
	free_array(map_five);
	free_array(map_six);
	return (color);
}
