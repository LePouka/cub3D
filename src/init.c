/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:58:45 by rshay             #+#    #+#             */
/*   Updated: 2024/06/03 16:28:05 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	init(t_rays *rays)
{
	t_data	*v;

	v = rays->vars->img;
	v->img = mlx_new_image(rays->vars->mlx, SCREENWIDTH, SCREENHEIGHT);
	v->addr = mlx_get_data_addr(v->img, &v->bpp, &v->l, &v->endian);
}

void	init_texturing(int **texture, t_rays *rays)
{
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
	calcs->camera_x = 2 * x / (double)SCREENWIDTH - 1;
	calcs->ray_dir_x = rays->dir_x + rays->plane_x * calcs->camera_x;
	calcs->ray_dir_y = rays->dir_y + rays->plane_y * calcs->camera_x;
	calcs->map_x = rays->pos_x;
	calcs->map_y = rays->pos_y;
	if (calcs->ray_dir_x == 0)
		calcs->delta_dist_x = 1e30;
	else
		calcs->delta_dist_x = ft_abs(1 / calcs->ray_dir_x);
	if (calcs->ray_dir_y == 0)
		calcs->delta_dist_y = 1e30;
	else
		calcs->delta_dist_y = ft_abs(1 / calcs->ray_dir_y);
	calcs->hit = 0;
}

void	init_side_dist(t_calcs *calcs, t_rays *rays)
{
	if (calcs->ray_dir_x < 0)
	{
		calcs->step_x = -1;
		calcs->side_dist_x = (rays->pos_x - calcs->map_x) * calcs->delta_dist_x;
	}
	else
	{
		calcs->step_x = 1;
		dd_calc(calcs, rays, 1);
	}
	if (calcs->ray_dir_y < 0)
	{
		calcs->step_y = -1;
		calcs->side_dist_y = (rays->pos_y - calcs->map_y) * calcs->delta_dist_y;
	}
	else
	{
		calcs->step_y = 1;
		dd_calc(calcs, rays, 0);
	}
}
