/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worldend.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42->fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:59:38 by rtissera          #+#    #+#             */
/*   Updated: 2024/04/29 04:43:34 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	mapend(t_map *map)
{
	int	i;

	i = 0;
	while (map->map[i])
	{
		free(map->map[i]);
		i++;
	}
	free(map->map);
	free(map);
}

void	textureend(t_mlx *mlx, t_data *pics)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		mlx_destroy_image(mlx.mlx, pics[i].img);
		i++;
	}
	free(pics);
}

void	mlxend(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
}

void	worldend(t_world *world)
{
	if (world)
	{
		if (world->map)
		{
			mapend(world->map);
		}
		if (world->texture)
		{
			textureend(world->mlx, world->pics);
		}
		if (world->mlx)
		{
			mlxend(world->mlx);
		}
		free(world);
	}
}
