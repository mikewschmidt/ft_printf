/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmidt <mschmidt@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 20:36:08 by mschmidt          #+#    #+#             */
/*   Updated: 2020/06/29 00:56:29 by mschmidt         ###   ########.fr       */
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
	char		*data;
	int		len;
}			t_param;

char	get_hex(int num)
{
	if (num <= 9)
		return (num + '0');
	else 
		return ('a' - 10 + num);
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
	while (i < 64)
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

int	*tobinary(long num)
{
	int i;
	int *num_arr;
	int neg;

        i = 63;
	num_arr = (int*)malloc(64 * sizeof(int));
	if (num < 0)
	{
		neg = 1;
		num *= -1;
		num -= 1;
	}
	while (i >= 0)
	{
		num_arr[i] = (neg) ? !(num % 2) : (num % 2);
		printf("%i", num_arr[i]);
		num = num / 2;
		i--;
	}
		printf("\n");
	return (num_arr);
}

char	*itoxstr(long num)
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

void	conv_adjust(char spec, t_param *param)
{
	//int		i;
	char	*ptr;
	char	*temp;
	///int	num;

	//i = 0;
	ptr = NULL;
	if (spec == 'd')
	{
		// this does NOTHING!  REMOVE THIS TRASH!
		temp = param->data; 
		ptr = temp;
	}
	else if (spec == 's') //Do nothing for now
	{
		// this does NOTHING!  REMOVE THIS TRASH!
		temp = param->data;
		temp = ptr;
	}
	else if (spec == 'c')
	{
	//	printf("it's a char!");
	}
}

void	precision_adjust(char *spec, t_param *param, char convchar)
{
	int		prec;
	char	*temp;
	int		offset;

	offset = (param->data[0] == '-' && convchar != 's') ? 1 : 0;
	if (spec)
	{
		prec = ft_atoi(spec);
		if (prec < 0)
			prec = 1;
	}
	else
		prec = 0;
	if (convchar == 's' && prec < param->len)
	{
		temp = (char*)ft_calloc(prec + 1, sizeof(char));
		ft_strlcpy(temp, param->data, prec + 1);
		free(param->data);
		param->data = temp;
		param->len = prec;
	}
	else if (convchar == 'p' && prec > param->len - 2)
	{
		temp = (char*)ft_calloc(prec + 3, sizeof(char));
		ft_memset(temp, '0', prec - param->len + 4);
		ft_strlcat(temp, param->data + 2, prec + 3);
		free(param->data);
		param->data = temp;
		ft_memcpy(param->data, "0x", 2);
		param->len = prec + 2;
	}
	else if (convchar != 's' && convchar != 'c' && prec > param->len - offset)
	{
		//printf("precision: %i is greater than length of input parameter\n", prec);
		temp = (char*)ft_calloc(prec + 1 + offset, sizeof(char));
		ft_memset(temp, '0', prec - param->len + offset + offset);
		//printf("param->len: %i\n", param->len);
		///printf("temp: %s\n", temp);
		if (param->data[0] == '-')
			temp[0] = '-';
		ft_strlcat(temp, param->data + offset, prec + 1 + offset);
		free(param->data);
		param->data = temp;
		param->len = prec + offset;
	}
	else if (prec == 0 && convchar == 'p' && ft_strncmp(param->data, "0x0", 3) == 0)
	{
		free(param->data); // Don't free data just destroy it!!!
		param->data = ft_strdup("0x");
		param->len = 2;
	}
	else if (prec == 0 && param->data[0] == '0' && param->len == 1)
	{
		free(param->data); // Don't free data just destroy it!!!
		param->data = ft_strdup(""); 
		param->len = 0;
	}
}

void	width_adjust(int spec, t_param *param)
{
	int	width;
	char	*temp;

	width = spec;
	//printf("width: %i", width);
	if (width < 0)
		return ;
	if (param->len < width)
	{
		//ft_putstr_fd("making it wider \n", 1); //REMOVE
		temp = (char*)ft_calloc(width + 1, sizeof(char));
		temp = ft_memset(temp, ' ', width - param->len);
		ft_strlcat(temp, param->data, width + 1);
		free(param->data);
		param->data = temp;
		param->len = width;
	}
}

void	left_adjust(char spec, t_param *param)
{
	int	i;
	char	*parameter;
	char	*temp;

	i = 0;
	parameter = param->data;
	spec = (spec) ? 1 : 0; 
	while (parameter[i] == ' ')
		i++;
	temp = (char*)ft_calloc(param->len + 1, sizeof(char));
	ft_memset(temp, ' ', param->len);
	ft_memcpy(temp, parameter + i, param->len - i); 
	//printf("\n i: %i | len_param: %i |  temp: |%s| \n", i, len_param, temp); 
	free(param->data);
	param->data = temp;
}

void	zeropad_adjust(char spec, t_param *param)
{
	int	i;
	char	*parameter;

	i = 0;
	parameter = param->data;
	if (ft_strchr(parameter, '-'))
		parameter[i++] = '-';
	if (ft_strchr(parameter, '+'))
		parameter[i++] = '+';
	//printf("Zero padding");
	while ((parameter[i] == ' ' || parameter[i] == '-' || parameter[i] == '+') && spec == '0')
		parameter[i++] = '0';
}

void	replace_stars(char **spec, va_list args)
{
	int	i;
	char	**strarr;
	char	*str;
	char	*temp;
	char	*input_param;

	i = 0;
	strarr = ft_split(*spec, '*');
	str = ft_strdup("");
	//printf("ft_strlen: %li\n", ft_strlen(str));
	while (strarr[i + 1] != 0)
	{
		temp = ft_strjoin(str, strarr[i]);
		free(str);
		str = temp;
		input_param = ft_itoa(va_arg(args, int));
		temp = ft_strjoin(str, input_param);
		free(input_param);
		free(str);
		str = temp;
		//printf("strarr: %s\n",strarr[i]);
		free(strarr[i]);
		i++;
	}
	//printf("strarr: %s\n",strarr[i]);
	temp = ft_strjoin(str, strarr[i]);
	free(str);
	str = temp;
	free(strarr[i]);
	free(strarr);
	*spec = str;
	//return (str);
}

void	replace_spec(char *spec, va_list args, t_param *param)
{
	int		i;
	int		j;
	const char	convchars[10];
	char		convchar;
	int		prec_flag;
	int		zero_flag;
	int		left_flag;
	int		space_flag;
	int		plus_flag;
	int		width;
	char		*prec;
	char		*tempstr;
	//int		spec_size;
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
	space_flag = 0;
	plus_flag = 0;
	ft_strlcpy((char*)convchars, "cspdiuxX%", 10);
	replace_stars(&spec, args);
	//printf("spec after stars replace: %s \n", spec);
	while (!ft_strchr(convchars, spec[i]) && spec[i] != '\0')
	{
		if (i == 1 && spec[i] == ' ')
			space_flag = 1;
		if (spec[i] == '+')
		{
			space_flag = 0;
			plus_flag = 1;
		}
		if (spec[i] == '.')
		{
			prec_flag = 1; 
			//printf("prec_flag set \n");
		}
		if (spec[i] == '-' && prec_flag == 0)
			left_flag = 1;
		else if (spec[i] == '-' && prec_flag == 1)
			prec_flag = -1;
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
			tempstr = (char*)ft_calloc(j + 1, sizeof(char));
			ft_strlcpy(tempstr, spec + i - j, j + 1); 
			width = ft_atoi(tempstr);
			free(tempstr);
			//printf("width: %i\n", width);
			i--;
			//else
			//	prec = spec[i];
		}
		else if (ft_isdigit(spec[i]) && (prec_flag == 1 || prec_flag == -1))
		{
			j = 0;
			while (ft_isdigit(spec[i]))
			{
				j++;
				i++;
			}
			//printf("prec_flag: %i \n", prec_flag);
			if (prec_flag == 1)
			{
				prec = (char*)ft_calloc(j + 1, sizeof(char));
				ft_strlcpy(prec, spec + i - j, j + 1);
				//printf("prec: %s \n", prec);
			}
			i--;
		}
		i++;
	}
	//printf("specifier size:%i \n ", i + 1);
	//spec_size = i + 1;
	//printf("zero_flag: %i | left_flag: %i | width: %i  | prec_flag: %i | prec: %s  | space_flag: %i | plus_flag: %i | conv chr: %c \n",
	//		zero_flag, left_flag, width, prec_flag, prec, space_flag, plus_flag, spec[i]); //REMOVE
	//////////  STORE THE INPUT PARAMETER /////////////
	convchar = convchars[ft_strchr(convchars, spec[i]) - convchars]; //find better way to get convchar
	if (convchar == 'd' || convchar == 'i')
	{
		param->data = ft_itoa(va_arg(args, int));
		param->len = ft_strlen(param->data);
		if (space_flag && param->data[0] != '-' && !width && !prec)
			width = param->len + 1;
		//ft_putstr_fd("input parameter:  ",1);
		//ft_putstr_fd(param->data, 1);
		//ft_putstr_fd("\n", 1);
	}
	else if (convchar == 'u')
	{
		//uint_temp = va_arg(args, unsigned int);
		//ft_putlong_fd(uint_temp, 1);
		//ft_putstr_fd("<-- this is uint_temp\n", 1);
		param->data = ft_ltostr(va_arg(args, unsigned int));
		param->len = ft_strlen(param->data);
		//param = ft_itoa(va_arg(args, unsigned int));
		//ft_putnbr_fd((unsigned int)va_arg(args, unsigned int), 1);
		//ft_putstr_fd("\n", 1);
	}
	else if (convchar == 'p')
	{
		param->data = itoxstr(va_arg(args, unsigned long));
		if (!param->data)
		{
			param->data = (char*)ft_calloc(2, sizeof(char));
			param->data[0] = '0';
		}
		if (convchar == 'p')
		{
			tempstr = ft_strjoin("0x", param->data);
			free(param->data);
			param->data = tempstr;
			//printf("param->data: %s \n", param->data);
		}
		param->len = ft_strlen(param->data);
		//ft_putnbr_fd((unsigned int)va_arg(args, unsigned int), 1);
		//ft_putstr_fd("\n", 1);
	}
	else if (convchar == 'X' || convchar == 'x')
	{
		param->data = itoxstr(va_arg(args, unsigned int));
		//ft_putstr_fd(*conv_param, 1);
		if (!param->data)
		{
			param->data = (char*)ft_calloc(2, sizeof(char));
			param->data[0] = '0';
		}
		param->len = ft_strlen(param->data);
		if (convchar == 'X')
		{
			j = 0;
			while ((param->data)[j] != '\0')
			{
				(param->data)[j] = ft_toupper((param->data)[j]);
				j++;
			}
		}
	}
	else if (convchar == 'c')
	{
		param->data = (char*)ft_calloc(2, sizeof(char));
		(*param).data[0] = va_arg(args, unsigned int);
		param->len = 1; 
	}
	else if (convchar == 's')
	{
		//ft_putstr_fd("this is a string \n", 1);
		tempstr = va_arg(args, char*);
		if (!tempstr)
			tempstr = "(null)";
		param->len = ft_strlen(tempstr);
		param->data = (char*)ft_calloc(param->len + 1, sizeof(char));
		ft_strlcpy(param->data, tempstr, param->len + 1);
	}
	else if (convchar == '%')
	{
		//printf("found %% \n");
		param->data = (char*)ft_calloc(2, sizeof(char));
		param->len = 1; 
		ft_strlcpy(param->data, "%", 2);
		//return (spec_size);
		//return ;
	}
	else
		//printf("what the ! happened!?");
		return ;

	//param->data = ft_strdup(param->data);

	//ft_putstr_fd("input param: ", 1); //REMOVE
	//ft_putstr_fd(*conv_param, 1); //REMOVE
	//ft_putstr_fd("\n",1); //REMOVE 
	
	if (prec_flag == 1)
	{
		//printf("prec: %s \n", prec);
		precision_adjust(prec, param, convchar);
		//printf("  execute precision_adjust - param->data: %s\n", param->data);
		free(prec);
	}
	if (plus_flag && param->data[0] != '-' && (convchar == 'i' || convchar == 'd'))
	{
		//Add a + sign before the first digit
		tempstr = (char*)ft_calloc(param->len + 2, sizeof(char));
		tempstr[0] = '+';
		ft_strlcat(tempstr, param->data, param->len + 2);
		free(param->data);
		param->data = tempstr;
		param->len = ft_strlen(param->data);
	}
	if (width)
	{
		//printf("  execute width_adjust(%i, param)\n", width);
		width_adjust(width, param);
		width = 0; //I don't think I need to set this as 0 since this is not a loop anymore 
	}
	if (zero_flag == 1 && !left_flag && prec_flag != 1)
	{
		//ft_putstr_fd("  execute zeropad_adjust(spec[i], conv_param)\n",1);
		zeropad_adjust('0', param);
		zero_flag = 0;
	}
	if (left_flag)
	{
		//ft_putstr_fd("  execute left_adjust(spec[i], conv_param)\n",1);
		left_adjust(spec[i], param);
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
	free(spec);
	//return (spec_size);
}

char	*extract_spec(const char *str)
{
	int	i;
	char	convchars[10];

	i = 1;
	ft_strlcpy(convchars, "cspdiuxX%", 10);
	while (!ft_strchr(convchars, str[i]))
		i++;
	return (ft_substr(str, 0, i + 1));
}

int		ft_printf(const char *str, ...)
{
	int	idx;
	int	count;
	char	*conv_output;
	t_param	*param;
	char	*spec;
	//char	**arr_param;
	//char	(*fun_ptr)(char*, char);
	va_list	args;

	param = (t_param*)ft_calloc(3, sizeof(t_param));
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
			spec = extract_spec(str + idx);
			//printf("--spec: %s\n", spec);
			replace_spec(spec, args, param);
			write(1, param->data, param->len);
			//ft_putstr_fd(conv_output, 1);
			//printf("end idx: %i \n", idx);
			idx += ft_strlen(spec);
			count += param->len;
			free(param->data);
			free(spec);
		}
	}
	//ft_putstr_fd("\n", 1); 
	va_end(args);
	free(param);
	return(count);
}
