/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:23:03 by rshay             #+#    #+#             */
/*   Updated: 2024/05/31 16:20:51 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	free_data(t_rays *rays)
{
	int	i;

	i = 0;
	while (i < rays->width)
		free(rays->world_map[i++]);
	free(rays->world_map);
	free(rays->texture);
	i = 0;
	while (i < SCREENHEIGHT)
		free(rays->buffer[i++]);
	free(rays->buffer);
	i = 0;
	while (i < 8)
		mlx_destroy_image(rays->vars->mlx, rays->pics[i++].img);
	free(rays->pics);
}

void	calculate_dda(t_calcs *calcs, t_rays *rays)
{
	while (calcs->hit == 0)
	{
		if (calcs->side_dist_x < calcs->side_dist_y)
		{
			calcs->side_dist_x += calcs->delta_dist_x;
			calcs->map_x += calcs->step_x;
			calcs->side = 0;
			if (calcs->step_x >= 0)
				calcs->orientation = 2;
			else
				calcs->orientation = 3;
		}
		else
		{
			calcs->side_dist_y += calcs->delta_dist_y;
			calcs->map_y += calcs->step_y;
			calcs->side = 1;
			if (calcs->step_y >= 0)
				calcs->orientation = 1;
			else
				calcs->orientation = 0;
		}
		// printf("map_x = %d, map_y = %d\n", calcs->map_x, calcs->map_y);
		// if (calcs->map_x >= 33 || calcs->map_y >= 14)
		// 	exit(0);
		if (rays->world_map[calcs->map_y][calcs->map_x] > 0)
		calcs->hit = 1;
	}
}

void	wall_x_calculations(t_calcs *calcs, t_rays *rays)
{
	double	wall_x;

	if (calcs->side == 0)
		wall_x = rays->pos_y + calcs->perp_wall_dist * calcs->ray_dir_y;
	else
		wall_x = rays->pos_x + calcs->perp_wall_dist * calcs->ray_dir_x;
	wall_x -= floor((wall_x));
	calcs->tex_x = (int)(wall_x * (double)(TEXTWIDTH));
	if (calcs->side == 0 && calcs->ray_dir_x > 0)
		calcs->tex_x = TEXTWIDTH - calcs->tex_x - 1;
	if (calcs->side == 1 && calcs->ray_dir_y < 0)
		calcs->tex_x = TEXTWIDTH - calcs->tex_x - 1;
}

void	drawing_calculations(t_calcs *calcs, t_rays *rays)
{
	int		line_height;
	double	t_pos;

	if (calcs->side == 0)
		calcs->perp_wall_dist = (calcs->side_dist_x - calcs->delta_dist_x);
	else
		calcs->perp_wall_dist = (calcs->side_dist_y - calcs->delta_dist_y);
	line_height = (int)(SCREENHEIGHT / calcs->perp_wall_dist);
	calcs->draw_start = -line_height / 2 + SCREENHEIGHT / 2;
	if (calcs->draw_start < 0)
		calcs->draw_start = 0;
	calcs->draw_end = line_height / 2 + SCREENHEIGHT / 2;
	if (calcs->draw_end >= SCREENHEIGHT)
		calcs->draw_end = SCREENHEIGHT - 1;
	calcs->tex_num = rays->world_map[calcs->map_y][calcs->map_x] - 1;
	wall_x_calculations(calcs, rays);
	calcs->step = 1.0 * TEXTHEIGHT / line_height;
	t_pos = calcs->draw_start - SCREENHEIGHT / 2 + line_height / 2;
	calcs->tex_pos = t_pos * calcs->step;
}

void	speed_calculation(t_rays *rays)
{
	rays->old_time = rays->time;
	rays->time = time(NULL);
	rays->frame_time = (rays->time - rays->old_time) / 1000.0;
	rays->move_speed = rays->frame_time * 5.0;
	rays->rot_speed = rays->frame_time * 3.0;
}
