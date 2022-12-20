/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:11:40 by aestraic          #+#    #+#             */
/*   Updated: 2022/12/20 14:05:36 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	hook(void *param)
{
	t_trans		*transform;
	mlx_t		*mlx;
	mlx_image_t	*g_img;

	transform = param;
	mlx = transform->mlx;
	g_img = transform->img;
	if (mlx_is_key_down(mlx, MLX_KEY_P))
		init_perspective(transform, g_img);
	else if (mlx_is_key_down(mlx, MLX_KEY_LEFT_SHIFT))
		change_angles(mlx, transform, g_img);
	else if (mlx_is_key_down(mlx, MLX_KEY_TAB))
		perspective(mlx, transform, g_img);
	else
		translate(mlx, transform, g_img);
	if (transform->zoom < 0.06)
		transform->zoom = 0.06;
}

void	make_new_image(t_trans *transform, mlx_image_t *g_img)
{
	memset(g_img->pixels, 0, g_img->width * g_img->height * 4);
	transformation(transform);
	draw_image(g_img, transform);
}

void	change_angles(mlx_t *mlx, t_trans *transform, mlx_image_t *g_img)
{
	if (transform->alpha == 0)
		transform->alpha = 360;
	if (transform->beta == 0)
		transform->beta = 360;
	if (transform->gamma == 0)
		transform->gamma = 360;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
			transform->gamma -= 5;
	else if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		transform->gamma += 5;
	else if (mlx_is_key_down(mlx, MLX_KEY_UP))
		transform->alpha += 5;
	else if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		transform->alpha -= 5;
	else if (mlx_is_key_down(mlx, MLX_KEY_KP_0))
		transform->beta += 5;
	else if (mlx_is_key_down(mlx, MLX_KEY_RIGHT_CONTROL))
		transform->beta -= 5;
	else if (mlx_is_key_down(mlx, MLX_KEY_KP_ADD))
		transform->zoom -= 0.02;
	else if (mlx_is_key_down(mlx, MLX_KEY_KP_SUBTRACT))
		transform->zoom += 0.02;
	else
		return ;
	make_new_image(transform, g_img);
}

void	translate(mlx_t *mlx, t_trans *transform, mlx_image_t *g_img)
{	
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	else if (mlx_is_key_down(mlx, MLX_KEY_UP))
		transform->ey -= 10;
	else if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		transform->ey += 10;
	else if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		transform->ex -= 10;
	else if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		transform->ex += 10;
	else
		return ;
	make_new_image(transform, g_img);
}

void	perspective(mlx_t *mlx, t_trans *transform, mlx_image_t *g_img)
{
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT_CONTROL))
		transform->cz += 10;
	else if (mlx_is_key_down(mlx, MLX_KEY_KP_0))
		transform->cz -= 10;
	else if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		transform->cx += 10;
	else if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		transform->cx -= 10;
	else if (mlx_is_key_down(mlx, MLX_KEY_UP))
		transform->cy += 10;
	else if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		transform->cy -= 10;
	else
		return ;
	make_new_image(transform, g_img);
}
