/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:20:59 by rtissera          #+#    #+#             */
/*   Updated: 2024/05/06 16:25:31 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// TODO
// verifier si mlx image OK
// verifier si on sort des couleurs autorisees
// verifier map content
// verifier murs fermes
// checks spaces
void	parsingator(t_world *world)
{
	color_pars(world, world->color);
	map_pars(world, world->map);
}
