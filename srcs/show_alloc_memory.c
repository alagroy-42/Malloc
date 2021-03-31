/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_memory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 16:19:10 by alagroy-          #+#    #+#             */
/*   Updated: 2021/04/06 15:04:07 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

void						print_addr(void *ptr)
{
	unsigned char	addr[18];
	unsigned char	buf[8];
	unsigned char	convert[] = "0123456789ABCDEF";
	int		i;

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

static void					print_zone(t_zone *zone)
{
	if (zone->type == TINY)
		ft_putstr("TINY : ");
	if (zone->type == SMALL)
		ft_putstr("SMALL : ");
	if (zone->type == LARGE)
		ft_putstr("LARGE : ");
	print_addr(zone->addr);
	ft_putchar('\n');
}

static void					print_alloc(t_block *block)
{
	print_addr(block + 1);
	ft_putstr(" - ");
	print_addr((void *)block + META_SIZE + block->size);
	ft_putstr(" : ");
	ft_putull(block->size);
	ft_putendl(" bytes");
}

static unsigned long long	print_zone_content(t_zone *zone)
{
	t_block				*block;
	unsigned long long	total;

	block = zone->addr;
	total = 0;
	print_zone(zone);
	while (block)
	{
		if (integrity_check(block) && !block->free)
		{
			print_alloc(block);
			total += block->size;
		}
		block = block->next;
	}
	return (total);
}

void						show_alloc_memory(void)
{
	int					i;
	unsigned long long	total;
	t_zone				*zones;

	i = -1;
	zones = g_malloc.zones;
	total = 0;
	while (zones && zones[++i].size)
	{
		total += print_zone_content(zones + i);
		if (zones[i].next)
		{
			zones = zones[i].next;
			i = -1;
		}
	}
	ft_putstr("Total : ");
	ft_putull(total);
	ft_putchar('\n');
}