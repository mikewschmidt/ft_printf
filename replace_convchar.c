/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_convchar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmidt <mschmidt@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 07:59:22 by mschmidt          #+#    #+#             */
/*   Updated: 2020/08/17 08:57:46 by mschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void		replace_part1(const t_spec *fspec, va_list args, t_param *param)
{
	char	*tempstr;

	if (fspec->convchar == 'd' || fspec->convchar == 'i')
		param->data = ft_itoa(va_arg(args, int));
	else if (fspec->convchar == 'p')
	{
		param->data = ft_itoxstr(va_arg(args, unsigned long));
		if (!param->data)
		{
			param->data = (char*)ft_calloc(6, sizeof(char));
			param->data[0] = '0';
		}
		param->data = ft_strappd("0x", param->data, 1);
	}
	else if (fspec->convchar == 's')
	{
		tempstr = va_arg(args, char*);
		if (!tempstr)
			tempstr = "(null)";
		param->data = (char*)ft_calloc(ft_strlen(tempstr) + 1, sizeof(char));
		ft_strlcpy(param->data, tempstr, ft_strlen(tempstr) + 1);
	}
}

static void		toupper_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
}

static void		replace_part2(t_spec *fspec, va_list args, t_param *param)
{
	int	j;

	j = 0;
	if (fspec->convchar == 'c')
	{
		param->data = (char*)ft_calloc(2, sizeof(char));
		(*param).data[0] = va_arg(args, unsigned int);
		param->len = 1;
	}
	else if (fspec->convchar == 'u')
		param->data = ft_ltostr(va_arg(args, unsigned int));
	else if (fspec->convchar == 'X' || fspec->convchar == 'x')
	{
		param->data = ft_itoxstr(va_arg(args, unsigned int));
		if (!param->data)
		{
			param->data = (char*)ft_calloc(2, sizeof(char));
			param->data[0] = '0';
			fspec->hash_flag = 0;
		}
		else if (fspec->hash_flag == 1)
			param->data = ft_strappd("0x", param->data, 1);
		if (fspec->convchar == 'X')
			toupper_str(param->data);
	}
}

t_param			*replace_convchar(t_spec *fspec, va_list args, t_param *param)
{
	param->len = -1;
	if (ft_strchr("dips", fspec->convchar))
		replace_part1(fspec, args, param);
	else if (ft_strchr("cuxX", fspec->convchar))
		replace_part2(fspec, args, param);
	else if (fspec->convchar == '%')
	{
		param->data = (char*)ft_calloc(2, sizeof(char));
		param->data[0] = '%';
		param->len = 1;
	}
	else
	{
		param->len = 0;
		return (NULL);
	}
	if (param->len == -1 && param->data)
		param->len = ft_strlen(param->data);
	return (param);
}
