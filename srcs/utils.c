/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:26:11 by alagroy-          #+#    #+#             */
/*   Updated: 2021/04/20 11:15:13 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

void	*mmap_safe(size_t size)
{
	size_t	nb_pages;
	void	*ptr;

	nb_pages = size / g_malloc.pagesize;
	if (size % g_malloc.pagesize)
		nb_pages++;
	if (g_malloc.nb_pages + nb_pages > g_malloc.rlimit / g_malloc.pagesize)
		return (NULL);
	g_malloc.nb_pages += nb_pages;
	if (!(ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE
				| MAP_ANONYMOUS, -1, 0)))
		return (NULL);
	ft_bzero(ptr, size);
	return (ptr);
}

size_t	get_malloc_type(size_t size)
{
	if (size > SMALL)
		return (LARGE);
	if (size <= TINY)
		return (TINY);
	return (SMALL);
}

/*
**	ZONE_SIZE + META_SIZE is aligned so we just have to align the next block
**	to get only aligned blocks
*/

size_t	align_size(size_t size)
{
	if (!((size + META_SIZE) % ALIGN))
		return (size);
	return (size + (ALIGN - ((size + META_SIZE) % ALIGN)));
}

t_zone	*get_block_zone(t_block *block)
{
	int		i;
	t_zone	**zone;
	t_zone	**end;

	i = 0;
	zone = g_malloc.zones;
	end = (void *)zone + *(uint64_t *)zone;
	while (zone + ++i < end && zone[i])
	{
		if ((t_zone *)block > zone[i] && (void *)block < (void *)zone[i]
				+ zone[i]->size)
			return (zone[i]);
	}
	return (NULL);
}

int		init_malloc(size_t size)
{
	struct rlimit	limit;

	g_malloc.pagesize = (size_t)getpagesize();
	getrlimit(RLIMIT_DATA, &limit);
	g_malloc.rlimit = limit.rlim_cur;
	if (!(g_malloc.zones = mmap_safe(g_malloc.pagesize)))
		return (EXIT_FAILURE);
	*(g_malloc.zones) = (t_zone *)g_malloc.pagesize;
	if (!(create_zone(size)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
