/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:06:58 by cpapot            #+#    #+#             */
/*   Updated: 2025/06/25 18:42:35 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shared_memory.h"
#include "../inc/lem-ipc.h"
#include "../inc/game_process.h"

void	handle_client_close(int sig)
{
	(void)sig;
	if (sem_wait(g_shmData->semid) == -1) {
		perror("sem_wait handle_client_close");
		return;
	}
	//lock la memoire partagée
	g_shmData->data->connectedPlayers -= 1;
	if (g_shmData->data->connectedPlayers == 1)
	{
		ft_printf("%s Last player disconnected, cleaning up shared memory and IPC resources.\n", INFO_PRINT);
			// si le nombre de joueurs connectés est 0
	// 	// on supprime la mémoire partagée
	// 	// on supprime le sémaphore
	// 	// on supprime la queue de message
	// 	// on quitte le programme
	}
	else
	{
		g_shmData->data->board[g_shmData->actualPlayerPosition->x * g_shmData->data->boardSize + g_shmData->actualPlayerPosition->y] = 0;
		ft_printf("%s Player disconnected, remaining players: %d\n", INFO_PRINT, g_shmData->data->connectedPlayers);
		if (sem_signal(g_shmData->semid) == -1) {
			perror("sem_signal handle_client_close");
			return;
		}
		//clean la memoire locale
		//stock_free(&g_shmData->localeGameData);
		exit(0);
	}


	// unclock la memoire partagée
}
