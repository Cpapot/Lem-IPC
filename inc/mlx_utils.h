/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:11:53 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/13 16:45:28 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MLX_UTILS_H
#  define MLX_UTILS_H

# include "../mlx_lin/mlx.h"
# include "../libft/includes/libft.h"
# include <stdlib.h>

# define WIN_WIDTH 1080
# define WIN_HEIGHT 720
# define WIN_NAME "Lem-in IPC"

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

typedef struct	s_image_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_image_data;

typedef struct	s_mlx_slider {
	int				x;
	int				y;
	int				width;
	int				height;
	int				color;
	int				circleColor;

	int				minValue;
	int				maxValue;
	int				initialValue;
	int				step;
	int				*value;
	int				stepSize;
}		t_mlx_slider;

typedef struct s_mlx_button {
	char			*name; // si [0] == 0 -> pas de nom
	int				x;
	int				y;
	int				width;
	int				height;
	int				color;
	int				pressedColor;
	int				(*funct_ptr)();
	void			*param;
	t_image_data	*pressedButtonImg;
}	t_mlx_button;

typedef struct s_mlx_data {
	void			*mlx;
	void			*win;
	void			*ipc;
	t_memlist		*mlxMemList;	// stocke les stuct page et list page
	t_list			*pages;
}			t_mlx_data;

typedef struct s_mlx_page {
	int				color;
	t_mlx_data		*mlxData;
	t_list			*buttonsLst;
	t_list			*sliderLst;
	t_memlist		*memlist; // stocke uniquement les données de la page on peut le clean avec l'image quand on a plus besoin de la page
	t_image_data	img;
}	t_mlx_page;

int				mlx_button_hook(int button, int x, int y, t_mlx_page *page);
int				mlx_init_page(t_mlx_data *mlxData);
void			img_mlx_pixel_put(t_image_data *data, int x, int y, int color);
void			img_mlx_init(t_mlx_page *pageData, void *mlx);
t_mlx_data		*mlx_init_window(void);
void			img_mlx_put_image_to_window(t_mlx_data *mlxData, t_image_data *imgData);
int				rgb_to_int(int r, int g, int b);
int				mlx_free(t_mlx_data *mlxData);
void			mlx_hooks_init(t_mlx_data *mlxData);
int				mlx_render_all_button(t_mlx_page *page, t_mlx_data *mlxData);
bool			mlx_create_button(t_mlx_page *mlxPage, unsigned int btData[6], char *name, int (*funct_ptr)(), void *param);
int				check_hover_button(int x, int y, t_mlx_data *mlxData);
int				mlx_write_text_to_image(char *text, int x, int y, int text_size, bool centered,t_image_data *dest);
t_image_data	*mlx_clone_image(t_memlist **memlist, void *mlx, t_image_data *src);
void			set_image_color(t_image_data *img, int color);
int				mlx_create_slider(t_mlx_page *mlxPage, unsigned int sliderData[10], int *value);
int				mlx_render_all_slider(t_mlx_page *page, t_mlx_data *mlxData);
int				mlx_slider_hook(int button, int x, int y, t_mlx_page *page);
void			render_page(t_mlx_page *pageData, t_mlx_data *mlxData);


#endif
