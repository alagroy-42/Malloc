/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 13:05:06 by alagroy-          #+#    #+#             */
/*   Updated: 2021/04/20 11:31:09 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

static int		should_change_zone(size_t size, size_t new_size)
{
	if (get_malloc_type(size) != get_malloc_type(new_size))
		return (1);
	return (0);
}

static t_block	*increase_block_mem(t_block *block, size_t size)
{
	t_block	*next;
	t_block	*new_block;
	void	*ptr;

	ptr = block + 1;
	next = block->next;
	if (!next || !next->free || block->size + next->size + META_SIZE < size
			|| should_change_zone(block->size, size))
	{
		if (!(next = malloc(size)))
			return (NULL);
		ft_memcpy(next, block + 1, block->size);
		return (next - 1);
	}
	if (block->size + next->size - size < get_zone_min_size(block))
	{
		block->size += next->size + META_SIZE;
		block->next = next->next;
		return (block);
	}
	new_block = (void *)block + size + META_SIZE;
	ft_memcpy(new_block, block, META_SIZE);
	new_block->size -= size + META_SIZE;
	new_block->free = 1;
	block->size = size;
	block->next = new_block;
	return (block);
}

static t_block	*reduce_block_mem(t_block *block, size_t size)
{
	t_block	*new_block;

	if (should_change_zone(block->size, size))
	{
		if (!(new_block = malloc(size)))
			return (NULL);
		return (new_block - 1);
	}
	if (size <= META_SIZE + get_zone_min_size(block))
		return (block);
	new_block = (void *)block + size + META_SIZE;
	ft_memcpy(new_block, block, META_SIZE);
	new_block->size -= size + META_SIZE;
	new_block->free = 1;
	block->size = size;
	block->next = new_block;
	return (block);
}

void			*realloc(void *ptr, size_t size)
{
	t_block		*block;

	block = ptr - META_SIZE;
	if (!ptr)
		return (malloc(size));
	if (!integrity_check(block) || block->free)
		return (NULL);
	if (!size)
	{
		free(ptr);
		return (NULL);
	}
	size = align_size(size);
	if (block->size > size)
		block = reduce_block_mem(block, size);
	else if (block->size < size)
		block = increase_block_mem(block, size);
	if (!block)
		return (NULL);
	if (block == (t_block *)(ptr - META_SIZE))
		return (ptr);
	free(ptr);
	return (block + 1);
}
