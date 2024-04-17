/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:58:32 by rshay             #+#    #+#             */
/*   Updated: 2024/04/17 18:03:32 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int close_win(void *mlx) {
	mlx_loop_end(mlx);
	return (0);
}

int clavier(int keycode, t_rays *rays) {


	double rotate = -0.04;
	double move = -0.3;

	if (keycode == BAS) {
		if(rays->world_map[(int)(rays->pos_x + rays->dir_x * move)][(int)(rays->pos_y)] == false)
			rays->pos_x += rays->dir_x * move;
		if(rays->world_map[(int)(rays->pos_x)][(int)(rays->pos_y + rays->dir_y * move)] == false)
			rays->pos_y += rays->dir_y * move;
		init(rays);
	}

	if (keycode == HAUT) {
		if(rays->world_map[(int)(rays->pos_x - rays->dir_x * move)][(int)(rays->pos_y)] == false)
			rays->pos_x -= rays->dir_x * move;
		if(rays->world_map[(int)(rays->pos_x)][(int)(rays->pos_y - rays->dir_y * move)] == false)
			rays->pos_y -= rays->dir_y * move;
		init(rays);
	}

	if (keycode == DROITE) {
		//both camera direction and camera plane must be rotated
	  double olddir_x = rays->dir_x;
	  rays->dir_x = rays->dir_x * cos(rotate) - rays->dir_y * sin(rotate);
	  rays->dir_y = olddir_x * sin(rotate) + rays->dir_y * cos(rotate);
	  double oldplane_x = rays->plane_x;
	  rays->plane_x = rays->plane_x * cos(rotate) - rays->plane_y * sin(rotate);
	  rays->plane_y = oldplane_x * sin(rotate) + rays->plane_y * cos(rotate);

	  init(rays);

	}

	if (keycode == GAUCHE) {
		//both camera direction and camera plane must be rotated
	  double olddir_x = rays->dir_x;
	  rays->dir_x = rays->dir_x * cos(-rotate) - rays->dir_y * sin(-rotate);
	  rays->dir_y = olddir_x * sin(-rotate) + rays->dir_y * cos(-rotate);
	  double oldplane_x = rays->plane_x;
	  rays->plane_x = rays->plane_x * cos(-rotate) - rays->plane_y * sin(-rotate);
	  rays->plane_y = oldplane_x * sin(-rotate) + rays->plane_y * cos(-rotate);

	  init(rays);

	}

	if (keycode == ESCAPE) {
	mlx_loop_end(rays->vars->mlx);
  }

	return (0);

}
