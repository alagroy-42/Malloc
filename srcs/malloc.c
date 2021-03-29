/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 21:50:53 by alagroy-          #+#    #+#             */
/*   Updated: 2021/03/29 17:11:32 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

t_malloc g_malloc = {0, 0, 0, 0};

void	*malloc(size_t size)
{
	return (NULL);
	if (!g_malloc.nb_pages)
		init_malloc(size);
	return (allocate_block(size));
}
