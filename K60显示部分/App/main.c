#include "common.h"
#include "include.h"
#include "VCAN_menu.h"
#include "font.h"
#include "main_menu.h"
#include "water_weight.h"

#define uint unsigned int

extern void main_menu_task(void);
void pit_hander(void)
{
    if(PIT_TFLG(PIT0) == 1 )        //判断是否 PIT0 进入中断
    {
        PIT_Flag_Clear(PIT0);                   //清中断标志位
        key_IRQHandler();                       //把按键扫描程序加入到定时中断复位函数里，定时执行
    }
}
void  main(void)
{
    uint Weig;
    char ch;
    uint16  i = 0;
    Site_t site;
    LCD_init();
    key_init(KEY_MAX);
    site.x = 0;
    site.y = 0;
    LCD_FSTR_CH(site,front ,BLUE, WHITE) ;
    site.x = 0;
    site.y = 30;
    LCD_FSTR_CH(site,VCAN ,BLUE, WHITE) ;
    site.x = 0;
    site.y = 60;
    LCD_FSTR_CH(site,down ,BLUE, WHITE) ;
    site.x = 0;
    site.y = 90;
    LCD_FSTR_CH(site,department ,BLUE, WHITE) ;
    DELAY_MS(2000);
    pit_init_ms(PIT0,10);                               
    set_vector_handler(PIT0_VECTORn,pit_hander);         
    enable_irq(PIT0_IRQn);
    uart_init(UART4,115200);   
    HX711_init();
    Get_Maopi();
    DELAY_US(10);
    Get_Maopi(); 
    uart_putstr (UART4, "\n接收到字符串：");
    while(1)
    {			
       main_menu_task();       
    }

}




