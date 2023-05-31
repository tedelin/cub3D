/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatal-d <mcatal-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 23:14:33 by mcatal-d          #+#    #+#             */
/*   Updated: 2023/05/25 13:51:48 by mcatal-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_player(t_map *map)
{
	int	i;
	int	j;
	int	player;

	i = 0;
	player = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (ft_strchr("NSEW", map->map[i][j]))
			{
				if (player == 1)
					return (printf("Error\nMore than one player\n"),
						free_map(map), -1);
				player = 1;
			}
			j++;
		}
		i++;
	}
	if (player == 0)
		return (printf("Error\nNo player\n"), free_map(map), -1);
	return (verif_rgb(map));
}
