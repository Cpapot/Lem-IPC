/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:12:34 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/12 20:28:10 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mlx_utils.h"
#include <stdio.h>

// fonction pour ouvir fenetre
t_mlx_data	*mlx_init_window(void)
{
	t_mlx_data	*mlx_data;

	mlx_data = malloc(sizeof(t_mlx_data));
	if (!mlx_data)
		return NULL;
	mlx_data->mlx = mlx_init();
	if (!mlx_data->mlx)
		return NULL;
	mlx_data->win = mlx_new_window(mlx_data->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
	if (!mlx_data->win)
	{
		free(mlx_data->mlx);
		return NULL;
	}
	return (mlx_data);
}

// fonction pour creer une image dans une page
void	img_mlx_init(t_mlx_page *pageData, void *mlx)
{
	pageData->img.img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	pageData->img.addr = mlx_get_data_addr(pageData->img.img, &pageData->img.bits_per_pixel, &pageData->img.line_length,
		&pageData->img.endian);
}

int	mlx_init_page(t_mlx_data *mlxData)
{
	t_mlx_page	*pageData;

	pageData = stock_malloc(sizeof(t_mlx_page), &mlxData->mlxMemList);
	if (!pageData)
		return (1);
	pageData->buttonsLst = NULL;
	pageData->memlist = NULL;
	img_mlx_init(pageData, mlxData->mlx);
	ft_lstadd_back(&mlxData->pages, ft_lstnew(pageData, &mlxData->mlxMemList));
	return (0);
}

// fonction pour afficher l'image dans la fenetre
void	img_mlx_put_image_to_window(t_mlx_data *mlxData, t_image_data *imgData)
{
	mlx_put_image_to_window(mlxData->mlx, mlxData->win, imgData->img, 0, 0);
}

// fonction pour ajouter un pixel à l'image
void	img_mlx_pixel_put(t_image_data *imageData, int x, int y, int color)
{
	char	*dst;

	dst = imageData->addr + (y * imageData->line_length + x * ( imageData->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// rgb to int
int		rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

// fonction pour liberer la memoire de la mlx
int		mlx_free(t_mlx_data *mlxData)
{
	printf("mlx_free\n");
	(void)mlxData;
	// if (mlxData->img.img)
	// 	mlx_destroy_image(mlxData->mlx, mlxData->img.img);
	// if (mlxData->win)
	// 	mlx_destroy_window(mlxData->mlx, mlxData->win);
	// if (mlxData->mlx)
	// 	free(mlxData->mlx);
	// free(mlxData);
	exit(0);
	return (0);
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

// fonction pour gerer les hooks uniquement sur la premere page de la liste
void	mlx_hooks_init(t_mlx_data *mlxData)
{
	mlx_mouse_hook(mlxData->win, mlx_button_hook, mlxData->pages->content);
	mlx_hook(mlxData->win, ON_MOUSEMOVE, 1L<<6, check_hover_button, mlxData);
	mlx_hook(mlxData->win, ON_DESTROY, 0, mlx_free, mlxData);
	//pour chaque bouton on ajoute un hook pour le click
	mlx_loop(mlxData->mlx);
}

// on ajoute un t_mlx_button dans une liste chainée on ajoute un hook pour le click
// hover button effect (with mouse position)
// onclick button (prend effect au relachement du bouton)
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
	//mlx_mouse_hook(mlxData->win, funct_ptr, param);
}

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
	mlx_write_text_to_image(button->name, button->x, button->y, 2, img);
}

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

// doit etre appelé juste avant d'afficher l'image pour afficher les boutons par dessus le reste de l'image

// on dessine chaque bouton dans l'image

// on copie l'image avec les boutons dans pressedButtonImg et on redessine chaque bouton préssé 1 par 1
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

// void mlx_destroy_button(t_mlx_data *mlxData)
// {
	// 	mlx_destroy_window(mlxData->mlx, mlxData->win);
	// }
