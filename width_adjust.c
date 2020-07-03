
#include <stdlib.h>
#include "libft.h"

void    width_adjust(int spec, t_param *param)
{
        int     width;
        char    *temp;

        width = spec;
        if (width < 0)
                return ;
        if (param->len < width)
        {
                temp = (char*)ft_calloc(width + 1, sizeof(char));
                temp = ft_memset(temp, ' ', width - param->len);
                ft_strlcat(temp, param->data, width + 1);
                free(param->data);
                param->data = temp;
                param->len = width;
        }
}
