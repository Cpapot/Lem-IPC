/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_text.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:07:31 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/13 09:16:30 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mlx_utils.h"
#include "../inc/mlx_font.h"

int mlx_write_text_to_image(char *text, int x, int y, int text_size, t_image_data *dest)
{
	if (text == NULL || dest == NULL || text_size <= 0)
		return 1;

	int color = 0x000000; // Couleur blanche comme demandé
	int base_width = 8;  // Largeur de base d'un caractère
	int base_height = 8; // Hauteur de base d'un caractère
	int char_width = base_width * text_size;
	int char_height = base_height * text_size;
	int text_length = ft_strlen(text);
	int current_x = x;
	int current_y = y;

	for (int i = 0; i < text_length; i++) {
		char c = text[i];

		if (c == '\n') {
			current_x = x;
			current_y += char_height;
			continue;
		}

		for (int row = 0; row < base_height; row++) {
			for (int col = 0; col < base_width; col++) {
				if (font_8x8[(int)c - 32][row] & (1 << (base_width - 1 - col))) {
					for (int zoom_y = 0; zoom_y < text_size; zoom_y++) {
						for (int zoom_x = 0; zoom_x < text_size; zoom_x++) {
							int draw_x = current_x + col * text_size + zoom_x;
							int draw_y = current_y + row * text_size + zoom_y;
							img_mlx_pixel_put(dest, draw_x, draw_y, color);
						}
					}
				}
			}
		}
		current_x += char_width;
	}
	return 0;
}
