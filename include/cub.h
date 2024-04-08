/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:07:29 by rtissera          #+#    #+#             */
/*   Updated: 2024/04/08 14:23:34 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

#define GAUCHE 65361
#define HAUT 65362
#define DROITE 65363
#define BAS 65364

/******************************************************************************/
/*   INCLUDES                                                                 */
/******************************************************************************/
# include <stdio.h>
#include <stdint.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>
# include <math.h>
#include <time.h>
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
}           t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_data	*img;
}			t_vars;

typedef struct s_rays
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	double time;
	double oldTime;
	int		**worldMap;
	t_vars	*vars;

}			t_rays;




/******************************************************************************/
/*   FUNCTIONS                                                                */
/******************************************************************************/

void 	casting(t_rays *rays);
int 	clavier(int keycode, t_rays *rays);

#endif
