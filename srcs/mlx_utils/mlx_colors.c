/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:00:13 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/13 14:13:11 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mlx_utils.h"

int		rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	set_image_color(t_image_data *img, int color)
{
	int i;
	int j;

	i = 0;
	while (i < WIN_WIDTH)
	{
		j = 0;
		while (j < WIN_HEIGHT)
		{
			img_mlx_pixel_put(img, i, j, color);
			j++;
		}
		i++;
	}
}
