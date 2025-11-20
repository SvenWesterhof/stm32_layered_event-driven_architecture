#ifndef PINOUT_H
#define PINOUT_H

#define EXT_LED_PIN         GPIO_PIN_5
#define EXT_LED_GPIO_PORT   GPIOA

//display spi clock pin
#define DISPLAY_SCL_PIN     GPIO_PIN_6
#define DISPLAY_SCL_PORT    GPIOB

//display spi MI pin
#define DISPLAY_MI_PIN    GPIO_PIN_4
#define DISPLAY_MI_PORT   GPIOB

//display spi mo pin
#define DISPLAY_MO_PIN    GPIO_PIN_5
#define DISPLAY_MO_PORT   GPIOB

//display chip select pin
#define DISPLAY_CS_PIN      GPIO_PIN_7
#define DISPLAY_CS_PORT     GPIOB

#endif // PINOUT_H