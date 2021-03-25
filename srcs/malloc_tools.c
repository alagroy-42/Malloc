/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 13:26:23 by alagroy-          #+#    #+#             */
/*   Updated: 2021/03/25 14:35:46 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

void	*mmap_safe(size_t size)
{
	int		nb_pages;

	nb_pages = size / g_malloc.pagesize;
	if (size % g_malloc.pagesize)
		nb_pages++;
	if (g_malloc.nb_pages + nb_pages > g_malloc.rlimit / g_malloc.pagesize)
		return (NULL);
	g_malloc.nb_pages += nb_pages;
	return (mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE
				| MAP_ANONYMOUS, -1, 0));
}

int		get_malloc_type(size_t size)
{
	if (size > SMALL)
		return (LARGE);
	if (size < TINY)
		return (TINY);
	return (SMALL);
}

int		init_malloc(size_t size)
{
	struct rlimit	limit;

	g_malloc.pagesize = getpagesize();
	getrlimit(RLIMIT_DATA, &limit);
	g_malloc.rlimit = limit.rlim_cur;
	if (!(g_malloc.zones = mmap_safe(g_malloc.pagesize)))
		return (EXIT_FAILURE);
	ft_bzero(g_malloc.zones, g_malloc.pagesize);
	if (!(create_zone(size)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
