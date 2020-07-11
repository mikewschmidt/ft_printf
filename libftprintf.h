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

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

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

typedef struct		s_spec
{
	int		prec_flag;
	int		zero_flag;
	int		left_flag;
	int		space_flag;
	int		plus_flag;
	int		width;
	int		prec;
	char		convchar;
}			t_spec;

int		ft_printf(const char *str, ...);
void		parse_spec(t_spec *fspec, const char *spec);
t_param		*replace_convchar(const t_spec *fspec, va_list args, t_param *param);
char    	*ft_btoxstr(int *arr);
char    	ft_tohex(int num);
void    	precision_adjust(const int spec, t_param *param, char convchar);
void    	ft_putlong_fd(long long int n, int fd);
char    	*ft_ltostr(long long int n);
char    	*ft_itoxstr(long num);
char		*ft_strappd(char *str, char *appstr, int strbase);

#endif
