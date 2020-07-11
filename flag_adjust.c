
#include "libftprintf.h"
#include "libft.h"

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

static void    zeropad_adjust(char spec, t_param *param)
{
        int     i;
        char    *parameter;

        i = 0;
        parameter = param->data;
        if (ft_strchr(parameter, '-'))
                parameter[i++] = '-';
        if (ft_strchr(parameter, '+'))
                parameter[i++] = '+';
        while ((parameter[i] == ' ' || parameter[i] == '-' || parameter[i] == '+') && spec == '0')
                parameter[i++] = '0';
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

void		flag_adjust(const t_spec *fspec, t_param *param)
{
	if (fspec->prec_flag == 1)
		precision_adjust(fspec->prec, param, fspec->convchar);
	if (fspec->plus_flag && param->data[0] != '-')
		if (fspec->convchar == 'i' || fspec->convchar == 'd')
		{
			param->data = ft_strappd("+", param->data, 1);
			param->len++;
		}
	if (fspec->width)
		width_adjust(fspec->width, param);
	if (fspec->zero_flag == 1 && !fspec->left_flag && fspec->prec_flag != 1)
		zeropad_adjust('0', param);
	if (fspec->left_flag)
		left_adjust(param);
	if (fspec->space_flag && param->data[0] != '-' && ft_atoi(param->data))
	{
		if (!(fspec->convchar == 'd' && fspec->width) && fspec->convchar != 'u') 
		{
			param->data = ft_strappd(" ", param->data, 1);
			param->len++;
		}
	}
}
