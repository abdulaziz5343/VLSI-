#include "address_map_nios2.h"



/*global variable declaration*/
volatile int *pixel_ctrl_ptr=(int *)PIXEL_BUF_CTRL_BASE;   //PixelBufferBaseAddress
volatile int pixel_buffer_start;                           
short int front_pixel_buffer[512 * 256];                    //allocate memory for front buffer
short int back_pixel_buffer[512 * 256];                     //allocate memory for back buffer

/*integer definition*/
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
/*function definition*/
/*function for insert color of x,y pixels*/
void plot_pixel(int x, int y, short int line_color){
    *(short int*)(pixel_buffer_start+(y<<10)+(x<<1))=line_color;
}
/*clear display to white color*/
void clear_screen(){
    int x,y;
    for(x=0; x<=SCREEN_HEIGHT; x++){
        for(y=0; y<=SCREEN_HEIGHT-1; y++)
            plot_pixel(x,y, 0xFFFF);
		 }
}
/*drawing line*/
void draw_line(int x1, int y1, int x2, int y2, short int line_color)
{
    int t;
    int st=(abs(y2-y1)>abs(x2-x1));
    if(st){
        t=x1;
        x1=y1;
        y1=t;
        x2=y2;
        y2=t;
    }
    if(x1>x2){
        t=x1;
        x1=x2;
        x2=t;
        t=y1;
        y1=y2;
        y2=t;
    }
    int dx=abs(x1-x2);
    int dy=abs(y1-y2);
    int error=-(dx/2);
    int y=y1;
    int i;
    if(y1<y2) i=1;
    else i=-1;

    int x;
    for(x=x1; x<=x2; x++){
        if(st) plot_pixel(y,x, line_color);
        else plot_pixel(x,y, line_color);
        error=error+dy;
        if(error>=0){
            y=y+i;
            error=error-dx;
        }
    }
}
/*V-schronize activator*/
void wait_for_vsync(){
    register int status;
    *pixel_ctrl_ptr=1;
    status=*(pixel_ctrl_ptr+3);
    while((status&0x01)!=0){
        status=*(pixel_ctrl_ptr+3);
    }
}
int main(void)
{
    int y=0, dy=1;
    *(pixel_ctrl_ptr+1)=&front_pixel_buffer;

    wait_for_vsync();
    pixel_buffer_start=*pixel_ctrl_ptr;
    clear_screen();
    *(pixel_ctrl_ptr+1)=&back_pixel_buffer;
    while (1)
    {
        pixel_buffer_start=*(pixel_ctrl_ptr+1);
        clear_screen();
        draw_line(100, y, 200, y, 0);
        if(y==SCREEN_HEIGHT-1) dy=-1;
        else if(y=0) dy=1;
        y=y+dy;
        wait_for_vsync();
    }
}
