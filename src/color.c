/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 11:16:05 by atambo            #+#    #+#             */
/*   Updated: 2024/09/29 11:16:06 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	get_color_component(int base_color, int next_color, double ratio)
{
	int	base;
	int	next;

	base = base_color;
	next = next_color;
	return ((int)(base + ratio * (next - base)));
}

int	get_color_2(int out_color, int int_color,
	int iterations, int max_iterations)
{
	double	ratio;
	int		red;
	int		green;
	int		blue;

	ratio = (double)iterations / (double)max_iterations;
	red = get_color_component(out_color >> 16, int_color >> 16, ratio);
	green = get_color_component(out_color >> 8, int_color >> 8, ratio);
	blue = get_color_component(out_color & 0xFF, int_color & 0xFF, ratio);
	if (iterations == max_iterations)
		return (0xb51919 + (int)(0.01 * out_color));
	return ((red << 16) | (green << 8) | blue);
}

void	update_colors(t_data *data, int iterations)
{
	if (data->dist > 0)
	{
		data->color_1 -= iterations * sin(iterations) / 1.82703449496728343;
		data->color_2 -= iterations * sin(iterations) / 1.82703449496728343;
	}
}

void	get_color_1(t_data *data, int x_c, int y_c, int iterations)
{
	update_colors(data, iterations);
	if (data->view == 's')
	{
		data->color_0 = get_color_2(data->color_1, data->color_2,
				iterations, data->max_iterations);
	}
	else if (data->view == 'l')
	{
		data->color_0 = get_color_2(data->color_1
				* iterations, data->color_2 * iterations, iterations,
				data->max_iterations);
	}
	pixel_put_img(data, x_c, y_c, data->color_0);
}
