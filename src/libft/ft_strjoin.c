/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:02:48 by mreymond          #+#    #+#             */
/*   Updated: 2021/10/31 12:03:22 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	size_t	j;
	char	*str;
	size_t	len;

	i = -1;
	if (!s1)
		return (NULL);
	j = ft_strlen(s1);
	len = j + ft_strlen(s2) + 2;
	str = (char *)malloc(sizeof(char) * len);
	if (!str)
		return (NULL);
	while (s1[++i] != '\0')
		str[i] = s1[i];
	i = -1;
	while (s2[++i] != '\0')
	{
		str[j] = s2[i];
		j++;
	}
	str[j] = '\0';
	return (str);
}

// Alloue (avec malloc(3)) et retourne une nouvelle chaine, 
// résultat de la concaténation de s1 et s2.

// Parametres
// #1. La chaine de caractères préfixe.
// #2. La chaine de caractères suffixe.

// RETURN
// La nouvelle chaine de caractères. 
// NULL sil’allocation échoue.