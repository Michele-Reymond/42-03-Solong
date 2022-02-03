/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 10:44:58 by mreymond          #+#    #+#             */
/*   Updated: 2021/11/01 15:22:21 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	str = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (str == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

// Applique la fonction ’f’ à chaque caractère de lachaine de caractères passée 
// en argument pour créer une nouvelle chaine de caractères (avec malloc(3))
// résultant des applications successives de ’f’

// PARAMS 
// #1. La chaine de caractères sur laquelle itérer
// #2. La fonction à appliquer à chaque caractère.

// RETURN
// La chaine de caractères résultant des applicationssuccessives de f. 
// Retourne NULL si l’allocationéchoue.