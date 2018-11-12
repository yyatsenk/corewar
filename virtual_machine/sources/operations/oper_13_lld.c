/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper_13_lld.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayduk <maksim.gayduk@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 10:01:03 by mgayduk           #+#    #+#             */
/*   Updated: 2018/06/01 13:40:33 by mgayduk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	Load the value of the first argument in the registry.
**	Like ld, but without % IDX_MOD.
*/

void	lld(t_data *data, t_process *process)
{
	t_byte	*val;
	short	reg_num;

	data = NULL;
	reg_num = REG_NUM(process, 1);
	if (INCORRECT_REG_NUM(reg_num))
		return ;
	val = VALUE(process, 0);
	ft_memcpy(process->registers[reg_num], val, REG_SIZE);
	SET_CARRY(process, reg_num);
}
