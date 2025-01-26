#include <stdio.h>
#include "pico/stdlib.h"
#include <hardware/pio.h>
#include "hardware/clocks.h"
#include "ws2818b.pio.h"
#include "hardware/adc.h"

// Definições de constantes
#define LED_COUNT 25                // Número de LEDs na matriz
#define LED_PIN 7                   // Pino GPIO conectado aos LEDs
#define FPS 30                      // Frames por segundo (taxa de quadros)

// Estrutura para representar um pixel com componentes RGB
struct pixel_t { 
    uint8_t G, R, B;                // Componentes de cor: Verde, Vermelho e Azul
};

typedef struct pixel_t pixel_t;     // Alias para a estrutura pixel_t
typedef pixel_t npLED_t;            // Alias para facilitar o uso no contexto de LEDs

npLED_t leds[LED_COUNT];            // Array para armazenar o estado de cada LED
PIO np_pio;                         // Variável para referenciar a instância PIO usada
uint sm;                            // Variável para armazenar o número do state machine usado

// Função para inicializar o PIO para controle dos LEDs
void npInit(uint pin) 
{
    uint offset = pio_add_program(pio0, &ws2818b_program); // Carregar o programa PIO
    np_pio = pio0;                                         // Usar o primeiro bloco PIO

    sm = pio_claim_unused_sm(np_pio, false);              // Tentar usar uma state machine do pio0
    if (sm < 0)                                           // Se não houver disponível no pio0
    {
        np_pio = pio1;                                    // Mudar para o pio1
        sm = pio_claim_unused_sm(np_pio, true);           // Usar uma state machine do pio1
    }

    ws2818b_program_init(np_pio, sm, offset, pin, 800000.f); // Inicializar state machine para LEDs

    for (uint i = 0; i < LED_COUNT; ++i)                  // Inicializar todos os LEDs como apagados
    {
        leds[i].R = 0;
        leds[i].G = 0;
        leds[i].B = 0;
    }
}

// Função para definir a cor de um LED específico com intensidade reduzida
void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b) 
{
    leds[index].R = r * 0.3;                              // Reduzir intensidade do componente vermelho
    leds[index].G = g * 0.3;                              // Reduzir intensidade do componente verde
    leds[index].B = b * 0.3;                              // Reduzir intensidade do componente azul
}

// Função para limpar (apagar) todos os LEDs
void npClear() 
{
    for (uint i = 0; i < LED_COUNT; ++i)                  // Iterar sobre todos os LEDs
        npSetLED(i, 0, 0, 0);                             // Definir cor como preta (apagado)
}

// Função para atualizar os LEDs no hardware
void npWrite() 
{
    for (uint i = 0; i < LED_COUNT; ++i)                  // Iterar sobre todos os LEDs
    {
        pio_sm_put_blocking(np_pio, sm, leds[i].G);       // Enviar componente verde
        pio_sm_put_blocking(np_pio, sm, leds[i].R);       // Enviar componente vermelho
        pio_sm_put_blocking(np_pio, sm, leds[i].B);       // Enviar componente azul
    }
}

// Função de delay com base no FPS
void npDelay() 
{
    sleep_ms(1000 / FPS);  // Atraso baseado no FPS
}

// Função para o efeito de fade de cor
void fadeEffect() 
{
    for (int i = 0; i < 256; i++) 
    {
        for (uint j = 0; j < LED_COUNT; ++j)
        {
            npSetLED(j, i, 0, 0);  // Gradiente de vermelho
        }
        npWrite();
        npDelay();
    }

    for (int i = 0; i < 256; i++) 
    {
        for (uint j = 0; j < LED_COUNT; ++j)
        {
            npSetLED(j, 0, i, 0);  // Gradiente de verde
        }
        npWrite();
        npDelay();
    }

    for (int i = 0; i < 256; i++) 
    {
        for (uint j = 0; j < LED_COUNT; ++j)
        {
            npSetLED(j, 0, 0, i);  // Gradiente de azul
        }
        npWrite();
        npDelay();
    }
}

// Função para o efeito de onda de luz
void waveEffect() 
{
    for (int frame = 0; frame < LED_COUNT; ++frame) 
    {
        npClear();  // Limpar todos os LEDs
        for (uint i = 0; i <= frame; ++i)
        {
            npSetLED(i, 255, 255, 255);  // Acender LEDs com brilho máximo
        }
        npWrite();
        npDelay();
    }
}

// Função para o efeito de transição de cores
void colorTransitionEffect() 
{
    for (int i = 0; i < LED_COUNT; i++) 
    {
        npSetLED(i, 255, 0, 0);  // Vermelho
    }
    npWrite();
    npDelay();

    for (int i = 0; i < LED_COUNT; i++) 
    {
        npSetLED(i, 0, 255, 0);  // Verde
    }
    npWrite();
    npDelay();

    for (int i = 0; i < LED_COUNT; i++) 
    {
        npSetLED(i, 0, 0, 255);  // Azul
    }
    npWrite();
    npDelay();
}

// Função para o efeito de piscar
void blinkEffect() 
{
    for (int i = 0; i < 5; ++i) 
    {
        npClear();
        npWrite();
        npDelay();
        
        for (uint j = 0; j < LED_COUNT; ++j)
        {
            npSetLED(j, 255, 255, 255);  // Piscar com LEDs brancos
        }
        npWrite();
        npDelay();
    }
}

// Função para o efeito de rotação de LEDs
void rotationEffect() 
{
    for (int i = 0; i < LED_COUNT; ++i) 
    {
        npSetLED(i, 255, 0, 0);  // Acender LED vermelho
        npWrite();
        npDelay();
        npSetLED(i, 0, 0, 0);  // Apagar LED
    }
}

// Função para definir a bandeira do Brasil
void setBrazilFlag() 
{
    // Definir fundo verde
    for (uint i = 0; i < LED_COUNT; ++i) 
    {
        npSetLED(i, 0, 255, 0); // Verde
        npWrite();
        sleep_ms(100); // Atraso para visualizar o carregamento
    }

    // Definir losango amarelo
    npSetLED(6, 255, 255, 0); // Amarelo
    npWrite();
    sleep_ms(100);
    npSetLED(8, 255, 255, 0); // Amarelo
    npWrite();
    sleep_ms(100);
    npSetLED(10, 255, 255, 0); // Amarelo
    npWrite();
    sleep_ms(100);
    npSetLED(12, 255, 255, 0); // Amarelo
    npWrite();
    sleep_ms(100);
    npSetLED(14, 255, 255, 0); // Amarelo
    npWrite();
    sleep_ms(100);
    npSetLED(16, 255, 255, 0); // Amarelo
    npWrite();
    sleep_ms(100);
    npSetLED(18, 255, 255, 0); // Amarelo
    npWrite();
    sleep_ms(100);

    // Definir círculo azul
    npSetLED(12, 0, 0, 255); // Azul
    npWrite();
    sleep_ms(100);
}

int animacaoBrasil() 
{
    stdio_init_all();                                     // Inicializar a comunicação serial
    npInit(LED_PIN);                                      // Inicializar os LEDs

    while (true)                                          // Loop principal
    {
        npClear();                                        // Apagar todos os LEDs
        npWrite();                                        // Atualizar o estado dos LEDs
        sleep_ms(1000);                                   // Aguardar um segundo

        setBrazilFlag();                                  // Definir a bandeira do Brasil
        sleep_ms(1000);                                   // Aguardar um segundo

        // Teste dos efeitos
        fadeEffect();
        waveEffect();
        colorTransitionEffect();
        blinkEffect();
        rotationEffect();
    }
}
