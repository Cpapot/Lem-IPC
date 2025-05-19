/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_page.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 08:56:20 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/19 18:55:00 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mlx_utils.h"
#include <stdio.h>

int	mlx_init_page(t_mlx_data *mlxData, char *name)
{
	t_mlx_page	*pageData;

	pageData = stock_malloc(sizeof(t_mlx_page), &mlxData->mlxMemList);
	if (!pageData)
		return (1);
	pageData->buttonsLst = NULL;
	pageData->sliderLst = NULL;
	pageData->memlist = NULL;
	pageData->mlxData = mlxData;
	pageData->name = name;
	img_mlx_init(pageData, mlxData->mlx);
	ft_lstadd_front(&mlxData->pages, ft_lstnew(pageData, &mlxData->mlxMemList));
	return (0);
}

t_mlx_page	*mlx_get_page(t_mlx_data *mlxData, char *name)
{
	t_list	*tmp;

	tmp = mlxData->pages;
	while (tmp)
	{
		if (ft_strcmp(((t_mlx_page *)tmp->content)->name, name))
			return ((t_mlx_page *)tmp->content);
		tmp = tmp->next;
	}
	ft_printf("%s Page %s not found\n", ERROR_PRINT, name);
	return (NULL);
}

void	mlx_free_page(t_mlx_data *mlxData, t_mlx_page *pageData)
{
	if (pageData->img.img)
		mlx_destroy_image(mlxData->mlx, pageData->img.img);
	t_list	*tmp = pageData->buttonsLst;
	while (tmp)
	{
		t_mlx_button *button = (t_mlx_button *)tmp->content;
		if (button->pressedButtonImg)
			mlx_destroy_image(mlxData->mlx, button->pressedButtonImg->img);
		tmp = tmp->next;
	}
	stock_free(&pageData->memlist);
	tmp = mlxData->pages;
	t_list	*prev = NULL;
	while (tmp)
	{
		if (tmp->content == pageData)
		{
			if (prev == NULL)
				mlxData->pages = tmp->next;
			else
				prev->next = tmp->next;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	ft_printf("%s Page freed: %s\n", DEBUG_PRINT, pageData->name);
}
