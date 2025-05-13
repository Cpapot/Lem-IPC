/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:15:54 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/13 14:44:45 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem-ipc.h"
#include "../inc/mlx_utils.h"
#include "../inc/ipc.h"
#include <stdio.h>

int test_button1(void *param)
{
	(void)param;
	printf("Button 1 pressed\n");
	return (0);
}

int test_button2(t_mlx_data *mlxData)
{
	if (mlx_init_page(mlxData))
		return (ft_putstr_fd("Error: mlx_init_page failed\n", 2), 1);


	int color = rgb_to_int(209, 207, 207);
	for (int i = 0; i < WIN_WIDTH; i++)
	{
		for (int j = 0; j < WIN_HEIGHT; j++)
		{
			img_mlx_pixel_put(&((t_mlx_page *)mlxData->pages->content)->img, i, j, (int)color);
		}
	}
	// mlx_create_button(mlxData->pages->content, (unsigned int[6]){0, 0, 200, 50, 0xA6A6A6, 0x6B6B6B}, "START", test_button1, NULL);
	mlx_create_button(mlxData->pages->content, (unsigned int[6]){700, 100, 200, 50, 0xA6A6A6, 0x6B6B6B}, "Exit", mlx_free, mlxData);

	if (mlx_render_all_button(mlxData->pages->content, mlxData))
	{
		ft_putstr_fd("Error: mlx_render_all_button failed\n", 2);
		return (1);
	}

	img_mlx_put_image_to_window(mlxData, &((t_mlx_page *)mlxData->pages->content)->img);
	return (0);
}

// int main(void)
// {
// 	t_mlx_data		*mlxData = mlx_init_window();

// 	if (!mlxData)
// 		return (ft_putstr_fd("Error: mlx_init_window failed\n", 2), 1);

// 	if (mlx_init_page(mlxData))
// 		return (ft_putstr_fd("Error: mlx_init_page failed\n", 2), 1);

// 	mlx_create_button(mlxData->pages->content, (unsigned int[6]){200, 100, 200, 50, 0xA6A6A6, 0x6B6B6B}, "Start", test_button1, NULL);
// 	mlx_create_button(mlxData->pages->content, (unsigned int[6]){400, 100, 200, 50, 0xA6A6A6, 0x6B6B6B}, "Change page", test_button2, mlxData);
// 	mlx_create_button(mlxData->pages->content, (unsigned int[6]){700, 100, 200, 50, 0xA6A6A6, 0x6B6B6B}, "Exit", mlx_free, mlxData);


// 	int color = rgb_to_int(209, 207, 207);
// 	for (int i = 0; i < WIN_WIDTH; i++)
// 	{
// 		for (int j = 0; j < WIN_HEIGHT; j++)
// 		{
// 			img_mlx_pixel_put(&((t_mlx_page *)mlxData->pages->content)->img, i, j, (int)color);
// 		}
// 	}
// 	if (mlx_render_all_button(mlxData->pages->content, mlxData))
// 	{
// 		ft_putstr_fd("Error: mlx_render_all_button failed\n", 2);
// 		return (1);
// 	}
// 	img_mlx_put_image_to_window(mlxData, &((t_mlx_page *)mlxData->pages->content)->img);
// 	mlx_hooks_init(mlxData);
// 	mlx_loop(mlxData->mlx);
// 	//ft_printf("Hello, World!\n");
// }

void launch_menu(t_ipc *ipc);

int main(void)
{
	// on verifie si la queue de message existe déjà

	// si oui on n'est pas l'host
	// on se connecte à la queue de message
	// on envoie un message pour dire qu'on est là
	// on recupere le terrain (memoire partagée)
	// on attend le message qui nous dit que la partie commence

	// sinon on est l'host et on crée la queue de message
	// on demande le nombre de de joueurs (depuis le argv)
	// on initalise le terrain (on cree un tableau de memoire partagé)
	// on attend le message de chaque joueur pour dire qu'il sont la
	// on envoie le message pour dire que la partie commence
	t_ipc	ipc;

	switch (ipc_create_or_connect(&ipc))
	{
		case 1:
			// host
			//ipc_receive_message(&ipc);
			//ipc_send_message(&ipc, "Je suis l'hôte !");
			launch_menu(&ipc);
			break;
		case 2:
			// client
			ipc_send_message(&ipc, "hello");
			ipc_receive_message(&ipc);
			break;
		case 0:
			ft_printf("%s Error: ipc_create_or_connect failed\n", ERROR_PRINT);
	}
	ipc_clean(&ipc);
}
