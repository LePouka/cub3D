/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:20:59 by rtissera          #+#    #+#             */
/*   Updated: 2024/05/10 15:29:26 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	check_map_content(t_world *world, t_map *map)
{
	int	i;

	i = 0;
	while (map->i_map[i])
	{
		i++;
	}
}

// TODO
// verifier si mlx image OK
// verifier si on sort des couleurs autorisees
// verifier map content
// verifier murs fermes
// checks spaces
//
void	parsingator(t_world *world, t_map *map)
{
	check_map_content(world, map);
}
