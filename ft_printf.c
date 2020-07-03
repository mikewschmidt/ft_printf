
#include <stdlib.h>
#include "libftprintf.h"

static char	*extract_spec(const char *str)
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
			spec = extract_spec(str + idx);
			replace_spec(spec, args, param);
			write(1, param->data, param->len);
			idx += ft_strlen(spec);
			count += param->len;
			free(param->data);
			free(spec);
		}
	}
	va_end(args);
	free(param);
	return(count);
}
