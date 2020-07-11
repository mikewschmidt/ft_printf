
#include <stdlib.h>
#include "libftprintf.h"
#include "libft.h"

static void	str_prec_adjust(int prec, t_param *param)
{
	char	*temp;

	temp = (char*)ft_calloc(prec + 1, sizeof(char));
	ft_strlcpy(temp, param->data, prec + 1);
	free(param->data);
	param->data = temp;
	param->len = prec;
}

static void	ptr_prec_adjust(int prec, t_param *param)
{
	char	*temp;

	temp = (char*)ft_calloc(prec + 3, sizeof(char));
	ft_memset(temp, '0', prec - param->len + 4);
	ft_strlcat(temp, param->data + 2, prec + 3);
	free(param->data);
	param->data = temp;
	ft_memcpy(param->data, "0x", 2);
	param->len = prec + 2;
}

static void	nonchars_prec_adjust(int prec, t_param *param, int offset)
{
	char	*temp;

	temp = (char*)ft_calloc(prec + 1 + offset, sizeof(char));
	ft_memset(temp, '0', prec - param->len + offset + offset);
	if (param->data[0] == '-')
		temp[0] = '-';
	ft_strlcat(temp, param->data + offset, prec + 1 + offset);
	free(param->data);
	param->data = temp;
	param->len = prec + offset;
}

static void	null_prec_adjust(t_param *param, char *nullstr)
{
	free(param->data);
	param->data = ft_strdup(nullstr);
	param->len = ft_strlen(param->data);
}

void		precision_adjust(int prec, t_param *param, char convchar)
{
        char    	*temp;
        int             offset;

        offset = (param->data[0] == '-' && convchar != 's') ? 1 : 0;
        if (!prec)
                prec = 0;
	if (prec < 0)
		prec = 1;
        if (convchar == 's' && prec < param->len)
		str_prec_adjust(prec, param);
        else if (convchar == 'p' && prec > param->len - 2)
		ptr_prec_adjust(prec, param); 
        else if (convchar != 's' && convchar != 'c' && prec > param->len - offset)
		nonchars_prec_adjust(prec, param, offset);
        else if (prec == 0 && convchar == 'p' && ft_strncmp(param->data, "0x0", 3) == 0)
		null_prec_adjust(param, "0x");
        else if (prec == 0 && param->data[0] == '0' && param->len == 1)
		null_prec_adjust(param, "");
}
