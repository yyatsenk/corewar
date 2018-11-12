/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 11:22:43 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/05/09 11:22:47 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cor.h"

int				check_end_string(char *end_line)
{
	int	counter;

	counter = 0;
	while (end_line[counter])
	{
		while (end_line[counter] && (end_line[counter] == '\t' ||\
			end_line[counter] == ' '))
			counter++;
		if (!end_line[counter] || end_line[counter] == ';' ||\
			end_line[counter] == COMMENT_CHAR)
			return (1);
		if (end_line[counter] && end_line[counter] != ';' &&\
			end_line[counter] != COMMENT_CHAR)
		{
			ft_printf("%&Error at [%i] line\n", 2, g_num_str);
			return (-1);
		}
		counter++;
	}
	return (1);
}
