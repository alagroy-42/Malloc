/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 13:00:13 by alagroy-          #+#    #+#             */
/*   Updated: 2021/04/08 16:05:47 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

void		free(void *ptr)
{
	t_block	*block;
	t_block	*free;

	ft_putendl("free");
	block = ptr - META_SIZE;
	if (!ptr || !integrity_check(block) || block->free)
		return ;
	block->free = 1;
	free = block;
	while (free && integrity_check(free) && free->free)
		free = free->next;
	block->next = free;
	block->size = free - block;
}
