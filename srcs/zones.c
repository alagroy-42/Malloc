/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zones.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:31:38 by alagroy-          #+#    #+#             */
/*   Updated: 2021/04/20 12:51:19 by alagroy-         ###   ########.fr       */
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

static int		extend_g_zones(void)
{
	t_zone		**old_zones;
	uint64_t	size;

	old_zones = g_malloc.zones;
	size = *(uint64_t *)old_zones;
	if (!(g_malloc.zones = mmap_safe(size + g_malloc.pagesize)))
	{
		g_malloc.zones = old_zones;
		return (EXIT_FAILURE);
	}
	ft_memcpy(g_malloc.zones, old_zones, size);
	*(uint64_t *)g_malloc.zones = size + g_malloc.pagesize;
	return (EXIT_SUCCESS);
}

t_zone			*create_zone(size_t size)
{
	t_zone	**end;
	t_zone	**zones;
	int		i;
	size_t	zone_size;
	t_block	block;

	zone_size = get_new_zone_size(size);
	zones = g_malloc.zones;
	end = (void *)zones + *(uint64_t *)(zones);
	i = 0;
	while (zones + i < end && zones[++i])
		continue ;
	if (zones + i >= end)
	{
		if (extend_g_zones() == EXIT_FAILURE)
			return (NULL);
		zones = g_malloc.zones;
	}
	if (!(zones[i] = mmap_safe(zone_size)))
		return (NULL);
	zones[i]->type = get_malloc_type(size);
	zones[i]->size = zone_size - ZONE_SIZE;
	block = (t_block){zones[i]->size - META_SIZE, MALLOC_MAGIC, 1, NULL};
	ft_memcpy((void *)zones[i] + ZONE_SIZE, &block, sizeof(t_block));
	return (zones[i]);
}

void			free_zone(t_zone *zone)
{
	t_zone	**zones;
	t_zone	**end;
	int		i;
	int		found;

	zones = g_malloc.zones;
	i = 0;
	found = 0;
	end = (void *)zones + *(uint64_t *)(zones);
	while (!found && zones[++i] && zones + i < end)
		if (zones[i] == zone)
			found = 1;
	if (!found)
		return ;
	g_malloc.nb_pages = (zone->size + ZONE_SIZE) / g_malloc.pagesize;
	munmap(zone, zone->size);
	i--;
	while (zones + ++i < end && zones[i])
		zones[i] = zones[i + 1];
	zones[i - 1] = NULL;
}
