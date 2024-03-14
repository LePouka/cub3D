/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:52:18 by rtissera          #+#    #+#             */
/*   Updated: 2023/05/26 16:11:35 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*str;

	if (!nmemb || !size)
		return (malloc(0));
	if (((size * nmemb) / nmemb) != size)
		return (NULL);
	str = malloc(size * nmemb);
	if (!str)
		return (NULL);
	str = ft_memset(str, 0, (nmemb * size));
	return (str);
}
