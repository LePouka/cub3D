/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturificator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:02:16 by rtissera          #+#    #+#             */
/*   Updated: 2024/05/28 14:57:29 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_data	*ft_get_data_addr(t_world *world, t_mlx *mlx, t_data *pics)
{
	int	i;

	if (!pics[0].img || !pics[1].img || !pics[2].img || !pics[3].img)
	{
		ft_error(world, "Failed Creating Images");
	}
	world->texture = (int **)malloc(sizeof(int *) * 4);
	i = 0;
	while (i < 4)
	{
		world->texture[i] = (int *)mlx_get_data_addr(pics[i].img, \
			&(pics[i]).bpp, &(pics[i]).l, &(pics[i]).endian);
		if (!world->texture[i])
		{
			while (--i)
			{
				mlx_destroy_image(mlx->mlx, pics[i].img);
			}
			ft_error(world, "Failed Getting Data Address");
		}
		i++;
	}
	return (pics);
}

t_data	*texturificator(t_world *world, t_mlx *mlx, t_map *map)
{
	int		th;
	int		tw;
	t_data	*pics;

	if (!world || !mlx || !mlx->mlx || !map || !map->map || !map->map[0] \
		|| !map->map[1] || !map->map[2] || !map->map[3])
	{
		return (NULL);
	}
	if (strncmp("NO ./", map->map[0], 5) || strncmp("SO ./", map->map[1], 5) || \
		strncmp("WE ./", map->map[2], 5) || strncmp("EA ./", map->map[3], 5))
	{
		ft_error(world, "map: invalid texture format");
	}
	pics = (t_data *)malloc(sizeof(t_data) * 4);
	if (!pics)
	{
		ft_error(world, strerror(errno));
	}
	pics[0].img = mlx_xpm_file_to_image(mlx->mlx, map->map[0] + 5, &tw, &th);
	pics[1].img = mlx_xpm_file_to_image(mlx->mlx, map->map[1] + 5, &tw, &th);
	pics[2].img = mlx_xpm_file_to_image(mlx->mlx, map->map[2] + 5, &tw, &th);
	pics[3].img = mlx_xpm_file_to_image(mlx->mlx, map->map[3] + 5, &tw, &th);
	return (ft_get_data_addr(world, world->mlx, pics));
}
