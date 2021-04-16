/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 14:20:43 by alagroy-          #+#    #+#             */
/*   Updated: 2021/04/14 15:19:32 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

int		integrity_check(t_block *block)
{
	return (get_block_zone(block) && (block->magic == MALLOC_MAGIC));
}

size_t	get_zone_min_size(t_block *block)
{
	t_zone	*zone;

	if (!(zone = get_block_zone(block)))
		return (0);
	if (zone->type == TINY)
		return (MIN_CHUNK_SIZE);
	if (zone->type == SMALL)
		return (TINY + 1);
	else
		return (LARGE);
}
