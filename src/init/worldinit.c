/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worldinit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:06:35 by rtissera          #+#    #+#             */
/*   Updated: 2024/04/20 18:49:33 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"


t_world	*worldinit(char *file_name)
{
	int	fd;
	t_world	*world;

	world = (t_world *)malloc(sizeof(t_world));
	if (!world)
	{
		ft_error(strerror(errno));
		return (NULL);
	}
	fd = openificator(file_name);
	if (fd == -1)
	{
		return (false);
	}
	world.map = readificator(fd);
	close(fd);
	world.mlx = mlx_init();
	world.mlx_win = mlx_new_window(world.m, world.map.y * 80, world.map.x * 80, "Cub3D");
	world.width = 80 * world.map.p_y;
	world.height = 80 * world.map.p_x;
	world.texture = texturifictor(world.map);
	return (world);
}
