#define LED_GPIO_PINRed 3 // Set GPIO 3 (Pin 5) for LED
#define LED_GPIO_PINGreen 4 // Set GPIO 4 (Pin 6) for LED
#define LED_GPIO_PINBlue 5 // Set GPIO 5 (Pin 7) for LED

//macro

int pico_led_init(void);
void pico_set_led(bool led_on_Red,bool led_on_Green, bool led_on_Blue);