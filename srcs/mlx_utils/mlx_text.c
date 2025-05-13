/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_text.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:07:31 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/13 10:09:53 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mlx_utils.h"
#include "../inc/mlx_font.h"

static void centered_text(char *text, int *x, int *y, int text_length, int char_height, int char_width)
{
	int lineCount = 1;
	for (int i = 0; i < text_length; i++)
	{
		if (text[i] == '\n')
		{
			lineCount++;
			text_length--;
		}
	}
	int total_width = text_length * char_width;
	int total_height = char_height * lineCount;
	*x = (*x - total_width / 2);
	*y = (*y - total_height / 2);
}

int mlx_write_text_to_image(char *text, int x, int y, int text_size, bool centered,t_image_data *dest)
{
	if (text == NULL || dest == NULL || text_size <= 0)
		return 1;

	int char_width = 8 * text_size;
	int char_height = 8 * text_size;
	int text_length = ft_strlen(text);
	if (centered)
		centered_text(text, &x, &y, text_length, char_height, char_width);
	int current_x = x;

	for (int i = 0; i < text_length; i++) {
		char c = text[i];

		if (c == '\n') {
			current_x = x;
			y += char_height;
			continue;
		}

		for (int row = 0; row < 8; row++) {
			for (int col = 0; col < 8; col++) {
				if (font_8x8[(int)c - 32][row] & (1 << (8 - 1 - col))) {
					for (int zoom_y = 0; zoom_y < text_size; zoom_y++) {
						for (int zoom_x = 0; zoom_x < text_size; zoom_x++) {
							int draw_x = current_x + col * text_size + zoom_x;
							int draw_y = y + row * text_size + zoom_y;
							img_mlx_pixel_put(dest, draw_x, draw_y, 0x000000);
						}
					}
				}
			}
		}
		current_x += char_width;
	}
	return 0;
}
