/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_button.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 08:52:00 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/13 10:04:12 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mlx_utils.h"

static void draw_button(t_mlx_button *button, t_image_data *img, bool drawPressed)
{
	int x;
	int y;

	x = button->x;
	y = button->y;
	while (y < button->y + button->height)
	{
		x = button->x;
		while (x < button->x + button->width)
		{
			if (drawPressed)
			img_mlx_pixel_put(img, x, y, button->pressedColor);
			else
			img_mlx_pixel_put(img, x, y, button->color);
			x++;
		}
		y++;
	}
	mlx_write_text_to_image(button->name, button->x + button->width / 2, button->y + button->height / 2, 2, true, img);
}

bool	mlx_create_button(t_mlx_page *mlxPage, unsigned int btData[6], char *name, int (*funct_ptr)(), void *param)
{
	t_mlx_button	*button;
	t_list			*new;

	button = stock_malloc(sizeof(t_mlx_button), &mlxPage->memlist);
	if (!button)
		return false;
	button->name = name;
	button->x = btData[0];
	button->y = btData[1];
	button->width = btData[2];
	button->height = btData[3];
	button->color = btData[4];
	button->pressedColor = btData[5];
	button->pressedButtonImg = NULL;
	button->funct_ptr = funct_ptr;
	button->param = param;
	new = ft_lstnew(button, &mlxPage->memlist);
	if (new == NULL)
	return false;
	ft_lstadd_back(&mlxPage->buttonsLst, new);
	return true;
}

int	check_hover_button(int x, int y, t_mlx_data *mlxData)
{
	t_list		*actual = ((t_mlx_page *)mlxData->pages->content)->buttonsLst;
	bool		hover = false;
	while (actual)
	{
		if (x >= ((t_mlx_button *)actual->content)->x && x <= ((t_mlx_button *)actual->content)->x + ((t_mlx_button *)actual->content)->width
			&& y >= ((t_mlx_button *)actual->content)->y && y <= ((t_mlx_button *)actual->content)->y + ((t_mlx_button *)actual->content)->height)
		{
			img_mlx_put_image_to_window(mlxData, ((t_mlx_button *)actual->content)->pressedButtonImg);
			hover = true;
		}
		actual = actual->next;
	}
	if (!hover)
		img_mlx_put_image_to_window(mlxData, &((t_mlx_page *)mlxData->pages->content)->img);
	return (0);
}

// doit etre appelé juste avant d'afficher l'image pour afficher les boutons par dessus le reste de l'image
int	mlx_render_all_button(t_mlx_page *page, t_mlx_data *mlxData)
{
	t_list		*actual = page->buttonsLst;
	while (actual)
	{
		draw_button((t_mlx_button *)actual->content, &page->img, false);
		actual = actual->next;
	}
	actual = page->buttonsLst;
	while (actual)
	{
		if (((t_mlx_button *)actual->content)->pressedButtonImg == NULL)
		{
			((t_mlx_button *)actual->content)->pressedButtonImg = mlx_clone_image(&page->memlist, mlxData->mlx, &page->img);
			if (!((t_mlx_button *)actual->content)->pressedButtonImg)
				return 1;
			draw_button((t_mlx_button *)actual->content, ((t_mlx_button *)actual->content)->pressedButtonImg, true);
		}
		actual = actual->next;
	}
	return 0;
}

int	mlx_button_hook(int button, int x, int y, t_mlx_page *page)
{
	t_list		*actual = page->buttonsLst;
	(void)button;

	while (actual)
	{
		if (x >= ((t_mlx_button *)actual->content)->x && x <= ((t_mlx_button *)actual->content)->x + ((t_mlx_button *)actual->content)->width
			&& y >= ((t_mlx_button *)actual->content)->y && y <= ((t_mlx_button *)actual->content)->y + ((t_mlx_button *)actual->content)->height)
		{
			if (((t_mlx_button *)actual->content)->funct_ptr)
				((t_mlx_button *)actual->content)->funct_ptr(((t_mlx_button *)actual->content)->param);
			return (0);
		}
		actual = actual->next;
	}
	return (0);
}
