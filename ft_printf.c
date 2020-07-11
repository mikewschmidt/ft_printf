
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "libftprintf.h"

static char	*replace_stars(char *spec, va_list args)
{
	int     i;
	char    **strarr;
	char    *str;
	char    *temp;
	char    *input_param;

	i = 0;
	if (!ft_strchr(spec, '*'))
		return (spec);
	strarr = ft_split(spec, '*');
	str = ft_strdup("");
	while (strarr[i + 1] != 0)
	{
		str = ft_strappd(str, strarr[i], 0);
		input_param = ft_itoa(va_arg(args, int));
		str = ft_strappd(str, input_param, 0);
		free(input_param);
		free(strarr[i]);
		i++;
	}
	str = ft_strappd(str, strarr[i], 0);
	free(strarr[i]);
	free(strarr);
	free(spec);
	return(str);
}

static void	replace_fspec(char *input_spec, va_list args, t_param *param)
{
	int		i;
	int		j;
	t_spec		*fspec;

	i = 1;
	j = 0;
	input_spec = replace_stars(input_spec, args);
	fspec = (t_spec*)ft_calloc(1, sizeof(t_spec));
	parse_spec(fspec, input_spec);
	if (!fspec->convchar)
	{
		free(fspec);
		free(input_spec);
		return ;
	}
	free(input_spec);
	param = replace_convchar(fspec, args, param);
	if (!param)
	{
		free(fspec);
		return ;
	}
	flag_adjust(fspec, param);
	free(fspec);
}

static char	*extract_spec(const char *str)
{
	int	i;
	char	convchars[10];

	i = 1;
	ft_strlcpy(convchars, "cspdiuxX%", 10);
	while (!ft_strchr(convchars, str[i]) && str[i] != '\0') 
		i++;
	return (ft_substr(str, 0, i + 1));
}

static int	replace_put_fspec(const char *str, va_list args, t_param *param, int *idx)
{
	char	*input_spec;

	input_spec = extract_spec(str + *idx);
	*idx += ft_strlen(input_spec);
	replace_fspec(input_spec, args, param);
	write(1, param->data, param->len);
	free(param->data);
	return (param->len);
}

int		ft_printf(const char *str, ...)
{
	int	idx;
	int	count;
	t_param	*param;
	va_list	args;

	idx = 0;
	count = 0;
	param = (t_param*)ft_calloc(1, sizeof(t_param));
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
			count += replace_put_fspec(str, args, param, &idx);
	}
	va_end(args);
	free(param);
	return(count);
}
