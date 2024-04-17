/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturificator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:02:16 by rtissera          #+#    #+#             */
/*   Updated: 2024/04/17 17:49:08 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_image	init_image(t_vars v)
{
	t_image	i;

	v.s = init_sprite();
	i.cha = mlx_xpm_file_to_image(v.m, v.s.character, &v.width, &v.height);
	i.col = mlx_xpm_file_to_image(v.m, v.s.collectible, &v.width, &v.height);
	i.flo = mlx_xpm_file_to_image(v.m, v.s.floor, &v.width, &v.height);
	i.wal = mlx_xpm_file_to_image(v.m, v.s.wall, &v.width, &v.height);
	i.exi = mlx_xpm_file_to_image(v.m, v.s.exit, &v.width, &v.height);
	if (!i.exi || !i.cha || !i.col || !i.flo || !i.wal)
	{
		v.img.created = 0;
		ft_printf_fd(1, "Error: Cannot Create Images\n");
		close_window(&v);
	}
	i.created = 1;
	return (i);
}

t_texture	*texturificator(char	**map)
{
	t_texture	*texture;

	if (strncmp("NO ./", map[0], 5) || strncmp("SO ./", map[0], 5) || \
		strncmp("WE ./", map[0], 5) || strncmp("EA ./", map[0], 5))
	{
		ft_error("Invalid textures");
		return (NULL);
	}
	return (world);
}
