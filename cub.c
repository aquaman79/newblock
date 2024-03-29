/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquamar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 09:53:54 by aquamar           #+#    #+#             */
/*   Updated: 2021/03/30 09:53:57 by aquamar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <mlx.h>
#include <math.h>
#include <stdlib.h>

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void drawcube(struct mywin win, int x, int y, int color)
{
    int max_x;
    int max_y;

    max_x = x + tailx;
    max_y = y + taily;

    while (x < (max_x))
    {

        y = max_y - taily;
        while (y < (max_y))
        {
            my_mlx_pixel_put(&win.img, x, y, color);
            y++;
        }
        x++;
    }
}
/*void drawline(struct mywin *new,int x0, int y0, int x1, int y1)
{
    int dx, dy, p, x, y;
 
	dx=x1-x0;
	dy=y1-y0;
 
	x=x0;
	y=y0;
 
	p=2*dy-dx;
 
	while(x<x1 || y <y1)
	{
		if(p>=0)
		{
			my_mlx_pixel_put(&new->img,x,y,1783434);
			y=y+1;
			p=p+2*dy-2*dx;
		}
		else
		{
			my_mlx_pixel_put(&new->img,x,y,1783434);
			p=p+2*dy;
		}
		x=x+1;
	}
}*/
void dda(int x1, int y1, int x2, int y2, t_data *img)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    float xinc, yinx;
    int steps;
    int i = 0;

    if (abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);

    xinc = dx / (float)steps;
    yinx = dy / (float)steps;

    float x = x1;
    float y = y1;
    while (i <= steps)
    {
        my_mlx_pixel_put(img, round(x), round(y), 0x000000FF);
        x += xinc;
        y += yinx;
        i++;
    }
}
void draw_line(int a, int b, float rotation, int d, t_data *img)
{
    int i;
    int c;

    c = 1703425;
    i = 0;
    if (d == 0)
        d = 50;
    while (i <= d)
    {
        a = (px) + cos(rotation) * i;
        b = (py) + sin(rotation) * i;
        my_mlx_pixel_put(img, a, b, c);
        i++;
    }

    a = (px) + cos(rotation) * 55;
    b = (py) + sin(rotation) * 55;
    my_mlx_pixel_put(img, a, b, c + 210);

}

void draw_circle(struct mywin *new, int px, int py, int d)
{

    int r = d / 2;
    //int m = r;
    int t = 0; //degree from 0 to 360
    int x = (px + (r * cos(t * M_PI / 180)));
    int y = (py + (r * sin(t * M_PI / 180)));

    int ox = px, oy = py; // origin

    for (int x = -r; x < r; x++)
    {
        int height = (int)sqrt(r * r - x * x);

        for (int y = -height; y < height; y++)
            my_mlx_pixel_put(&new->img, x + ox, y + oy, 0x0FF0000);
    }
}
void draw_all_line(struct mywin *new,int px , int py)
{
    float rayangle = rotation -(FOV/2);
    int i = 0 ; 
    int l=50;
    while (i < tailx)
    {
        rayangle =rayangle+FOV/tailx;
        draw_line(px, py,rayangle, l, &new->img);
        i++;
    }
}
void draw_the_player(struct mywin *new, int px, int py)
{
    int d = 20;
    int l = 50;
    draw_circle(new, px, py, d);
    float angle = 90 * M_PI / 180;
    //dda(px, py, px + cos(angle) * l, py + sin(angle) * l, &new->img);

    /// the wrong lin!e
    //  draw_line(px, py, angle, l, &new->img);

    //// the right line
    draw_line(px, py,rotation, l, &new->img);
    draw_all_line(new,px,py);
    //rotation=M_PI/2;
  //  draw_line(px, py, 180 * M_PI / 180, l, &new->img);
}

void reykey_hook(struct mywin *new)
{
    new->play.hori = 0;
    new->play.hori = 0;
    new->play.ver = 0;
    new->play.ver = 0;
    new->play.angle=0;
   //rotation = M_PI/2;
}

int key_hook(int keycode, struct mywin *new)
{

    if (keycode == left)
        new->play.ver = -1;
    else if (keycode == right)
        new->play.ver = +1;
    else
        new->play.ver = 0;

    if (keycode == up)
        new->play.hori = -1;
    else if (keycode == down)
        new->play.hori = +1;
    else
        new->play.hori = 0;
    if(keycode== rotr)
        new->play.angle=1;
    if(keycode ==rotl)
        new->play.angle=-1;
    //new->play.rotation=M_PI/2;
   // printf("Hello from key_hook!\n");
    //printf("%d \n",new->play.ver);
   //printf("cou %d cou \n", keycode);
    return 0;
}

void draw(struct mywin *new)
{
    int i;
    int j;
    j = 0;
    while (j < 15)
    {
        i = 0;
        while (i < 25)
        {
            if (new->map[j][i] == 1)
                drawcube(*new, i * tailx, j * taily, 255255240);
            i++;
        }
        j++;
    }
}

void draw_hot(struct mywin *new)
{
    int x = 0 ;
    int y = 0;
     while (x < 15)
    {
   dda(1, x * (32 ), (25) * (32 ), x *(32),&new->img);
  // dda(x *(32), 1, x* (32 ), (32) * 15, &new->img);
     x++;
    }
   // printf("%d",x);
         //  dda(24 *(32), 1, 24* (32 ), (32) * 15, &new->img);

   x = 25 ; 
   /*while(x>=15)
   {
               dda(x *(32), 1, x* (32 ), (32) * 15, &new->img);
               x--;
   }*/
      //  dda(24 *(32), 1, 24* (32 ), (32) * 15, &new->img);

    /*while (x>0)
    {
     dda(x *(32), 1, x* (32 ), (32) * 15, &new->img);

         printf("%d",x);

     x--;
    }*/
    //printf("%d",x);
    

    /*
    while(y<25)
    {
    dda(y * (32), 1, y * (32 ), (32) * 15, &new->img);
    y++;
    }*/
}

void update(struct mywin *new, int *px, int *py)//, float *rotation)
{
    *px = *px + new->play.ver;
    *py = *py + new->play.hori;
    float *a ; 
    a =&rotation;
   if (new->play.ver == -1 )
           *a = 3.142; //M_PI/2 +M_PI/2 ;
    if (new->play.ver == 1 ) 
        *a = 6.283; //0
    if(new->play.hori==1)
        *a=1.571; //Pi/2
    if(new->play.hori==-1)
        *a=-1.571; //-Pi/2
    if(new->play.angle==1)
    {
        if(*a!=M_PI/2)
            *a= *a- 0.0174533 ;
    }
    if(new->play.angle==-1)
    {
            *a= *a+ 0.0174533 ;
    }
      reykey_hook(new);
}
void creati(struct mywin *new)
{
    new->img.img = mlx_new_image(new->mlx, 800, 480);
    new->img.addr = mlx_get_data_addr(new->img.img, &new->img.bits_per_pixel, &new->img.line_length,
                                      &new->img.endian);
}
float firsty; 
float firstx;
void findfirstcord_h(void)
{
   
    float *ptr1,*ptr2;
    ptr1=&firsty;
    ptr2=&firstx; 
    *ptr1= (py/32)*32;
  // printf("%f \n",*ptr1);
   // *ptr2= px+((*ptr1-py)/tan(rotation));
  //printf("%f \n",*ptr2);
}
void find(struct mywin *new)
{
    //findfirstcord_h();
  //  float nexthortouchx=firstx;
    float nexthortouchy=firsty;
   // printf(" jojo %d \n",(int)nexthortouchx/32);
     printf(" gogo %d \n",(int)nexthortouchy/32);

    int wallx = 0 ; 
    int wally =0 ;
  //  printf("%f \n",nexthortouchx);
    //while(nexthortouchx >= 0 && nexthortouchx <= 32*15 && nexthortouchy >0 && nexthortouchy <= 32*25)
    //{
       // int i =(int)nexthortouchx/32;
        int j = (int)nexthortouchy/32;
     printf("%d \n",new->map[1][7]);

     //   printf("i == %d \n",i);
       // printf("j == %d \n",j);
     //   if(new->map[i][j]==1)
       //     printf("%d \n",new->map[i][j]);
       // else
        //printf("hani nta \n");
    //nexthortouchx++;
    //nexthortouchy++;
    //}




}
int drawc(struct mywin *new)
{
    draw(new);
    draw_hot(new);
    draw_the_player(new, px, py);
    mlx_put_image_to_window(new->mlx,
     new->win, new->img.img, 0, 0);
    if (!(new->play.ver) || !(new->play.hori))
    {
        creati(new);
        draw(new);
        draw_hot(new);
        update(new, &px, &py);
        draw_the_player(new, px, py);
        findfirstcord_h();
        find(new);
        mlx_put_image_to_window(new->mlx, new->win, new->img.img, 0, 0);
    }
    return 0;
}

int main()
{
    int map[15][25] =
        {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1},
            {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1},
            {1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
            {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
            {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        };
    struct mywin new;
    new.mlx = mlx_init();
    new.win = mlx_new_window(new.mlx, 800, 480, "hello");
    memcpy(new.map, map, sizeof(int) * 25 * 15);
    creati(&new);

    mlx_hook(new.win, 2, 1L << 0, key_hook, &new);

    mlx_loop_hook(new.mlx, drawc, &new);

    mlx_loop(new.mlx);
}