/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:58:45 by rshay             #+#    #+#             */
/*   Updated: 2024/05/31 17:38:19 by rshay            ###   ########.fr       */
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
