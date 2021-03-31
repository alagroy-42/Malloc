/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_malloc.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 20:29:38 by alagroy-          #+#    #+#             */
/*   Updated: 2021/04/06 13:02:17 by alagroy-         ###   ########.fr       */
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
# define SMALL 4096
# define LARGE 4097
# define NB_ALLOCT 250
# define NB_ALLOCS 100
# define MALLOC_MAGIC 0x90abcdef

typedef	unsigned long long	t_zsize;
typedef	int					t_ztype;

typedef struct				s_block
{
	uint32_t		magic;
	uint8_t			free;
	size_t			size;
	struct s_block	*next;
}							t_block;

# define META_SIZE sizeof(t_block)

typedef struct				s_zone
{
	t_zsize			size;
	void			*addr;
	struct s_zone	*next;
	t_ztype			type;
}							t_zone;

typedef struct				s_malloc
{
	t_zone			*zones;
	int				pagesize;
	rlim_t			rlimit;
	rlim_t			nb_pages;
}							t_malloc;

extern t_malloc				g_malloc;

void						*malloc(size_t size);
void						free(void *ptr);
void						*realloc(void *ptr, size_t size);
int							init_malloc(size_t size);
void						*mmap_safe(size_t size);
t_zone						*create_zone(size_t size);
int							get_malloc_type(size_t size);
void						*allocate_block(size_t size);
int							integrity_check(t_block *ptr);
void						show_alloc_memory(void);
void						print_addr(void *ptr);
// REMOVE BEFORE PUSH
void						*calloc(size_t count, size_t size);

#endif
