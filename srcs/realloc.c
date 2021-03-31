/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 15:15:24 by alagroy-          #+#    #+#             */
/*   Updated: 2021/04/06 15:09:45 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

static void	*extend_block(void *ptr, size_t size)
{
	t_block	*block;
	t_block	*new_block;

	block = ptr - META_SIZE;
	if (block->size + block->next->size - size <= META_SIZE)
	{
		block->size = size;
		block->next = block->next->next;
		return (ptr);
	}
	new_block = ptr + size;
	ft_memcpy(new_block, ptr + block->size, META_SIZE);
	new_block->size -= size - block->size;
	block->next = new_block;
	return (ptr);
}

static void	*real_realloc(void *ptr, size_t size)
{
	t_block	*block;
	void	*new_ptr;

	block = ptr - META_SIZE;
	if (block->next && block->next->free
			&& block->size + block->next->size + META_SIZE >= size)
		return (extend_block(ptr, size));
	if (!(new_ptr = malloc(size)))
		return (NULL);
	ft_memcpy(new_ptr, ptr, block->size);
	free(ptr);
	return (ptr);	
}

void		*realloc(void *ptr, size_t size)
{
	write(1, "realloc\n", 8);
	// show_alloc_memory();
	if (!ptr)
		return (malloc(size));
	if (!integrity_check(ptr - META_SIZE) || ((t_block *)ptr - 1)->free)
		return (NULL);
	if (!size)
	{
		free(ptr);
		return (malloc(0));
	}
	return (real_realloc(ptr, size));
}