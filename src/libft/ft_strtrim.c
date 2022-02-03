/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 13:40:15 by mreymond          #+#    #+#             */
/*   Updated: 2021/10/31 12:04:05 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	starttrim(const char *s1, const char *set)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	start = 0;
	while (s1[j] != '\0')
	{
		i = 0;
		while (set[i] != '\0')
		{
			if (set[i] == s1[j])
			{
				start++;
				break ;
			}
			i++;
		}
		if (set[i] == '\0')
			break ;
		j++;
	}
	return (start);
}

static int	endtrim(const char *s1, const char *set, int start)
{
	int	i;
	int	j;
	int	end;

	i = 0;
	end = ft_strlen(s1);
	j = end - 1;
	while (j > start)
	{
		i = 0;
		while (set[i] != '\0')
		{
			if (set[i] == s1[j])
			{
				end--;
				break ;
			}
			i++;
		}
		if (set[i] == '\0')
			break ;
		j--;
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		start;
	int		end;
	int		len;

	if (!s1)
		return (NULL);
	start = starttrim(s1, set);
	end = endtrim(s1, set, start);
	len = end - start;
	str = ft_substr(s1, start, len);
	return (str);
}

// Alloue (avec malloc(3)) et retourne une copie de la chaine ’s1’, 
// sans les caractères spécifiés dans ’set’ au début et à la fin 
// de la chaine decaractères.

// PARAM 
// #1. La chaine de caractères à trimmer.
// #2. Le set de reference de caractères à trimmer.

// RETURN
// La chaine de caractères trimmée. NULL sil’allocation échoue