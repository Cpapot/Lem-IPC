/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_page.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:03:24 by cpapot            #+#    #+#             */
/*   Updated: 2025/06/25 18:44:58 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/mlx_utils.h"
# include "../inc/ipc.h"
# include "../inc/lem-ipc.h"
# include "../inc/shared_memory.h"
# include "../inc/game_process.h"

void render_game_board(int *board, int boardSize, t_mlx_data *mlxData)
{
	int width = 600, y = 75, x = 200, lineGap = width / boardSize, boardIndex = 0;
	while (lineGap * boardSize >= width)
		lineGap--;
	for (int i = x; i < width + x; i++)
	{
		for (int j = y; j < width + y; j++)
		{
			boardIndex = ((i - x) / lineGap) + ((j - y) / lineGap) * boardSize;
			switch (board[boardIndex])
			{
				case 0:
					break;
				case 1:
					img_mlx_pixel_put(&((t_mlx_page *)mlxData->pages->content)->img, i, j, rgb_to_int(255, 0, 0));
					break;
				case 2:
					img_mlx_pixel_put(&((t_mlx_page *)mlxData->pages->content)->img, i, j, rgb_to_int(0, 255, 0));
					break;
				case 3:
					img_mlx_pixel_put(&((t_mlx_page *)mlxData->pages->content)->img, i, j, rgb_to_int(0, 0, 255));
					break;
				case 4:
					img_mlx_pixel_put(&((t_mlx_page *)mlxData->pages->content)->img, i, j, rgb_to_int(255, 255, 0));
					break;
			}
			if (((i - x) % lineGap == 0 ||(j - y) % lineGap == 0 ) && lineGap * boardSize >= (j - y) && lineGap * boardSize >= (i - x))
				img_mlx_pixel_put(&((t_mlx_page *)mlxData->pages->content)->img, i, j, rgb_to_int(0, 0, 0));
		}
	}
}

void render_game(void *pageData, t_mlx_data *mlxData)
{
	t_mlx_page *page = (t_mlx_page *)pageData;
	set_image_color(&((t_mlx_page *)mlxData->pages->content)->img, page->color);
	render_game_board(mlxData->shmData->data->board, mlxData->shmData->data->boardSize, mlxData);
	if (mlx_render_all_slider(pageData, mlxData))
		perror("mlx_render_all_slider"), mlx_free(mlxData);
	if (mlx_render_all_button(pageData, mlxData))
		perror("mlx_render_all_button"), mlx_free(mlxData);
	img_mlx_put_image_to_window(mlxData, &page->img);
}

static int	rerender_game(void *param)
{
	t_rerender_data *load_data = (t_rerender_data *)param;
	long current_time = get_current_time_ms();

	if (current_time - load_data->last_update >= 100) {
		t_mlx_data *mlxData = load_data->mlx_data;
		t_mlx_page *page = (t_mlx_page *)mlxData->pages->content;
		if (mlxData->shmData->data->isFinish)
		{
			ft_printf("%s Game finished!\n", INFO_PRINT);
			mlx_free(mlxData);
			exit(0);
		}

		render_game(page, mlxData);
		load_data->last_update = current_time;
	}

	return (0);
}

void launch_game_page(t_mlx_data *mlxData)
{
	ft_printf("%s Launching game page...\n", INFO_PRINT);

	if (mlx_init_page(mlxData, "game"))
		perror("mlx_init_page"), mlx_free(mlxData);

	((t_mlx_page *)mlxData->pages->content)->color = rgb_to_int(220, 220, 220);

	render_game(mlxData->pages->content, mlxData);

	t_rerender_data *load_data = stock_malloc(sizeof(t_rerender_data), &((t_mlx_page *)mlxData->pages->content)->memlist);
	load_data->mlx_data = mlxData;
	load_data->previous_count = 1;
	load_data->last_update = get_current_time_ms();

	mlxData->shmData->localeGameData = NULL;
	mlxData->shmData->actualPlayerPosition = set_random_player_position(mlxData->shmData->hostTeamId, mlxData->shmData->data->board, mlxData->shmData->data->boardSize, mlxData->shmData->semid, &mlxData->shmData->localeGameData);

	mlx_loop_hook(mlxData->mlx, rerender_game, load_data);

	mlx_loop(mlxData->mlx);
}
