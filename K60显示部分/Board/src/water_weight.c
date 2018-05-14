#include "common.h"
#include "include.h"
#include "water_weight.h"

#define uint unsigned int

#define HX711_DOUT             GPIO_GET(PTA15)
#define HX711_DOUT_HIGH()      GPIO_SET(PTA15,1) 
#define HX711_DOUT_LOW()       GPIO_SET(PTA15,0) 
#define HX711_SCK_HIGH()       GPIO_SET(PTA16,1) 
#define HX711_SCK_LOW()        GPIO_SET(PTA16,0)

uint32_t ticktime;
unsigned long HX711_Buffer = 0;
unsigned int Weight_Maopi = 0,Weight_Shiwu = 0;
char Price_Count = 0;
unsigned char KEY_NUM = 0;
unsigned char Price_Buffer[5] = {0x00,0x00,0x00,0x00,0x00};
unsigned long Money = 0;
unsigned char Flag_OK = 0;

unsigned char temp = 0,temp1 = 0xf7;

void NOP(void)
{ uint8 i;	for(i=0; i<100; i++); } 




void Delay__hx711_us(void)
{
	NOP();
	NOP();
}

unsigned long HX711_Read()
{
  unsigned long count; 
  unsigned char i;
  
  	HX711_DOUT_HIGH(); 
	Delay__hx711_us();
  	HX711_SCK_LOW(); 
 	count=0; 
  	while(HX711_DOUT);
	NOP(); 
  	for(i=0;i<24;i++)
	{ 
	  	HX711_SCK_HIGH();		 
	  	count=count<<1; 
		NOP();
		HX711_SCK_LOW(); 
	  	if(HX711_DOUT)
			count++; 
		NOP();
	} 
 	HX711_SCK_HIGH(); 
//	count=count&0x007fffff;
	Delay__hx711_us();
	HX711_SCK_LOW();  
	return(count);
}

uint Get_Weight()
{
  HX711_Buffer = HX711_Read();
  HX711_Buffer = HX711_Buffer/100;
  if(HX711_Buffer >= Weight_Maopi)			
	{
		Weight_Shiwu = HX711_Buffer;
		Weight_Shiwu = Weight_Shiwu - Weight_Maopi;				
	
		Weight_Shiwu = (unsigned int)((float)Weight_Shiwu/2.135+0.05); 	
}
return Weight_Shiwu/2;
}
void Get_Maopi()
{
	HX711_Buffer = HX711_Read();
	Weight_Maopi = HX711_Buffer/100;	 			
} 
void HX711_init(void)
 {
  gpio_init(PTA16,GPO,1);                     
  gpio_init(PTA15,GPI,0); 
		
 }