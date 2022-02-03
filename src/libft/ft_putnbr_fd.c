/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 18:46:02 by mreymond          #+#    #+#             */
/*   Updated: 2021/10/31 12:02:53 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		i;
	char	ptr[12];

	i = 0;
	if (n == INT_MIN)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n == 0)
		write(fd, "0", 1);
	if (n < 0)
	{
		n = -n;
		write(fd, "-", 1);
	}
	while (n > 0)
	{
		ptr[i] = n % 10 + 48;
		n /= 10;
		i++;
	}
	while (--i > -1)
		write(fd, &ptr[i], 1);
}
