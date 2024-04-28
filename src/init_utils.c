/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:30:29 by rshay             #+#    #+#             */
/*   Updated: 2024/04/28 18:41:33 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

double	ft_abs(double x)
{
	if (x < 0)
		return (-x);
	return (x);
}

void	dd_calc(t_calcs *calcs, t_rays *rays, int x)
{
	double	dd;

	if (x)
	{
		dd = calcs->delta_dist_x;
		calcs->side_dist_x = (calcs->map_x + 1.0 - rays->pos_x) * dd;
	}
	else
	{
		dd = calcs->delta_dist_y;
		calcs->side_dist_y = (calcs->map_y + 1.0 - rays->pos_y) * dd;
	}
}
