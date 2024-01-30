#include "main.h"
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void delay_ms(uint32_t t){
	LL_InitTick(8000000,1/(t*0.001));
	while(LL_SYSTICK_IsActiveCounterFlag() == 0){}
	LL_SYSTICK_DisableIT();
}
int main(void)
{
  SystemClock_Config();
  MX_GPIO_Init();
  while (1)
  {
	  LL_GPIO_TogglePin(GPIOC,LL_GPIO_PIN_13);
	  delay_ms(1000);
  }
}

void SystemClock_Config(void)
{
  LL_RCC_HSI_Enable();
  while(LL_RCC_HSI_IsReady() != 1){}
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI){}
}

static void MX_GPIO_Init(void)
{
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);
  LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_13);
  GPIO_InitStruct.Pin = LL_GPIO_PIN_13;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}
