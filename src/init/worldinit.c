/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worldinit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:06:35 by rtissera          #+#    #+#             */
/*   Updated: 2024/04/17 17:53:05 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"


t_world	*worldinit(char *file_name)
{
	int	fd;
	t_world	*world;

	world = (t_world *)malloc(sizeof(t_world));
	if (!world)
	{
		return (ft_error("Cannot allocate world"));
	}
	fd = openificator(file_name);
	if (fd == -1)
	{
		return (false);
	}
	world.map = readificator(fd);
	close(fd);
	world.texture = texturifictor(world.map);
	return (world);
}
