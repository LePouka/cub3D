/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorificator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:02:07 by rtissera          #+#    #+#             */
/*   Updated: 2024/04/29 06:22:55 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_colord	*colorificator(t_map *map)
{
	t_color	*color;

	if (strncmp("F ", map->map[5], 2) || strncmp("C ", map->map[6], 2))
	{
		return (ft_error("map: Invalid Color Format"), NULL);
	}
	color = (t_color *)malloc(sizeof(t_color *));
	if (!color)
		return (ft_error(strerror(errno)), NULL);
	return (color);
}
