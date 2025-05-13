/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:41:43 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/13 17:32:48 by cpapot           ###   ########.fr       */
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

void launch_menu(t_ipc *ipc)
{
	ft_printf("%s Launching menu...\n", INFO_PRINT);
	t_mlx_data		*mlxData = mlx_init_window();

	if (!mlxData)
		perror("mlx_init_window"), ipc_clean(ipc);

	mlxData->ipc = ipc;
	if (mlx_init_page(mlxData))
		perror("mlx_init_page"), mlx_free(mlxData);

	((t_mlx_page *)mlxData->pages->content)->color = rgb_to_int(0, 0, 207);

	int sliderValue = 0;
	mlx_create_slider(mlxData->pages->content, (unsigned int[10]){100, 600, 300, 10, 0xA6A6A6, 0x6B6B6B, 0, 100, 20, 10}, &sliderValue);
	mlx_create_button(mlxData->pages->content, (unsigned int[6]){0, 0, 200, 50, 0xA6A6A6, 0x6B6B6B}, "START", test_button8, NULL);

	render_page(mlxData->pages->content, mlxData);
	mlx_hooks_init(mlxData);
	mlx_loop(mlxData->mlx);
}

