#include "stm32f10x.h"
#include "MyI2C.h"
#include "HMC.h"
#include "Delay.h"
#include "OLED.h"

#define HMC5883L_ADDRESS 0x3C

void HMC_WriteReg(uint8_t RegAddress, uint8_t Data){
	MyI2C_Start();
	MyI2C_SendByte(HMC5883L_ADDRESS);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(RegAddress);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(Data);
	MyI2C_ReceiveAck();
	MyI2C_Stop();
}

uint8_t HMC_ReadReg(uint8_t RegAddress)
{
	uint8_t Data;
	
	MyI2C_Start();
	MyI2C_SendByte(HMC5883L_ADDRESS);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(RegAddress);
	MyI2C_ReceiveAck();
	
	MyI2C_Start();
	MyI2C_SendByte(HMC5883L_ADDRESS | 0x01);
	MyI2C_ReceiveAck();
	Data = MyI2C_ReceiveByte();
	MyI2C_SendAck(1);
	MyI2C_Stop();
	
	return Data;
}

void HMC_Init(void){
	MyI2C_Init();
	HMC_WriteReg(0x00,0x70);
	HMC_WriteReg(0x01,0xA0);
	HMC_WriteReg(0x02,0x00);
	
}

void HMC_GetData(int16_t *x,int16_t *y,int16_t *z){
	uint8_t DataH, DataL;
	
        
		HMC_WriteReg(0x3C,0x03);
		
		DataH = HMC_ReadReg(0x03);
	    DataL = HMC_ReadReg(0x04);
		*x = (DataH << 8) | DataL;
	
		DataH = HMC_ReadReg(0x05);
	    DataL = HMC_ReadReg(0x06);
		*z = (DataH << 8) | DataL;
	
		DataH = HMC_ReadReg(0x07);
	    DataL = HMC_ReadReg(0x08);
		*y = (DataH << 8) | DataL;
		
		
	
	
	
	
}



