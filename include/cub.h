/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:07:29 by rtissera          #+#    #+#             */
/*   Updated: 2024/04/17 18:05:24 by rtissera         ###   ########.fr       */
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
	void	*NO;
	void	*SO;
	void	*WE;
	void	*EA;
	char	*F;
	char	*C;
}	t_texture;

typedef struct s_world {
	char		**map;
	void		*mlx;
	void		*mlx_win;
	t_texture	*texture;
}	t_world;

/* ************************************************************************** */
/*   FUNCTIONS                                                                */
/* ************************************************************************** */
/* Parsing */
bool	parsingator(char *file_name);

/* Init */
t_world	*worldinit(char *argv);
char	**readificator(t_world *world);

/* Utils */
int	ft_error(char *s);
int	openificator(char *file_name);

#endif
