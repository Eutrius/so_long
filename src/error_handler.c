/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 12:45:35 by jyriarte          #+#    #+#             */
/*   Updated: 2025/01/26 22:35:54 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include <stdlib.h>

void	print_error_exit(char *error, char *name, t_data *data)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(error, 2);
	if (name)
		ft_putstr_fd(name, 2);
	ft_putstr_fd("\n", 2);
	if (data)
		free_data(data);
	exit(EXIT_FAILURE);
}
