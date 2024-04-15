/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:20:59 by rtissera          #+#    #+#             */
/*   Updated: 2024/04/15 14:17:31 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	check_content(t_map *map)
{
	(void)map;
	return (true);
}

bool	parsingator(char *file_name)
{
	int	fd;
	t_map	*map;

	fd = openificator(file_name);
	if (fd == -1)
	{
		return (false);
	}
	map = readificator(argv[1]);
	return (true);
}
