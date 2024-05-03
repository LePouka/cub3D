/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorificator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:02:07 by rtissera          #+#    #+#             */
/*   Updated: 2024/05/03 18:14:16 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	put_color(u_int32_t *color, int **rgb)
{
	if (!rgb)
	{
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

t_color	*colorificator(t_map *map)
{
	t_color		*color;

	if (strncmp("F ", map->map[5], 2) || strncmp("C ", map->map[6], 2))
	{
		return (ft_error("map: Invalid Color Format"), NULL);
	}
	color = (t_color *)malloc(sizeof(t_color) * 2);
	if (!color)
		return (ft_error(strerror(errno)), NULL);
	if (!put_color(&color->floor, ft_arrtouille(ft_split(map->map[5] + 2, ','), \
		-1, 0)) || !put_color(&color->ceiling, ft_arrtouille(ft_split(map->map[6] \
		+ 2, ','), -1, 0)))
	{
		return (NULL);
	}
	return (color);
}
