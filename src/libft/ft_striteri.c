/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 12:16:27 by mreymond          #+#    #+#             */
/*   Updated: 2021/10/31 12:25:18 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}

// Applique la fonction f à chaque caractère de lachaîne de 
// caractères transmise comme argument, et en passant son index comme 
// premier argument. Chaque caractère est transmis par adresse à f 
// pour être modifié si nécessaire.

// PARAMS
// #1. La chaine de caractères sur laquelle itérer.
// #2. La fonction à appliquer à chaque caractère.