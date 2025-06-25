/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:25:15 by cpapot            #+#    #+#             */
/*   Updated: 2025/06/25 18:41:40 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ipc.h"
#include "../inc/shared_memory.h"
#include <signal.h>
#include <time.h>
# include "../inc/game_process.h"


// quand on start la game chaque joueur doit 1 par 1 prendre une case random sur le plateau qui n'est pas prise et adjacente
// quand tout le monde a pris une case on lance la game (cree algo pour jouer un coup selon la config du plateau)
// au debut du tour du joueur il verifie si il est mort ou pas (si oui il senleve du plateau et il quitte la game)

// avant chaque coup on sem_wait et a la fin du coup on sem_signal et on sleep (speed * nb de joueurs vivant)

t_shared_data_manager	*g_shmData;

// return 0 si personne 1 si quelqu un est adjacent 2 si deux joueurs d'une meme team qui n'est pas la sienne est adjacente
int		check_ajdacent(int teamID, int *board, int boardSize, t_player_position playerPosition)
{
	int	adjacentTeamCount[4] = {0, 0, 0, 0};

	for (int i = playerPosition.x - 1; i <= playerPosition.x + 1; i++)
	{
		for (int j = playerPosition.y - 1; j <= playerPosition.y + 1; j++)
		{
			if (i < 0 || i >= boardSize || j < 0 || j >= boardSize)
				continue;
			if (board[i * boardSize + j] != 0)
				adjacentTeamCount[board[i * boardSize + j] - 1]++;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if (adjacentTeamCount[i] > 0 && i + 1 != teamID)
		{
			if (adjacentTeamCount[i] >= 2)
				return 2;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if (adjacentTeamCount[i] >= 1)
			return 1;
	}
	return 0;
}

t_player_position	*set_random_player_position(int teamID, int *board, int boardSize, int semid, t_memlist **mem)
{
	t_player_position *playerPosition = (t_player_position *)stock_malloc(sizeof(t_player_position), mem);
	if (!playerPosition)
	{
		perror("malloc set_random_player_position");
		return NULL;
	}

	if (sem_wait(semid) == -1) {
		perror("sem_wait game_process");
		return NULL;
	}

	while (true)
	{
		srand(time(NULL));
		playerPosition->x = rand() % boardSize;
		playerPosition->y = rand() % boardSize;
		ft_printf("\033[7;49;92mINFO\033[0m : Player %d trying position (%d, %d)\n", teamID, playerPosition->x, playerPosition->y);
		if (board[playerPosition->x * boardSize + playerPosition->y] == 0)
		{
			if (check_ajdacent(teamID, board, boardSize, *playerPosition) == 0)
			{
				board[playerPosition->x * boardSize + playerPosition->y] = teamID;
				break;
			}
		}
	}
	if (sem_signal(semid) == -1) {
		perror("sem_signal game_process");
		return NULL;
	}

	return playerPosition;
}

int game_process(t_shared_data_manager *shmData, int team_id)
{
	g_shmData = shmData;
	t_memlist *localGameMem = NULL;
	ft_printf("\033[7;49;92mINFO\033[0m : Starting game process for team %d\n", team_id);

	shmData->actualPlayerPosition = set_random_player_position(team_id, shmData->data->board, shmData->data->boardSize, shmData->semid, &localGameMem);
	ft_printf("\033[7;49;92mINFO\033[0m : Player %d position set to (%d, %d)\n", \
		team_id, shmData->actualPlayerPosition->x, shmData->actualPlayerPosition->y);

	signal(SIGINT, handle_client_close);
	while (true)
	{

	}

	return 0;
}
