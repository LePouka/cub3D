/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorificator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:02:07 by rtissera          #+#    #+#             */
/*   Updated: 2024/05/09 14:15:40 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	is_color_valid(int color)
{
	return (color >= 0 && color <= 255);
}

bool	put_color(u_int32_t *color, int **rgb)
{
	if (!rgb || !is_color_valid(rgb[0]) || !is_color_valid(rgb[1]) || \
		is_valid_color(rgb[2]))
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

	if (!map || !map->map)
		return (NULL);
	if (strncmp("F ", map->map[5], 2) || strncmp("C ", map->map[6], 2))
	{
		ft_error(world, "Invalid Color Format");
	}
	color = (t_color *)malloc(sizeof(t_color) * 2);
	if (!color)
		ft_error(world, strerror(errno));
	if (!put_color(&color->floor, ft_arrtouille(world, ft_split(map->map[5] + \
		2, ','), -1, 0)) || !put_color(&color->ceiling, ft_arrtouille(world, \
		ft_split(map->map[6] + 2, ','), -1, 0)))
	{
		ft_error(world, "Invalid Color Format");
	}
	return (color);
}
