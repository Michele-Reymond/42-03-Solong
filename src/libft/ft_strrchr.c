/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:58:16 by mreymond          #+#    #+#             */
/*   Updated: 2021/10/31 12:03:59 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	lettre;

	i = 0;
	lettre = c;
	while (s[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (s[i] == lettre)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
