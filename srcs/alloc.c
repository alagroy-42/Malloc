/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 12:05:23 by alagroy-          #+#    #+#             */
/*   Updated: 2021/04/16 13:07:52 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

static t_block	*extend_zones(size_t size, t_zone **zone)
{
	t_zone		*new_zone;

	if (!(new_zone = create_zone(size)))
		return (NULL);
	*zone = new_zone;
	return ((t_block *)(new_zone + 1));
}

static t_block	*find_free_block(size_t size, t_zone **zone_ptr)
{
	t_block	*ptr;
	t_zone	**end_zones;
	t_zone	**zone;
	int		i;

	zone = g_malloc.zones;
	end_zones = (void *)zone + *(uint64_t *)zone;
	i = 0;
	while (zone[++i] && zone + i < end_zones)
	{
		if (zone[i]->type != get_malloc_type(size))
			continue ;
		*zone_ptr = zone[i];
		ptr = (t_block *)(zone[i] + 1);
		while (ptr && integrity_check(ptr))
		{
			if (ptr->free && ptr->size >= size)
				return (ptr);
			ptr = ptr->next;
		}
	}
	return (extend_zones(size, zone_ptr));
}

void			*allocate_block(size_t size)
{
	t_block		*free_block;
	t_block		*next;
	t_zone		*zone;

	size = align_size(size);
	if (!(free_block = find_free_block(size, &zone)))
		return (NULL);
	next = (void *)(free_block + 1) + size;
	if ((!free_block->next && (void *)next + META_SIZE
			+ get_zone_min_size(free_block) < (void *)(zone + 1) + zone->size)
			|| free_block->next - next > (long)(META_SIZE
				+ get_zone_min_size(free_block)))
	{
		ft_memcpy(next, free_block, META_SIZE);
		free_block->next = next;
		next->size -= size + META_SIZE;
		free_block->size = size;
	}
	free_block->free = 0;
	return (free_block + 1);
}
