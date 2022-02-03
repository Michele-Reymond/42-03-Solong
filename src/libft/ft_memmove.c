/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:53:10 by mreymond          #+#    #+#             */
/*   Updated: 2021/10/31 12:02:35 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest;
	const char		*source;

	i = -1;
	dest = dst;
	source = src;
	if (src < dst && *source != '\0')
	{
		while (--n > 0)
			dest[n] = source[n];
		dest[n] = source[n];
	}
	else if (src > dst)
	{
		while (++i < n)
			dest[i] = source[i];
	}
	return (dest);
}
