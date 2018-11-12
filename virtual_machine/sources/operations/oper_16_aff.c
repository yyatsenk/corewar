/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper_16_aff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayduk <maksim.gayduk@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 17:19:56 by mgayduk           #+#    #+#             */
/*   Updated: 2018/06/01 13:41:35 by mgayduk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	aff(t_data *data, t_process *process)
{
	int		val;
	short	reg_num;

	data = NULL;
	reg_num = REG_NUM(process, 0);
	if (INCORRECT_REG_NUM(reg_num))
		return ;
	val = get_int_number(VALUE(process, 0)) % 256;
	ft_printf("Aff: %c\n", val);
}
