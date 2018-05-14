#include "main_menu.h"
#include "font.h"
#include "water_weight.h"
#include "VCAN_LCD.h"
#include "font.h"


#define uint unsigned int



uint32 water;
uint32 current;
uint32 now;
uint32 days[7]={0,0,0,0,0,0,0};
uint32 Temp_water;
uint i;
uint Temp_i=0;
char Cycle[100];
uint32 drinkwater;
extern uint cup_weight;


void main_menu_task(void)
{
  Site_t site2;   
  site2.x = 0;
  site2.y = 60;
  Site_t site;
  result_e result;
  KEY_MSG_t keymsg;  
MAIN_INIT:
  while(get_key_msg(&keymsg) == 1);      //��հ�����Ϣ
  LCD_clear(BCOLOUR);                     //���� 
  main_menu_init();                       //�˵���ʼ��
  site.x = 0;
  site.y = 90;
  LCD_FSTR_CH(site,mainFUC ,BLUE, WHITE) ;
    while(1)
    {
        result = main_menu_deal();
        if(result == RESULT_INIT )
        {
            //LCD_init();
            return ;      //ֱ���˳��󣬻����½���
        }
        else if(result == RESULT_TO_MENU )
        {
            goto MAIN_INIT;
        }
    }
}



result_e main_func(void)
{
   Site_t site     = {0, 0};                           //��ʾͼ�����Ͻ�λ��
   Site_t site2;
   Site_t site_water;
   Site_t ml_d; 
   site2.x = 0;
   site2.y = 60;
   char display_W;
   KEY_MSG_t keymsg;
   while(get_key_msg(&keymsg) == 1);                   //��հ�����Ϣ
   LCD_clear(BCOLOUR);                                 //����   
   LCD_FSTR_CH(site,main_func_name,FCOLOUR,BCOLOUR);     //��ʾ�˵�����
   //�����ʼ��
   HX711_init();
   Get_Maopi();				
   DELAY_US(10);
   Get_Maopi();	
   site2.x = 0;
   site2.y = 60;  
   gpio_init(PTC15,GPI,0);                      //��ʼ�����İ�����������ڲ���������
   port_init_NoALT(PTC15,PULLUP);
   gpio_init(PTC14,GPI,0);                      //��ʼ�����İ�����������ڲ���������
   port_init_NoALT(PTC14,PULLUP);
   LCD_FSTR_CH(site2,water_display ,BLUE, WHITE) ;
   site_water.x = 60;
   site_water.y = 60;
   ml_d.x=100;
   ml_d.y=60;
   LCD_FSTR_CH(ml_d,ml ,BLUE, WHITE) ;
   now=0;
   while(1)
    {
//      for(uint h=0;h<7;h++)
//      {
//       printf("h=%d\n",days[h]);
//      }
//      printf("\n");      
      //����ѭ��ִ�����ݡ��û����в��䡿
        if(PTC15_IN == 0 && PTC14_IN == 1)        //���ذ������µ���������û��
        {
            current = Get_Weight(); 
            DELAY_MS(200);                        
        }  
        
        if(PTC15_IN == 1)       //���ذ���û���¼�������Ҳû����
        {  
          if(current<Temp_water)
        {
          drinkwater=Temp_water-current+drinkwater;
        }
        Temp_water=current;
       // Cycle=drinkwater;
        display_W=drinkwater; 
        printf("%d\n",drinkwater);
        DELAY_MS(100);
        LCD_num(site_water,drinkwater,BLUE,WHITE);
          if(PTC14_IN == 0)
          {
            //printf("i=%d\n",i);
            days[i]=drinkwater;
            DELAY_MS(500);
            i++;
            drinkwater=0;
            LCD_num(site_water,0,BLUE,WHITE);
            if(i==7)
              i=0;
          }        
        }
         
      //���񰴼�����
      while(get_key_msg(&keymsg) == 1)               // ��������
      {
          if((keymsg.status == KEY_DOWN) && (keymsg.key == KEY_A ))       //A �� ����ʱ�˳�
          {
              //�����˳�����
              LCD_clear(BCOLOUR); 
              LCD_FSTR_CH(site2,warning ,BLUE, WHITE) ;
              DELAY_MS(1000);

              return  RESULT_TO_MENU;
          }
          //�����İ�������
          
          
      }
   }
}



result_e led_func(void)
{
   Site_t site     = {0, 0};                           //��ʾͼ�����Ͻ�λ��


   KEY_MSG_t keymsg;
   while(get_key_msg(&keymsg) == 1);                   //��հ�����Ϣ

   LCD_clear(BCOLOUR);                                 //����
   LCD_FSTR_CH(site,led_func_name,FCOLOUR,BCOLOUR);     //��ʾ�˵�����

   //�����ʼ��

   while(1)
    {
      //����ѭ��ִ������

      

      //���񰴼�����
      while(get_key_msg(&keymsg) == 1)               // ��������
      {
          if((keymsg.status == KEY_DOWN) && (keymsg.key == KEY_A ))       //A �� ����ʱ�˳�
          {
              //�����˳�����

              return  RESULT_TO_MENU;
          }
          //�����İ�������
          
          
      }
   }
}



result_e cam_func(void)
{
   Site_t site     = {0, 0};                           //��ʾͼ�����Ͻ�λ��


   KEY_MSG_t keymsg;
   while(get_key_msg(&keymsg) == 1);                   //��հ�����Ϣ

   LCD_clear(BCOLOUR);                                 //����
   LCD_FSTR_CH(site,cam_func_name,FCOLOUR,BCOLOUR);     //��ʾ�˵�����
   site.x = 90;
   site.y = 0;
   LCD_FSTR_CH(site,ml ,BLUE, WHITE) ;
   //�����ʼ��
   
   
    site.x = 0;
    site.y = 15;
    LCD_FSTR_CH(site,Mon ,BLUE, WHITE) ;

    site.x = 0;
    site.y = 30;
    LCD_FSTR_CH(site,Tue ,BLUE, WHITE) ;

    site.x = 0;
    site.y = 45;
    LCD_FSTR_CH(site,Wen,BLUE, WHITE) ;

    site.x = 0;
    site.y = 60;
    LCD_FSTR_CH(site,Thu,BLUE, WHITE) ;

    site.x = 0;
    site.y = 75;
    LCD_FSTR_CH(site,Fri ,BLUE, WHITE) ;

    site.x = 0;
    site.y = 90;
    LCD_FSTR_CH(site,Sat,BLUE, WHITE) ;

    site.x = 0;
    site.y = 105;
    LCD_FSTR_CH(site,Sun,BLUE, WHITE) ;


    
   

   while(1)
    {
      //����ѭ��ִ������
        
    site.x = 60;
    site.y = 15;
    LCD_num(site,days[0],BLUE,WHITE);    
    site.x = 60;
    site.y = 30;
    LCD_num(site,days[1],BLUE,WHITE);    
    site.x = 60;
    site.y = 45;
    LCD_num(site,days[2],BLUE,WHITE);    
    site.x = 60;
    site.y = 60;
    LCD_num(site,days[3],BLUE,WHITE);    
    site.x = 60;
    site.y = 75;
    LCD_num(site,days[4],BLUE,WHITE);    
    site.x = 60;
    site.y = 90;
    LCD_num(site,days[5],BLUE,WHITE);    
    site.x = 60;
    site.y = 105;
    LCD_num(site,days[6],BLUE,WHITE);
      
      
      //���񰴼�����
      while(get_key_msg(&keymsg) == 1)               // ��������
      {
          if((keymsg.status == KEY_DOWN) && (keymsg.key == KEY_A ))       //A �� ����ʱ�˳�
          {
              //�����˳�����

              return  RESULT_TO_MENU;
          }
          //�����İ�������
          
          
      }
   }
}