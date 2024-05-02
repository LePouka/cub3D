/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorificator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:02:07 by rtissera          #+#    #+#             */
/*   Updated: 2024/05/02 14:54:36 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_colord	*colorificator(t_map *map)
{
	char		**c_color;
	t_color		*color;
	u_int32_t	hex;

	if (strncmp("F ", map->map[5], 2) || strncmp("C ", map->map[6], 2))
	{
		return (ft_error("map: Invalid Color Format"), NULL);
	}
	c_color = ft_split(map[5] + 2, ',');
	color = (t_color *)malloc(sizeof(t_color) * 2);
	if (!color)
		return (ft_error(strerror(errno)), NULL);
	color = 0x00 << 4;
	color |= 0xFF << 2;
	color |= 0x00;
	return (color);
}
