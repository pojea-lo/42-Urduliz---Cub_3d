/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith < jsmith@student.42urduliz.com >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 21:31:30 by jsmith            #+#    #+#             */
/*   Updated: 2022/10/02 21:55:44 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

    
    	hk->gr->mlx_win = mlx_new_window(hk->gr->mlx, WIN_WIDTH, WIN_HEIGHT + 100,"Cub3d");
    
    hk->gr->hud = mlx_xpm_file_to_image(hk->gr->mlx,"./pics/hud.xpm",&res2,&res);
	mlx_put_image_to_window(hk->gr->mlx,hk->gr->mlx_win,hk->gr->hud,0,WIN_HEIGHT);
	hk->gr->gun = mlx_xpm_file_to_image(hk->gr->mlx,"./pics/gun.xpm",&res3,&res3);
	hk->gr->fired = mlx_xpm_file_to_image(hk->gr->mlx,"./pics/fire_gun.xpm",&res3,&res3);
	hk->gr->bullet = mlx_xpm_file_to_image(hk->gr->mlx,"./pics/bullet.xpm",&res3,&res3);
	hk->gr->face = mlx_xpm_file_to_image(hk->gr->mlx,"./pics/face.xpm",&res3,&res3);
	//FIN INHABILITAR EL HUD
	mlx_put_image_to_window(hk->gr->mlx,hk->gr->mlx_win,hk->gr->bullet,WIN_WIDTH - 60,WIN_HEIGHT +18);
	mlx_put_image_to_window(hk->gr->mlx,hk->gr->mlx_win,hk->gr->bullet,WIN_WIDTH - 100,WIN_HEIGHT +18);
	mlx_put_image_to_window(hk->gr->mlx,hk->gr->mlx_win,hk->gr->bullet,WIN_WIDTH - 140,WIN_HEIGHT +18);
	mlx_put_image_to_window(hk->gr->mlx,hk->gr->mlx_win,hk->gr->bullet,WIN_WIDTH - 180,WIN_HEIGHT +18);
	mlx_put_image_to_window(hk->gr->mlx,hk->gr->mlx_win,hk->gr->bullet,WIN_WIDTH - 220,WIN_HEIGHT +18);
	mlx_put_image_to_window(hk->gr->mlx,hk->gr->mlx_win,hk->gr->bullet,WIN_WIDTH - 260,WIN_HEIGHT +18);
	mlx_put_image_to_window(hk->gr->mlx,hk->gr->mlx_win,hk->gr->bullet,WIN_WIDTH - 300,WIN_HEIGHT +18);
	mlx_put_image_to_window(hk->gr->mlx,hk->gr->mlx_win,hk->gr->bullet,WIN_WIDTH - 340,WIN_HEIGHT +18);
	mlx_put_image_to_window(hk->gr->mlx,hk->gr->mlx_win,hk->gr->bullet,WIN_WIDTH - 380,WIN_HEIGHT +18);
	mlx_put_image_to_window(hk->gr->mlx,hk->gr->mlx_win,hk->gr->face,WIN_WIDTH / 2,WIN_HEIGHT +18);


	//mlx_put_image_to_window(hk->gr->mlx, hk->gr->mlx_win, hk->gr->gun, 438, 400);

		//mlx_hook(hk->gr->mlx_win, 4,(1L << 2), &click, hk);
		int click(int key, int x , int y, t_hook *hk)
{
	(void)x;
	(void)y;
	(void)key;
	(void)hk;
	mlx_put_image_to_window(hk->gr->mlx,hk->gr->mlx_win,hk->gr->fired,438,380);
	return (1);
}

//	manage_movements(hk);//	mlx_hook(hk->gr->mlx_win, 6, (1L << 0), mouse, hk);
//	mlx_mouse_hook(hk->gr->mlx_win,mouse, hk);

int mouse(int x, int y,t_hook *hk)
{
	//double mouse;
	//int y = 0;
	//int x = 0;
	//int x_x;
	//int y_y;
	(void)y;
	double whereis;
	whereis = x - (WIN_WIDTH / 2);
	double mouse;
	mouse  = mlx_mouse_get_pos(hk->gr->mlx_win,&x, &y);
	(void) mouse;
	double old_rot = hk->dt->rotspeed;
	hk->dt->rotspeed = 0.0005;
	if (whereis < 0)
	{
		hk->dt->rotation_left = true;
		hk->dt->rotation_right = false;
	}
	if (whereis > 0)
	{
		hk->dt->rotation_right = true;
		hk->dt->rotation_left = false;
	}
	if (whereis == 0)
	{
		hk->dt->rotation_left = false;
		hk->dt->rotation_right = false;
	}
	mlx_mouse_move(hk->gr->mlx_win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	hk->dt->rotspeed = old_rot;
	return (1);
}

int	mouse(int x, int y, t_hook *hk)
{
	double	whereis;

	whereis = x - (WIN_WIDTH / 2);
	mlx_mouse_get_pos(hk->gr->mlx_win, &x, &y);
	(void)y;
	if (whereis < 0)
	{
		hk->dt->rotation_left = true;
		hk->dt->rotation_right = false;
	}
	if (whereis > 0)
	{
		hk->dt->rotation_right = true;
		hk->dt->rotation_left = false;
	}
	if (whereis == 0)
	{
		hk->dt->rotation_left = false;
		hk->dt->rotation_right = false;
	}
	mlx_mouse_move(hk->gr->mlx_win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	return (1);
}