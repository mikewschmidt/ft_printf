/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltostr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmidt <mschmidt@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 08:40:54 by mschmidt          #+#    #+#             */
/*   Updated: 2020/08/17 08:50:17 by mschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	nbrcnt(long long int n)
{
	int		cnt;

	cnt = 0;
	if (n <= 0)
		cnt++;
	while (n != 0)
	{
		n /= 10;
		cnt++;
	}
	return (cnt);
}

char		*ft_ltostr(long long int n)
{
	int		sign;
	int		cnt;
	char	*str;

	sign = 1;
	if (n < 0)
		sign = -1;
	cnt = nbrcnt(n);
	str = (char*)ft_calloc(cnt + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (cnt--)
	{
		str[cnt] = ((n % 10) * sign) + '0';
		n /= 10;
	}
	if (sign == -1)
		str[0] = '-';
	return (str);
}
