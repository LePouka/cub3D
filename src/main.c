/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:58:55 by rshay             #+#    #+#             */
/*   Updated: 2024/05/31 17:38:01 by rshay            ###   ########.fr       */
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

void	init_rays(t_rays *rays, t_world *world)
{
	rays->width = world->map->lig;
	rays->c_color = world->color->ceiling;
	rays->f_color = world->color->floor;
	rays->pos_x = world->map->player_x;
	rays->pos_y = world->map->player_y;
	rays->dir_x = -1;
	rays->dir_y = 0;
	rays->plane_x = 0;
	rays->plane_y = 0.66;
	rays->move_speed = 0;
	rays->time = 0;
	rays->old_time = 0;
	rays->world_map = world->map->i_map;
	for (int i = 0; i < world->map->lig; i++) {
		for (size_t j = 0; j < world->map->len; j++) {
			if (rays->world_map[i][j] != 1 && rays->world_map[i][j] != 0)
				rays->world_map[i][j] = 0;
		}
	}
}

void	vars_init(t_rays *rays, t_world *world)
{
	void		*mlx;
	t_data		img;
	u_int32_t	**buffer;
	int			i;
	void		*mlx_win;
	t_vars 		vars;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, SCREENWIDTH, SCREENHEIGHT, "Cub3d");
	vars.img = &img;
	vars.mlx = mlx;
	vars.win = mlx_win;
	rays->vars = &vars;
	init(rays);
	buffer = malloc(SCREENHEIGHT * sizeof(int *));
	i = 0;
	while (i < SCREENHEIGHT)
	{
		buffer[i] = malloc(SCREENWIDTH * sizeof(int));
		i++;
	}
	rays->buffer = buffer;
	init_rays(rays, world);
	gameloop(rays, world);
}

void	gameloop(t_rays *rays, t_world *world)
{

	rays->texture = world->texture;
	if (world->map->player_p == 'N')
		rotate(-15,rays);
	if (world->map->player_p == 'S')
		rotate(15, rays);
	if (world->map->player_p == 'E')
		rotate(30, rays);
	mlx_loop_hook(rays->vars->mlx, &casting, rays);
	mlx_hook(rays->vars->win, 2, 1L << 0, clavier, rays);
	mlx_hook(rays->vars->win, 17, 1L << 0, close_win, rays->vars->mlx);
	mlx_loop(rays->vars->mlx);
	free_data(rays);
	mlx_destroy_image(rays->vars->mlx, rays->vars->img->img);
	mlx_destroy_window(rays->vars->mlx, rays->vars->win);
	mlx_destroy_display(rays->vars->mlx);
	free(rays->vars->mlx);
	worldend(world);
}

int	main(int argc, char **argv)
{
	t_rays		rays;
	t_world		*world;

	if (argc != 2) {
		ft_dprintf(2, "Error\nBad Arguments\n");
 		return (-1);
	}
	world = worldinit(argv[1]);
	vars_init(&rays, world);
}
