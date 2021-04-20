/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 13:00:13 by alagroy-          #+#    #+#             */
/*   Updated: 2021/04/20 11:37:56 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

static int	count_zones_type(t_block *block)
{
	t_zone	**zone;
	t_zone	**end;
	int		i;
	int		count;

	zone = g_malloc.zones;
	end = (void *)zone + *(uint64_t *)zone;
	i = 0;
	count = 0;
	while (zone + ++i < end && zone[i])
	{
		if (zone[i]->size == get_malloc_type(block->size))
			count++;
	}
	return (count);
}

static void	defrag_zone(t_block *block)
{
	t_zone	*zone;
	t_block	*tmp;
	int		unmap;

	if (!(zone = get_block_zone(block)))
		return ;
	tmp = (t_block *)(zone + 1);
	unmap = 1;
	while (tmp && integrity_check(tmp))
	{
		if (!tmp->free)
			unmap = 0;
		if (tmp->free && tmp->next && tmp->next->free
				&& get_malloc_type(tmp->size + tmp->next->size + META_SIZE)
				== zone->type)
		{
			tmp->size += tmp->next->size + META_SIZE;
			tmp->next = tmp->next->next;
			continue ;
		}
		tmp = tmp->next;
	}
	if (unmap && count_zones_type(block) > 1)
		free_zone(zone);
}

void		free(void *ptr)
{
	t_block	*block;

	block = ptr - META_SIZE;
	if (!ptr || !integrity_check(block) || block->free)
		return ;
	if (block->size > SMALL)
		return (free_zone((void *)block - ZONE_SIZE));
	block->free = 1;
	defrag_zone(block);
}
