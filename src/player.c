/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 22:18:15 by jyriarte          #+#    #+#             */
/*   Updated: 2025/01/29 17:27:48 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>

static void	check_for_moulinette(t_data *data, char **map, t_point *location);
static void	attack_moulinette(t_data *data, char **map, t_point *location);

void	move_player(t_data *data, int x, int y)
{
	char	**map;
	t_point	*location;

	map = data->map->grid;
	location = data->player->location;
	if (map[y + location->y][x + location->x] != '1')
	{
		data->moves++;
		location->x += x;
		location->y += y;
	}
	attack_moulinette(data, map, location);
	check_for_moulinette(data, map, location);
}

static void	check_for_moulinette(t_data *data, char **map, t_point *location)
{
	if (map[location->y + 1][location->x] == 'C')
		data->player->img = data->imgs[player_attack];
	else if (map[location->y - 1][location->x] == 'C')
		data->player->img = data->imgs[player_attack];
	else if (map[location->y][location->x + 1] == 'C')
	{
		data->player->mirror = 0;
		data->player->img = data->imgs[player_attack];
	}
	else if (map[location->y][location->x - 1] == 'C')
	{
		data->player->mirror = 1;
		data->player->img = data->imgs[player_attack];
	}
	else if (map[location->y][location->x] != 'C')
	{
		data->player->img = data->imgs[player0];
	}
}

static void	attack_moulinette(t_data *data, char **map, t_point *location)
{
	if (map[location->y][location->x] == 'C')
		data->player->img = data->imgs[player_attacked];
}

void	player_won(t_data *data)
{
	if (!data->finished)
		return ;
	if (ft_pointcmp(data->exit->location, data->player->location))
	{
		ft_printf("Congratulations you finished the map!\n");
		ft_printf("Total moves: %i\n", data->moves);
		free_data(data);
		exit(0);
	}
}

void	player_lost(t_data *data)
{
	if (data->moves < 3)
		return ;
	if (ft_pointcmp(data->player->location, data->black_hole->location))
	{
		ft_printf("%sYou have been absorbed by the blackhole\n", "\x1B[31m");
		ft_printf("Total moves: %i\n", data->moves);
		free_data(data);
		exit(0);
	}
}
