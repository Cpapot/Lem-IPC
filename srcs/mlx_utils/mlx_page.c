/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_page.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 08:56:20 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/13 09:45:01 by cpapot           ###   ########.fr       */
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
	img_mlx_init(pageData, mlxData->mlx);
	ft_lstadd_front(&mlxData->pages, ft_lstnew(pageData, &mlxData->mlxMemList));
	return (0);
}

