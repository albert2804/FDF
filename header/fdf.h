/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:58:50 by aestraic          #+#    #+#             */
/*   Updated: 2022/12/22 18:25:17 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# ifndef WIDTH
#  define WIDTH 1200
# endif

# ifndef HEIGHT
#  define HEIGHT 1200
# endif

# include <fcntl.h>
# include <limits.h>
# include <memory.h>
# include <math.h>
# include <stdbool.h>

# include <libft.h>
# include "../MLX42/include/MLX42/MLX42.h"

//STRUCTS
/**
 * Stores initial information about the map, 
 * which are read in from test_maps.
 * 
 * @param count_x Counts the nodes in x-direction
 * @param count_y Counts the nodes in y-direction
 * @param total_count Represents total count of nodes (=count_x * count_y)
 * @param max_xy Represents the max-value between count_x and count_y 
 * @param values_matrix Stores the xyz-positions of all nodes in the form
 * 						 [[x1,y1,z1], [x2, y2, z2], ...] + color_code
 * @param delta Represents the distance between nodes in xy-direction
 * @param offset_x Represents the x-offset from Imageeckpunkt x (0,0)
 * @param offset_y Represents the y-offset from Imageeckpunkt y (0,0)
 * @param center Represents the center coordiantes in x-y direction.
 */
typedef struct s_readmap
{
	size_t		count_x;
	size_t		count_y;
	size_t		max_xy;
	int			delta;
	int			offset_x;
	int			offset_y;
	size_t		total_count;
	int			**values_matrix;
	int			**rgb_values;
}			t_readmap;

/**
 * Used for storing calculation values, dependng on the viewing angle.
 * @param angles Represents the viewing angle
 * @param matrix Stores the newly calculated values for of each node in 
 * 						3D representation in the form  [[x1,y1,z1],[x2,y2,z1]]
 * 						, depending on the viewing angles and 
 * 							distance of the "camera(view point)"
 * @param b_x Represents the x-coordiante of the 2D-depiction of all nodes.
 * @param b_y Represents the y-coordiante of the 2D-depiction of all nodes.
 * @param cx Represents the x-coordiante of the camera.
 * @param cy Represents the y-coordiante of the camera..
 * @param cz Represents the z-coordiante of the camera..
 * @param ex surface position relative to camera position cx
 * @param ey surface position relative to camera position cy
 * @param ez surface position relative to camera position cz
 * @param perspective flag to decide if displazed in parallel or
 * 						 perspective projection. 
 * 							1 means perspective projection.
 * @param arr[10] array needed for bresenham variables.
*/
typedef struct s_trans
{
	mlx_image_t	*img;
	mlx_t		*mlx;
	t_readmap	*map_data;
	int			**matrix;
	size_t		alpha;
	size_t		beta;
	size_t		gamma;
	int			*b_x;
	int			*b_y;
	double		zoom;
	int			ex;
	int			ey;
	int			ez;
	int			cx;
	int			cy;
	int			cz;
	int			color_gradient;
	int			perspective_projection;
	int			arr[11];
}			t_trans;

//Read maps
size_t	ft_count_spaces(char *c);
void	read_map_vertices(int fd, t_readmap *map_data);
void	get_map_information(char *map_name, t_readmap *map_data);
void	xyz_pos(int fd, size_t row, size_t col, t_readmap *map_data);
void	init_map(char *map_name, t_readmap *map_data, t_trans *transform);
void	init_perspective(t_trans *transform, mlx_image_t *g_img);
void	read_color(int fd, size_t row, size_t col, t_readmap *md);
bool	input_handling(int argc, char **argv);
void	controls(void);

//Transform from 2D into 3D
void	transformation(t_trans *t);
int		transform_x(t_trans *trans, int p_x, int p_y, int p_z);
int		transform_y(t_trans *trans, int p_x, int p_y, int p_z);
int		transform_z(t_trans *trans, int p_x, int p_y, int p_z);
void	calculate_xy(t_trans *transform, size_t node);

//Utils
void	fr_dblsgl_p(void **dbl, void *sgl, size_t c);
void	determine_delta(t_readmap *map_data);
bool	equal(int a, int b, int c, int d);
char	*trim(char **line);

//Bresenham
int		bigysmall(int x, int y);
void	init_bresenham(t_trans *t, int node0, int node1);
void	bresenham(size_t node0, size_t node1, int n_pixel, t_trans *t);
bool	error_x(t_trans *t);
bool	error_y(t_trans *t);

//Draw-Utils
void	draw_image(mlx_image_t *g_img, t_trans *calc);
void	hor_line(size_t node, mlx_image_t *g_img, t_trans *trans);
void	ver_line(size_t node, mlx_image_t *g_img, t_trans *trans);
void	draw_grid(t_trans *transform, mlx_image_t *g_img);
bool	ft_putpixel(uint32_t x, uint32_t y, int color, t_trans *t);

//Hooks
void	change_angles(mlx_t *mlx, t_trans *transform, mlx_image_t *g_img);
void	make_new_image(t_trans *transform, mlx_image_t *g_img);
void	hook(void *param);
void	translate(mlx_t *mlx, t_trans *transform, mlx_image_t *g_img);
void	perspective(mlx_t *mlx, t_trans *transform, mlx_image_t *g_img);
void	effect(t_trans *transform, mlx_image_t *g_img);

//Colors
int		*rgb_converter( int i, char *str, int **rgb_values, t_readmap *md);
int		get_rgba(int r, int g, int b, int a);
int		*rgb_decider(char *str, int *digits);

//Allocations
int		**cal_matrix(t_readmap *map_data);
int		*cal_values(t_readmap *map_data, int **matrix, size_t row);
size_t	*cal_vertices(t_readmap *map_data);
void	free_map_data(t_trans *transform);
void	free_bx(t_readmap *map_data, t_trans *trans);
void	free_by(t_readmap *map_data, t_trans *trans, int *bx);
void	free_mlx(t_readmap *map_data, t_trans *trans, int *bx);
void	free_matrix(t_readmap *map_data);
void	free_vertices(t_readmap *map_data);
void	free_values(t_readmap *map_data, int **matrix, int row);
void	free_rgbv(t_readmap *map_data);
void	free_rgbc(t_readmap *map_data, int **rgb_values, int count);
void	free_digits(t_readmap *map_data, int **rgb_values, int count, int *rgb);

#endif