
#include <stdlib.h>
#include "libft.h"

void    left_adjust(char spec, t_param *param)
{
        int     i;
        char    *parameter;
        char    *temp;

        i = 0;
        parameter = param->data;
        spec = (spec) ? 1 : 0;
        while (parameter[i] == ' ')
                i++;
        temp = (char*)ft_calloc(param->len + 1, sizeof(char));
        ft_memset(temp, ' ', param->len);
        ft_memcpy(temp, parameter + i, param->len - i);
        free(param->data);
        param->data = temp;
}

