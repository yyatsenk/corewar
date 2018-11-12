/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper_02_ld.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayduk <maksim.gayduk@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 10:01:03 by mgayduk           #+#    #+#             */
/*   Updated: 2018/05/23 16:15:53 by mgayduk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	Load the value of the first argument in the registry.
*/

void	ld(t_data *data, t_process *process)
{
	t_byte	*val;
	short	reg_num;

	data = NULL;
	reg_num = REG_NUM(process, 1);
	if (INCORRECT_REG_NUM(reg_num))
		return ;
	if (TYPE(process, 0) == DIR_CODE)
		val = VALUE(process, 0);
	else if (TYPE(process, 0) == IND_CODE)
		val = VALUE_IDX(process, 0);
	else
		return ;
	ft_memcpy(process->registers[reg_num], val, REG_SIZE);
	SET_CARRY(process, reg_num);
}
