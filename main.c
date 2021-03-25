/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 11:41:53 by alagroy-          #+#    #+#             */
/*   Updated: 2021/03/25 16:11:26 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"
#include <stdio.h>

int		main(void)
{
	char	*str;

	if (!(str = malloc(43)))
	{
		ft_printf("problem !!\n");
		return (1);
	}
	ft_memset(str, 'X', 42);
	str[42] = '\0';
	ft_putendl(str);
	return 0;
}