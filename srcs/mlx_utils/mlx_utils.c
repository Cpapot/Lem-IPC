/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:12:34 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/13 09:03:04 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mlx_utils.h"

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

// fonction pour liberer la memoire de la mlx
int		mlx_free(t_mlx_data *mlxData)
{
	ft_printf("mlx_free\n");
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

