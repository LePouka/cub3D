/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:58:55 by rshay             #+#    #+#             */
/*   Updated: 2024/05/31 16:56:56 by rshay            ###   ########.fr       */
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
	rays.width = world->map->lig;
	rays.c_color = world->color->ceiling;
	rays.f_color = world->color->floor;
	printf("ceiling = %d, floor = %d\n", (int)rays.c_color, (int)rays.f_color);
	printf("ceiling : t = %d, r = %d, g = %d, b = %d\n", (rays.c_color >> 24) & 0xFF, (rays.c_color >> 16) & 0xFF, (rays.c_color >> 8) & 0xFF, rays.c_color & 0xFF);
	rays.pos_x = world->map->player_x;
	rays.pos_y = world->map->player_y;
	printf("width = %zu, height = %d\n", world->map->len, world->map->lig);
	printf("p_x = %f, p_y = %f\n", rays.pos_x, rays.pos_y);
	rays.dir_x = -1;
	rays.dir_y = 0;
	rays.plane_x = 0;
	rays.plane_y = 0.66;
	rays.move_speed = 0;
	rays.time = 0;
	rays.old_time = 0;
	rays.world_map = world->map->i_map;
	printf("%d\n", world->map->i_map[0][0]);
	for (int i = 0; i < world->map->lig; i++) {
		for (size_t j = 0; j < world->map->len; j++) {
			if (rays.world_map[i][j] != 1 && rays.world_map[i][j] != 0)
				rays.world_map[i][j] = 0;
			printf("%d ", rays.world_map[i][j]);
		}
		printf("\n");
	}
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, SCREENWIDTH, SCREENHEIGHT, "Cub3d");
	vars.img = &img;
	vars.mlx = mlx;
	vars.win = mlx_win;
	rays.vars = &vars;
	init(&rays);
	init_texturing(texture, &rays);
	rays.texture = texture;
	if (world->map->player_p == 'N')
		rotate(-15,&rays);
	if (world->map->player_p == 'S')
		rotate(15, &rays);
	if (world->map->player_p == 'E')
		rotate(30, &rays);
	//move_y(-1, &rays);
	mlx_loop_hook(mlx, &casting, &rays);
	mlx_hook(rays.vars->win, 2, 1L << 0, clavier, &rays);
	mlx_hook(mlx_win, 17, 1L << 0, close_win, mlx);
	mlx_loop(mlx);
	free_data(&rays);
	mlx_destroy_image(mlx, img.img);
	mlx_destroy_window(mlx, mlx_win);
	mlx_destroy_display(mlx);
	free(mlx);
	worldend(world);
}
