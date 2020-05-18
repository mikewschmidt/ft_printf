/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmidt <mschmidt@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 19:53:47 by mschmidt          #+#    #+#             */
/*   Updated: 2020/05/18 05:17:55 by mschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include "./libft/libft.h" // FIX THIS TRASH!!

void	left_adjust(t_list **lst);
void	zeropad_adjust(t_list **lst);
void	width_adjust(t_list **lst);
void	precision_adjust(t_list **lst);
t_list	*conv_stack(void *param, char conv);

void	ft_lstprint(t_list *lst, const char *delim)
{
	t_list	*temp;

	temp = lst;
	while (temp)
	{
		ft_putstr_fd(temp->content, 1);
		ft_putstr_fd(delim, 1);
		temp = temp->next;
	}

}

void	printf_parser(t_list **stack, const char *str)
{
	int		i;
	const char	convchar[9];

	i = 1;
	ft_strlcpy((char*)convchar, "cspdiuxX", 9);
	// CHECK INPUT
	ft_putstr_fd("parser input str: ", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\n", 1);
	////////
	while (!ft_strchr(convchar, str[i]) && str[i] != '\0')
	{
		ft_lstadd_front(stack, ft_lstnew(ft_substr(&str[i], 0, 1)));
		i++;
	}
	ft_lstadd_front(stack, ft_lstnew(ft_substr(&str[i], 0, 1)));
}

t_list	*ft_lstfind(t_list *lst, void *content)
{
	while (lst)
	{
		if (!ft_strncmp(lst->content, content, ft_strlen(content)))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_lstreplaceone(t_list **lst, t_list *old, t_list *new)
{
	old->content = new->content;
	*lst = *lst;
}

t_list	*create_call_stack(const char *str)
{
	int		i;
	t_list	*call_stack;
	char	conv_char[9];
	int		zero_flag;
	int		prec_flag;

	i = 0;
	zero_flag = 0;
	prec_flag = 0;
	ft_strlcpy((char*)conv_char, "cspdiuxX", 9);
	while (!ft_strchr(conv_char, str[i]))
	{
		if (str[i] == '-')
		{
			ft_lstadd_front(&call_stack, ft_lstnew((char*)&left_adjust));
			zero_flag = 1;
		}
		else if (str[i] == '0' && zero_flag == 0)
		{
			ft_lstadd_front(&call_stack, ft_lstnew((char*)&zeropad_adjust));
			zero_flag = 0;
		}
		else if ((str[i] == '*' || ft_isdigit(str[i])) && prec_flag == 0)
			ft_lstadd_front(&call_stack, ft_lstnew((char*)&width_adjust));
		else if (str[i] == '.')
			prec_flag = 1;
		else if ((str[i] == '*' || ft_isdigit(str[i])) && prec_flag == 1)
			ft_lstadd_front(&call_stack, ft_lstnew((char*)&precision_adjust));
		else 
		{
			ft_putstr_fd("UNKNOWN CHARACTER!", 1);
			return (NULL);
		}
		i++;
	}
	ft_lstadd_front(&call_stack, ft_lstnew((char*)&str[i]));
	return (call_stack);
}

int		ft_printf(const char *str, ...)
{
	int		idx;
	t_list	*spec_stack;
	t_list	*call_stack;
	t_list	*temp_node;
	//char	*flags;
	char	*width;
	//int		precision;
	//char	*conv;
	va_list	args;

	idx = 0;
	spec_stack = NULL;
	va_start(args, str);
	while (str[idx] != '%')
		idx++;
	printf_parser(&spec_stack, &str[idx]);
	call_stack = create_call_stack(&str[idx]);
	ft_lstprint(spec_stack, "");
	ft_putstr_fd("\n", 1);
	if ((temp_node = ft_lstfind(spec_stack, "*")))
	{
		ft_putstr_fd("found a *", 1); //REMOVE
		ft_putstr_fd("\n", 1);// REMOVE
		ft_putstr_fd(temp_node->content, 1); //REMOVE
		ft_putstr_fd("\n", 1);// REMOVE
		width = ft_itoa(va_arg(args, int)); //REMOVE
		temp_node->content = width;
		//ft_lstreplaceone(&spec_stack, "*", ft_lstnew(va_arg(args, int)));
	}
	ft_lstprint(spec_stack, "");
	ft_putstr_fd("\n", 1);

	return (0);
}
