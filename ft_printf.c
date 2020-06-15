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

typedef struct		s_param
{
	int		len;
	char*		data;
}			t_param;

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

static int	nbrcnt(long long int n)
{
	int	cnt;

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

char	*ft_ltostr(long long int n)
{
	int	sign;
	int	cnt;
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

void	conv_adjust(char spec, char **param)
{
	//int		i;
	char	*ptr;
	char	*temp;
	///int	num;

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
	else if (spec == 'c')
	{
	//	printf("it's a char!");
	}
}

void	precision_adjust(char *spec, char **param, len_param, char convchar)
{
	int	len_param;
	int	prec;
	char	*temp;

	len_param = ft_strlen(*param);
	if(spec)
		prec = ft_atoi(spec);
	else
		prec = 0;
	if (prec < len_param && convchar == 's')
	{
		temp = (char*)ft_calloc(prec + 1, sizeof(char));
		ft_strlcpy(temp, *param, prec + 1);
		free(*param);
		*param = temp;
	}
	else if (prec > len_param && convchar != 's')
	{
		//printf("precision: %i is greater than lenght of input parameter\n", prec);
		temp = (char*)ft_calloc(prec + 1, sizeof(char));
		ft_memset(temp, '0', prec - len_param);
		ft_strlcat(temp, *param, prec + 1);
		free(*param);
		*param = temp;
	}
	else if (prec == 0 && **param == '0')
	{
		free(*param);
		*param = ft_strdup(""); 
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

void	left_adjust(char spec, char **param)
{
	int	i;
	char	*parameter;
	char	*temp;
	int	len_param;

	i = 0;
	parameter = *param;
	len_param = ft_strlen(parameter);
	spec = (spec) ? 1 : 0; 
	while (parameter[i] == ' ')
		i++;
	temp = (char*)ft_calloc(len_param + 1, sizeof(char));
	ft_memset(temp, ' ', len_param);
	ft_memcpy(temp, parameter + i, len_param - i); 
	//printf("\n i: %i | len_param: %i |  temp: |%s| \n", i, len_param, temp); 
	free(*param);
	*param = temp;
}

void	zeropad_adjust(char spec, char **param)
{
	int	i;
	char	*parameter;

	i = 0;
	parameter = *param;
	if (ft_strchr(parameter, '-'))
		parameter[i++] = '-';
	while ((parameter[i] == ' ' || parameter[i] == '-') && spec == '0')
		parameter[i++] = '0';
}

int	spec_parser(const char *spec, va_list args, char **conv_param)
{
	int		i;
	int		j;
	const char	convchars[10];
	char		convchar;
	int		prec_flag;
	int		zero_flag;
	int		left_flag;
	char		*width;
	char		*prec;
	//char		*param;
	int		len_param;
	int			spec_size;
	unsigned int	uint_temp;

	//ft_putstr_fd("spec coming in:  ", 1); //REMOVE
	//ft_putstr_fd(spec, 1); //REMOVE
	//ft_putstr_fd("\n", 1); //REMOVE
	i = 1;
	j = 0;
	prec_flag = 0;
	zero_flag = -1;
	width = 0;
	prec = 0;
	left_flag = 0;
	ft_strlcpy((char*)convchars, "cspdiuxXi%", 11);
	while (!ft_strchr(convchars, spec[i]) && spec[i] != '\0')
	{
		if (spec[i] == '.')
		{
			prec_flag = 1; 
			//printf("prec_flag set \n");
		}
		if (spec[i] == '-')
			left_flag = 1;
		if (spec[i] == '0' && zero_flag == -1)
		{
			zero_flag = 1;
			//printf("zero padding \n");
		}
		else if (ft_isdigit(spec[i]) && zero_flag == -1)
		{
			zero_flag = 0;
			//printf("No padding: %c \n", spec[i]);
		}
		if (ft_isdigit(spec[i]) && width == 0  && prec_flag == 0 && zero_flag != -1)
		{
			j = 0;
			while (ft_isdigit(spec[i]))
			{
				j++;
				i++;
			}
			//printf("width size: %i \n", j);
			width = (char*)ft_calloc(j + 1, sizeof(char));
			ft_strlcpy(width, spec + i - j, j + 1); 
			//printf("width: %s\n", width);
			i--;
			//else
			//	prec = spec[i];
		}
		else if (ft_isdigit(spec[i]) && prec_flag == 1)
		{
			j = 0;
			while (ft_isdigit(spec[i]))
			{
				j++;
				i++;
			}
			prec = (char*)ft_calloc(j + 1, sizeof(char));
			ft_strlcpy(prec, spec + i - j, j + 1);
			//printf("prec: %s \n", prec);
			i--;
		}
		i++;
	}
	//printf("specifier size:%i \n ", i + 1);
	spec_size = i + 1;
	//printf("zero_flag: %i | width: %s | conv chr: %c \n",
	//		zero_flag, width, spec[i]); //REMOVE
	//////////  STORE THE INPUT PARAMETER /////////////
	convchar = convchars[ft_strchr(convchars, spec[i]) - convchars] ;
	if (convchar == 'd' || convchar == 'i')
	{
		*conv_param = ft_itoa(va_arg(args, int));
		len_param = ft_strlen(*conv_param);
		//ft_putstr_fd("input paramter:  ",1);
		//printf("%x", va_arg(args,int));
		//ft_putstr_fd(*conv_param, 1);
		//ft_putstr_fd("\n", 1);
	}
	else if (convchar == 'u')
	{
		//uint_temp = va_arg(args, unsigned int);
		//ft_putlong_fd(uint_temp, 1);
		//ft_putstr_fd("<-- this is uint_temp\n", 1);
		*conv_param = ft_ltostr(va_arg(args, unsigned int));
		len_param = ft_strlen(*conv_param);
		//*conv_param = ft_itoa(va_arg(args, unsigned int));
		//ft_putnbr_fd((unsigned int)va_arg(args, unsigned int), 1);
		//ft_putstr_fd("\n", 1);
	}
	else if (convchar == 'x')
	{
		*conv_param = itoxstr(va_arg(args, unsigned int));
		len_param = ft_strlen(*conv_param);
		if (!*conv_param)
		{
			*conv_param = (char*)ft_calloc(2, sizeof(char));
			**conv_param = '0';
		}
		//ft_putnbr_fd((unsigned int)va_arg(args, unsigned int), 1);
		//ft_putstr_fd("\n", 1);
	}
	else if (convchar == 'X')
	{
		*conv_param = itoxstr(va_arg(args, unsigned int));
		len_param = ft_strlen(*conv_param);
		//ft_putstr_fd(*conv_param, 1);
		if (!*conv_param)
		{
			*conv_param = (char*)ft_calloc(2, sizeof(char));
			**conv_param = '0';
		}
		j = 0;
		while ((*conv_param)[j] != '\0')
		{
			(*conv_param)[j] = ft_toupper((*conv_param)[j]);
			j++;
		}
	}
	else if (convchar == 'c')
	{
		*conv_param = (char*)ft_calloc(2, sizeof(char));
		(*conv_param)[0] = va_arg(args, unsigned int);
		len_param = 1; 
	}
	else if (convchar == 's')
	{
		//ft_putstr_fd("this is a string \n", 1);
		*conv_param = va_arg(args, char*);
		len_param = ft_strlen(*conv_param);
	}	
	else if (convchar == '%')
	{
		//printf("found %% \n");
		*conv_param = (char*)ft_calloc(2, sizeof(char));
		len_param = 1; 
		ft_strlcpy(*conv_param, "%", 2);
		return (spec_size);
	}
	else
		printf("what the ! happened!?");

	*conv_param = ft_strdup(*conv_param);

	//ft_putstr_fd("input param: ", 1); //REMOVE
	//ft_putstr_fd(*conv_param, 1); //REMOVE
	//ft_putstr_fd("\n",1); //REMOVE 
	
	if (prec_flag)
	{
		//ft_putstr_fd("  execute precision_adjust(spec[i], conv_param)\n",1);
		precision_adjust(prec, conv_param, len_param, convchar);
		prec_flag = 0;
	}
	if (width)
	{
		//ft_putstr_fd("  execute width_adjust(spec[i], conv_param)\n",1);
		width_adjust(width, conv_param, len_param);
		width = 0; //so it doesn't loop again if width is 2 or more digits
	}
	if (zero_flag && !left_flag)
	{
		//ft_putstr_fd("  execute zeropad_adjust(spec[i], conv_param)\n",1);
		zeropad_adjust('0', conv_param, len_param);
		zero_flag = 0;
	}
	if (left_flag)
	{
		//ft_putstr_fd("  execute left_adjust(spec[i], conv_param)\n",1);
		left_adjust(spec[i], conv_param, len_param);
	}
	if (convchar == 'c')
	{
		//while (**conv_param)
		//{
		//	printf("while loop");
		//	write (1, *conv_param++, 1);
		//}
		//write (1, *conv_param, 1); 
		//spec_size++;
	}
/*
	while (i > 0)
	{
		//ft_putchar_fd(spec[i], 1); //REMOVE
		if (ft_strchr(convchars, spec[i]))
		{
			//ft_putstr_fd("  execute conv_adjust(spec[i], conv_param)\n",1);
			//conv_adjust(spec[i], conv_param);
		}
		else if (ft_isdigit(spec[i]) && prec_flag)
		{
			ft_putstr_fd("  execute precision_adjust(spec[i], conv_param)\n",1);
			precision_adjust(prec, conv_param, convchar);
			prec_flag = 0;
		}
		else if (ft_isdigit(spec[i]) && width)
		{
			//ft_putstr_fd("  execute width_adjust(spec[i], conv_param)\n",1);
			width_adjust(width, conv_param);
			width = 0; //so it doesn't loop again if width is 2 or more digits
		}
		else if (spec[i] == '0' && zero_flag == 1)
		{
			//ft_putstr_fd("  execute zeropad_adjust(spec[i], conv_param)\n",1);
			zeropad_adjust(spec[i], conv_param);
			zero_flag = 0;
		}
		else if (spec[i] == '-')
		{
			//ft_putstr_fd("  execute left_adjust(spec[i], conv_param)\n",1);
			left_adjust(spec[i], conv_param);
		}
			
		i--;
	}
	//ft_putstr_fd("\n", 1); //REMOVE
*/
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
			//printf("start idx: %i | ", idx);
			idx += spec_parser(str + idx, args, &conv_output);
			ft_putstr_fd(conv_output, 1);
			//printf("end idx: %i \n", idx);
			count += ft_strlen(conv_output);
			free(conv_output);
		}
	}
	//ft_putstr_fd("\n", 1); 
	va_end(args);
	return(count);
}
