#include <stm32f10x.h>                  // Device header
#include "MyI2C.h"
#include "OLED.h"
#include "HMC.h"
#include "Delay.h"
#include "math.h"

int main(void){
	
	int Magangle;//偏转角
	
	int16_t x,y,z;//三个方向的磁场数据
	int16_t averagex,averagey,xkey,ykey,xmax,ymax,xmin,ymin;
	
	MyI2C_Init();
	OLED_Init();
	
	HMC_Init();
	HMC_ReadReg(0x03);//读取第一个数据并丢弃
	HMC_ReadReg(0x04);
	HMC_ReadReg(0x05);
	HMC_ReadReg(0x06);
	HMC_ReadReg(0x07);
	HMC_ReadReg(0x08);
	
	
	
	
	while(1){
		HMC_GetData(&x,&y,&z); 
		
		xmin = xmin > x? x:xmin;
		ymin = ymin > y? y:ymin;
		
		//y = y + xmin - ymin;
		
		
		
		OLED_ShowSignedNum(2,1,x,5);
		OLED_ShowSignedNum(3,1,y,5);
		OLED_ShowSignedNum(4,1,z,5);
		
		
		
		 
		
		
		if((x > 0)&&(y > 0)) Magangle = atan((float)y/x)*57;
			else if((x > 0)&&(y < 0)) Magangle = 270-atan((float)x/y)*57;
			else if((x == 0)&&(y > 0)) Magangle = 90;
			else if((x == 0)&&(y < 0)) Magangle = 270;
			else if(x < 0) Magangle = 180+atan((float)y/x)*57;
		
		OLED_ShowNum(1,1,Magangle,3);
		
		
		
		
		Delay_ms(67);	
	}
}
