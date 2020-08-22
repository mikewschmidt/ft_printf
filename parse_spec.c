/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmidt <mschmidt@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 07:57:45 by mschmidt          #+#    #+#             */
/*   Updated: 2020/08/17 09:49:35 by mschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void		set_width(const char *spec, int *idx, t_spec *fspec)
{
	int		j;
	int		i;
	char	*tempstr;

	j = 0;
	i = *idx;
	while (ft_isdigit(spec[i]))
	{
		j++;
		i++;
	}
	tempstr = (char*)ft_calloc(j + 1, sizeof(char));
	ft_strlcpy(tempstr, spec + i - j, j + 1);
	fspec->width = ft_atoi(tempstr);
	free(tempstr);
	*idx = --i;
}

static void		set_prec(const char *spec, int *idx, t_spec *fspec)
{
	int		j;
	int		i;
	char	*tempstr;

	j = 0;
	i = *idx;
	while (ft_isdigit(spec[i]))
	{
		j++;
		i++;
	}
	tempstr = (char*)ft_calloc(j + 1, sizeof(char));
	ft_strlcpy(tempstr, spec + i - j, j + 1);
	fspec->prec = ft_atoi(tempstr);
	free(tempstr);
	*idx = --i;
}

static void		set_plus(t_spec *fspec)
{
	fspec->space_flag = 0;
	fspec->plus_flag = 1;
}

static void		set_fspec(const char *spec, int *idx, t_spec *fspec)
{
	int	i;

	i = *idx;
	if (i == 1 && spec[i] == ' ')
		fspec->space_flag = 1;
	if (spec[i] == '+')
		set_plus(fspec);
	if (spec[i] == '#')
		fspec->hash_flag = 1;
	if (spec[i] == '.')
		fspec->prec_flag = 1;
	if (spec[i] == '-' && fspec->prec_flag == 0)
		fspec->left_flag = 1;
	else if (spec[i] == '-' && fspec->prec_flag == 1)
		fspec->prec_flag = -1;
	if (spec[i] == '0' && fspec->zero_flag == -1)
		fspec->zero_flag = 1;
	else if (ft_isdigit(spec[i]) && fspec->zero_flag == -1)
		fspec->zero_flag = 0;
	if (ft_isdigit(spec[i]) && fspec->width == 0 && fspec->prec_flag == 0 && fspec->zero_flag != -1)
		set_width(spec, idx, fspec);
	else if (ft_isdigit(spec[i]) && fspec->prec_flag != 0)
		set_prec(spec, idx, fspec);
}

void			parse_spec(t_spec *fspec, const char *spec)
{
	int	i;

	i = 1;
	fspec->prec_flag = 0;
	fspec->zero_flag = -1;
	fspec->width = 0;
	fspec->prec = 0;
	fspec->left_flag = 0;
	fspec->space_flag = 0;
	fspec->plus_flag = 0;
	while (!ft_strchr("cspdiuxX%", spec[i]) && spec[i] != '\0')
	{
		set_fspec(spec, &i, fspec);
		i++;
	}
	fspec->convchar = *(ft_strchr("cspdiuxX%", spec[i]));
}
