/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:07:29 by rtissera          #+#    #+#             */
/*   Updated: 2024/04/16 15:26:36 by rtissera         ###   ########.fr       */
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
typedef struct s_world {
	char	**map;
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char	*F;
	char	*C;
}	t_world;

/* ************************************************************************** */
/*   FUNCTIONS                                                                */
/* ************************************************************************** */
/* Tests */
bool	parsingator(char *file_name);

/* Utils */
int	ft_error(char *s);
int	openificator(char *file_name);
t_map	readificator(int fd);

#endif
