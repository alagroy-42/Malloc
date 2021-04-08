/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_memory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:28:12 by alagroy-          #+#    #+#             */
/*   Updated: 2021/04/08 18:19:13 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

void						print_addr(void *ptr)
{
	unsigned char	addr[18];
	unsigned char	buf[8];
	unsigned char	convert[] = "0123456789abcdef";
	int				i;

	i = 0;
	ft_memcpy(buf, &ptr, sizeof(void *));
	while (i < 16)
	{
		addr[17 - i - 1] = convert[buf[i / 2] / 16];
		addr[17 - i] = convert[buf[i / 2] % 16];
		i += 2;
	}
	ft_memcpy(addr, "0x", 2);
	write(1, addr, 18);
}

static void					display_block(t_block *block)
{
	print_addr(block + 1);
	ft_putstr(" - ");
	print_addr((void *)block + block->size + META_SIZE);
	ft_putstr(" : ");
	ft_putull(block->size);
	ft_putendl(" bytes");
}

static unsigned long long	display_zone(t_zone *zone)
{
	t_block *block;
	int		type;
	int		total;

	total = 0;
	type = zone->type;
	if (type == TINY)
		ft_putstr("TINY : ");
	else if (type == SMALL)
		ft_putstr("SMALL : ");
	else
		ft_putstr("LARGE : ");
	print_addr(zone);
	ft_putchar('\n');
	block = (t_block *)(zone + 1);
	while (block)
	{
		if (!block->free)
		{
			total += block->size;
			display_block(block);
		}
		block = block->next;
	}
	return (total);
}

void						show_alloc_memory(void)
{
	t_zone				**zone;
	t_zone				**end;
	int					i;
	unsigned long long	total;

	i = 0;
	total = 0;
	zone = g_malloc.zones;
	end = (void *)zone + *(size_t *)zone;
	while (zone[++i] && zone + i < end)
		total += display_zone(zone[i]);
	ft_putstr("Total : ");
	ft_putull(total);
	ft_putendl(" bytes");
}
