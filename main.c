/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 11:41:53 by alagroy-          #+#    #+#             */
/*   Updated: 2021/03/31 16:47:01 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

int		main(void)
{
	char *str;
	char *str2;
	
	write(1, "beginning\n", 11);
	str = ft_strdup("lolilol");
	str2 = ft_strdup("lolilol");
	write(1, "free 1\n", 8);
	free(str);
	write(1, "free 2\n", 8);
	free(str2);
	str = ft_strdup("lolilol");
	str2 = ft_strdup("lolilol");
	write(1, "free 3\n", 8);
	free(str);
	write(1, "free 4\n", 8);
	free(str2);
	return 0;
}