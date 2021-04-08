/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 12:05:23 by alagroy-          #+#    #+#             */
/*   Updated: 2021/04/08 18:15:23 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

static t_block	*extend_zones(size_t size)
{
	t_zone		*zone;

	if (!(zone = create_zone(size)))
		return (NULL);
	return ((t_block *)(zone + 1));
}

static t_block	*find_free_block(size_t size)
{
	t_block	*ptr;
	void	*end_zones;
	t_zone	**zone;
	int		i;

	end_zones = g_malloc.zones + *((uint64_t *)g_malloc.zones);
	zone = g_malloc.zones;
	i = 0;
	while (zone[++i] && (void *)(zone + i) < end_zones)
	{
		if (zone[i]->type != get_malloc_type(size))
			continue ;
		ptr = (t_block *)(zone[i] + 1);
		while (ptr && integrity_check(ptr) && !ptr->free)
		{
			if (ptr->size >= size)
				return (ptr);
			ptr = ptr->next;
		}
	}
	return (extend_zones(size));
}

void			*allocate_block(size_t size)
{
	t_block		*free_block;
	t_block		*next;

	if (!(free_block = find_free_block(size)))
		return (NULL);
	next = (void *)(free_block + 1) + free_block->size;
	if (free_block->next - next > (long)META_SIZE)
	{
		ft_memcpy(next, free_block, META_SIZE);
		free_block->next = next;
		next->size -= size + META_SIZE;
	}
	free_block->free = 0;
	free_block->size = size;
	show_alloc_memory();
	return (free_block + 1);
}
