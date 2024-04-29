/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:07:29 by rtissera          #+#    #+#             */
/*   Updated: 2024/04/29 17:04:20 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

/* ************************************************************************** */
/*   INCLUDES                                                                 */
/* ************************************************************************** */
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../lib/minilibx-linux/mlx.h"
# include "../lib/libft/include/libft.h"

/* ************************************************************************** */
/*   DEFINES                                                                  */
/* ************************************************************************** */
# define SCREENWIDTH 1920
# define SCREENHEIGHT 1080

/* ************************************************************************** */
/*   STRUCTURES                                                               */
/* ************************************************************************** */
typedef struct s_color {
	char	*floor;
	char	*ceiling;
	u_int32_t	floor;
	u_int32_t	ceiling;
}	t_color;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bpp;
	int		l;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_map {
	int				**map;
	unsigned int	player_x;
	unsigned int	player_y;
}	t_map;

typedef struct s_mlx {
	void		*mlx;
	void		*mlx_win;
}	t_mlx;

typedef struct s_world {
	int			**texture;
	t_mlx		*mlx;
	t_map		*map;
	t_data		*pics;
}	t_world;

/* ************************************************************************** */
/*   FUNCTIONS                                                                */
/* ************************************************************************** */
/* Parsing */
bool		parsingator(t_world *world);
bool		mlx_pars(t_texture *texture);

/* Init */
t_world		*worldinit(char *file_name);
t_map		*readificator(char *file_name);
t_mlx		*mlxator(void);
t_texture	texturificator(t_world *world, t_map *map);

/* Utils */
void		worldend(t_world *world);
int			ft_error(char *s);
int			**char_to_int(char **arr, int lignes, int collones);
void		free_array(char **arr);

#endif
