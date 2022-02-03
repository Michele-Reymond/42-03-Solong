/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:03:05 by mreymond          #+#    #+#             */
/*   Updated: 2021/10/31 12:03:47 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	if (len < 0)
		return ((char *)haystack - 1);
	while (haystack[i] != '\0' && ((i < len - 1) || ft_strlen(needle) == 1)
		&& i <= (ft_strlen(haystack) - ft_strlen(needle)) && len > 0)
	{
		j = 0;
		if (needle[j] == haystack[i])
		{
			k = i - 1;
			while (needle[j] == haystack[++k] && needle[j] != '\0')
				j++;
			if (needle[j] == '\0' && k <= len)
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return (NULL);
}
