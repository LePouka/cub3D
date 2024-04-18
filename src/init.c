/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:58:45 by rshay             #+#    #+#             */
/*   Updated: 2024/04/18 18:54:15 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

#define ABS(x) x >= 0 ? x : -x

void init(t_rays *rays) {
   rays->vars->img->img = mlx_new_image(rays->vars->mlx, SCREENWIDTH, SCREENHEIGHT);
	rays->vars->img->addr = mlx_get_data_addr(rays->vars->img->img, &(rays->vars->img)->bpp, &(rays->vars->img)->l,
								&(rays->vars->img)->endian);
}

void init_texturing (int **texture, t_rays *rays) {
	int		th;
	int		tw;

	rays->pics = malloc(8 * sizeof(t_data));
	rays->pics[0].img = mlx_xpm_file_to_image(rays->vars->mlx, "img/eagle.xpm", &tw, &th);
	rays->pics[1].img = mlx_xpm_file_to_image(rays->vars->mlx, "img/redbrick.xpm", &tw, &th);
	rays->pics[2].img = mlx_xpm_file_to_image(rays->vars->mlx, "img/purplestone.xpm", &tw, &th);
	rays->pics[3].img = mlx_xpm_file_to_image(rays->vars->mlx, "img/greystone.xpm", &tw, &th);
	rays->pics[4].img = mlx_xpm_file_to_image(rays->vars->mlx, "img/bluestone.xpm", &tw, &th);
	rays->pics[5].img = mlx_xpm_file_to_image(rays->vars->mlx, "img/mossy.xpm", &tw, &th);
	rays->pics[6].img = mlx_xpm_file_to_image(rays->vars->mlx, "img/wood.xpm", &tw, &th);
	rays->pics[7].img = mlx_xpm_file_to_image(rays->vars->mlx, "img/colorstone.xpm", &tw, &th);

	for (int i = 0; i < 7; i++) {
		texture[i] = (int *)mlx_get_data_addr(rays->pics[i].img, &(rays->pics[i]).bpp, &(rays->pics[i]).l, &(rays->pics[i]).endian);
	}
}

void	init_calculating(t_calcs *calcs, t_rays *rays, int x)
{
	//calculate ray position and direction
	calcs->camera_x = 2 * x / (double)SCREENWIDTH - 1; //x-coordinate in camera space
	calcs->ray_dir_x = rays->dir_x + rays->plane_x * calcs->camera_x;
	calcs->ray_dir_y = rays->dir_y + rays->plane_y * calcs->camera_x;
	//which box of the map we're in
	calcs->map_x = rays->pos_x;
	calcs->map_y = rays->pos_y;

	//length of ray from one x or y-side to next x or y-side
	calcs->delta_dist_x = (calcs->ray_dir_x == 0) ? 1e30 : ABS(1 / calcs->ray_dir_x);
	calcs->delta_dist_y = (calcs->ray_dir_y == 0) ? 1e30 : ABS(1 / calcs->ray_dir_y);
	calcs->hit = 0;

}

void init_side_dist(t_calcs *calcs, t_rays *rays) {
	if (calcs->ray_dir_x < 0)
	  {
		calcs->step_x = -1;
		calcs->side_dist_x = (rays->pos_x - calcs->map_x) * calcs->delta_dist_x;
	  }
	  else
	  {
		calcs->step_x = 1;
		calcs->side_dist_x = (calcs->map_x + 1.0 - rays->pos_x) * calcs->delta_dist_x;
	  }
	  if (calcs->ray_dir_y < 0)
	  {
		calcs->step_y = -1;
		calcs->side_dist_y = (rays->pos_y - calcs->map_y) * calcs->delta_dist_y;
	  }
	  else
	  {
		calcs->step_y = 1;
		calcs->side_dist_y = (calcs->map_y + 1.0 - rays->pos_y) * calcs->delta_dist_y;
	  }
}

