/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:42:43 by tedelin           #+#    #+#             */
/*   Updated: 2023/06/01 22:29:36 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	forward_backward(t_data *data, int key)
{
	if (key == XK_w)
	{
		if (data->map->map_int[(int)(data->pos_x + data->dir_x
				* MSPEED)][(int)(data->pos_y)] == 0)
			data->pos_x += data->dir_x * MSPEED;
		if (data->map->map_int[(int)(data->pos_x)][(int)(data->pos_y
				+ data->dir_y * MSPEED)] == 0)
			data->pos_y += data->dir_y * MSPEED;
	}
	if (key == XK_s)
	{
		if (data->map->map_int[(int)(data->pos_x - data->dir_x
				* MSPEED)][(int)(data->pos_y)] == 0)
			data->pos_x -= data->dir_x * MSPEED;
		if (data->map->map_int[(int)(data->pos_x)][(int)(data->pos_y
				- data->dir_y * MSPEED)] == 0)
			data->pos_y -= data->dir_y * MSPEED;
	}
}

void	left_right(t_data *data, int key)
{
	if (key == XK_a)
	{
		if (data->map->map_int[(int)(data->pos_x - data->plane_x
				* MSPEED)][(int)(data->pos_y)] == 0)
			data->pos_x -= data->plane_x * MSPEED;
		if (data->map->map_int[(int)(data->pos_x)][(int)(data->pos_y
				- data->plane_y * MSPEED)] == 0)
			data->pos_y -= data->plane_y * MSPEED;
	}
	if (key == XK_d)
	{
		if (data->map->map_int[(int)(data->pos_x + data->plane_x
				* MSPEED)][(int)(data->pos_y)] == 0)
			data->pos_x += data->plane_x * MSPEED;
		if (data->map->map_int[(int)(data->pos_x)][(int)(data->pos_y
				+ data->plane_y * MSPEED)] == 0)
			data->pos_y += data->plane_y * MSPEED;
	}
}

void	ft_right(t_data *data, int key)
{
	double	olddir_x;
	double	oldplane_x;

	if (key == XK_Right)
	{
		olddir_x = data->dir_x;
		data->dir_x = data->dir_x * cos(-RSPEED) - data->dir_y * sin(-RSPEED);
		data->dir_y = olddir_x * sin(-RSPEED) + data->dir_y * cos(-RSPEED);
		oldplane_x = data->plane_x;
		data->plane_x = data->plane_x * cos(-RSPEED) - data->plane_y
			* sin(-RSPEED);
		data->plane_y = oldplane_x * sin(-RSPEED) + data->plane_y
			* cos(-RSPEED);
	}
}

void	ft_left(t_data *data, int key)
{
	double	olddir_x;
	double	oldplane_x;

	if (key == XK_Left)
	{
		olddir_x = data->dir_x;
		data->dir_x = data->dir_x * cos(RSPEED) - data->dir_y * sin(RSPEED);
		data->dir_y = olddir_x * sin(RSPEED) + data->dir_y * cos(RSPEED);
		oldplane_x = data->plane_x;
		data->plane_x = data->plane_x * cos(RSPEED) - data->plane_y
			* sin(RSPEED);
		data->plane_y = oldplane_x * sin(RSPEED) + data->plane_y * cos(RSPEED);
	}
}
