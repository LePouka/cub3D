/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:07:29 by rtissera          #+#    #+#             */
/*   Updated: 2024/04/21 18:53:34 by rtissera         ###   ########.fr       */
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
/*   STRUCTURES                                                               */
/* ************************************************************************** */
typedef struct s_texture {
	void	*north;
	void	*south;
	void	*west;
	void	*east;
	char	*floor;
	char	*ceiling;
}	t_texture;

typedef struct s_map {
	char			**map;
	unsigned int	player_x;
	unsigned int	player_y;
}	t_map;

typedef struct s_mlx {
	void		*mlx;
	void		*mlx_win;
}	t_mlx;

typedef struct s_world {
	t_mlx		*mlx;
	t_map		*map;
	t_texture	*texture;
}	t_world;

/* ************************************************************************** */
/*   FUNCTIONS                                                                */
/* ************************************************************************** */
/* Parsing */
bool		parsingator(char *file_name);

/* Init */
t_world		*worldinit(char *file_name);
t_map		*readificator(char *file_name);
t_mlx		*mlxator(void);
t_texture	*texturificator(t_world *world, t_map *map);

/* Utils */
void		worldend(t_world *world);
int			ft_error(char *s);

#endif
