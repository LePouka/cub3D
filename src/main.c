/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:58:55 by rshay             #+#    #+#             */
/*   Updated: 2024/06/03 18:33:22 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"
#include <sys/types.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->l + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	main(int argc, char **argv)
{
	t_data		img;
	t_rays		rays;
	u_int32_t	**buffer;
	t_vars 		vars;
	t_world		*world;
	int			i;

	if (argc != 2) {
		ft_dprintf(2, "Error\nBad Arguments\n");
 		return (-1);
	}
	buffer = malloc(SCREENHEIGHT * sizeof(int *));
	i = 0;
	while (i < SCREENHEIGHT)
	{
		buffer[i] = malloc(SCREENWIDTH * sizeof(int));
		i++;
	}
	world = worldinit(argv[1]);
	rays.buffer = buffer;
	rays.width = world->map->lig;
	rays.c_color = world->color->ceiling;
	rays.f_color = world->color->floor;
	rays.pos_x = world->map->player_y;
	rays.pos_y = world->map->player_x;
	rays.dir_x = -1;
	rays.dir_y = 0;
	rays.plane_x = 0;
	rays.plane_y = 0.66;
	rays.move_speed = 0;
	rays.time = 0;
	rays.old_time = 0;
	rays.world_map = map_rotate(*world, world->map->i_map);
	for (int i = 0; i < world->map->lig; i++) {
		for (size_t j = 0; j < world->map->len; j++) {
			if (rays.world_map[i][j] != 1 && rays.world_map[i][j] != 0)
				rays.world_map[i][j] = 0;
		}
	}
	vars.img = &img;
	vars.mlx = world->mlx->mlx;
	vars.win = world->mlx->mlx_win;
	rays.vars = &vars;
	rays.vars->mlx = world->mlx->mlx;
	world->rays = &rays;
	init(&rays);
	rays.texture = world->texture;
	if (world->map->player_p == 'N')
		rotate(-15,&rays);
	if (world->map->player_p == 'S')
		rotate(15, &rays);
	if (world->map->player_p == 'E')
		rotate(30, &rays);
	mlx_loop_hook(rays.vars->mlx, &casting, &rays);
	mlx_hook(rays.vars->win, 2, 1L << 0, clavier, &rays);
	mlx_hook(rays.vars->win, 17, 1L << 0, close_win, rays.vars->mlx);
	mlx_loop(rays.vars->mlx);
	worldend(world);
}
