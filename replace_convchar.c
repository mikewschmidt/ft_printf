
#include "libftprintf.h"
#include "libft.h"

static void	replace_part1(const t_spec *fspec, va_list args, t_param *param)
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
		if (!tempstr && (!fspec->prec || fspec->prec_flag == -1))
			tempstr = "(null)";
		else if (!tempstr)
			tempstr = (fspec->prec >= 6) ? "(null)" : "";
		param->data = (char*)ft_calloc(ft_strlen(tempstr) + 1, sizeof(char));
		ft_strlcpy(param->data, tempstr, ft_strlen(tempstr) + 1);
	}
}

static void	toupper_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
}

static void	replace_part2(const t_spec *fspec, va_list args, t_param *param)
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
		}
		if (fspec->convchar == 'X')
			toupper_str(param->data);
	}
}


t_param	*replace_convchar(const t_spec *fspec, va_list args, t_param *param)
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
		return (NULL);
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
