/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmidt <mschmidt@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 16:39:16 by mschmidt          #+#    #+#             */
/*   Updated: 2020/05/15 16:39:50 by mschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>

typedef struct		s_call_stack
{
        void                    *fun_ptr;
        char                    *spec;
}			t_call_stack;

typedef struct          s_param
{
        char            *data;
        int             len;
}                       t_param;

char    get_hex(int num)
{
        if (num <= 9)
                return (num + '0');
        else
                return ('a' - 10 + num);
}

int	ft_printf(const char *str, ...);
void	replace_spec(char *spec, va_list args, t_param *param);
char    *ft_btoxstr(int *arr);
void    left_adjust(char spec, t_param *param);
char    ft_tohex(int num);
void    precision_adjust(char *spec, t_param *param, char convchar);
void    ft_putlong_fd(long long int n, int fd);
char    *ft_ltostr(long long int n);
char    *ft_itoxstr(long num);
void    zeropad_adjust(char spec, t_param *param);
void    width_adjust(int spec, t_param *param);
void    replace_stars(char **spec, va_list args);


