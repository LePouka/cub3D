/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:58:55 by rshay             #+#    #+#             */
/*   Updated: 2024/05/28 17:13:40 by rshay            ###   ########.fr       */
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
	void		*mlx;
	t_data		img;
	t_rays		rays;
	void		*mlx_win;
	int			**texture;
	u_int32_t	**buffer;
	t_vars 		vars;
	t_world		*world;
	int			i;

	if (argc != 2) {
		ft_dprintf(2, "Error\nBad Arguments\n");
 		return (-1);
	}
	texture = malloc(8 * sizeof(int *));
	buffer = malloc(SCREENHEIGHT * sizeof(int *));
	i = 0;
	while (i < SCREENHEIGHT)
	{
		buffer[i] = malloc(SCREENWIDTH * sizeof(int));
		i++;
	}
	world = worldinit(argv[1]);
	rays.buffer = buffer;
	rays.pos_x = 12;
	rays.pos_y = 12;
	rays.dir_x = -1;
	rays.dir_y = 0;
	rays.plane_x = 0;
	rays.plane_y = 0.66;
	rays.move_speed = 0;
	rays.time = 0;
	rays.old_time = 0;
	rays.world_map = world->map->i_map;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, SCREENWIDTH, SCREENHEIGHT, "Cub3d");
	vars.img = &img;
	vars.mlx = mlx;
	vars.win = mlx_win;
	rays.vars = &vars;
	init(&rays);
	init_texturing(texture, &rays);
	rays.texture = texture;
	rotate(-15,&rays);
	mlx_loop_hook(mlx, &casting, &rays);
	mlx_hook(rays.vars->win, 2, 1L << 0, clavier, &rays);
	mlx_hook(mlx_win, 17, 1L << 0, close_win, mlx);
	mlx_loop(mlx);
	free_data(&rays);
	mlx_destroy_image(mlx, img.img);
	mlx_destroy_window(mlx, mlx_win);
	mlx_destroy_display(mlx);
	free(mlx);
}

// int	main(int argc, char **argv)
// {
// 	t_world	*world;
// 	if (argc == 2)
// 	{
// 		world = worldinit(argv[1]);
// 		parsingator(world);
// 		worldend(world);
// 	}
// 	else
// 	{
// 		ft_dprintf(2, "Error\nBad Arguments\n");
// 		return (-1);
// 	}
// 	return (0);
// }
