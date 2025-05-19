/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:15:54 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/19 20:44:48 by cpapot           ###   ########.fr       */
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

// int test_button2(t_mlx_data *mlxData)
// {
// 	if (mlx_init_page(mlxData))
// 		return (ft_putstr_fd("Error: mlx_init_page failed\n", 2), 1);


// 	int color = rgb_to_int(209, 207, 207);
// 	for (int i = 0; i < WIN_WIDTH; i++)
// 	{
// 		for (int j = 0; j < WIN_HEIGHT; j++)
// 		{
// 			img_mlx_pixel_put(&((t_mlx_page *)mlxData->pages->content)->img, i, j, (int)color);
// 		}
// 	}
// 	// mlx_create_button(mlxData->pages->content, (unsigned int[6]){0, 0, 200, 50, 0xA6A6A6, 0x6B6B6B}, "START", test_button1, NULL);
// 	mlx_create_button(mlxData->pages->content, (unsigned int[6]){700, 100, 200, 50, 0xA6A6A6, 0x6B6B6B}, "Exit", mlx_free, mlxData);

// 	if (mlx_render_all_button(mlxData->pages->content, mlxData))
// 	{
// 		ft_putstr_fd("Error: mlx_render_all_button failed\n", 2);
// 		return (1);
// 	}

// 	img_mlx_put_image_to_window(mlxData, &((t_mlx_page *)mlxData->pages->content)->img);
// 	return (0);
// }

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

void launch_menu(t_shared_data_manager *shmData);

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
	t_shared_data_manager	shmData;


	// gerer team avec argv[1] = team_id(int) entre 1 et 4 compris

	shmData.semid = create_or_join_semaphore(0, &shmData.isHost);
	if (shmData.semid == -1)
	{
		ft_printf("%s Error: ipc_create_or_connect failed\n", ERROR_PRINT);
		return (1);
	}
	if (shmData.isHost)
	{			// host
			//ipc_receive_message(&ipc);
			//ipc_send_message(&ipc, "Je suis l'hôte !");
		ft_printf("%s Semaphore created\n", DEBUG_PRINT);
		launch_menu(&shmData);
	}
	else
	{			// client
		ft_printf("%s Host already exists, joining...\n", INFO_PRINT);
		ft_printf("%s Waiting for the host to define game rules and all players to join.\n", INFO_PRINT);
		sem_wait(shmData.semid);
		/*
			quand on se connecte deux possibilités sois le host est en train de faire ses trucs
			pour le verifier on essaye de se connecter à la memoire partagée si on arrive sy connecter c'est que le deuxieme cas si on viens de la créer on la supprime et c'est le premier cas
				quand il fait ses trucs il n'y a pas de shared memory
				on attend qu'il nous dise que la que la memoire est prete et on fait la deuxieme partie
			deuxieme cas
				on se connecte a la memoire partagée
				lock la memoire partagée
				on incremente le nombre de joueurs connectés
				unclock la memoire partagée
		*/
		ft_printf("%s All players have joined game starting.\n", INFO_PRINT);
	}
	clean_shared_memory(shmData.shmid, shmData.semid, shmData.data, true);
}
