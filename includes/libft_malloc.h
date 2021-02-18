/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_malloc.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 20:29:38 by alagroy-          #+#    #+#             */
/*   Updated: 2021/02/18 14:16:04 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

# include "libft.h"
# include <errno.h>
# include <unistd.h>
# include <sys/mman.h>
# include <sys/resource.h>

# define TINY  256
# define SMALL 1024
# define LARGE 4096

# define TINY_ZONE 49152
# define SMALL_ZONE 102400

typedef	unsigned long long	t_zsize;
typedef	char				t_ztype;

typedef struct				s_zone
{
	t_zsize	size;
	t_ztype	type;
	t_list	*alloc_list;
	void	*addr;
}							t_zone;

typedef struct				s_alloc
{
	void	*addr;
	size_t	size;
}							t_alloc;

void						*malloc(size_t size);

#endif
