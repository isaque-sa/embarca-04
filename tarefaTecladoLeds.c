#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"
#include "pico/cyw43_arch.h"
#include "ws2812.pio.h"
#include "pico/bootrom.h"

#define NUM_PIXELS 25      // Quantidade de pixels da tarefa
#define WS2812_PIN 7       // GPIO onde a cadeia de pixels está conectada
#define BUZZER_A 21        // GPIO do buzzer A
#define BUZZER_B 10        // GPIO do buzzer A
#define NUM_ROWS 4         // Quantidade de linhas do teclado
#define NUM_COLS 4         // Quantidade de colunas do teclado

// GPIO para as colunas e as linhas do teclado
#define PIN_COL_1 5
#define PIN_COL_2 4
#define PIN_COL_3 3
#define PIN_COL_4 2
#define PIN_ROW_1 12
#define PIN_ROW_2 11
#define PIN_ROW_3 9
#define PIN_ROW_4 8

/// Envia um pixel para o PIO
static inline void put_pixel(PIO pio, uint sm, uint32_t pixel_grb) {
    pio_sm_put_blocking(pio, sm, pixel_grb << 8u);
}

// Junta os pixels em uma única word
static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return
            ((uint32_t) (r) << 8) |
            ((uint32_t) (g) << 16) |
            (uint32_t) (b);
}

char key_map[NUM_ROWS][NUM_COLS] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}};

uint8_t key_rows[NUM_ROWS] = {PIN_ROW_1,PIN_ROW_2,PIN_ROW_3,PIN_ROW_4};
uint8_t key_cols[NUM_COLS] = {PIN_COL_1,PIN_COL_2,PIN_COL_3,PIN_COL_4};

void init_keyboard(void)
{
    for(int i=0; i<NUM_ROWS; i++){
        gpio_init(key_cols[i]); gpio_init(key_rows[i]);
        gpio_set_dir(key_cols[i],GPIO_IN);
        gpio_set_dir(key_rows[i],GPIO_OUT);
        gpio_pull_up(key_cols[i]);}

    for(int i=0; i<NUM_ROWS; i++){
        gpio_put(key_rows[i],1);
    }
}

void init_buzzers(void)
{
    gpio_init(BUZZER_A); gpio_init(BUZZER_B);
    gpio_set_dir(BUZZER_A,GPIO_OUT); gpio_set_dir(BUZZER_B,GPIO_OUT);
}

char get_char(void)
{
    char key_char = 0;

    for(int i=0; i<NUM_ROWS; i++){
        gpio_put(key_rows[i],0);
        for(int j=0; j<NUM_COLS; j++){
            if(!gpio_get(key_cols[j]))
                key_char = key_map[i][j];
        }
        gpio_put(key_rows[i],1);
    }
    return key_char;
}

void animacao_0(uint8_t num_pix, PIO pio, uint sm, uint32_t (* urgb)(uint8_t,uint8_t,uint8_t), void (*put_p)(PIO,uint,uint32_t));

int main() {
    // Iicialização da comunicação serial
    stdio_init_all();

    // Inicialização do teclado
    init_keyboard();

    // Inicialização do PIO
    PIO pio; uint sm; uint offset;
    bool success = pio_claim_free_sm_and_add_program_for_gpio_range(&ws2812_program, &pio, &sm, &offset, WS2812_PIN, 1, true);
    hard_assert(success);
    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000.f);

    // Inicialização dos buzzers
    init_buzzers();

    char character_1, character_2 = 0;
    
    sleep_us(1);

    while (1) {
        character_1 = get_char();
        sleep_ms(1);

        if(character_1 == 'A')
            character_2 = character_1;

        if(character_1 == 'B')
            character_2 = character_1;

        if(character_1 == 'C')
            character_2 = character_1;

        if(character_1 == 'D')
            character_2 = character_1;

        if(character_1 == '#')
            character_2 = character_1;

        if(character_1 == '*')
            character_2 = character_1;

        if(character_1 == '0')
            character_2 = character_1;

        if(character_1 == '1')
            character_2 = character_1;

        if(character_1 == '2')
            character_2 = character_1;

        if(character_1 == '3')
            character_2 = character_1;

        if(character_1 == '4')
            character_2 = character_1;

        if(character_1 == '5')
            character_2 = character_1;

        if(character_1 == '6')
            character_2 = character_1;

        if(character_1 == '7')
            character_2 = character_1;

        if(character_1 == '8')
            character_2 = character_1;

        if(character_1 == '9')
            character_2 = character_1;

        switch(character_2){
            // Desliga todos os pixels
            case 'A':
            for(int i=0; i<NUM_PIXELS; i++)
                put_pixel(pio,sm,urgb_u32(0,0,0));
            gpio_put(BUZZER_A,0); gpio_put(BUZZER_B,0);
            break;

            // Liga todos os pixels na cor azul com 100%
            case 'B':
            for(int i=0; i<NUM_PIXELS; i++)
                put_pixel(pio,sm,urgb_u32(0,0,255));
            break;

            //Liga todos os pixels na cor vermelha com 80%
            case 'C':
            for(int i=0; i<NUM_PIXELS; i++)
                put_pixel(pio,sm,urgb_u32(204,0,0));
            break;

            //Liga todos os pixels na cor verde com 50%
            case 'D':
            for(int i=0; i<NUM_PIXELS; i++)
                put_pixel(pio,sm,urgb_u32(0,128,0));
            break;

            //Liga todos os pixels na cor branca com 20%
            case '#':
            for(int i=0; i<NUM_PIXELS; i++)
                put_pixel(pio,sm,urgb_u32(51,51,51));
            break;

            // Habilita o modo gravação do microcontrolador
            case '*':
            reset_usb_boot(0,0);
            break;

            // Animação etc_e_tal
            case '1':
            //animacao_etc_tal();
            break;

            // Animação etc_e_tal
            case '2':
            //animacao_etc_tal();
            break;

            // Animação etc_e_tal
            case '3':
            //animacao_etc_tal();
            break;

            // Animação etc_e_tal
            case '4':
            //animacao_etc_tal();
            break;

            // Animação etc_e_tal
            case '5':
            //animacao_etc_tal();
            break;

            // Animação etc_e_tal
            case '6':
            //animacao_etc_tal();
            break;

            // Animação etc_e_tal
            case '7':
            //animacao_etc_tal();
            break;

            // Animação etc_e_tal
            case '8':
            //animacao_etc_tal();
            break;

            // Animação etc_e_tal
            case '9':
            //animacao_etc_tal();
            break;

            // Animação 0
            case '0':
            animacao_0(NUM_PIXELS,pio,sm,urgb_u32,put_pixel);
            break;
        }
    }

    // This will free resources and unload our program
    pio_remove_program_and_unclaim_sm(&ws2812_program, pio, sm, offset);

    return 0;
}
