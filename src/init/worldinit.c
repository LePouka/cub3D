/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worldinit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:06:35 by rtissera          #+#    #+#             */
/*   Updated: 2024/04/28 19:21:52 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_world	*worldinit(char *file_name)
{
	t_world	*world;

	world = (t_world *)malloc(sizeof(t_world));
	if (!world)
	{
		ft_error(strerror(errno));
		return (NULL);
	}
	world->map = readificator(file_name);
	world->mlx = mlxator();
	if (!world->map || !world->mlx || !texturificator(world, world->map))
	{
		worldend(world);
		return (NULL);
	}
	return (world);
}
