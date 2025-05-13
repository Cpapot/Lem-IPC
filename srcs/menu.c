/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:41:43 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/13 19:29:00 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/mlx_utils.h"
# include "../inc/ipc.h"
# include "../inc/lem-ipc.h"

int test_button8(void *param)
{
	(void)param;
	ft_printf("Button 1 pressed\n");
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

void launch_menu(t_ipc *ipc)
{
	ft_printf("%s Launching menu...\n", INFO_PRINT);
	t_mlx_data		*mlxData = mlx_init_window();

	if (!mlxData)
		perror("mlx_init_window"), ipc_clean(ipc);

	mlxData->ipc = ipc;
	if (mlx_init_page(mlxData))
		perror("mlx_init_page"), mlx_free(mlxData);

	((t_mlx_page *)mlxData->pages->content)->color = rgb_to_int(220, 220, 220);

	int size = 0;
	int player = 0;
	int speed = 0;
	mlx_create_slider(mlxData->pages->content, (unsigned int[10]){100, 450, 300, 10, 0xA6A6A6, 0x6B6B6B, 4, 100, 20, 1}, &size, "Arena Size:");
	mlx_create_slider(mlxData->pages->content, (unsigned int[10]){100, 300, 300, 10, 0xA6A6A6, 0x6B6B6B, 2, 16, 4, 1}, &player, "Player Count:");
	mlx_create_slider(mlxData->pages->content, (unsigned int[10]){100, 600, 300, 10, 0xA6A6A6, 0x6B6B6B, 1, 5, 3, 1}, &speed, "Speed:");
	mlx_create_button(mlxData->pages->content, (unsigned int[6]){100, 100, 300, 50, 0xA6A6A6, rgb_to_int(77, 255, 136)}, "START", test_button8, NULL);


	render_page(mlxData->pages->content, mlxData);
	mlx_hooks_init(mlxData);
	mlx_loop(mlxData->mlx);
}

