
#include <stdarg.h>
#include <stdlib.h>
#include "libft.h"
#include "libftprintf.h"

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
	unsigned int	uint_temp;

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
		param->data = ft_itoxstr(va_arg(args, unsigned long));
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
		param->data = ft_itoxstr(va_arg(args, unsigned int));
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
	free(spec);
}

