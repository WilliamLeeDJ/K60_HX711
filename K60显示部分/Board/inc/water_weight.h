#ifdef _WATER_WEIGHT_H_
#define _WATER_WEIGHT_H_


#define uint unsigned int
#define uchar unsigned char 
#define ulong unsigned long


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

extern void NOP(void);
extern unsigned long HX711_Read();
extern uint Get_Weight();
extern void Get_Maopi();
extern void HX711_init(void);


#endif
