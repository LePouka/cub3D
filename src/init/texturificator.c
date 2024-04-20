/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturificator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:02:16 by rtissera          #+#    #+#             */
/*   Updated: 2024/04/20 18:30:56 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_texture	*texturificator(t_world world, char **map)
{
	t_texture	*texture;

	if (strncmp("NO ./", map[0], 5) || strncmp("SO ./", map[1], 5) || \
		strncmp("WE ./", map[2], 5) || strncmp("EA ./", map[3], 5) || \
		strncmp("F ", map[5], 2) || strncmp("C ", map[6], 2))
	{
		ft_error("Map: Invalid Format");
		return (NULL);
	}
	texture = (t_texture *)malloc(sizeof(t_texture *));
	if (!texture)
	{
		ft_error(strerror(errno));
		return (NULL);
	}
	texture.NO = mlx_xpm_file_to_image(world.mlx, texture.NO, &World.width, \
		&world.height);
	texture.SO = mlx_xpm_file_to_image(world.mlx, texture.SO, &World.width, \
		&world.height);
	texture.WE = mlx_xpm_file_to_image(world.mlx, texture.WE, &World.width, \
		&world.height);
	texture.EA = mlx_xpm_file_to_image(world.mlx, texture.EA, &World.width, \
		&world.height);
	if (!texture.NO || !texture.SO || !texture.WE || !texture.EA)
	{
		ft_error("Cannot Create Images");
		return (NULL);
	}
	return (world);
}
