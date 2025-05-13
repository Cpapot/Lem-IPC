/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_page.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 08:56:20 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/13 16:45:16 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mlx_utils.h"
#include <stdio.h>

int	mlx_init_page(t_mlx_data *mlxData)
{
	t_mlx_page	*pageData;

	pageData = stock_malloc(sizeof(t_mlx_page), &mlxData->mlxMemList);
	if (!pageData)
		return (1);
	pageData->buttonsLst = NULL;
	pageData->memlist = NULL;
	pageData->mlxData = mlxData;
	img_mlx_init(pageData, mlxData->mlx);
	ft_lstadd_front(&mlxData->pages, ft_lstnew(pageData, &mlxData->mlxMemList));
	return (0);
}

void render_page(t_mlx_page *pageData, t_mlx_data *mlxData)
{
	set_image_color(&((t_mlx_page *)mlxData->pages->content)->img, pageData->color);
	if (mlx_render_all_slider(pageData, mlxData))
		perror("mlx_render_all_slider"), mlx_free(mlxData);
	if (mlx_render_all_button(pageData, mlxData))
		perror("mlx_render_all_button"), mlx_free(mlxData);
	img_mlx_put_image_to_window(mlxData, &pageData->img);
}
