/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_page.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:41:43 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/19 20:30:30 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/mlx_utils.h"
# include "../inc/ipc.h"
# include "../inc/lem-ipc.h"
# include "../inc/shared_memory.h"

void loading_page(t_mlx_data *mlxData);

int start_button(void *param)
{
	t_mlx_data *data = (t_mlx_data *)param;
	t_mlx_page *page = mlx_get_page(data, "menu");
	int *values = mlx_get_all_slider_value(page);
	if (!values) {
		perror("mlx_get_all_slider_value"); mlx_free(data);
	}

	ft_printf("%s Start button pressed\n%s Arena Size: %d\n%s Player Count: %d\n%s Speed: %d\n" \
		, INFO_PRINT, INFO_PRINT, values[0], INFO_PRINT, values[1], INFO_PRINT, values[2]);

	data->shmData->data = create_or_get_shared_memory(&data->shmData->shmid, true);
	if (!data->shmData->data) {
		perror("create_or_get_shared_memory"); mlx_free(data);
	}
	ft_printf("%s Shared memory created at: %p\n", DEBUG_PRINT, data->shmData->data);
	if (write_game_rules(data->shmData->data, data->shmData->semid, values[1], values[0], values[2], &data->mlxMemList)) {
		perror("write_game_rules"); mlx_free(data);
	}
	mlx_free_page(data, page);
	ft_printf("%s Waiting for players to connect...\n", INFO_PRINT);
	loading_page(data);
	return (0);
}

void render_preview_board(int *size, t_mlx_data *mlxData)
{
	int width = 550, y = 100, x = 475, lineGap = width / *size;
	while (lineGap * *size >= width)
		lineGap--;
	for (int i = x; i < width + x; i++)
	{
		for (int j = y; j < width + y; j++)
		{
			if (((i - x) % lineGap == 0 ||(j - y) % lineGap == 0 ) && lineGap * *size >= (j - y) && lineGap * *size >= (i - x))
				img_mlx_pixel_put(&((t_mlx_page *)mlxData->pages->content)->img, i, j, rgb_to_int(0, 0, 0));
		}
	}
}

void render_menu(void *pageData, t_mlx_data *mlxData)
{
	t_mlx_page *page = (t_mlx_page *)pageData;
	set_image_color(&((t_mlx_page *)mlxData->pages->content)->img, page->color);
	render_preview_board(((t_mlx_slider *)((t_mlx_page *)mlxData->pages->content)->sliderLst->content)->value, mlxData);
	if (mlx_render_all_slider(pageData, mlxData))
		perror("mlx_render_all_slider"), mlx_free(mlxData);
	if (mlx_render_all_button(pageData, mlxData))
		perror("mlx_render_all_button"), mlx_free(mlxData);
	img_mlx_put_image_to_window(mlxData, &page->img);
}


void launch_menu(t_shared_data_manager *shmData)
{
	ft_printf("%s Launching menu...\n", INFO_PRINT);
	t_mlx_data		*mlxData = mlx_init_window();

	mlxData->shmData = shmData;
	if (mlx_init_page(mlxData, "menu"))
		perror("mlx_init_page"), mlx_free(mlxData);

	((t_mlx_page *)mlxData->pages->content)->color = rgb_to_int(220, 220, 220);

	int size = 0;
	int player = 0;
	int speed = 0;
	mlx_create_slider(mlxData->pages->content, (unsigned int[10]){100, 450, 300, 10, 0xA6A6A6, 0x6B6B6B, 4, 100, 20, 1}, &size, "Arena Size:");
	mlx_create_slider(mlxData->pages->content, (unsigned int[10]){100, 300, 300, 10, 0xA6A6A6, 0x6B6B6B, 2, 16, 4, 1}, &player, "Player Count:");
	mlx_create_slider(mlxData->pages->content, (unsigned int[10]){100, 600, 300, 10, 0xA6A6A6, 0x6B6B6B, 1, 5, 3, 1}, &speed, "Speed:");
	mlx_create_button(mlxData->pages->content, (unsigned int[6]){100, 100, 300, 50, 0xA6A6A6, rgb_to_int(77, 255, 136)}, "START", start_button, mlxData);
	((t_mlx_page *)mlxData->pages->content)->render = render_menu;
	((t_mlx_page *)mlxData->pages->content)->render(((t_mlx_page *)mlxData->pages->content), mlxData);
	mlx_hooks_init(mlxData);
	mlx_loop(mlxData->mlx);
}

