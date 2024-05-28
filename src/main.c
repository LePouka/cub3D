/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:58:55 by rshay             #+#    #+#             */
/*   Updated: 2024/05/28 15:47:37 by rshay            ###   ########.fr       */
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

void	floor_casting(t_rays *rays)
{
	for(int y = 0; y < SCREENHEIGHT; y++)
    {
		float rayDirX0 = rays->dir_x - rays->plane_x;
		float rayDirY0 = rays->dir_y - rays->plane_y;
		float rayDirX1 = rays->dir_x + rays->plane_x;
		float rayDirY1 = rays->dir_y + rays->plane_y;
		int p = y - SCREENHEIGHT / 2;
		float posZ = 0.5 * SCREENHEIGHT;
		float rowDistance = posZ / p;
		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / SCREENWIDTH;
		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / SCREENWIDTH;
		float floorX = rays->pos_x + rowDistance * rayDirX0;
		float floorY = rays->pos_y + rowDistance * rayDirY0;
		for(int x = 0; x < SCREENWIDTH; ++x)
      {
        floorX += floorStepX;
        floorY += floorStepY;
        u_int32_t color;
		color = 0x0500FF00;
        color = (color >> 1) & 8355711;
        rays->buffer[y][x] = color;
		color = 0x00e11e00;
        color = (color >> 1) & 8355711;
        rays->buffer[SCREENHEIGHT - y - 1][x] = color;
      }
	}
}

int casting(t_rays *rays) {

  t_calcs	calcs;

	floor_casting(rays);


	for (int x = 0; x < SCREENWIDTH; x++) {

		init_calculating(&calcs, rays, x);
		init_side_dist(&calcs, rays);
		calculate_dda(&calcs, rays);
		drawing_calculations(&calcs, rays);
		for(int y = calcs.draw_start; y<calcs.draw_end; y++)
	  {
		int texY = (int)calcs.tex_pos & (TEXTHEIGHT - 1);
		calcs.tex_pos += calcs.step;
		u_int32_t color = rays->texture[calcs.tex_num][TEXTHEIGHT * texY + calcs.tex_x];
		if(calcs.side == 1) color = (color >> 1) & 8355711;
		rays->buffer[y][x] = color;
	  }
	  for (int y = 0; y < SCREENHEIGHT; y++) {
		my_mlx_pixel_put(rays->vars->img, x, y, rays->buffer[y][x]);
	  }

	}
	speed_calculation(rays);
	mlx_put_image_to_window(rays->vars->mlx, rays->vars->win, rays->vars->img->img, 0, 0);
	return (0);


}

/*int main(int argc, char **argv) {
	void	*mlx;
	t_data	img;
  	t_rays rays;
	void *mlx_win;
	int		**texture;
	t_world	*world;

	texture = malloc(8 * sizeof(int *));
	if (argc == 2)
	{
		;
	}
	world = worldinit(argv[1]);

	 int **world_map = world->map->i_map;
  {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
  	};

	u_int32_t	**buffer;
	buffer = malloc(SCREENHEIGHT * sizeof(int *));
	for (int i = 0;i < SCREENHEIGHT; i++) {
		buffer[i] = malloc(SCREENWIDTH * sizeof(int));
	}
	rays.buffer = buffer;

	double pos_x = 22, pos_y = 12;
	double dir_x = -1, dir_y = 0;
	double plane_x = 0, plane_y = 0.66;
	rays.pos_x = pos_x;
	rays.pos_y = pos_y;
	rays.dir_x = dir_x;
	rays.dir_y = dir_y;
	rays.plane_x = plane_x;
	rays.plane_y = plane_y;
	rays.move_speed = 0;
	rays.time = 0;
	rays.old_time = 0;

   int **heapmap = malloc(24 * sizeof(int *));

	for (int i = 0; i < 24; i++) {
	  heapmap[i] = malloc(24 * sizeof(int));
	  for (int j = 0; j < 24; j++) {
		heapmap[i][j] = world_map[i][j];
	  }
	}
  rays.world_map = world_map;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, SCREENWIDTH, SCREENHEIGHT, "Cub3d");
  t_vars vars;
  vars.img = &img;
  vars.mlx = mlx;
  vars.win = mlx_win;
  rays.vars = &vars;

  	init(&rays);
	init_texturing(texture, &rays);
	rays.texture = texture;
	mlx_loop_hook(mlx, &casting, &rays);
  	mlx_hook(rays.vars->win, 2, 1L << 0, clavier, &rays);
  	mlx_hook(mlx_win, 17, 1L<< 0, close_win, mlx);

	mlx_loop(mlx);
	free_data(&rays);
	mlx_destroy_image(mlx, img.img);
	mlx_destroy_window(mlx, mlx_win);
	mlx_destroy_display(mlx);
	free(mlx);
}*/

int	main(int argc, char **argv)
{
	t_world	*world;
	//void	*mlx;
	//t_data	img;
  	t_rays rays;
	//void *mlx_win;
	//int		**texture;
	if (argc == 2)
	{
		world = worldinit(argv[1]);
		rays.world_map = world->map->i_map;
		printf("%d\n", world->map->i_map[0][0]);
		worldend(world);
	}
	else
	{
		ft_dprintf(2, "Error\nBad Arguments\n");
		return (-1);
	}
	return (0);
}
