/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:20:59 by rtissera          #+#    #+#             */
/*   Updated: 2024/05/03 14:53:59 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// TODO
// verifier si mlx image OK
// verifier si on sort des couleurs autorisees
// verifier map content
// verifier murs fermes
// checks spaces
bool	parsingator(t_world *world)
{
	if (!mlx_pars(world) || color_pars(world->color) || map_pars(world->map))
	{
		return (false);
	}
	return (true);
}
