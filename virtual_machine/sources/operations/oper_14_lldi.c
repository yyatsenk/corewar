/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper_14_lldi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayduk <maksim.gayduk@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 13:45:25 by mgayduk           #+#    #+#             */
/*   Updated: 2018/06/01 13:41:12 by mgayduk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	The same as ldi, but without offset %= IDX_MOD;
**	Modifies carry;
*/

void	lldi(t_data *data, t_process *process)
{
	t_byte		*val1;
	t_byte		*val2;
	short		reg_num;
	int			dest;

	reg_num = REG_NUM(process, 2);
	if (INCORRECT_REG_NUM(reg_num))
		return ;
	val1 = TYPE(process, 0) == IND_CODE ? VALUE_IDX(process, 0) :
											VALUE(process, 0);
	val2 = VALUE(process, 1);
	dest = get_number(val1, SIZE(process, 0)) +
			get_number(val2, SIZE(process, 1));
	dest = process->pc + dest;
	read_arena_chunk(data, process->registers[reg_num], dest, REG_SIZE);
	SET_CARRY(process, reg_num);
}
