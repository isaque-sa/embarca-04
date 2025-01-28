#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "love_leds_funcao_moises.h"

#define LED_PIN 7         // Pino GPIO conectado aos LEDs

int main() {
    stdio_init_all();

    // Inicializa os LEDs
    npInit(LED_PIN);
    
    // Cria uma thread para executar a música em segundo plano
    multicore_launch_core1(music_thread);

    // Loop principal para animações LEDs
    while (true) {
        animar(); // Exibe LOVE e outras animações
    }

    return 0;
}
