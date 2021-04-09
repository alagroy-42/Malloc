/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:23:18 by alagroy-          #+#    #+#             */
/*   Updated: 2021/04/09 16:05:46 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

t_malloc		g_malloc = {NULL, 0, 0, 0};

void			*calloc(size_t count, size_t size)
{
	void	*ptr;

	size *= count;
	if (!(ptr = malloc(size)))
		return (NULL);
	ft_bzero(ptr, size);
	return (ptr);
}

void			*malloc(size_t size)
{
	if (!size)
		return (NULL);
	if (!g_malloc.zones)
		if (init_malloc(size) == EXIT_FAILURE)
			return (NULL);
	return (allocate_block(size));
}
