/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btoxstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmidt <mschmidt@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 08:34:53 by mschmidt          #+#    #+#             */
/*   Updated: 2020/08/17 08:50:04 by mschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*ft_btoxstr(int *arr)
{
	int		i;
	int		j;
	int		calc;
	char	*hex;

	i = 0;
	j = 0;
	calc = 0;
	hex = (char*)malloc(8 * sizeof(char));
	while (i < 64)
	{
		calc += arr[i + 3] * (1);
		calc += arr[i + 2] * (2);
		calc += arr[i + 1] * (2 * 2);
		calc += arr[i + 0] * (2 * 2 * 2);
		hex[j] = ft_tohex(calc);
		calc = 0;
		i += 4;
		j++;
	}
	return (hex);
}
