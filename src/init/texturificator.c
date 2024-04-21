/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturificator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:02:16 by rtissera          #+#    #+#             */
/*   Updated: 2024/04/21 19:05:17 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_texture	*texturificator(t_world *world, t_map *map)
{
	t_texture	*texture;

	if (!world || !map)
		return (NULL);
	if (strncmp("NO ./", map[0], 5) || strncmp("SO ./", map[1], 5) || \
		strncmp("WE ./", map[2], 5) || strncmp("EA ./", map[3], 5) || \
		strncmp("F ", map[5], 2) || strncmp("C ", map[6], 2))
	{
		return (ft_error("Map: Invalid Format"), NULL);
	}
	texture = (t_texture *)malloc(sizeof(t_texture *));
	if (!texture)
		return (ft_error(strerror(errno)), NULL);
	texture.north = mlx_xpm_file_to_image(world.mlx, map[0] + 5, \
		&World.width, &world.height);
	texture.south = mlx_xpm_file_to_image(world.mlx, map[1] + 5, \
		&World.width, &world.height);
	texture.west = mlx_xpm_file_to_image(world.mlx, map[2] + 5, \
		&World.width, &world.height);
	texture.east = mlx_xpm_file_to_image(world.mlx, map[3] + 5, \
		&World.width, &world.height);
	texture.floor = ft_strdup(map[5] + 2);
	texture.ceiling = ft_strdup(map[6] + 2);
	return (world);
}
