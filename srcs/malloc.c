/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 21:50:53 by alagroy-          #+#    #+#             */
/*   Updated: 2021/04/06 15:34:21 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"
#include <malloc/malloc.h>

t_malloc	g_malloc = {0, 0, 0, 0};

void	*calloc(size_t count, size_t size)
{
	void	*ptr;

	ft_putendl("calloc");
	if (!(ptr = malloc(count * size)))
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

void	*malloc(size_t size)
{
	write(1, "malloc\n", 7);
	if (!g_malloc.nb_pages)
		init_malloc(size);
	return (allocate_block(size));
}