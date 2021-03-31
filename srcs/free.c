/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 12:44:02 by alagroy-          #+#    #+#             */
/*   Updated: 2021/04/06 16:07:36 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

void		free_block(t_block *ptr)
{
	t_block *next;

	if (!integrity_check(ptr) || !ptr->free)
		return ;
	ptr->free = 1;
	next = ptr->next;
	if (!integrity_check(next) || !next->free)
		return ;
	ptr->next = next;
	ptr->size += next->size + META_SIZE;
	next->magic = 0;
}

void		free(void *ptr)
{
	write(1, "free\n", 5);
	if (!ptr)
		return ;
	free_block(ptr - META_SIZE);
}