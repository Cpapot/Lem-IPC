/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 08:57:04 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/13 16:59:21 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mlx_utils.h"

static int click_hook(int button, int x, int y, void *ptr)
{
	mlx_button_hook(button, x, y, ptr);
	mlx_slider_hook(button, x, y, ptr);
	return (0);
}

void	mlx_hooks_init(t_mlx_data *mlxData)
{
	mlx_mouse_hook(mlxData->win, click_hook, mlxData->pages->content);
	mlx_hook(mlxData->win, ON_MOUSEMOVE, 1L<<6, check_hover_button, mlxData);
	mlx_hook(mlxData->win, ON_DESTROY, 0, mlx_free, mlxData);
	mlx_loop(mlxData->mlx);
}
