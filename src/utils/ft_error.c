/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:58:32 by rtissera          #+#    #+#             */
/*   Updated: 2024/04/07 19:06:00 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_error(char *s)
{
	if (s)
	{
		ft_dprintf(2, "Error\n%s\n", s);
	}
	else
	{
		ft_dprintf(2, "Error\nExplicit error message of your choice\n");
	}
	return (-1);
}

void	close_free_error(int fd, char *s1, char *s2)
{
	free(s1);
	close_error(fd, s2);
}

void	close_error(int fd, char *s)
{
	close(fd);
	return (ft_error(s));
}
