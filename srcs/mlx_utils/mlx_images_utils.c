/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_images_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 08:54:28 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/13 08:56:11 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mlx_utils.h"

t_image_data	*mlx_clone_image(t_memlist **memlist, void *mlx, t_image_data *src)
{
	t_image_data	*newImg;

	newImg = stock_malloc(sizeof(t_image_data), memlist);
	if (!newImg)
		return (NULL);
	newImg->img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	newImg->addr = mlx_get_data_addr(newImg->img, &newImg->bits_per_pixel, &newImg->line_length,
		&newImg->endian);
	if (!newImg->addr)
		return NULL;
	ft_memcpy(newImg->addr, src->addr, WIN_WIDTH * WIN_HEIGHT * (src->bits_per_pixel / 8));
	return (newImg);
}

// fonction pour ajouter un pixel à l'image
void	img_mlx_pixel_put(t_image_data *imageData, int x, int y, int color)
{
	char	*dst;

	dst = imageData->addr + (y * imageData->line_length + x * ( imageData->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// fonction pour afficher l'image dans la fenetre
void	img_mlx_put_image_to_window(t_mlx_data *mlxData, t_image_data *imgData)
{
	mlx_put_image_to_window(mlxData->mlx, mlxData->win, imgData->img, 0, 0);
}

// fonction pour creer une image dans une page
void	img_mlx_init(t_mlx_page *pageData, void *mlx)
{
	pageData->img.img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	pageData->img.addr = mlx_get_data_addr(pageData->img.img, &pageData->img.bits_per_pixel, &pageData->img.line_length,
		&pageData->img.endian);
}
