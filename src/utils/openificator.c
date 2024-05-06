/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openificator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:38:22 by rtissera          #+#    #+#             */
/*   Updated: 2024/05/06 16:34:47 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	openificator(t_world *world, char *file_name)
{
	int		fd;

	if (file_name == NULL || file_name[0] == 0)
	{
		ft_error(world, "Invalid file input");
	}
	if (ft_strncmp(file_name + ft_strlen(file_name) - 4, ".cub", 4))
	{
		ft_error(world, "Invalid file extension");
	}
	fd = open(file_name, O_RDONLY, 0777);
	if (fd == -1)
	{
		ft_error(world, strerror(errno));
	}
	return (fd);
}
