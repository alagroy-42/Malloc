/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zones.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:31:38 by alagroy-          #+#    #+#             */
/*   Updated: 2021/04/08 16:06:49 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

static size_t	round_zone_size(size_t size)
{
	if (!(size % g_malloc.pagesize))
		return (size);
	return ((size / g_malloc.pagesize + 1) * g_malloc.pagesize);
}

static size_t	get_new_zone_size(size_t size)
{
	int		min;

	if (size > SMALL)
		return (round_zone_size(size + ZONE_SIZE + META_SIZE));
	if (size <= TINY)
	{
		min = 250 * (TINY + META_SIZE) + ZONE_SIZE;
		return (round_zone_size(min));
	}
	min = 100 * (SMALL + META_SIZE) + ZONE_SIZE;
	return (round_zone_size(min));
}

////////// extend zone si g_zones rempli
t_zone			*create_zone(size_t size)
{
	void	*end;
	t_zone	**zones;
	int		i;
	size_t	zone_size;
	t_block	block;

	zone_size = get_new_zone_size(size);
	zones = g_malloc.zones;
	end = zones + *(uint64_t *)(zones);
	i = 0;
	while (zones[++i] && zones + i < (t_zone **)end)
		continue ;
	if (!(zones[i] = mmap_safe(zone_size)))
		return (NULL);
	zones[i]->type = get_malloc_type(size);
	zones[i]->size = zone_size - ZONE_SIZE;
	block = (t_block){zones[i]->size - META_SIZE, MALLOC_MAGIC, 1, NULL};
	ft_memcpy((void *)zones[i] + ZONE_SIZE, &block, sizeof(t_block));
	return (zones[i]);
}
