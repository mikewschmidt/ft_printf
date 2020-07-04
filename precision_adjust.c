
#include <stdlib.h>
#include "libftprintf.h"
#include "libft.h"

void    precision_adjust(char *spec, t_param *param, char convchar)
{
        int             prec;
        char    *temp;
        int             offset;

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
                temp = (char*)ft_calloc(prec + 1 + offset, sizeof(char));
                ft_memset(temp, '0', prec - param->len + offset + offset);
                if (param->data[0] == '-')
                        temp[0] = '-';
                ft_strlcat(temp, param->data + offset, prec + 1 + offset);
                free(param->data);
                param->data = temp;
                param->len = prec + offset;
        }
        else if (prec == 0 && convchar == 'p' && ft_strncmp(param->data, "0x0", 3) == 0)
        {
                free(param->data);
                param->data = ft_strdup("0x");
                param->len = 2;
        }
        else if (prec == 0 && param->data[0] == '0' && param->len == 1)
        {
                free(param->data);
                param->data = ft_strdup("");
                param->len = 0;
        }
}
