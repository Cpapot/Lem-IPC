/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_page.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:25:40 by cpapot            #+#    #+#             */
/*   Updated: 2025/06/25 17:46:22 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/mlx_utils.h"
# include "../inc/ipc.h"
# include "../inc/lem-ipc.h"
# include "../inc/shared_memory.h"
# include <stdio.h>
# include <string.h>

void launch_game_page(t_mlx_data *mlxData);

//NOT CLEAN MALLOC UNSECURE

// page d'attente des joueurs
// on affiche une page de loading avec un fond gris
// on affiche le nombre de joueurs connectés/joueurs max
// essayer de faire une animation de loading ('Waiting for players''Waiting for players.''Waiting for players..''Waiting for players...')


static void		add_player_count(int playerCount, int maxPlayerCount, t_mlx_page *page)
{
	char buff[64];

	sprintf(buff, "%d/%d", playerCount, maxPlayerCount);
	mlx_write_text_to_image(buff, WIN_WIDTH / 2, WIN_HEIGHT / 2 + 50, 2, true, &page->img);
}

// //NOT CLEAN MALLOC UNSECURE
// void update_loading_text(t_mlx_page *page, int dots)
// {
// 	char loading_text[30];
// 	int i;

// 	strcpy(loading_text, "Waiting for players");
// 	i = strlen(loading_text);

// 	for (int j = 0; j < dots; j++)
// 		loading_text[i++] = '.';
// 	loading_text[i] = '\0';

// 	set_image_color(&page->img, rgb_to_int(209, 207, 207));
// 	mlx_write_text_to_image(loading_text, WIN_WIDTH / 2, WIN_HEIGHT / 2 - 100, 4, true, &page->img);
// }

void render_loading_page(void *pageData, t_mlx_data *mlxData)
{
	t_mlx_page *page = (t_mlx_page *)pageData;

	int connected = check_connected_players(mlxData->shmData->data, mlxData->shmData->semid);
	if (connected == -1) {
		ft_putstr_fd("Error: check_connected_players failed\n", 2);
		return;
	}

	set_image_color(&page->img, rgb_to_int(209, 207, 207));
	mlx_write_text_to_image("Waiting for players", WIN_WIDTH / 2, WIN_HEIGHT / 2 - 100, 4, true, &page->img);
	add_player_count(connected, mlxData->shmData->data->playerCount, page);
	img_mlx_put_image_to_window(mlxData, &page->img);
}

static int check_players_loop(void *param)
{
    t_rerender_data *load_data = (t_rerender_data *)param;
    long current_time = get_current_time_ms();

    // Vérifier si une seconde s'est écoulée depuis le dernier rafraîchissement
    if (current_time - load_data->last_update >= 1000) {
		t_mlx_data *mlx_data = load_data->mlx_data;
		t_mlx_page *page = (t_mlx_page *)mlx_data->pages->content;
		t_shared_data *shared_data = mlx_data->shmData->data;
		int semid = mlx_data->shmData->semid;

        // Vérifier si de nouveaux joueurs se sont connectés
        int connected = check_connected_players(shared_data, semid);
        if (connected == -1) {
            ft_printf("%s Error checking connected players\n", ERROR_PRINT);
            return (0);
        }

        // Si un nouveau joueur s'est connecté
        if (connected > load_data->previous_count) {
            ft_printf("%s New player connected! (%d/%d)\n",
                INFO_PRINT, connected, shared_data->playerCount);
            load_data->previous_count = connected;
        }

		render_loading_page(page, mlx_data);

		if (connected >= shared_data->playerCount) {
			ft_printf("%s All players connected! Starting game...\n", INFO_PRINT);
			shared_data->gameStarted = true;
			mlx_loop_hook(mlx_data->mlx, NULL, NULL);
			mlx_free_page(mlx_data, page);
			launch_game_page(mlx_data);
			return (1);
		}

		load_data->last_update = current_time;
    }

    return (0);
}

void loading_page(t_mlx_data *mlxData)
{
    ft_printf("%s Launching loading page...\n", INFO_PRINT);
    mlx_init_page(mlxData, "loading");
    if (mlxData->pages == NULL) {
        ft_putstr_fd("Error: mlx_init_page failed\n", 2);
        return;
    }

    render_loading_page(mlxData->pages->content, mlxData);

    // Configurer la structure de données pour la boucle de vérification
    t_rerender_data *load_data = stock_malloc(sizeof(t_rerender_data), &((t_mlx_page *)mlxData->pages->content)->memlist);
    if (!load_data) {
        ft_putstr_fd("Error: malloc failed\n", 2);
        return;
    }
    load_data->mlx_data = mlxData;
    load_data->previous_count = 1;
    load_data->last_update = get_current_time_ms();

    // Enregistrer la fonction de vérification périodique
    mlx_loop_hook(mlxData->mlx, check_players_loop, load_data);

    // Démarrer la boucle
    mlx_loop(mlxData->mlx);

    // Libérer la mémoire (ceci ne sera exécuté qu'après avoir quitté la boucle)
    free(load_data);
}	// on doit faire en sorte d'unlock la semaphore apres avoir affcihé la page et s'attendre a etre lock autant de fois qu'il y a de joueurs - 1(l'host)
      // a chaque unlock on incremente le nombre de joueurs connectés

// quand tout le monde est co on change de page pour la page de jeu
// on place les joueurs sur le terrain
