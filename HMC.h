#ifndef __HMC_H
#define __HMC_H

void HMC_WriteReg(uint8_t RegAddress, uint8_t Data);
uint8_t HMC_ReadReg(uint8_t RegAddress);
void HMC_Init(void);
void HMC_GetData(int16_t *x,int16_t *y,int16_t *z);

#endif
