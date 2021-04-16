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

static void	defrag_zone(t_block *block)
{
	t_zone	*zone;
	int		unmap;

	if (!(zone = get_block_zone(block)))
		return ;
	block = (t_block *)(zone + 1);
	unmap = 1;
	while (block && integrity_check(block))
	{
		if (!block->free)
			unmap = 0;
		if (block->free && block->next && block->next->free
				&& get_malloc_type(block->size + block->next->size + META_SIZE)
				== zone->type)
		{
			block->size += block->next->size + META_SIZE;
			block->next = block->next->next;
			continue ;
		}
		block = block->next;
	}
	if (unmap)
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
