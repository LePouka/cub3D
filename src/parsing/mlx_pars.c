/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42->fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:54:07 by rtissera          #+#    #+#             */
/*   Updated: 2024/04/28 18:49:30 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	color_pars(char *color)
{
	int	nb;
	int	coma;

	coma = 0;
	nb = ft_atoi(color) + coma;
	while (nb < 0 || nb > 255)
	{
		color = ft_strchr();
	}
	return (true);
}

bool	mlx_pars(t_texture *texture)
{
	if (!texture->north || !texture->south || !texture->west || !texture->east)
	{
		ft_error("Cannot Create Images");
		return (false);
	}
	if (!color_pars(texture->floor) || !color_pars(texture->ceiling))
	{
		ft_error("Invalid Colors");
		return (false);
	}
	return (true);
}
