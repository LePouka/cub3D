/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorificator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:02:07 by rtissera          #+#    #+#             */
/*   Updated: 2024/05/24 17:28:27 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	is_color_valid(int* color)
{
	int	i;

	i = 0;
	while (color[i])
	{
		if (!(color[i] > 0 && color[i] < 255))
		{
			return (false);
		}
		i++;
	}
	return (true);
}

bool	put_color(t_world *world, u_int32_t *color, char **c_rgb)
{
	int	**rgb;

	rgb = ft_arrtouille(world, c_rgb, -1, 0, 0);
	free_array(c_rgb);
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || !is_color_valid(rgb[0]) \
		|| !is_color_valid(rgb[1]) || is_color_valid(rgb[2]))
	{
		if (rgb)
		{
			free_int_array(rgb);
		}
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
	if (strncmp("F ", map->map[4], 2) || strncmp("C ", map->map[5], 2))
	{
		ft_error(world, "Invalid Color Format");
	}
	color = (t_color *)malloc(sizeof(t_color) * 2);
	if (!color)
		ft_error(world, strerror(errno));
	if (!put_color(world, &color->floor, ft_split(map->map[4] + 2, ',')) \
		|| !put_color(world, &color->ceiling, ft_split(map->map[5] + 2, ',')))
	{
		ft_error(world, "Invalid Color Format");
	}
	return (color);
}
