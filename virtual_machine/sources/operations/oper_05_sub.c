/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper_05_sub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayduk <maksim.gayduk@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 15:36:28 by mgayduk           #+#    #+#             */
/*   Updated: 2018/06/01 13:36:28 by mgayduk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	sub(t_data *data, t_process *process)
{
	int		res;
	int		v1;
	int		v2;
	short	reg_num;

	data = NULL;
	if (INCORRECT_REG_NUM(REG_NUM(process, 0)) ||
		INCORRECT_REG_NUM(REG_NUM(process, 1)) ||
		INCORRECT_REG_NUM(REG_NUM(process, 2)))
		return ;
	v1 = get_int_number(VALUE(process, 0));
	v2 = get_int_number(VALUE(process, 1));
	res = v1 - v2;
	reg_num = REG_NUM(process, 2);
	res = get_int_number(&res);
	ft_memcpy(process->registers[reg_num], &res, REG_SIZE);
	SET_CARRY(process, reg_num);
}
