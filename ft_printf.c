/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmidt <mschmidt@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 20:36:08 by mschmidt          #+#    #+#             */
/*   Updated: 2020/05/25 18:06:02 by mschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"  //FIX THIS TRASH!!
#include <stdio.h> // REMOVE THIS LINE!!!
typedef struct		s_call_stack
{
	void			*fun_ptr;
	char			*spec;
}					t_call_stack;

char	get_hex(int num)
{
	if (num <= 9)
		return (num + '0');
	else 
		return (num + 87);
}

char	*btoxstr(int *arr)
{
	int i;
	int j;
	int calc;
	char *hex;

	i = 0;
	j = 0;
	calc = 0;
	hex = (char*)malloc(8 * sizeof(char));
	while (i < 32)
	{
	        calc += arr[i + 3] * (1);
		calc += arr[i + 2] * (2);
		calc += arr[i + 1] * (2 * 2);
		calc += arr[i + 0] * (2 * 2 * 2);
		hex[j] = get_hex(calc);
		calc = 0;
		i += 4;
		j++;
	}
	return (hex);
}

int	*tobinary(int num)
{
	int i;
	int *num_arr;
	int neg;

        i = 31;
	num_arr = (int*)malloc(32 * sizeof(int));
	if (num < 0)
	{
		neg = 1;
		num *= -1;
		num -= 1;
	}
	while (i >= 0)
	{
		num_arr[i] = (neg) ? !(num % 2) : (num % 2);
		num = num / 2;
		i--;
	}
	return (num_arr);
}

char	*itoxstr(int num)
{
	char	*mod;
	char	*div;
	char	*xstr;
	char	temp;
	int	*num_arr;
	
	if (num < 0)
	{
		num_arr = tobinary(num);
		xstr = btoxstr(num_arr);
		free(num_arr);
		return (xstr);
	}
		
	if (num == 0)
		return (NULL);
	else
	{
		div = itoxstr(num / 16);
		temp = get_hex(num % 16);
		mod = ft_calloc(2, sizeof(char));
		ft_strlcpy(mod, &temp, 2);
	}
	if (div)
	{
		xstr = ft_strjoin(div, mod);
		free(div);
		free(mod);
		return (xstr);
	}
	else
		return (mod);
}

void	conv_adjust(char spec, char **param)
{
	//int		i;
	char	*ptr;
	char	*temp;

	//i = 0;
	ptr = NULL;
	if (spec == 'd')
	{
		temp = *param;
		ptr = temp;
	}
	else if (spec == 's') //Do nothing for now
	{
		temp = *param;
		temp = ptr;
	}
}

void	width_adjust(char *spec, char **param)
{
	int		len_param;
	int		width;
	char	*temp;

	len_param = ft_strlen(*param);
	width = ft_atoi(spec);
	if (len_param < width)
	{
		//ft_putstr_fd("making it wider \n", 1); //REMOVE
		temp = (char*)ft_calloc(width + 1, sizeof(char));
		temp = ft_memset(temp, ' ', width - len_param);
		ft_strlcat(temp, *param, width + 1);
		free(*param);
		*param = temp;
	}
}

int		spec_parser(const char *spec, va_list args, char **conv_param)
{
	int		i;
	int		j;
	const char	convchar[9];
	//int		prec_flag;
	int		zero_flag;
	char		*width;
	//char		prec;
	//char		*param;
	int			spec_size;

	//ft_putstr_fd("spec coming in:  ", 1); //REMOVE
	//ft_putstr_fd(spec, 1); //REMOVE
	//ft_putstr_fd("\n", 1); //REMOVE
	i = 1;
	j = 0;
	//prec_flag = 0;
	zero_flag = -1;
	width = 0;
	//prec = 0;
	ft_strlcpy((char*)convchar, "cspdiuxX", 9);
	while (!ft_strchr(convchar, spec[i]))
	{
		//if (spec[i] == '.')
		//	prec_flag = 1; 
		if (ft_isdigit(spec[i]) && zero_flag == -1 && spec[i] == 0)
			zero_flag = 1;
		else
			zero_flag = 0;
		if (ft_isdigit(spec[i]) && zero_flag != -1)
		{
			//if (prec_flag == 0)
			//width = spec[i];
			j = 0;
			while (ft_isdigit(spec[i]))
			{
				j++;
				i++;
			}
			//printf("width size: %i \n", j);
			width = (char*)ft_calloc(j + 1, sizeof(char));
			ft_strlcpy(width, spec + i - j, j + 1); 
			//printf("width: %s", width);
			i--;
			//else
			//	prec = spec[i];
		}
		i++;
	}
	spec_size = i + 1;
	//printf("zero_flag: %i | width: %c | conv chr: %c \n",
	//		zero_flag, width, spec[i]); //REMOVE
	//////////  STORE THE INPUT PARAMETER /////////////
	if (spec[i] == 'd' || spec[i] == 'i')
	{
		*conv_param = ft_itoa(va_arg(args, int));
		//ft_putstr_fd("input paramter:  ",1);
		//printf("%x", va_arg(args,int));
		//ft_putstr_fd(*conv_param, 1);
		//ft_putstr_fd("\n", 1);
	}
	else if (spec[i] == 'u')
	{
		*conv_param = ft_itoa(va_arg(args, unsigned int));
		//ft_putnbr_fd((unsigned int)va_arg(args, unsigned int), 1);
		//ft_putstr_fd("\n", 1);
	}
	else if (spec[i] == 'x')
	{
		*conv_param = itoxstr(va_arg(args, unsigned int));
		//ft_putnbr_fd((unsigned int)va_arg(args, unsigned int), 1);
		//ft_putstr_fd("\n", 1);
	}
	else if (spec[i] == 'X')
	{
		*conv_param = itoxstr(va_arg(args, unsigned int));
		//ft_putstr_fd(*conv_param, 1);
		j = 0;
		while (j < (*conv_param)[j])
		{
			(*conv_param)[j] = ft_toupper((*conv_param)[j]);
			j++;
		}
	}
	else if (spec[i] == 'c' || spec[i] == 's')
		*conv_param = (char*)va_arg(args, int*);

	*conv_param = ft_strdup(*conv_param);

	//ft_putstr_fd("input param: ", 1); //REMOVE
	//ft_putstr_fd(*conv_param, 1); //REMOVE
	//ft_putstr_fd("\n",1); //REMOVE 

	while (i > 0)
	{
		//ft_putchar_fd(spec[i], 1); //REMOVE
		if (ft_strchr(convchar, spec[i]))
		{
			//ft_putstr_fd("  execute conv_adjust(spec[i], conv_param)\n",1);
			conv_adjust(spec[i], conv_param);
		}
		//else if (ft_isdigit(spec[i]) && prec_flag)
		//{
		//	ft_putstr_fd("  execute precision_adjust(spec[i], conv_param)\n",1);
		//	prec_flag = 0;
		//	precision_adjust(spec[i], conv_param);
		//}
		else if (ft_isdigit(spec[i]) && width)
		{
			//ft_putstr_fd("  execute width_adjust(spec[i], conv_param)\n",1);
			width_adjust(width, conv_param);
			width = 0; //so it doesn't loop again if width is 2 or more digits
		}
		else if (spec[i] == 0 && zero_flag == 1)
		{
			ft_putstr_fd("  execute zeropad_adjust(spec[i], conv_param)\n",1);
			zero_flag = 0;
		}
		else if (spec[i] == '-')
			ft_putstr_fd("  execute left_adjust(spec[i], conv_param)\n",1);
			
		i--;
	}
	//ft_putstr_fd("\n", 1); //REMOVE
	return (spec_size);
}

int		ft_printf(const char *str, ...)
{
	int		idx;
	int		count;
	char	*conv_output;
	//char	**arr_param;
	//char	(*fun_ptr)(char*, char);
	va_list	args;

	idx = 0;
	count = 0;
	va_start(args, str);
	while (str[idx] != '\0')
	{
		if (str[idx] != '%')
		{
			ft_putchar_fd(str[idx], 1);
			idx++;
			count++;
		}
		else
		{
			idx += spec_parser(ft_strchr(str, '%'), args, &conv_output);
			ft_putstr_fd(conv_output, 1);
			count += ft_strlen(conv_output);
			free(conv_output);
		}
	}
	//ft_putstr_fd("\n", 1); 
	va_end(args);
	return(count);
}
