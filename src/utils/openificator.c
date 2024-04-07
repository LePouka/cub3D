/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openificator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 18:22:43 by rtissera          #+#    #+#             */
/*   Updated: 2024/04/07 18:41:58 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	openificator(char *file_name)
{
	int		fd;

	if (file_name == NULL || file_name[0] == 0)
	{
		return (ft_error("Invalid file input"));
	}
	if (ft_strncmp(file_name + ft_strlen(file_name) - 4, ".cub", 4))
	{
		return (ft_error("Invalid file extension"));
	}
	fd = open(file_name, O_RDONLY, 0777);
	if (fd == -1)
	{
		return (ft_error(strerror(errno)));
	}
	return (fd);
}
