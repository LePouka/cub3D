/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worldinit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:06:35 by rtissera          #+#    #+#             */
/*   Updated: 2024/05/06 17:26:53 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_world	*worldinit(char *file_name)
{
	t_world	*world;

	world = (t_world *)malloc(sizeof(t_world));
	if (!world)
	{
		ft_error(NULL, strerror(errno));
	}
	world->map = readificator(world, file_name);
	world->mlx = mlxator(world);
	world->pics = texturificator(world, world->mlx, world->map);
	world->color = colorificator(world, world->map);
	if (!world->map || !world->mlx || !world->pics || !world->color)
	{
		ft_error(world, "Initialisation Error");
	}
	return (world);
}
