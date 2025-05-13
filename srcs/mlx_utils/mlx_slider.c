/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_slider.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:07:08 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/13 17:55:42 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mlx_utils.h"

// ne fonctionne pas exactement comme un bouton on doit redessiner la page a chaque changement du slider (avec bouton appuyé)

static void draw_slider(t_mlx_slider *slider, t_image_data *img)
{
	int x;
	int y;

	x = slider->x;
	y = slider->y;
	while (y < slider->y + slider->height)
	{
		x = slider->x;
		while (x < slider->x + slider->width)
		{
			img_mlx_pixel_put(img, x, y, slider->color);
			x++;
		}
		y++;
	}
	int circleY = slider->y + (slider->height / 2);
	int circleX = slider->x + ((*slider->value - slider->minValue) / slider->step) * slider->stepSize;
	int circleRadius = slider->height * 1.5;
	for (int i = -circleRadius; i <= circleRadius; i++)
	{
		for (int j = -circleRadius; j <= circleRadius; j++)
		{
			if (i * i + j * j <= circleRadius * circleRadius && circleX + i >= 0 && circleX + i < WIN_WIDTH)
				img_mlx_pixel_put(img, circleX + i, circleY + j, slider->circleColor);
		}
	}
	char *value = ft_itoa(*slider->value);
	if (value)
	{
		mlx_write_text_to_image(value, circleX + 2 , circleY + 2, 2, true, img);
		free(value);
	}
}

int		mlx_create_slider(t_mlx_page *mlxPage, unsigned int sliderData[10], int *value)
{
	t_mlx_slider	*slider;
	t_list		*new;

	slider = stock_malloc(sizeof(t_mlx_slider), &mlxPage->memlist);
	if (!slider)
		return (1);
	slider->x = sliderData[0];
	slider->y = sliderData[1];
	slider->width = sliderData[2];
	slider->height = sliderData[3];
	slider->color = sliderData[4];
	slider->circleColor = sliderData[5];
	slider->minValue = sliderData[6];
	slider->maxValue = sliderData[7];
	slider->initialValue = sliderData[8];
	slider->step = sliderData[9];
	slider->value = value;
	*slider->value = slider->initialValue;
	slider->stepSize = (slider->width * slider->step) / (slider->maxValue - slider->minValue);
	new = ft_lstnew(slider, &mlxPage->memlist);
	if (new == NULL)
		return (1);
	ft_lstadd_back(&mlxPage->sliderLst, new);
	return (0);
}

int	mlx_render_all_slider(t_mlx_page *page, t_mlx_data *mlxData)
{
	(void)mlxData;
	t_list		*actual = page->sliderLst;
	while (actual)
	{
		draw_slider((t_mlx_slider *)actual->content, &page->img);
		actual = actual->next;
	}
	return 0;
}

int		mlx_slider_hook(int button, int x, int y, t_mlx_page *page)
{
	t_list		*actual = page->sliderLst;
	(void)button;

	while (actual)
	{
		int circleY = ((t_mlx_slider *)actual->content)->y + (((t_mlx_slider *)actual->content)->height / 2);
		int circleRadius = ((t_mlx_slider *)actual->content)->height * 1.5;
		if (y >= circleY - circleRadius && y <= circleY + circleRadius * 10 && x >= ((t_mlx_slider *)actual->content)->x \
			&& x <= ((t_mlx_slider *)actual->content)->x + ((t_mlx_slider *)actual->content)->width + ((t_mlx_slider *)actual->content)->stepSize){
			int newValue = ((x - ((t_mlx_slider *)actual->content)->x) / (((t_mlx_slider *)actual->content)->stepSize)) * ((t_mlx_slider *)actual->content)->step + ((t_mlx_slider *)actual->content)->minValue;
			if (newValue < ((t_mlx_slider *)actual->content)->minValue)
				newValue = ((t_mlx_slider *)actual->content)->minValue;
			if (newValue > ((t_mlx_slider *)actual->content)->maxValue)
				newValue = ((t_mlx_slider *)actual->content)->maxValue;
			*((int *)(((t_mlx_slider *)actual->content)->value)) = newValue;
			render_page(page, page->mlxData);
		}
		actual = actual->next;
	}
	return (0);
}
