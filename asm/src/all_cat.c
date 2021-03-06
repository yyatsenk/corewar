/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_cat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 19:21:33 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/05/08 19:21:34 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cor.h"

#define STR_ARG	"%&Syntax error at [TOKEN][%03i:%03li]\n"

char		*label_cat(char *str, int *end)
{
	int		i;
	int		begin;
	char	*res;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (!str[i])
		return (NULL);
	begin = i;
	while (str[i] && str[i] != ':')
	{
		if (!ft_strchr(LABEL_CHARS, str[i]))
		{
			ft_printf(STR_ARG, 2, g_num_str, i);
			ft_memdel((void **)&str);
			error_exit_with_sound(-1);
		}
		i++;
	}
	if (!str[i])
		return (NULL);
	*end = i;
	res = ft_strsub(str, begin, *end - begin);
	return (res);
}

char		*comm_cat(char *str, int i)
{
	char	*res;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\t')
		i++;
	res = ft_strsub(str, 0, i);
	return (res);
}

char		*arg_cat(char *str, int *i)
{
	char	*res;
	int		begin;

	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
	begin = *i;
	if (!str[*i])
		return (NULL);
	while (str[*i] && str[*i] != ' ' && str[*i] != '\t'\
		&& str[*i] != ',' && str[*i] != '\n')
		(*i)++;
	res = ft_strsub(str, begin, *i - begin);
	return (res);
}
