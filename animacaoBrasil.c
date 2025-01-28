#include "pico/stdlib.h"
#include <hardware/pio.h>

// Definições de constantes
#define LED_COUNT 25                // Número de LEDs na matriz
#define FPS 30                      // Frames por segundo (taxa de quadros)

// Estrutura para representar um pixel com componentes RGB
struct pixel_t { 
    uint8_t G, R, B;                // Componentes de cor: Verde, Vermelho e Azul
};

typedef struct pixel_t pixel_t;     // Alias para a estrutura pixel_t
typedef pixel_t npLED_t;            // Alias para facilitar o uso no contexto de LEDs

npLED_t leds[LED_COUNT];            // Array para armazenar o estado de cada LED

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
void npWrite(PIO np_pio, uint sm)
{
    for (uint i = 0; i < LED_COUNT; ++i)                  // Iterar sobre todos os LEDs
    {
        pio_sm_put_blocking(np_pio, sm, leds[i].G<<24 | leds[i].R<<16 | leds[i].B<<8);  // Envia informação de pixels para a matriz
    }
}

// Função de delay com base no FPS
void npDelay() 
{
    sleep_ms(1000 / FPS);  // Atraso baseado no FPS
}

// Função para o efeito de fade de cor
void fadeEffect(PIO pio, uint sm)
{
    for (int i = 0; i < 256; i++) 
    {
        for (uint j = 0; j < LED_COUNT; ++j)
        {
            npSetLED(j, i, 0, 0);  // Gradiente de vermelho
        }
        npWrite(pio,sm);
        npDelay();
    }

    for (int i = 0; i < 256; i++) 
    {
        for (uint j = 0; j < LED_COUNT; ++j)
        {
            npSetLED(j, 0, i, 0);  // Gradiente de verde
        }
        npWrite(pio,sm);
        npDelay();
    }

    for (int i = 0; i < 256; i++) 
    {
        for (uint j = 0; j < LED_COUNT; ++j)
        {
            npSetLED(j, 0, 0, i);  // Gradiente de azul
        }
        npWrite(pio,sm);
        npDelay();
    }
}

// Função para o efeito de onda de luz
void waveEffect(PIO pio, uint sm)
{
    for (int frame = 0; frame < LED_COUNT; ++frame) 
    {
        npClear();  // Limpar todos os LEDs
        for (uint i = 0; i <= frame; ++i)
        {
            npSetLED(i, 255, 255, 255);  // Acender LEDs com brilho máximo
        }
        npWrite(pio,sm);
        npDelay();
    }
}

// Função para o efeito de transição de cores
void colorTransitionEffect(PIO pio, uint sm)
{
    for (int i = 0; i < LED_COUNT; i++) 
    {
        npSetLED(i, 255, 0, 0);  // Vermelho
    }
    npWrite(pio,sm);
    npDelay();

    for (int i = 0; i < LED_COUNT; i++) 
    {
        npSetLED(i, 0, 255, 0);  // Verde
    }
    npWrite(pio,sm);
    npDelay();

    for (int i = 0; i < LED_COUNT; i++) 
    {
        npSetLED(i, 0, 0, 255);  // Azul
    }
    npWrite(pio,sm);
    npDelay();
}

// Função para o efeito de piscar
void blinkEffect(PIO pio, uint sm)
{
    for (int i = 0; i < 5; ++i) 
    {
        npClear();
        npWrite(pio,sm);
        npDelay();
        
        for (uint j = 0; j < LED_COUNT; ++j)
        {
            npSetLED(j, 255, 255, 255);  // Piscar com LEDs brancos
        }
        npWrite(pio,sm);
        npDelay();
    }
}

// Função para o efeito de rotação de LEDs
void rotationEffect(PIO pio, uint sm)
{
    for (int i = 0; i < LED_COUNT; ++i) 
    {
        npSetLED(i, 255, 0, 0);  // Acender LED vermelho
        npWrite(pio,sm);
        npDelay();
        npSetLED(i, 0, 0, 0);  // Apagar LED
    }
}

// Função para definir a bandeira do Brasil
void setBrazilFlag(PIO pio, uint sm)
{
    // Definir fundo verde
    for (uint i = 0; i < LED_COUNT; ++i) 
    {
        npSetLED(i, 0, 255, 0); // Verde
        npWrite(pio,sm);
        sleep_ms(100); // Atraso para visualizar o carregamento
    }

    // Definir losango amarelo
    npSetLED(6, 255, 255, 0); // Amarelo
    npWrite(pio,sm);
    sleep_ms(100);
    npSetLED(8, 255, 255, 0); // Amarelo
    npWrite(pio,sm);
    sleep_ms(100);
    npSetLED(10, 255, 255, 0); // Amarelo
    npWrite(pio,sm);
    sleep_ms(100);
    npSetLED(12, 255, 255, 0); // Amarelo
    npWrite(pio,sm);
    sleep_ms(100);
    npSetLED(14, 255, 255, 0); // Amarelo
    npWrite(pio,sm);
    sleep_ms(100);
    npSetLED(16, 255, 255, 0); // Amarelo
    npWrite(pio,sm);
    sleep_ms(100);
    npSetLED(18, 255, 255, 0); // Amarelo
    npWrite(pio,sm);
    sleep_ms(100);

    // Definir círculo azul
    npSetLED(12, 0, 0, 255); // Azul
    npWrite(pio,sm);
    sleep_ms(100);
}

void animacaoBrasil(PIO pio, uint sm)
{
    npClear();                                        // Apagar todos os LEDs
    npWrite(pio,sm);                                        // Atualizar o estado dos LEDs
    sleep_ms(1000);                                   // Aguardar um segundo

    setBrazilFlag(pio,sm);                            // Definir a bandeira do Brasil
    sleep_ms(1000);                                   // Aguardar um segundo

    // Exibição dos efeitos
    fadeEffect(pio,sm);
    waveEffect(pio,sm);
    colorTransitionEffect(pio,sm);
    blinkEffect(pio,sm);
    rotationEffect(pio,sm);
}
