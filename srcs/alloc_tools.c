/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 14:22:32 by alagroy-          #+#    #+#             */
/*   Updated: 2021/03/25 15:57:58 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

static t_block	*extend_zones(size_t size)
{
	t_zone	*zone;

	if (!(zone = create_zone(size)))
		return (NULL);
	return (zone->addr);
}

static t_block	*find_free_block(t_zone *zones, size_t size)
{
	int		i;
	void	*ptr;
	void	*end;

	i = -1;
	while (zones[i].size)
	{
		ptr = zones[i].addr;
		end = ptr + zones[i].size;
		if (zones[i].next)
		{
			zones = zones[i].next;
			i = -1;
		}
		if (zones[i].type != get_malloc_type(size))
			continue ;
		while (ptr && ptr < end)
		{
			if (((t_block *)ptr)->size >= size && ((t_block *)ptr)->free)
				return (ptr);
			ptr = ((t_block *)ptr)->next;
		}
	}
	return (extend_zones(size));
}

void			*allocate_block(size_t size)
{
	t_block *free_block;
	t_block *footer;
	int		old_size;

	if (!(free_block = find_free_block(g_malloc.zones, size)))
		return (NULL);
	old_size = free_block->size;
	free_block->size = size;
	free_block->free = 0;
	footer = (void *)free_block + size + META_SIZE;
	if (!free_block->next || footer < free_block->next - META_SIZE)
	{
		footer->free = 1;
		footer->size = old_size - size - META_SIZE;
		footer->next = free_block->next;
		free_block->next = footer;
	}
	return (free_block + 1);
}
