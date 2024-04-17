/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:07:29 by rtissera          #+#    #+#             */
/*   Updated: 2024/04/17 17:08:56 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# define GAUCHE 65361
# define HAUT 65362
# define DROITE 65363
# define BAS 65364
# define ESCAPE 65307
# define SCREENWIDTH 1920
# define SCREENHEIGHT 1080
# define TEXTWIDTH 64
# define TEXTHEIGHT 64
# define MAPWIDTH 24
# define MAPHEIGHT 24

/******************************************************************************/
/*   INCLUDES                                                                 */
/******************************************************************************/
# include <stdio.h>
# include <stdint.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>
# include <math.h>
# include <sys/types.h>
# include <time.h>
# include "../lib/minilibx-linux/mlx.h"
# include "../lib/libft/include/libft.h"

/******************************************************************************/
/*   STRUCTURES                                                               */
/******************************************************************************/

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		l;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_data	*img;
}			t_vars;

typedef struct s_rays
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	time;
	double	old_time;
	double	move_speed;
	double	rot_speed;
	int		**world_map;
	t_vars	*vars;

}			t_rays;

typedef struct s_calcs
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		hit;
	double	side_dist_x;
	double	side_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		side;
	int		draw_start;
	int		draw_end;
	int		tex_num;
	int		tex_x;
	double	step;
	double	tex_pos;

}			t_calcs;

/******************************************************************************/
/*   FUNCTIONS                                                                */
/******************************************************************************/

void	init(t_rays *rays);
int		casting(t_rays *rays);
int		clavier(int keycode, t_rays *rays);
int		close_win(void *mlx);
void	init(t_rays *rays);
void	init_texturing(int **texture, t_rays *rays);
void	init_calculating(t_calcs *calcs, t_rays *rays, int x);
void	init_side_dist(t_calcs *calcs, t_rays *rays);

#endif
