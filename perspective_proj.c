/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_transform.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:16:28 by aestraic          #+#    #+#             */
/*   Updated: 2022/12/02 15:35:35 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void transformation(t_readmap *map_data, t_trans *transform)
{	
	double	rad;
	int		c_y;
	int		c_x;
	int		c_z;
	int		e_x = 600;
	int		e_y = 600;
	int		e_z = 50;
	int		p_x;
	int		p_y;
	int		p_z;
	size_t	node;

	transform->alpha = 0;
	transform->beta = 70;
	transform->gamma = 0;
	c_x = WIDTH/2;
	c_y = HEIGHT/2;
	c_z = -2000;
	rad = ((M_PI/180));
	node = 0;
	transform->matrix = map_data->values_matrix;
	
	ft_printf("\n\n----------Transformation----------\n");
	ft_printf("Node X: %d\n", map_data->values_matrix[1][0]);
	ft_printf("Node Y: %d\n", map_data->values_matrix[1][1]);
	ft_printf("Node Z: %d\n", map_data->values_matrix[1][2]);
	while (node < map_data->total_count)
	{
		p_x = map_data->values_matrix[node][0];
		p_y = map_data->values_matrix[node][1];
		p_z = map_data->values_matrix[node][2] * (-10);
		transform->matrix[node][0] = cos(transform->beta * rad) * (sin(transform->gamma * rad) * (p_y - c_y) +\
											cos(transform->gamma * rad) * (p_x - c_x)) -\
									sin(transform->beta * rad) * (p_z - c_z);
		transform->matrix[node][1] = sin(transform->alpha * rad) * (cos(transform->beta * rad) * (p_z - c_z) +\
																	sin(transform->beta * rad) * (sin(transform->gamma * rad) * (p_y - c_y) +\
																									cos(transform->gamma * rad) * (p_x - c_x))) +\
									cos(transform->alpha * rad) * (cos(transform->gamma * rad) * (p_y - c_y) -\
																	sin(transform->gamma * rad) * (p_x - c_x));
		transform->matrix[node][2] = cos(transform->alpha * rad) * (cos(transform->beta * rad) * (p_z - c_z) +\
																	sin(transform->beta * rad) * (sin(transform->gamma * rad) * (p_y - c_y) +\
																									cos(transform->gamma * rad) * (p_x - c_x))) -\
									sin(transform->alpha * rad) * (cos(transform->gamma * rad) * (p_y - c_y) -\
																	sin(transform->gamma * rad) * (p_x - c_x));
		transform->b_x[node] = e_z * transform->matrix[node][0]/transform->matrix[node][2] + e_x;
		transform->b_y[node] = e_z * transform->matrix[node][1]/transform->matrix[node][2] + e_y;
		ft_printf("\ntransformed x: %d\n", node);
		// ft_printf("transformed y: %d\n", transform->b_y[node]);
		node ++;
	}
ft_printf("\ntransformed: %d\n", node);

}
