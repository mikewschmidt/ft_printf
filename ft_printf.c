/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmidt <mschmidt@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 19:48:31 by mschmidt          #+#    #+#             */
/*   Updated: 2020/05/15 19:49:36 by mschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include "./libft/libft.h"  // FIX THIS TRASH!!

/*
void	printf_conv_flags(const char **arg, const char flag)
{
	
}
*/

void	ft_lstprint(t_list *lst, char *delimiter)
{
	while (lst != NULL)
	{
		ft_putstr_fd(lst->content, 1);
		ft_putstr_fd(delimiter, 1);
		lst = lst->next;
	}
}

char	*printf_parser(const char *str, t_list **stack)
{
	int		i;
	const char	convchar[9];
	int		start;

	if (!str)
		return (0);
	i = 1;
	start = 0;
	ft_strlcpy((char*)convchar, "cspdiuxX", 9);
	ft_putstr_fd("parser str: ", 1);
	ft_putstr_fd(str, 1);
	while (!ft_strchr(convchar, str[i]))
	{
		if (ft_isdigit(str[i]))
		{
			if(ft_isdigit(str[i + 1]) && start == 0)
				start = i;
		}
		else if (start > 0 && !ft_isdigit(str[i]))
		{
			ft_lstadd_front(stack, ft_lstnew(ft_substr(str, start, (i - start))));
			ft_lstadd_front(stack, ft_lstnew(ft_substr(&str[i], 0, 1)));
			start = 0;
		}
		else
			ft_lstadd_front(stack, ft_lstnew(ft_substr(&str[i], 0, 1)));
		i++;
		ft_lstprint(*stack, "");
		ft_putstr_fd("\n", 1);
	}
	ft_lstadd_front(stack, ft_lstnew(ft_substr(&str[i], 0, 1)));
	ft_lstprint(*stack, " ");
	ft_putstr_fd("\n", 1);
	return(ft_substr(str, 0, (i + 1)));
}

char	*printf_replace_star(const char *pars, int num)
{
	int		i;
	char	*str;
	char	**split;

	i = 0;
	split = ft_split(pars, '*');
	str = ft_strjoin(split[0], ft_itoa(num));
	str = ft_strjoin(str, split[1]);
	free(split[0]);
	free(split[1]);
	return (str);
}

int		ft_printf(const char *str, ...)
{
	int				idx;
	va_list			args;
	//unsigned char	c;
	//char			*i;
	char			*temp;
	t_list			*f_stack;

	idx = 0;
	va_start(args, str);
	ft_putstr_fd("input string: ", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\n", 1);
	while (str[idx] != '%')
		idx++;
	temp = printf_parser(&str[idx], &f_stack);
	f_stack = NULL;

	//if (ft_strchr(temp, '*'))
	//	temp = printf_replace_star(temp, va_arg(args, int)); // Memory Leak here
	//if (ft_strchr(temp, '*'))
	//	temp = printf_replace_star(temp, va_arg(args, int)); // Memory Leak here
	
	idx = 0;
	/*
	while (str[idx] != '\0')
	{

		if (str[idx] == '%')
		{
			idx++;
			if (str[idx] == 'c')
			{
				c = va_arg(args, int);
				write (1, &c, 1);
			}
			else if (str[idx] == 'i')
			{
				idx++;
				i = ft_itoa(va_arg(args, int));
				ft_putstr_fd(i, 1);
				ft_putstr_fd("\n", 1);
			}
		}		
		i++;
	}
	*/
	va_end(args);
	return (idx);
}
