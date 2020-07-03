
#include <stdlib.h>
#include "libft.h"

void    zeropad_adjust(char spec, t_param *param)
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

