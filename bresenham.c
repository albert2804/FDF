/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:38:18 by aestraic          #+#    #+#             */
/*   Updated: 2022/12/21 11:50:55 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
/**
 * Original version bresenham from wikipedia and adapted for colors
 * 
 * void	bresenham(size_t node0, size_t node1, int n_pixel, t_trans *t)
{
	int	*rgb0;
	int	*rgb1;
	int	gr[3];
	int	i;

	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	error;
	int	e2;
	int	x0;
	int	x1;
	int	y0;
	int	y1;

	i = 0;
	rgb0 = t->map_data->rgb_values[node0];
	rgb1 = t->map_data->rgb_values[node1];
	gr[0] = (rgb1[0] - rgb0[0]) / n_pixel;
	gr[1] = (rgb1[1] - rgb0[1]) / n_pixel;
	gr[2] = (rgb1[2] - rgb0[2]) / n_pixel;

	init_bresenham(t, node0, node1);
	x0 = t->arr[0];
	x1 = t->arr[1];
	y0 = t->arr[2];
	y1 = t->arr[3];
	dx = t->arr[4];
	dy = t->arr[5];
	sx = t->arr[6];
	sy = t->arr[7];
	error = t->arr[8];
	while (true)
	{
		i ++;
		if ((x0 == x1 && y0 == y1) \
		|| (!ft_putpixel(x0, y0, get_rgba(rgb0[0] + (gr[0] * i), \
			rgb0[1] + (gr[1] * i), rgb0[2] + (gr[2] * i), 255), t)))
			break ;
		e2 = 2 * error;
		if (e2 >= dy)
		{
			if (x0 == x1)
				break ;
			error = error + dy;
			x0 = x0 + sx;
		}
		if (e2 <= dx)
		{
			if (y0 == y1)
				break ;
			error = error + dx;
			y0 = y0 + sy;
		}
	}
}

Translate the above version with these equations below
 * arr[0] = dx
 * arr[1] = sx
 * arr[2] = dy
 * arr[3] = sy
 * arr[4] = error
 * arr[5] = e2
 * arr[6] = x0
 * arr[7] = x1
 * arr[8] = y0
 * arr[9] = y1
*/
void	bresenham(size_t node0, size_t node1, int n_pixel, t_trans *t)
{
	int	*rgb0;
	int	*rgb1;
	int	gr[3];

	rgb0 = t->map_data->rgb_values[node0];
	rgb1 = t->map_data->rgb_values[node1];
	gr[0] = (rgb1[0] - rgb0[0]) / n_pixel;
	gr[1] = (rgb1[1] - rgb0[1]) / n_pixel;
	gr[2] = (rgb1[2] - rgb0[2]) / n_pixel;
	init_bresenham(t, node0, node1);
	while (true)
	{
		t->arr[9]++;
		if ((t->arr[0] == t->arr[1] && t->arr[2] == t->arr[3]) || \
	(!ft_putpixel(t->arr[0], t->arr[2], get_rgba(rgb0[0] + (gr[0] * t->arr[9]), \
	rgb0[1] + (gr[1] * t->arr[9]), rgb0[2] + (gr[2] * t->arr[9]), 255), t)))
			break ;
		t->arr[10] = 2 * t->arr[8];
		if (t->arr[10] >= t->arr[5])
			if (error_y(t))
				break ;
		if (t->arr[10] <= t->arr[4])
			if (error_x(t))
				break ;
	}
}

int	bigysmall(int x, int y)
{
	if (x < y)
		return (1);
	else
		return (-1);
}

/**
 * @param arr[0] = x0; * @param arr[1] = x1;
 * @param arr[2] = y0; * @param arr[3] = y1;
 * @param arr[4] = dx; * @param arr[5] = dy;
 * @param arr[6] = sx; * @param arr[7] = sy;
 * @param arr[8] = error;
 * @param arr[9] = i //countervariable;
 * @param arr[10] = e2 //countervariable;
*/
void	init_bresenham(t_trans *t, int node0, int node1)
{
	t->arr[0] = t->b_x[node0];
	t->arr[1] = t->b_x[node1];
	t->arr[2] = t->b_y[node0];
	t->arr[3] = t->b_y[node1];
	t->arr[4] = abs(t->b_x[node1] - t->b_x[node0]);
	t->arr[5] = -abs(t->b_y[node1] - t->b_y[node0]);
	t->arr[6] = bigysmall(t->b_x[node0], t->b_x[node1]);
	t->arr[7] = bigysmall(t->b_y[node0], t->b_y[node1]);
	t->arr[8] = t->arr[4] + t->arr[5];
	t->arr[9] = 0;
}

bool	error_x(t_trans *t)
{
	if (t->arr[2] == t->arr[3])
		return (true);
	t->arr[8] = t->arr[8] + t->arr[4];
	t->arr[2] = t->arr[2] + t->arr[7];
	return (false);
}

bool	error_y(t_trans *t)
{
	if (t->arr[0] == t->arr[1])
		return (true);
	t->arr[8] = t->arr[8] + t->arr[5];
	t->arr[0] = t->arr[0] + t->arr[6];
	return (false);
}
