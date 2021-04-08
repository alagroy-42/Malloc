/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 13:05:06 by alagroy-          #+#    #+#             */
/*   Updated: 2021/04/08 16:05:31 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

static t_block	*increase_block_mem(t_block *block, size_t size)
{
	t_block	*next;
	t_block	*new_block;
	void	*ptr;

	ptr = block + 1;
	next = block->next;
	if (!next->free || block->size + next->size + META_SIZE < size)
	{
		if (!(next = malloc(size)))
			return (NULL);
		ft_memcpy(next, ptr, block->size);
		free(ptr);
		return (next + 1);
	}
	if (block->size + next->size - size <= 0)
	{
		block->size = size;
		return (block);
	}
	new_block = (void *)block + size;
	ft_memcpy(block, new_block, META_SIZE);
	new_block->size -= size + META_SIZE;
	new_block->free = 1;
	block->size = size;
	block->next = new_block;
	return (block);
}

static t_block	*reduce_block_mem(t_block *block, size_t size)
{
	t_block	*new_block;

	if (block->size - size <= META_SIZE)
	{
		block->size = size;
		return (block);
	}
	new_block = (void *)block + size;
	ft_memcpy(block, new_block, META_SIZE);
	new_block->size -= size + META_SIZE;
	new_block->free = 1;
	block->size = size;
	block->next = new_block;
	return (block);
}

void			*realloc(void *ptr, size_t size)
{
	t_block		*block;

	ft_putendl("realloc");
	block = ptr - META_SIZE;
	if (!ptr || !integrity_check(block) || block->free)
		return (malloc(size));
	if (!size)
	{
		free(ptr);
		return (NULL);
	}
	if (block->size > size)
		block = reduce_block_mem(block, size);
	else
		block = increase_block_mem(block, size);
	if (!block)
		return (NULL);
	if (block == (t_block *)(ptr - META_SIZE))
		return (ptr);
	free(ptr);
	return (block + 1);
}
