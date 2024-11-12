/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:44:13 by atambo            #+#    #+#             */
/*   Updated: 2024/09/28 15:44:15 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	draw_if(t_data *data)
{
	if (data->fractal == 1)
		data->fractal = 'm';
	else if (data->fractal == 2)
		data->fractal = 'j';
	draw_fractal(data, data->x, data->y);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void	key_hook_2(int keycode, t_data *data)
{
	double	change;

	change = 0.0001 * data->x_max * data->color_2 * sin(data->x_max);
	if (keycode == SPACE)
	{
		data->color_1 += change;
		data->color_2 += change;
	}
	if (keycode == S)
	{
		data->view = 's';
	}
	if (keycode == L)
	{
		data->view = 'l';
	}
	if (keycode == D)
	{
		data->dist = data->dist * -1;
	}
}

int	key_hook(int keycode, t_data *data)
{
	double	dxy;

	dxy = (data->x_max - data->x_min) * 0.05;
	if ((keycode == DOWN) || (keycode == UP))
	{
		if (keycode == 65361)
			xy_lim_add(data, -dxy, 0.0);
		else
			xy_lim_add(data, +dxy, 0.0);
	}
	if ((keycode == LEFT) || (keycode == RIGHT))
	{
		if (keycode == 65362)
			xy_lim_add(data, 0.0, -dxy);
		else
			xy_lim_add(data, 0.0, +dxy);
	}
	if (keycode == ESC)
		close_window(data);
	key_hook_2(keycode, data);
	draw_if(data);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_data *data)
{
	double zoom_factor;
	zoom_factor = 0.0;
	if (button == 4 && x)
	{
		if (data->x_max - data->x_min <= 1.0e-100)
			ft_put_error("Max zoom lvl\n");
		else
			zoom_factor = 0.1;
	}
	else if (button == 5 && y)
	{				
		if (data->x_max - data->x_min >= 500)
			ft_put_error("Max zoom lvl\n");
		else
			zoom_factor = -0.1;
	}
	else
		return (0);

	// Calculate current width and height of the viewport
	double width = data->x_max - data->x_min;
	double height = data->y_max - data->y_min;

	// Mouse position as a fraction of the window
	double x_ratio = (double)x / WIDTH;
	double y_ratio = (double)y / HEIGHT;

	// Adjust the boundaries based on the zoom factor and mouse position ratio
	data->x_min += width * (zoom_factor) * x_ratio;
	data->x_max -= width * (zoom_factor) * (1 - x_ratio);
	data->y_min += height * (zoom_factor) * y_ratio;
	data->y_max -= height * (zoom_factor) * (1 - y_ratio);

	draw_if(data); // Redraw with the new zoom level
	return (0);
}

