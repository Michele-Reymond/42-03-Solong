/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 14:46:42 by mreymond          #+#    #+#             */
/*   Updated: 2021/10/31 12:01:42 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	i;

	i = -1;
	ptr = malloc(size * count);
	if (!ptr)
		return (NULL);
	while (++i < size * count)
		ptr[i] = 0;
	return (ptr);
}

// The calloc() function contiguously allocates enough space for count
// objects that are size bytes of memory each and returns a pointer to the
// allocated memory.  The allocated memory is filled with bytes of value
// zero.

// RETURN
// If successful, calloc(), malloc(), realloc(), reallocf(), valloc(), and
// aligned_alloc() functions return a pointer to allocated memory.  If
// there is an error, they return a NULL pointer and set errno to ENOMEM.