/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:07:29 by rtissera          #+#    #+#             */
/*   Updated: 2024/05/06 19:32:56 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# define W 119
# define S 115
# define A 97
# define D 100
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
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		time;
	double		old_time;
	double		move_speed;
	double		rot_speed;
	double		frame_time;
	int			**world_map;
	int			**texture;
	u_int32_t	**buffer;
	u_int32_t	color;
	t_data		*pics;
	t_vars		*vars;

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
	int		orientation;
	int		draw_start;
	int		draw_end;
	int		tex_num;
	int		tex_x;
	double	step;
	double	tex_pos;

}			t_calcs;

typedef struct s_casting
{
	float	ray_dir_x0;
	float	ray_dir_y0;
	float	ray_dir_x1;
	float	ray_dir_y1;
	int		p;
	float	pos_z;
	float	row_distance;
	float	floor_step_x;
	float	floor_step_y;
	float	floor_x;
	float	floor_y;
	float	diff_x;
	float	diff_y;
}			t_casting;

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
void	free_data(t_rays *rays);
double	ft_abs(double x);
void	dd_calc(t_calcs *calcs, t_rays *rays, int x);
void	floor_casting(t_rays *rays);
int		casting(t_rays *rays);
void	free_data(t_rays *rays);
void	calculate_dda(t_calcs *calcs, t_rays *rays);
void	drawing_calculations(t_calcs *calcs, t_rays *rays);
void	speed_calculation(t_rays *rays);
void	floor_casting(t_rays *rays);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	rotate(int fact, t_rays *rays);
#endif
