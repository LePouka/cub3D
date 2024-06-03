/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:30:06 by rtissera          #+#    #+#             */
/*   Updated: 2024/06/03 18:30:08 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	**ft_mallocator(t_world *world)
{
	int	**ret;
	int	i;
	int	j;

	ret = (int **)malloc(sizeof(char *) * (world->map->len + 1));
	if (!ret)
		ft_error(world, strerror(errno));
	i = 0;
	while (i < world->map->len)
	{
		ret[i] = (int *)malloc(sizeof(char) * world->map->lig);
		if (!ret[i])
			ft_error(world, strerror(errno));
		j = -1;
		while (++j < world->map->lig)
			ret[i][j] = 1;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

int	**map_rotate(t_world *world, int **i_map)
{
	int	**ret;
	int	i;
	int	j;

	ret = ft_mallocator(world);
	i = 0;
	j = 0;
	while (i_map[i] && i_map[i][j])
	{
		i = 0;
		while (i_map[i] && i_map[i][j])
		{
			ret[j][i] = i_map[i][j];
			i++;
		}
		j++;
	}
	free(i_map);
	i = world->map->lig;
	world->map->lig = world->map->len;
	world->map->len = i;
	return (ret);
}
