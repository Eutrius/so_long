/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:08:58 by jyriarte          #+#    #+#             */
/*   Updated: 2025/01/29 17:20:54 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>

void	render_all(t_data *data)
{
	render_map(data);
	render_exit(data);
	render_black_hole(data);
	render_player(data);
	render_moulinettes(data);
	render_moves(data);
	render_explosion(data);
}

void	render_player(t_data *data)
{
	static int	rate;
	t_entity	*player;

	player_won(data);
	player_lost(data);
	player = data->player;
	render_entity(data, player);
	if (rate == PLAYER_FRAMERATE)
	{
		if (player->img == data->imgs[player0])
			player->img = data->imgs[player1];
		else if (player->img == data->imgs[player1])
			player->img = data->imgs[player2];
		else if (player->img == data->imgs[player2])
			player->img = data->imgs[player0];
		rate = 1;
	}
	rate++;
}

void	render_moulinettes(t_data *data)
{
	int			i;
	t_entity	*moulinette;

	i = 0;
	while (i < data->map->moulinettes)
	{
		moulinette = data->moulinettes[i];
		if (moulinette)
		{
			if (ft_pointcmp(moulinette->location, data->player->location))
			{
				data->explosion = moulinette->location;
				data->map->grid[data->explosion->y][data->explosion->x] = '0';
				free(moulinette);
				moulinette = NULL;
				data->moulinettes[i] = NULL;
			}
			else
				render_entity(data, moulinette);
		}
		i++;
	}
}

void	render_exit(t_data *data)
{
	int			i;
	t_entity	*moulinette;

	i = 0;
	while (data->finished == 0 && i < data->map->moulinettes)
	{
		moulinette = data->moulinettes[i];
		if (moulinette != NULL)
			return ;
		i++;
	}
	data->finished = 1;
	render_tile(data, stairs, data->exit->location->x, data->exit->location->y);
}
