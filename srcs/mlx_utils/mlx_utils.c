/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:12:34 by cpapot            #+#    #+#             */
/*   Updated: 2025/06/04 16:49:27 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mlx_utils.h"
#include "../inc/ipc.h"


// fonction pour ouvir fenetre
t_mlx_data	*mlx_init_window(void)
{
	t_mlx_data	*mlx_data;

	mlx_data = malloc(sizeof(t_mlx_data));
	if (!mlx_data)
		return NULL;
	mlx_data->mlxMemList = NULL;
	mlx_data->pages = NULL;
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
	t_list		*actual = mlxData->pages;
	while (actual)
	{
		t_list	*actualbutton = ((t_mlx_page *)actual->content)->buttonsLst;
		while (actualbutton)
		{
			t_mlx_button *button = (t_mlx_button *)actualbutton->content;
			if (button->pressedButtonImg)
				mlx_destroy_image(mlxData->mlx, button->pressedButtonImg->img);
			actualbutton = actualbutton->next;
		}
		mlx_destroy_image(mlxData->mlx, ((t_mlx_page *)actual->content)->img.img);
		stock_free(&((t_mlx_page *)actual->content)->memlist);
		actual = actual->next;
	}
	stock_free(&mlxData->mlxMemList);
	if (mlxData->win)
		mlx_destroy_window(mlxData->mlx, mlxData->win);
	if (mlxData->mlx)
		free(mlxData->mlx);

	//TO MOVE LATER

	sem_wait(mlxData->shmData->semid);
	mlxData->shmData->data->isFinish = true;
	sem_signal(mlxData->shmData->semid);

	usleep(10000);

	clean_shared_memory(mlxData->shmData->shmid, mlxData->shmData->data, true);
	remove_semaphore(mlxData->shmData->semid, mlxData->shmData->isHost);


	//
	free(mlxData);
	exit(0);
	return (0);
}

