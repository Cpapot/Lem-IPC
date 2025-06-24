/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_memory_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:34:40 by cpapot            #+#    #+#             */
/*   Updated: 2025/06/24 19:35:12 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shared_memory.h"
// !!!! NOTHING CLEAN IF ERROR FOR NOW (memory not freed)

int		sem_wait(int semid)
{
	struct sembuf op = {0, -1, 0};
	return semop(semid, &op, 1);
}

int		sem_signal(int semid)
{
	struct sembuf op = {0, 1, 0};
	return semop(semid, &op, 1);
}

t_shared_data	*create_or_get_shared_memory(int *shmid, bool create)
{
	if (create)
	{
		*shmid = shmget(SHM_KEY, sizeof(t_shared_data), IPC_CREAT | 0666);
		if (*shmid == -1 && errno != EEXIST) {
			perror("shmget"); return NULL;
		}
	}
	else
	{
		*shmid = shmget(SHM_KEY, sizeof(t_shared_data), 0666);
		if (*shmid == -1) {
			return NULL;
		}
	}

	t_shared_data *data = (t_shared_data *)shmat(*shmid, NULL, 0);
	if (data == (t_shared_data *)-1) {
		perror("shmat"); return NULL;
	}
	return data;
}

void		clean_shared_memory(int shmid, t_shared_data *data, bool isHost)
{
	shmdt(data);
	if (isHost) {
		shmctl(shmid, IPC_RMID, NULL);
	}
}

//changer ca en creant un tableau plat (boardSize * boardSize) et en le stockant dans la memoire partagée
int		write_game_rules(t_shared_data *data, int semid, int playerCount, int boardSize, int speed, t_memlist **mem)
{
	data->gameStarted = false;
	data->isFinish = false;
	data->boardSize = boardSize;
	data->playerCount = playerCount;
	data->connectedPlayers = 1;
	data->speed = speed;

	data->board = (int **)stock_malloc(sizeof(int *) * boardSize + 1, mem);
	printf("board: %p\n", data->board);
	if (!data->board) {
		sem_signal(semid);
		return (1);
	}
	for (int i = 0; i < boardSize; i++)
	{
		data->board[i] = (int *)stock_malloc(sizeof(int) * boardSize + 1, mem);
		if (!data->board[i]) {
			sem_signal(semid); return (1);
		}
		for (int j = 0; j < boardSize; j++)
			data->board[i][j] = 0;
	}

	if (sem_signal(semid) == -1) {
		perror("sem_signal");
		return -1;
	}

	return 0;
}

int check_connected_players(t_shared_data *data, int semid)
{
	int connected;

	if (sem_wait(semid) == -1) {
		perror("sem_wait check_connected_players");
		return -1;
	}

	connected = data->connectedPlayers;

	if (sem_signal(semid) == -1) {
		perror("sem_signal");
		return -1;
	}

	return connected;
}

int register_new_player(t_shared_data *data, int semid)
{
	int player_id;

	if (sem_wait(semid) == -1) {
		perror("sem_wait");
		return -1;
	}

	data->connectedPlayers += 1;
	player_id = data->connectedPlayers;

	if (sem_signal(semid) == -1) {
		perror("sem_signal");
		return -1;
	}
	ft_printf("\033[7;49;92mINFO\033[0m : Player %d registered\n", player_id);

	return player_id;
}

int create_or_join_semaphore(int initial_value, bool *is_creator)
{
	int semid = semget(SEM_KEY, 1, IPC_CREAT | IPC_EXCL | 0666);
	if (semid >= 0) {
		union semun arg;
		arg.val = initial_value;
		if (semctl(semid, 0, SETVAL, arg) == -1) {
			perror("semctl (SETVAL)"); return -1;
		}
		*is_creator = 1;
	} else if (errno == EEXIST) {
		// Déjà existant → rejoindre
		semid = semget(SEM_KEY, 1, 0666);
		if (semid == -1) {
			perror("semget (join)"); return -1;
		}
		*is_creator = 0;
	} else {
		perror("semget"); return -1;
	}
	return semid;
}

void	remove_semaphore(int semid, int is_host)
{
	if (!is_host)
		return;

	if (semctl(semid, 0, IPC_RMID) == -1) {
		perror("semctl (IPC_RMID)");
	}
	ft_printf("\033[7;49;96mDEBUG\033[0m : Semaphore removed\n");
}
