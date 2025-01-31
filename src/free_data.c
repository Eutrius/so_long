/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 22:18:16 by jyriarte          #+#    #+#             */
/*   Updated: 2025/01/29 17:20:47 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "so_long.h"
#include <stdlib.h>

static void	free_map(t_data *data);
static void	free_imgs(t_data *data);
static void	free_moulinettes(t_data *data);
static void	free_mlx(t_data *data);

void	free_data(t_data *data)
{
	free_moulinettes(data);
	free_map(data);
	if (data->player)
	{
		if (data->player->location)
			free(data->player->location);
		free(data->player);
	}
	if (data->black_hole)
	{
		if (data->black_hole->location)
			free(data->black_hole->location);
		free(data->black_hole);
	}
	free(data->moves_location);
	if (data->exit)
	{
		if (data->exit->location)
			free(data->exit->location);
		free(data->exit);
	}
	free_mlx(data);
}

static void	free_map(t_data *data)
{
	t_map	*map;

	if (!data->map)
		return ;
	map = data->map;
	if (map->grid)
		ft_free_strs(map->grid);
	if (map->start_point)
		free(map->start_point);
	if (map->exit_point)
		free(map->exit_point);
	ft_free_points(map->moulinettes_arr);
	free(map);
}

static void	free_imgs(t_data *data)
{
	int	i;

	i = 0;
	while (data->imgs[i] != NULL)
	{
		mlx_destroy_image(data->process, data->imgs[i]->addr);
		free(data->imgs[i]);
		i++;
	}
	free(data->imgs);
}

static void	free_moulinettes(t_data *data)
{
	int			i;
	t_entity	*moulinette;

	if (!data->moulinettes)
		return ;
	i = 0;
	while (i < data->map->moulinettes)
	{
		moulinette = data->moulinettes[i];
		if (moulinette)
			free(moulinette->location);
		free(moulinette);
		moulinette = NULL;
		i++;
	}
	free(data->moulinettes);
}

static void	free_mlx(t_data *data)
{
	if (data->process)
	{
		if (data->imgs)
			free_imgs(data);
		if (data->window)
			mlx_destroy_window(data->process, data->window);
		mlx_destroy_display(data->process);
		free(data->process);
	}
}
