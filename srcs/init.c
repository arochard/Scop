#include "../includes/scop.h"

static int		get_key(int keycode, void *param)
{
	if (keycode == ESCAPE)
		exit(0);

	param = param + 3;

	return (0);
}

static int		expose_hook(t_data *data)
{
	loading_buffer(data);
	draw(data);
	return (0);
}

void			init_window(t_data *data)
{
	int			context;

	data->ptr_mlx = mlx_init();
	data->ptr_win = mlx_new_opengl_window(data->ptr_mlx, 1920, 1080, "OpenGl Test");
	context = mlx_opengl_window_set_context(data->ptr_win);
	loading_buffer(data);
	mlx_key_hook(data->ptr_win, get_key, NULL);
	mlx_expose_hook(data->ptr_win, expose_hook, data);
	mlx_loop(data->ptr_mlx);
}