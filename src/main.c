/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:58:55 by rshay             #+#    #+#             */
/*   Updated: 2024/04/28 15:00:31 by rshay            ###   ########.fr       */
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

void free_data(t_rays *rays)
{
	for (int i = 0; i < MAPWIDTH; i++) {
		free(rays->world_map[i]);
	}
	free(rays->world_map);
	free(rays->texture);

	for (int i = 0; i < SCREENHEIGHT; i++) {
		free(rays->buffer[i]);
	}
	free(rays->buffer);
	for (int i = 0; i < 8; i++) {
		mlx_destroy_image(rays->vars->mlx, rays->pics[i].img);
	}
	free(rays->pics);

}

void calculate_dda(t_calcs *calcs, t_rays *rays)
{
	 while (calcs->hit == 0)
	{
		if (calcs->side_dist_x < calcs->side_dist_y)
		{
		  calcs->side_dist_x += calcs->delta_dist_x;
		  calcs->map_x += calcs->step_x;
		  calcs->side = 0;
		}
		else
		{
		  calcs->side_dist_y += calcs->delta_dist_y;
		  calcs->map_y += calcs->step_y;
		  calcs->side = 1;
		}
		if (rays->world_map[calcs->map_x][calcs->map_y] > 0) calcs->hit = 1;
	  }
}

void drawing_calculations(t_calcs *calcs, t_rays *rays)
{
	if(calcs->side == 0) calcs->perp_wall_dist = (calcs->side_dist_x - calcs->delta_dist_x);
	else		  calcs->perp_wall_dist = (calcs->side_dist_y - calcs->delta_dist_y);
	int lineHeight = (int)(SCREENHEIGHT / calcs->perp_wall_dist);
	calcs->draw_start = -lineHeight / 2 + SCREENHEIGHT / 2;
	if(calcs->draw_start < 0)calcs->draw_start = 0;
	calcs->draw_end = lineHeight / 2 + SCREENHEIGHT / 2;
	if(calcs->draw_end >= SCREENHEIGHT)calcs->draw_end = SCREENHEIGHT - 1;
	calcs->tex_num = rays->world_map[calcs->map_x][calcs->map_y] - 1;
	double wallX;
	if (calcs->side == 0) wallX = rays->pos_y + calcs->perp_wall_dist * calcs->ray_dir_y;
	else		   wallX = rays->pos_x + calcs->perp_wall_dist * calcs->ray_dir_x;
	wallX -= floor((wallX));
	calcs->tex_x = (int)(wallX * (double)(TEXTWIDTH));
	if(calcs->side == 0 && calcs->ray_dir_x > 0) calcs->tex_x = TEXTWIDTH - calcs->tex_x - 1;
	if(calcs->side == 1 && calcs->ray_dir_y < 0) calcs->tex_x = TEXTWIDTH - calcs->tex_x - 1;
	calcs->step = 1.0 * TEXTHEIGHT / lineHeight;
	calcs->tex_pos = (calcs->draw_start - SCREENHEIGHT / 2 + lineHeight / 2) * calcs->step;
}

void speed_calculation(t_rays *rays)
{
	rays->old_time = rays->time;
	rays->time = time(NULL);
	rays->frame_time = (rays->time - rays->old_time) / 1000.0;
	rays->move_speed = rays->frame_time * 5.0;
	rays->rot_speed = rays->frame_time * 3.0;
}

void floor_casting(t_rays *rays)
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
        //int cellX = (int)(floorX);
        //int cellY = (int)(floorY);
        //int tx = (int)(TEXTWIDTH * (floorX - cellX)) & (TEXTWIDTH - 1);
        //int ty = (int)(TEXTHEIGHT * (floorY - cellY)) & (TEXTHEIGHT - 1);

        floorX += floorStepX;
        floorY += floorStepY;
        //int floorTexture = 3;
        //int ceilingTexture = 6;
        u_int32_t color;
        //color = rays->texture[floorTexture][TEXTWIDTH * ty + tx];
		color = 0x0500FF00;
        color = (color >> 1) & 8355711;
        rays->buffer[y][x] = color;
        //color = rays->texture[ceilingTexture][TEXTWIDTH * ty + tx];
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

int main() {
	void	*mlx;
	t_data	img;
  	t_rays rays;
	void *mlx_win;
	int		**texture;

	texture = malloc(8 * sizeof(int *));

	 int world_map[MAPWIDTH][MAPHEIGHT]=
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
  rays.world_map = heapmap;

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
}
