#include "hal_bootloader_jump/jump.h"

#include "main.h"

void JumpToBootloader(void)
{
  volatile uint32_t bootloader_address;

#if defined(STM32C0)
  bootloader_address = 0x1FFF0000;
#elif defined(STM32F0)

#if defined(STM32F030x8)
  bootloader_address = 0x1FFFEC00;
#elif defined(STM32F030xC)
  bootloader_address = 0x1FFFD800;
#elif defined(STM32F030x6) || defined(STM32F031x6) || defined(STM32F038xx)
  bootloader_address = 0x1FFFEC00;
#elif defined(STM32F042x6) || defined(STM32F048xx)
  bootloader_address = 0x1FFFC400;
#elif defined(STM32F051x8) || defined(STM32F058xx)
  bootloader_address = 0x1FFFEC00;
#elif defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || defined(STM32F070xB) || defined(STM32F070x6)
  bootloader_address = 0x1FFFC800;
#elif defined(STM32F091xC) || defined(STM32F098xx)
  bootloader_address = 0x1FFFD800;
#endif

#elif defined(STM32F1)

#if defined(STM32F105xC) || defined(STM32F107xC)
  bootloader_address = 0x1FFFB000;
#elif defined(STM32F101x6) || defined(STM32F102x6) || defined(STM32F103x6) || defined(STM32F100xB) || \
    defined(STM32F101xB) || defined(STM32F102xB) || defined(STM32F103xB) || defined(STM32F100xE) ||   \
    defined(STM32F101xE) || defined(STM32F103xE) || defined(STM32F101xG) || defined(STM32F103xG)
  bootloader_address = 0x1FFFF000;
#endif

#elif defined(STM32F2)
  bootloader_address = 0x1FFF0000;
#elif defined(STM32F3)
  bootloader_address = 0x1FFFD800;
#elif defined(STM32F4)
  bootloader_address = 0x1FFF0000;
#elif defined(STM32F7)
  bootloader_address = 0x1FF00000;
#elif defined(STM32G0)
  bootloader_address = 0x1FFF0000;
#elif defined(STM32G4)
  bootloader_address = 0x1FFF0000;
#elif defined(STM32H5)
  #error "Not implemented"
#elif defined(STM32H7)
  #error "Not implemented"
#elif defined(STM32L0)
  bootloader_address = 0x1FF00000;
#elif defined(STM32L1)
  bootloader_address = 0x1FF00000;
#elif defined(STM32L4)
  bootloader_address = 0x1FFF0000;
#elif defined(STM32L5)
  bootloader_address = 0x0BF90000;
#elif defined(STM32WBA)
  bootloader_address = 0x0BF88000;
#elif defined(STM32WBX)
  bootloader_address = 0x1FFF0000;
#elif defined(STM32WL)
  bootloader_address = 0x1FFF0000;
#elif defined(STM32U5)
  bootloader_address = 0x0BF90000;
#endif

  HAL_DeInit();

  // Disable the PLL used
  __HAL_RCC_PLL_DISABLE();
  while (__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY) != RESET)
    ;

  // Disable interrupts
  for (uint8_t i = 0; i < 240; i++)
  {
    NVIC_DisableIRQ((IRQn_Type)i);
  }

  // Clear pending interrupts
  for (uint8_t i = 0; i < 240; i++)
  {
    NVIC_ClearPendingIRQ((IRQn_Type)i);
  }

  // Set the MSP to the bootloader's MSP
  __set_MSP(*(uint32_t *)bootloader_address);

  // Jump to bootloader
  void (*Bootloader)(void);
  Bootloader = (void (*)(void))(*((uint32_t *)((bootloader_address + 4))));
  Bootloader();
}