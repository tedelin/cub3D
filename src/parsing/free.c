/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 07:17:58 by mcatal-d          #+#    #+#             */
/*   Updated: 2023/06/01 18:17:45 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_tab_int(int **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_mlx(t_data *data)
{
	if (data->n_wall.img)
		mlx_destroy_image(data->mlx, data->n_wall.img);
	if (data->s_wall.img)
		mlx_destroy_image(data->mlx, data->s_wall.img);
	if (data->e_wall.img)
		mlx_destroy_image(data->mlx, data->e_wall.img);
	if (data->w_wall.img)
		mlx_destroy_image(data->mlx, data->w_wall.img);
	if (data->render.img)
		mlx_destroy_image(data->mlx, data->render.img);
	if (data->win)
	{
		mlx_clear_window(data->mlx, data->win);
		mlx_destroy_window(data->mlx, data->win);
	}
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	free(data->mlx);
	free_map(data->map);
}

void	free_map(t_map *map)
{
	free(map->north);
	free(map->south);
	free(map->east);
	free(map->west);
	free(map->floor);
	free(map->celestial);
	free_tab(map->file_content);
	free_tab(map->map);
	free_tab(map->celestial_tab);
	free_tab(map->floor_tab);
	free_tab_int(map->map_int);
	free(map);
}
