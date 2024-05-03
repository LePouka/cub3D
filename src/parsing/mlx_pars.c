/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42->fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:54:07 by rtissera          #+#    #+#             */
/*   Updated: 2024/05/03 17:38:51 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	is_valid(u_int32_t color)
{
	if (!color)
		return (false);
	return (true);
}

bool	mlx_pars(t_world *world)
{
	if (!is_valid(world->color->floor) || !is_valid(world->color->ceiling))
	{
		ft_error("Invalid Colors");
		return (false);
	}
	return (true);
}
