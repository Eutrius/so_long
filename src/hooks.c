/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:52:10 by jyriarte          #+#    #+#             */
/*   Updated: 2025/01/28 22:40:49 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"
#include <X11/keysym.h>
#include <stdlib.h>

static int	input_event(int keycode, t_data *data);
static int	exit_event(t_data *data);
static int	render(t_data *data);

void	hooks(t_data *data)
{
	mlx_loop_hook(data->process, render, data);
	mlx_key_hook(data->window, input_event, data);
	mlx_hook(data->window, 17, 0, exit_event, data);
}

static int	input_event(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		exit_event(data);
	if (keycode == XK_d)
	{
		data->player->mirror = 0;
		move_player(data, 1, 0);
	}
	if (keycode == XK_a)
	{
		data->player->mirror = 1;
		move_player(data, -1, 0);
	}
	if (keycode == XK_w)
		move_player(data, 0, -1);
	if (keycode == XK_s)
		move_player(data, 0, 1);
	return (0);
}

static int	exit_event(t_data *data)
{
	free_data(data);
	exit(EXIT_SUCCESS);
}

static int	render(t_data *data)
{
	static int	rate;

	if (rate == GLOBAL_FRAMERATE)
	{
		render_all(data);
		rate = 0;
	}
	rate++;
	return (0);
}
