/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worldend.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:59:38 by rtissera          #+#    #+#             */
/*   Updated: 2024/06/03 20:28:21 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	mapend(t_map *map)
{
	if (map->map)
		free_array(map->map);
	if (map->i_map)
		free_int_array(map->i_map);
	free(map);
}

void	textureend(t_mlx *mlx, t_data *pics)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		mlx_destroy_image(mlx->mlx, pics[i].img);
		i++;
	}
	free(pics);
}

void	mlxend(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	free(mlx);
}

void	colorend(t_color *color)
{
	if (color)
	{
		free(color);
	}
}

void	worldend(t_world *world)
{
	if (world)
	{
		if (world->map)
			mapend(world->map);
		if (world->rays)
			raysend(world->rays);
		if (world->texture)
		{
			textureend(world->mlx, world->pics);
			free(world->texture);
		}
		if (world->mlx)
		{
			mlxend(world->mlx);
		}
		if (world->color)
		{
			colorend(world->color);
		}
		free(world);
	}
}
