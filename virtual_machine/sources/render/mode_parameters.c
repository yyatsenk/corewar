/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_parameters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayduk <maksim.gayduk@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:52:17 by mgayduk           #+#    #+#             */
/*   Updated: 2018/06/02 14:07:56 by mgayduk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	change_speed(t_data *data, int c)
{
	if (c == 's')
		data->render.speed -= 100;
	else if (c == 'q')
		data->render.speed -= 10;
	else if (c == 'w')
		data->render.speed -= 1;
	else if (c == 'e')
		data->render.speed += 1;
	else if (c == 'r')
		data->render.speed += 10;
	else if (c == 'd')
		data->render.speed += 100;
	if (data->render.speed < 1)
		data->render.speed = 1;
	if (data->render.speed > 1000)
		data->render.speed = 1000;
}

void		set_speed(t_data *data)
{
	int c;

	while ((c = getch()) != ' ')
	{
		data->render.paused = 1;
		render_speed_data(data);
		change_speed(data, c);
		if (c == 'i')
		{
			INTERACTIVE = 1;
			break ;
		}
		render_speed_data(data);
	}
	data->render.paused = !data->render.paused;
	render_speed_data(data);
}

void		handle_interactive_mode(t_data *data)
{
	int c;

	while ((c = getch()) != 'i')
		if (c == ' ')
		{
			INTERACTIVE = 0;
			render_speed_data(data);
			break ;
		}
}
