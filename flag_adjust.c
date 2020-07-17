
#include "libftprintf.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h> //REMOVE THIS LINE

static void    width_adjust(const int spec, t_param *param)
{
	int     width;
	char    *temp;

	width = spec;
	if (width < 0)
		return ;
    if (param->len < width)
	{
		temp = (char*)ft_calloc(width - param->len + 1, sizeof(char));
		temp = ft_memset(temp, ' ', width - param->len);
		param->data = ft_strappd(temp, param->data, 1);
		free(temp);
		param->len = width;
	}
}

static void    zeropad_adjust(t_spec *fspec, t_param *param)
{
        int     i;
		char	*data;
		int		offset;
		char	*prefix;

        i = 0;
		data = param->data;
		//printf("param->data: %s\n", data);
        if (ft_strchr(data, '-'))
			data[i++] = '-';
        if (ft_strchr(data, '+'))
			data[i++] = '+';
		if (fspec->hash_flag)
		{
			prefix = (ft_strchr(param->data, 'x')) ? "0x" : "0X";
			offset = ft_strnstr(data, prefix, param->len) - data;
			ft_memcpy(data + offset, "  ", 2);
			ft_memcpy(data, prefix, 2);
			i += 2;
		}
        while ((data[i] == ' ' || data[i] == '-' || data[i] == '+'))
                data[i++] = '0';
}

static void    left_adjust(t_param *param)
{
        int     i;
        char    *parameter;
        char    *temp;

        i = 0;
        parameter = param->data;
        while (parameter[i] == ' ')
                i++;
        temp = (char*)ft_calloc(param->len + 1, sizeof(char));
        ft_memset(temp, ' ', param->len);
        ft_memcpy(temp, parameter + i, param->len - i);
        free(param->data);
        param->data = temp;
}

static void		space_adjust(t_spec *fspec, t_param *param, int origin_len)
{
	//if (fspec->convchar == 'i' || fspec->width <= origin_len || fspec->left_flag || fspec->zero_flag)
	if (fspec->left_flag)
	{
		//printf("adding a space | len: %i | width: %i\n", origin_len, fspec->width);
		param->data = ft_strappd(" ", param->data, 1);
		param->len++;
	}
	else if (fspec->width >= origin_len && fspec->zero_flag)
	{
		param->data[0] = ' ';
	}
}
void		flag_adjust(t_spec *fspec, t_param *param)
{
	int		origin_len;

	origin_len = param->len;
	if (param->data[0] == '-')
		fspec->space_flag = 0;
	if (fspec->prec_flag == 1)
		precision_adjust(fspec->prec, param, fspec);
	if (fspec->plus_flag && param->data[0] != '-')
		if (fspec->convchar == 'i' || fspec->convchar == 'd')
		{
			param->data = ft_strappd("+", param->data, 1);
			param->len++;
		}
	if (fspec->width)
		width_adjust(fspec->width - fspec->space_flag, param);
	if (fspec->zero_flag == 1 && !fspec->left_flag && fspec->prec_flag != 1)
		zeropad_adjust(fspec, param);
	if (fspec->left_flag)
		left_adjust(param);
	//printf("space_flag: %i | param->data[0]: %c | width: %i | origin_len: %i\n",fspec->space_flag, param->data[0], fspec->width, origin_len);
	if (fspec->space_flag && param->data[0] != '-' && param->data != '\0' && fspec->convchar != 'u')
	{
		param->data = ft_strappd(" ", param->data, 1);
		param->len++;
		//space_adjust(fspec, param, origin_len);
	}
}
