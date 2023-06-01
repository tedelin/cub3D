/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 22:28:45 by tedelin           #+#    #+#             */
/*   Updated: 2023/06/01 22:32:46 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_data *data)
{
	if (key == XK_w)
		data->forward = 1;
	if (key == XK_s)
		data->backward = 1;
	if (key == XK_a)
		data->left = 1;
	if (key == XK_d)
		data->right = 1;
	if (key == XK_Left)
		data->l_cam = 1;
	if (key == XK_Right)
		data->r_cam = 1;
	if (key == XK_Escape)
		mlx_loop_end(data->mlx);
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == XK_w)
		data->forward = 0;
	if (key == XK_s)
		data->backward = 0;
	if (key == XK_a)
		data->left = 0;
	if (key == XK_d)
		data->right = 0;
	if (key == XK_Left)
		data->l_cam = 0;
	if (key == XK_Right)
		data->r_cam = 0;
	return (0);
}

int	ft_move(t_data *data)
{
	if (data->forward == 1)
		forward_backward(data, XK_w);
	if (data->backward == 1)
		forward_backward(data, XK_s);
	if (data->left == 1)
		left_right(data, XK_a);
	if (data->right == 1)
		left_right(data, XK_d);
	if (data->r_cam == 1)
		ft_right(data, XK_Right);
	if (data->l_cam == 1)
		ft_left(data, XK_Left);
	if (data->right == 1 || data->left == 1 || data->forward == 1
		|| data->backward == 1 || data->r_cam == 1 || data->l_cam == 1)
	{
		ft_draw(data);
		mlx_put_image_to_window(data->mlx, data->win, data->render.img, 0, 0);
	}
	return (0);
}
