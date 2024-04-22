/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturificator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:02:16 by rtissera          #+#    #+#             */
/*   Updated: 2024/04/22 17:00:18 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

	for (int i = 0; i < 7; i++) {
		texture[i] = (int *)mlx_get_data_addr(rays->pics[i].img, \
		&(rays->pics[i]).bpp, &(rays->pics[i]).l, &(rays->pics[i]).endian);
	}

t_texture	*texturificator(t_world *world, t_map *map)
{
	t_texture	*texture;
	int			th;
	int			tw;

	if (!world || !map->map)
		return (NULL);
	if (strncmp("NO ./", map->map[0], 5) || strncmp("SO ./", map->map[1], 5) || \
		strncmp("WE ./", map->map[2], 5) || strncmp("EA ./", map->map[3], 5) || \
		strncmp("F ", map->map[5], 2) || strncmp("C ", map->map[6], 2))
	{
		return (ft_error("map->map: Invalid Format"), NULL);
	}
	texture = (t_texture *)malloc(sizeof(t_texture *));
	if (!texture)
		return (ft_error(strerror(errno)), NULL);
	texture->north = mlx_xpm_file_to_image(world->mlx, map->map[0] + 5, &tw, \
		&th);
	texture->south = mlx_xpm_file_to_image(world->mlx, map->map[1] + 5, &tw, \
		&th);
	texture->west = mlx_xpm_file_to_image(world->mlx, map->map[2] + 5, &tw, \
		&th);
	texture->east = mlx_xpm_file_to_image(world->mlx, map->map[3] + 5, &tw, \
		&th);
	texture->floor = ft_strdup(map->map[5] + 2);
	texture->ceiling = ft_strdup(map->map[6] + 2);
	return (world);
}
