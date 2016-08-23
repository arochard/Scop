#include "../includes/scop.h"


// void		loop()
// {
// 	int 	con;

// 	glClear();

// 	con = mlx_opengl_swap_buffers(ptr_win);
// }

void		get_key()
{

}

int			main()
{
	void	*ptr_init;
	void	*ptr_win;
	int 	context;

	ptr_init = mlx_init();
	ptr_win = mlx_new_opengl_window(ptr_init, 500, 500, "OpenGl Test");
	context = mlx_opengl_window_set_context(ptr_win);
	//mlx_key_hook(ptr_win, get_key);
	mlx_loop(ptr_init);
	
	return (0);
}