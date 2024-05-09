/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturificator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:02:16 by rtissera          #+#    #+#             */
/*   Updated: 2024/05/09 19:04:42 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_data_to_cfg(t_config *cfg, t_file_data *fdata)
{
	int			i;
	static char	id_array[ID_NB][3]
		= {"C", "F", "NO", "SO", "WE", "EA"};
	static int	(*array_ft[ID_NB])(t_config *, t_file_data *)
		= {ft_get_ceilar, ft_get_floor, ft_get_no_text,
		ft_get_so_text, ft_get_we_text, ft_get_ea_text};

	if (fdata->paramlist)
		ft_free_tab(&fdata->paramlist);
	fdata->paramlist = ft_split(fdata->line, ' ');
	i = 0;
	while (i < ID_NB)
	{
		if (ft_strequ(id_array[i], *fdata->paramlist))
			return (array_ft[i](cfg, fdata));
		i++;
	}
	ft_manage_parse_error(ERROR_ID, cfg, fdata);
	return (-1);
}

t_data	*ft_get_data_addr(t_world *world, t_mlx *mlx, t_data *pics)
{
	int	i;

	if (!pics[0].img || !pics[1].img || !pics[2].img || !pics[3].img)
	{
		ft_error(world, "Failed Creating Images");
	}
	i = 0;
	while (i < 4)
	{
		world->texture[i] = (int *)mlx_get_data_addr(pics[i].img, \
			&(pics[i]).bpp, &(pics[i]).l, &(pics[i]).endian);
		if (!world->texture[i])
		{
			while (--i)
			{
				mlx_destroy_image(mlx->mlx, pics[i].img);
			}
			ft_error(world, "Failed Getting Data Address");
		}
		i++;
	}
	return (pics);
}

t_data	*texturificator(t_world *world, t_mlx *mlx, t_map *map)
{
	int		th;
	int		tw;
	t_data	*pics;

	if (!world || !mlx || !mlx->mlx || !map || !map->map)
		return (NULL);
	if (strncmp("NO ./", map->map[0], 5) || strncmp("SO ./", map->map[1], 5) || \
		strncmp("WE ./", map->map[2], 5) || strncmp("EA ./", map->map[3], 5))
	{
		ft_error(world, "map: invalid texture format");
	}
	pics = (t_data *)malloc(sizeof(t_data) * 4);
	if (!pics)
		ft_error(world, strerror(errno));
	pics[0].img = mlx_xpm_file_to_image(mlx->mlx, map->map[0] + 5, &tw, \
		&th);
	pics[1].img = mlx_xpm_file_to_image(mlx->mlx, map->map[1] + 5, &tw, \
		&th);
	pics[2].img = mlx_xpm_file_to_image(mlx->mlx, map->map[2] + 5, &tw, \
		&th);
	pics[3].img = mlx_xpm_file_to_image(mlx->mlx, map->map[3] + 5, &tw, \
		&th);
	return (ft_get_data_addr(world, world->mlx, pics));
}
