
#include <stdlib.h>
#include "libftprintf.h"

static int     *tobinary(long num)
{
        int i;
        int *num_arr;
        int neg;

        i = 63;
        num_arr = (int*)ft_calloc((i + 1), sizeof(int));
        if (num < 0)
        {
                neg = 1;
                num *= -1;
                num -= 1;
        }
        while (i >= 0)
        {
                num_arr[i] = (neg) ? !(num % 2) : (num % 2);
                num = num / 2;
                i--;
        }
        return (num_arr);
}

char    *ft_itoxstr(long num)
{
        char    *mod;
        char    *div;
        char    *xstr;
        char    temp;
        int     *num_arr;

        if (num < 0)
        {
                num_arr = tobinary(num);
                xstr = ft_btoxstr(num_arr);
                free(num_arr);
                return (xstr);
        }
        if (num == 0)
                return (NULL);
        else
        {
                div = ft_itoxstr(num / 16);
                temp = ft_tohex(num % 16);
                mod = ft_calloc(2, sizeof(char));
                ft_strlcpy(mod, &temp, 2);
        }
        if (div)
        {
                xstr = ft_strjoin(div, mod);
                free(div);
                free(mod);
                return (xstr);
        }
        else
                return (mod);
}
