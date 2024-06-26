/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:58:32 by rtissera          #+#    #+#             */
/*   Updated: 2024/05/06 16:30:51 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_error(t_world *world, char *s)
{
	if (s)
	{
		ft_dprintf(2, "Error\n%s\n", s);
	}
	else
	{
		ft_dprintf(2, "Error\nExplicit error message of your choice\n");
	}
	worldend(world);
	exit(EXIT_FAILURE);
}

int	close_error(t_world *world, int fd, char *s)
{
	close(fd);
	return (ft_error(world, s));
}

void	close_free_error(t_world *world, int fd, char *s1, char *s2)
{
	free(s1);
	close_error(world, fd, s2);
}

char	*free_strjoin(char *s1, char *s2)
{
	char	*s3;

	s3 = ft_strjoin(s1, s2);
	free(s1);
	return (s3);
}
