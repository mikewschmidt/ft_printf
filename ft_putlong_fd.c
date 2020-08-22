/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlong_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmidt <mschmidt@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 08:33:56 by mschmidt          #+#    #+#             */
/*   Updated: 2020/08/17 08:34:20 by mschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putlong_fd(long long int n, int fd)
{
	char	c;

	if (n == -9223372036854775807)
		write(fd, "-9223372036854775807", 20);
	else
	{
		if (n < 0)
		{
			n *= -1;
			write(fd, "-", 1);
		}
		if (n < 10)
		{
			c = n + '0';
			write(fd, &c, 1);
		}
		else
		{
			ft_putlong_fd(n / 10, fd);
			ft_putlong_fd(n % 10, fd);
		}
	}
}
