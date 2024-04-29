/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturificator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:02:16 by rtissera          #+#    #+#             */
/*   Updated: 2024/04/29 04:27:36 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_get_data_addr(t_world *world)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		world.texture[i] = (int *)mlx_get_data_addr(rays->pics[i].img, \
			&(rays->pics[i]).bpp, &(rays->pics[i]).l, &(rays->pics[i]).endian);
		i++;
	}
}

bool	texturificator(t_world *world, t_map *map)
{
	int	th;
	int	tw;

	if (!world || !map->map)
		return (false);
	if (strncmp("NO ./", map->map[0], 5) || strncmp("SO ./", map->map[1], 5) || \
		strncmp("WE ./", map->map[2], 5) || strncmp("EA ./", map->map[3], 5))
	{
		return (ft_error("map: Invalid Texture Format"), false);
	}
	world.pics = (t_data *)malloc(sizeof(t_data) * 8);
	if (!texture)
		return (ft_error(strerror(errno)), false);
	world.pics[0] = mlx_xpm_file_to_image(world->mlx, map->map[0] + 5, &tw, \
		&th);
	world.pics[1] = mlx_xpm_file_to_image(world->mlx, map->map[1] + 5, &tw, \
		&th);
	world.pics[2] = mlx_xpm_file_to_image(world->mlx, map->map[2] + 5, &tw, \
		&th);
	world.pics[3] = mlx_xpm_file_to_image(world->mlx, map->map[3] + 5, &tw, \
		&th);
	ft_get_data_addr(world);
	return (true);
}
