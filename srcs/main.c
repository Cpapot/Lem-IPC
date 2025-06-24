/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:15:54 by cpapot            #+#    #+#             */
/*   Updated: 2025/06/24 19:07:02 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem-ipc.h"
#include "../inc/mlx_utils.h"
#include "../inc/ipc.h"
#include <stdio.h>

/*
CE NEST PAS LHOST QUI CLEAN LA MEMOIRE PARTAGEE ET LES IPC MAIS LE LAST PLAYER
*/

int game_process(t_shared_data_manager *shmData, int semid, int team_id);

int test_button1(void *param)
{
	(void)param;
	printf("Button 1 pressed\n");
	return (0);
}

void launch_menu(t_shared_data_manager *shmData);

int team_id_from_argv(int argc, char **argv)
{
	if (argc < 2)
	{
		ft_printf_fd(1, "%s Error: No team ID provided. Please provide a team ID between 1 and 4.\n", ERROR_PRINT);
		return (-1);
	}
	int team_id = ft_atoi(argv[1]);
	if (team_id < 1 || team_id > 4)
	{
		ft_printf_fd(1, "%s Error: Invalid team ID %d. Please provide a team ID between 1 and 4.\n", ERROR_PRINT, team_id);
		return (-1);
	}
	return (team_id);
}

int main(int argc, char **argv)
{
	int teamId = team_id_from_argv(argc, argv);
	if (teamId == -1)
		return (1);

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

	shmData.semid = create_or_join_semaphore(1, &shmData.isHost);
	printf("semid: %d\n", shmData.semid );
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
		shmData.data = create_or_get_shared_memory(&shmData.shmid, false);
		if (!shmData.data)
		{
			ft_printf("%s The host has not finished configuring the game, retry later.\n", INFO_PRINT);
			return (1);
		}
		register_new_player(shmData.data, shmData.semid);
		while(42)
		{
			sem_wait(shmData.semid);
			if (shmData.data->gameStarted)
			{
				ft_printf("%s Game started, you can now play!\n", INFO_PRINT);
				break;
			}
			if (shmData.data->isFinish)
			{
				ft_printf("%s The host has ended the game, exiting...\n", INFO_PRINT);
				return (0);
			}

			sem_signal(shmData.semid);
			usleep(100000); // sleep 100ms to avoid busy waiting
		}
		//sem_wait(shmData.semid);
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
		game_process(&shmData, shmData.semid, teamId);
	}
	// il faut clean uniquement l'host
}
