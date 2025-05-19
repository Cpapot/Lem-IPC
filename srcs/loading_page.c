/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_page.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:25:40 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/19 20:43:05 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/mlx_utils.h"
# include "../inc/ipc.h"
# include "../inc/lem-ipc.h"
# include "../inc/shared_memory.h"
# include <stdio.h>

// page d'attente des joueurs
// on affiche une page de loading avec un fond gris
// on affiche le nombre de joueurs connectés/joueurs max
// essayer de faire une animation de loading ('Waiting for players''Waiting for players.''Waiting for players..''Waiting for players...')

static void add_player_count(int playerCount, int maxPlayerCount, t_mlx_page *page)
{
	char buff[64];

	sprintf(buff, "%d/%d", playerCount, maxPlayerCount);
	mlx_write_text_to_image(buff, WIN_WIDTH / 2, WIN_HEIGHT / 2 + 50, 2, true, &page->img);
}

void loading_page(t_mlx_data *mlxData)
{
	ft_printf("%s Lauching loading page...\n", INFO_PRINT);
	mlx_init_page(mlxData, "loading");
	if (mlxData->pages == NULL)
	{
		ft_putstr_fd("Error: mlx_init_page failed\n", 2);
		return ;
	}
	set_image_color(&((t_mlx_page *)mlxData->pages->content)->img, rgb_to_int(209, 207, 207));
	mlx_write_text_to_image("Waiting for players", WIN_WIDTH / 2, WIN_HEIGHT / 2 - 100, 4, true, &((t_mlx_page *)mlxData->pages->content)->img);
	add_player_count(1, 2, (t_mlx_page *)mlxData->pages->content);
	img_mlx_put_image_to_window(mlxData, &((t_mlx_page *)mlxData->pages->content)->img);
	mlx_loop(mlxData->mlx);
}	// on doit faire en sorte d'unlock la semaphore apres avoir affcihé la page et s'attendre a etre lock autant de fois qu'il y a de joueurs - 1(l'host)
      // a chaque unlock on incremente le nombre de joueurs connectés

// quand tout le monde est co on change de page pour la page de jeu
// on place les joueurs sur le terrain
