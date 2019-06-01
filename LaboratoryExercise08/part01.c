#include "address_map_nios2.h"
/*global variable declaration*/
volatile int *pixel_ctrl_ptr=(int *) PIXEL_BUF_CTRL_BASE;
volatile int pixel_buffer_start;
/*integer definition*/
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
/*function definition*/
/*function for insert color of x,y pixels*/
void plot_pixel(int x, int y, short int line_color){
*(short int *)(pixel_buffer_start+(y<<10)+(x<<1))=line_color;
}
/*clear display to white color*/
void clear_screen(){
    int x,y;
    for(x=0; x<=SCREEN_WIDTH-1; x++){                           
        for (y=0; y<=SCREEN_HEIGHT-1; y++)
        plot_pixel(x,y, 0xFFFF);
    }
}
/*function for draw line*/
void draw_line(int x1, int y1, int x2, int y2, short int line_color)
{
    int t;
    int st=(abs(y2-y1)>abs(x2-x1));         //Specify a variable to compare slopes
    if(st){                                 //if slope is greater then absolute value 1
        t=x1;                               
        x1=y1;
        y1=t;
        t=x2;
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
    int dx=abs(x1-x2);                      //specified a variable to appear x's interval 
    int dy=abs(y1-y2);                      //specified a variable to appear y's interval

    int error=-(dx/2);                      //An error value that determines whether y 
    int y=y1;                               //moves each time x moves by one pixel
    int i;
    if(y1<y2) i=1;
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
int main(void){
    pixel_buffer_start=*pixel_ctrl_ptr;

    clear_screen();
    draw_line(0, 0, 150, 150, 0x001F);
    draw_line(150, 150, 319, 0, 0x07E0);
    draw_line(0, 239, 319, 239, 0xF800);
    draw_line(319, 0, 0, 239, 0xF81F);
    
}
