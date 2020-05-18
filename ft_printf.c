/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmidt <mschmidt@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 19:53:47 by mschmidt          #+#    #+#             */
/*   Updated: 2020/05/17 02:39:11 by mschmidt         ###   ########.fr       */
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
		if (ft_strncmp(lst->content, content, ft_strlen(content)))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_lstreplaceone(t_list **lst, void *old, void *new)
{
	t_list	*curr;

	curr = *lst;
	while (curr)
	{
		if (ft_strncmp(curr->content, old, ft_strlen(old)))
		{
			curr->content = new;
		}
	}
}
int		ft_printf(const char *str, ...)
{
	int		idx;
	t_list	*stack;
	char	*flags;
	char	*width;
	char	*precision;
	char	*conv;
	va_list	args;

	idx = 0;
	stack = NULL;
	va_start(args, str);
	while (str[idx] != '%')
		idx++;
	printf_parser(&stack, &str[idx]);
	ft_lstprint(stack, "");
	ft_putstr_fd("\n", 1);
	if (ft_lstfind(stack, "*"))
	{
		ft_putstr_fd("found a *", 1); //REMOVE
		ft_putstr_fd("\n", 1);// REMOVE
		ft_lstreplaceone(&stack, "*", &va_arg(args, int));
	}
	ft_lstprint(*stack, "");
	ft_putstr_fd("\n", 1);

	return (0);
}
