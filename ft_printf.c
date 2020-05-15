/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmidt <mschmidt@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 19:48:31 by mschmidt          #+#    #+#             */
/*   Updated: 2020/05/15 15:30:30 by mschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

void	printf_conv_flags(const char **arg, const char flag)
{
	
}

char	*printf_parser(const char *str)
{
	int		i;
	const char	convchar[9];

	if (!str)
		return (0);
	i = 0;
	ft_strlcpy((char*)convchar, "cspdiuxX", 9);
	while (!ft_strchr(convchar, str[i]))
		i++;
	return(ft_substr(str, 0, (i + 1)));
}

char	*printf_flag_star(const char *pars, int num)
{
	int		i;
	char	*str;
	char	**split;

	i = 0;
	split = ft_split(pars, '*');
	str = ft_strjoin(split[0], ft_itoa(num));
	str = ft_strjoin(str, split[1]);
	free(split[0]);
	free(split[1]);
	return (str);
}

int		ft_printf(const char *str, ...)
{
	int				idx;
	va_list			args;
	unsigned char	c;
	char			*i;
	char			*temp;

	idx = 0;
	va_start(args, str);
	temp = printf_parser(ft_strchr(str, '%'));
	if (ft_strchr(temp, '*'))
		temp = printf_flag_star(temp, va_arg(args, int)); // Memory Leak here
	ft_putstr_fd(temp, 1);
	ft_putstr_fd("\n", 1);
	if (ft_strchr(temp, '*'))
		temp = printf_flag_star(temp, va_arg(args, int)); // Memory Leak here
	ft_putstr_fd(temp, 1);
	ft_putstr_fd("\n", 1);

	idx = 0;
	/*
	while (str[idx] != '\0')
	{

		if (str[idx] == '%')
		{
			idx++;
			if (str[idx] == 'c')
			{
				c = va_arg(args, int);
				write (1, &c, 1);
			}
			else if (str[idx] == 'i')
			{
				idx++;
				i = ft_itoa(va_arg(args, int));
				ft_putstr_fd(i, 1);
				ft_putstr_fd("\n", 1);
			}
		}		
		i++;
	}
	*/
	va_end(args);
	return (idx);
}

int		main()
{
	ft_printf("Your Mom! %-0*.*d Dude!", 11, 5, 7);
}
