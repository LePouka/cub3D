/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 20:02:02 by rtissera          #+#    #+#             */
/*   Updated: 2024/04/21 18:36:20 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main(int argc, char **argv)
{
	t_world	*world;

	if (argc == 2)
	{
		world = worldinit(argv[1]);
		parsingator(world);
		worldend(world);
	}
	else
	{
		return (ft_error("Bad arguments number"));
	}
	return (0);
}
