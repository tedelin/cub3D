/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 03:26:14 by tedelin           #+#    #+#             */
/*   Updated: 2023/05/31 11:56:39 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

t_img	ft_texture(t_data *data)
{
	t_img	cur_img;
	double	step;
	double	tex_pos;

	if (data->side == 0 && data->raydir_x < 0)
		cur_img = data->w_wall;
	else if (data->side == 0 && data->raydir_x > 0)
		cur_img = data->e_wall;
	else if (data->side == 1 && data->raydir_y < 0)
		cur_img = data->s_wall;
	else
		cur_img = data->n_wall;
	data->tex_x = (int)(data->wallx * (double)(cur_img.width));
	if (data->side == 0 && data->raydir_x > 0)
		data->tex_x = cur_img.width - data->tex_x - 1;
	if (data->side == 1 && data->raydir_y < 0)
		data->tex_x = cur_img.width - data->tex_x - 1;
	return (cur_img);
}

void	img_draw(int x, int start, int end, t_data *data)
{
	t_img	cur_img;
	double	step;
	double	tex_pos;
	int		tex_y;
	int		y;

	cur_img = ft_texture(data);
	step = 1.0 * cur_img.height / data->line_h;
	tex_pos = (start - SCREENHEIGHT / 2 + data->line_h / 2) * step;
	y = -1;
	while (++y < start)
		data->render.data[y * data->render.size_line / 4 + x] = data->ceiling;
	y = start - 1;
	while (++y <= end)
	{
		tex_y = (int)tex_pos & (cur_img.height - 1);
		tex_pos += step;
		data->color = cur_img.data[tex_y * cur_img.size_line / 4 + data->tex_x];
		data->render.data[y * data->render.size_line / 4 + x] = data->color;
	}
	y = end;
	while (++y < SCREENHEIGHT)
		data->render.data[y * data->render.size_line / 4 + x] = data->floor;
}

void	ft_before_dda(t_data *data)
{
	data->mapx = (int)data->pos_x;
	data->mapy = (int)data->pos_y;
	data->delt_distx = fabs(1 / data->raydir_x);
	data->delt_disty = fabs(1 / data->raydir_y);
	if (data->raydir_x < 0)
	{
		data->step_x = -1;
		data->s_dist_x = (data->pos_x - data->mapx) * data->delt_distx;
	}
	else
	{
		data->step_x = 1;
		data->s_dist_x = (data->mapx + 1.0 - data->pos_x) * data->delt_distx;
	}
	if (data->raydir_y < 0)
	{
		data->step_y = -1;
		data->s_dist_y = (data->pos_y - data->mapy) * data->delt_disty;
	}
	else
	{
		data->step_y = 1;
		data->s_dist_y = (data->mapy + 1.0 - data->pos_y) * data->delt_disty;
	}
}

void	ft_dda(t_data *data)
{
	data->hit = 0;
	while (data->hit == 0)
	{
		if (data->s_dist_x < data->s_dist_y)
		{
			data->s_dist_x += data->delt_distx;
			data->mapx += data->step_x;
			data->side = 0;
		}
		else
		{
			data->s_dist_y += data->delt_disty;
			data->mapy += data->step_y;
			data->side = 1;
		}
		if (data->map->map_int[data->mapx][data->mapy] > 0)
			data->hit = 1;
	}
	if (data->side == 0)
		data->perpwalldist = (data->s_dist_x - data->delt_distx);
	else
		data->perpwalldist = (data->s_dist_y - data->delt_disty);
}

void	ft_draw(t_data *data)
{
	int	x;

	x = -1;
	while (++x < SCREENWIDTH)
	{
		data->cam_x = 2 * x / (double)SCREENWIDTH - 1;
		data->raydir_x = data->dir_x + data->plane_x * data->cam_x;
		data->raydir_y = data->dir_y + data->plane_y * data->cam_x;
		ft_before_dda(data);
		ft_dda(data);
		data->line_h = (int)(SCREENHEIGHT / data->perpwalldist);
		data->draw_start = -data->line_h / 2 + SCREENHEIGHT / 2;
		if (data->draw_start < 0)
			data->draw_start = 0;
		data->draw_end = data->line_h / 2 + SCREENHEIGHT / 2;
		if (data->draw_end >= SCREENHEIGHT)
			data->draw_end = SCREENHEIGHT - 1;
		if (data->side == 0)
			data->wallx = data->pos_y + data->perpwalldist * data->raydir_y;
		else
			data->wallx = data->pos_x + data->perpwalldist * data->raydir_x;
		data->wallx -= floor((data->wallx));
		img_draw(x, data->draw_start, data->draw_end, data);
	}
}
