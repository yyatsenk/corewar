/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayduk <mgayduk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 10:50:36 by mgayduk           #+#    #+#             */
/*   Updated: 2018/06/01 16:36:24 by mgayduk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	init_colors(void)
{
	if (!has_colors())
	{
		endwin();
		error_msg("Your terminal does not support color", NULL);
	}
	start_color();
	init_color(COLOR_MAGENTA, 500, 500, 500);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5, COLOR_BLACK, COLOR_GREEN);
	init_pair(6, COLOR_BLACK, COLOR_BLUE);
	init_pair(7, COLOR_BLACK, COLOR_RED);
	init_pair(8, COLOR_BLACK, COLOR_CYAN);
	init_pair(11, COLOR_WHITE, COLOR_GREEN);
	init_pair(12, COLOR_WHITE, COLOR_BLUE);
	init_pair(13, COLOR_WHITE, COLOR_RED);
	init_pair(14, COLOR_WHITE, COLOR_CYAN);
	init_pair(42, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(43, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(47, COLOR_BLACK, COLOR_MAGENTA);
}

void	update_color_map(t_data *data, t_byte champion, int start, size_t n)
{
	size_t	i;
	int		index;
	int		parent_color;

	parent_color = champion + 1;
	i = 0;
	while (i < n)
	{
		index = normalize_index(start);
		data->render.color_map[index] = parent_color;
		data->render.brightness_map[index] = data->cycle;
		start++;
		i++;
	}
}
