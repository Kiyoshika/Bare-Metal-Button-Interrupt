# Bare Metal Button Interrupt (STM32)
This is some sample code I wrote for an STM32WB55xx board to toggle an LED with a button interrupt using "bare metal" code (i.e. interacting directly with the register addresses).

### Datasheet
The datasheet I referenced for this board is [RM0434](https://www.st.com/resource/en/reference_manual/rm0434-multiprotocol-wireless-32bit-mcu-armbased-cortexm4-with-fpu-bluetooth-lowenergy-and-802154-radio-solution-stmicroelectronics.pdf).
### Magic Numbers
Yes, there are lots of magic numbers here but this is example code and obviously not "production" worthy, so I did not bother creating macros for everything; only the main memory addresses I was interacting with.
### NOTE
For some boards, you will need to enable the SYSCFG peripheral (e.g. on the STM32F411xx). However, for whatever reason, SYSCFG on STM32WB55xx does not need to be explicitly enabled (it's not even in the RCC peripheral registers).