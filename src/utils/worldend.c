/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worldend.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:59:38 by rtissera          #+#    #+#             */
/*   Updated: 2024/04/21 18:14:22 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	mapend(t_map *map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	textureend(t_mlx *mlx, t_texture *texture)
{
	if (texture.north)
		mlx_destroy_image(mlx.mlx, texture.north);
	if (texture.south)
		mlx_destroy_image(mlx.mlx, texture.south);
	if (texture.west)
		mlx_destroy_image(mlx.mlx, texture.west);
	if (texture.east)
		mlx_destroy_image(mlx.mlx, texture.east);
	if (world.texture.floor)
		free(world.texture.floor);
	if (world.texture.ceiling)
		free(world.texture.ceiling);
	free(world.texture);
}

void	mlxend(t_mlx *mlx)
{
	mlx_destroy_window(mlx.mlx, mlx.mlx_win);
	mlx_destroy_display(mlx.mlx);
	free(mlx.mlx);
}

void	worldend(t_world *world)
{
	if (world)
	{
		if (world.map)
		{
			mapend(world.map);
		}
		if (world.texture)
		{
			textureend(world.mlx, world.texture);
		}
		if (world.mlx)
		{
			mlxend(world.mlx);
		}
		free(world);
	}
}
