/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worldend_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 20:24:55 by rshay             #+#    #+#             */
/*   Updated: 2024/06/03 20:31:04 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	raysend(t_rays *rays)
{
	int	i;

	i = 0;
	mlx_destroy_image(rays->vars->mlx, rays->vars->img->img);
	while (rays->buffer[i]) {
		free(rays->buffer[i]);
		i++;
	}
	free(rays->buffer);
}
