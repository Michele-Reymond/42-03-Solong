/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:07:52 by mreymond          #+#    #+#             */
/*   Updated: 2021/10/31 12:12:33 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countwords(char const *s, char c)
{
	int		i;
	int		words;
	size_t	sep;

	i = 0;
	words = 0;
	sep = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c)
			words++;
		if (s[i] == c)
			sep++;
		i++;
	}
	if (s[i - 1] == c)
		words--;
	if (words <= 0)
		words = 1;
	if (sep == ft_strlen(s))
		words = 0;
	return (words);
}

static int	copywords(char **strtab, char const *s, char c, int words)
{
	int	len;
	int	i;
	int	y;

	len = 0;
	i = 0;
	y = 0;
	while (s[i] != '\0' && y < words)
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		len = 0;
		while (s[i] != c && s[i] != '\0')
		{
			i++;
			len++;
		}
		strtab[y] = (char *)malloc(sizeof(char) * len + 1);
		if (!strtab[y])
			return (0);
		ft_strlcpy(strtab[y], &s[i - len], len + 1);
		y++;
	}
	return (y);
}

char	**ft_split(char const *s, char c)
{
	char	**strtab;
	int		i;
	int		y;
	int		words;

	i = 0;
	y = 0;
	if (s == NULL)
		return (NULL);
	words = countwords(s, c);
	strtab = (char **)malloc(sizeof(char *) * words + 1);
	if (!strtab)
		return (NULL);
	y = copywords(strtab, s, c, words);
	strtab[y] = 0;
	return (strtab);
}

// Alloue (avec malloc(3)) et retourne un tableau de chaines 
// de caracteres obtenu en séparant ’s’ à l’aide du caractère ’c’, 
// utilisé comme délimiteur. Le tableau doit être terminé par NULL.

// PARAM 
// #1. La chaine de caractères à découper.
// #2. Le caractère délimitant.

// RETURN
// Le tableau de nouvelles chaines de caractères,résultant du découpage. 
// NULL si l’allocation échoue.