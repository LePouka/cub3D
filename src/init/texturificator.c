/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturificator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:02:16 by rtissera          #+#    #+#             */
/*   Updated: 2024/05/03 17:51:09 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_data	*ft_get_data_addr(t_world *world, t_mlx *mlx, t_data *pics)
{
	int	i;

	if (!pics[0].img || !pics[1].img || !pics[2].img || !pics[3].img)
	{
		ft_error("Failed Creating Images");
		return (NULL);
	}
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
			ft_error("Failed Getting Data Address");
			return (NULL);
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

	if (!world || !mlx || !mlx->mlx || !map || !map->map)
		return (NULL);
	if (strncmp("no ./", map->map[0], 5) || strncmp("so ./", map->map[1], 5) || \
		strncmp("we ./", map->map[2], 5) || strncmp("ea ./", map->map[3], 5))
	{
		return (ft_error("map: invalid texture format"), NULL);
	}
	pics = (t_data *)malloc(sizeof(t_data) * 4);
	if (!pics)
		return (ft_error(strerror(errno)), NULL);
	pics[0].img = mlx_xpm_file_to_image(mlx->mlx, map->map[0] + 5, &tw, \
		&th);
	pics[1].img = mlx_xpm_file_to_image(mlx->mlx, map->map[1] + 5, &tw, \
		&th);
	pics[2].img = mlx_xpm_file_to_image(mlx->mlx, map->map[2] + 5, &tw, \
		&th);
	pics[3].img = mlx_xpm_file_to_image(mlx->mlx, map->map[3] + 5, &tw, \
		&th);
	return (ft_get_data_addr(world, world->mlx, pics));
}
