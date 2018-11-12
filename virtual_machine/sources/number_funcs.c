/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayduk <maksim.gayduk@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 21:40:48 by maks              #+#    #+#             */
/*   Updated: 2018/06/01 14:04:49 by mgayduk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	Such as readed memory dump from .cor file is big endian,
**	to correct casting, array should be reversed.
**	for example:
**		0017  --> {0x00, 0x17} in little endian will be 5888
**		after reverse - {0x17, 0x00} will be 23 as needed.
*/

/*
**	Converts array of bytes to a little-endian integer and returns it.
*/

int		get_int_number(void *arr)
{
	int				res;
	unsigned char	*s;

	res = 0;
	s = (unsigned char *)arr;
	res += s[3];
	res += s[2] << 8;
	res += s[1] << 16;
	res += s[0] << 24;
	return (res);
}

/*
**	Converts array of bytes to a little-endian short and returns it.
*/

short	get_short_number(void *arr)
{
	short			res;
	unsigned char	*s;

	res = 0;
	s = (unsigned char *)arr;
	res += s[1];
	res += s[0] << 8;
	return (res);
}

/*
**	Wrapper function for get_int_number and get_sort_number.
*/

int		get_number(void *arr, int size)
{
	int res;

	res = 0;
	if (size == REG_SIZE)
		res = get_int_number(arr);
	else if (size == IND_SIZE)
		res = get_short_number(arr);
	return (res);
}

/*
**	Converts number to a normalized arena index and returns it;
**	For example: 	4106 => 10;
**					-1 	 => 4095;
*/

int		normalize_index(int index)
{
	index = index % MEM_SIZE;
	if (index < 0)
		index += MEM_SIZE;
	return (index);
}
