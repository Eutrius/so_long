/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 21:09:54 by jyriarte          #+#    #+#             */
/*   Updated: 2025/01/29 14:50:06 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"
#include <stddef.h>
#include <stdlib.h>

static void		init_moulinettes(t_data *data);
static t_entity	*init_entity(t_data *data, t_point *location, t_imgname name);

void	init_data(t_data *data, char *mapname)
{
	init_map(data, mapname);
	init_moves(data);
	data->process = mlx_init();
	if (!data->process)
		print_error_exit("Initializing game: failed", NULL, data);
	init_imgs(data);
	data->window = mlx_new_window(data->process, 128 * data->map->width, 128
			* (data->map->height), "42 Adventure");
	if (!data->window)
		print_error_exit("Creating window: failed", NULL, data);
	init_moulinettes(data);
	data->player = init_entity(data, data->map->start_point, player0);
	data->exit = init_entity(data, data->map->exit_point, stairs);
	data->black_hole = init_entity(data, data->map->start_point, blackhole1);
}

static void	init_moulinettes(t_data *data)
{
	int	i;

	i = 0;
	data->moulinettes = ft_calloc(data->map->moulinettes + 1,
			sizeof(t_entity *));
	if (!data->moulinettes)
		print_error_exit("Memory allocation failed", NULL, data);
	while (data->map->moulinettes_arr[i] != NULL)
	{
		data->moulinettes[i] = init_entity(data, data->map->moulinettes_arr[i],
				moulinette);
		i++;
	}
}

static t_entity	*init_entity(t_data *data, t_point *location, t_imgname name)
{
	t_point		*location_dup;
	t_entity	*entity;

	entity = ft_calloc(1, sizeof(t_entity));
	if (!entity)
		print_error_exit("Memory allocation failed", NULL, data);
	location_dup = ft_pointnew(location->x, location->y);
	if (!location_dup)
	{
		free(entity);
		print_error_exit("Memory allocation failed", NULL, data);
	}
	entity->location = location_dup;
	entity->img = data->imgs[name];
	return (entity);
}
