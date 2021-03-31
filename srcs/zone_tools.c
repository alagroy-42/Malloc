/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:32:31 by alagroy-          #+#    #+#             */
/*   Updated: 2021/04/06 12:53:43 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

int		get_new_zone_size(size_t size)
{
	int		min;

	if (size > SMALL)
		return (size);
	if (size <= TINY)
	{
		min = 250 * (TINY + META_SIZE);
		if (!(min % g_malloc.pagesize))
			return (min);
		else
			return (((min / g_malloc.pagesize) + 1)
					* g_malloc.pagesize);
	}
	min = 100 * (SMALL + META_SIZE);
	if (!(min % g_malloc.pagesize))
		return (min);
	else
		return (((min / g_malloc.pagesize) + 1)
				* g_malloc.pagesize);
}

t_zone	*find_new_zone_addr(void)
{
	t_zone	*zones;
	int		i;

	i = -1;
	zones = g_malloc.zones;
	while (zones && zones[++i].size)
	{
		if (zones[i].next)
		{
			zones = zones[i].next;
			i = -1;
			continue ;
		}
		if (i == g_malloc.pagesize / sizeof(t_zone))
		{
			if (!(zones[i].next = mmap_safe(g_malloc.pagesize)))
				return (NULL);
			zones = zones[i].next;
			i = -1;
		}
	}
	return (zones + i);
}

t_zone	*create_zone(size_t size)
{
	t_zone	*new_zone;
	t_block	block;

	new_zone = find_new_zone_addr();
	new_zone->size = get_new_zone_size(size);
	new_zone->type = get_malloc_type(size);
	new_zone->next = NULL;
	new_zone->addr = mmap_safe(new_zone->size);
	block = (t_block){MALLOC_MAGIC, 1, new_zone->size - META_SIZE, NULL};
	ft_memcpy(new_zone->addr, &block, META_SIZE);
	return (new_zone);
}
