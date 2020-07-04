
#include <stdarg.h>
#include <stdlib.h>
#include "libft.h"
#include "libftprintf.h"

void    replace_stars(char **spec, va_list args)
{
        int     i;
        char    **strarr;
        char    *str;
        char    *temp;
        char    *input_param;

        i = 0;
        strarr = ft_split(*spec, '*');
        str = ft_strdup("");
        while (strarr[i + 1] != 0)
        {
                temp = ft_strjoin(str, strarr[i]);
                free(str);
                str = temp;
                input_param = ft_itoa(va_arg(args, int));
                temp = ft_strjoin(str, input_param);
                free(input_param);
                free(str);
                str = temp;
                free(strarr[i]);
                i++;
        }
        temp = ft_strjoin(str, strarr[i]);
        free(str);
        str = temp;
        free(strarr[i]);
        free(strarr);
        *spec = str;
}
