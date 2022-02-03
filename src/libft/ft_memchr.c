/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 10:54:46 by mreymond          #+#    #+#             */
/*   Updated: 2021/10/31 12:02:23 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	lettre;

	lettre = c;
	i = 0;
	str = (unsigned char *)s;
	if (n == 0)
		return (NULL);
	while (str && i < n - 1)
	{
		if (*str == lettre)
			return ((void *) str);
		str++;
		i++;
	}
	if (*str == lettre)
		return ((void *) str);
	return (NULL);
}

// The memchr() function locates the first occurrence 
// of c (converted to an unsigned char) in string s.

// RETURNThe memchr() function returns a pointer 
// to the byte located, or NULL if no such byte 
// exists within n bytes.