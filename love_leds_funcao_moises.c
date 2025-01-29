#include "pico/stdlib.h"
#include <hardware/pio.h>
#include "hardware/clocks.h"
#include "hardware/pwm.h"
#include "pico/multicore.h"

// Configurações
#define LED_COUNT 25  // Número de LEDs (matriz 5x5)

struct pixel_t
{
    uint8_t G, R, B; // Componentes de cor: Verde, Vermelho, Azul
};

typedef struct pixel_t pixel_t;
pixel_t leds2[LED_COUNT];

// Definições de notas em Hz
#define NOTE_B4 246.94
#define NOTE_D5 293.66
#define NOTE_E5 329.63
#define NOTE_FS5 740.00
#define NOTE_GS5 830.61
#define NOTE_A5 440.00
#define NOTE_B5 493.88

// Notas com sustenido (#)
#define NOTE_FS5 740.00
#define NOTE_GS5 830.61

// Definição para descanso (pausa)
#define REST 0

// Duração das notas (em ms)
#define WHOLE_NOTE 1000
#define HALF_NOTE 500
#define QUARTER_NOTE 250
#define EIGHTH_NOTE 125

int melodia[] = {
    NOTE_FS5, NOTE_FS5, NOTE_D5, NOTE_B4, REST, NOTE_B4, REST, NOTE_E5, REST,
    NOTE_E5, REST, NOTE_E5, NOTE_GS5, NOTE_GS5, NOTE_A5, NOTE_B5, NOTE_A5,
    NOTE_A5, NOTE_A5, NOTE_E5, REST, NOTE_D5, REST, NOTE_FS5, REST, NOTE_FS5,
    REST, NOTE_FS5, NOTE_E5, NOTE_E5, NOTE_FS5, NOTE_E5, REST, REST};

// Duração das notas
int duracoes[] = {
    EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE,
    EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE,
    EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE,
    EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE,
    EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE,
    EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE};

// Função para configurar e tocar uma nota
void set_pwm_pin(uint pin1, uint pin2, uint freq, uint duty_c)
{ // duty_c entre 0 e 10000
    uint slice_num1 = pwm_gpio_to_slice_num(pin1);
    uint slice_num2 = pwm_gpio_to_slice_num(pin2);
    pwm_config config = pwm_get_default_config();
    float div = (float)clock_get_hz(clk_sys) / (freq * 10000); // Obtém a frequência do clock do sistema
    pwm_config_set_clkdiv(&config, div);
    pwm_config_set_wrap(&config, 10000);
    pwm_init(slice_num1, &config, true); // Inicia o PWM com a configuração
    pwm_init(slice_num2, &config, true);
    pwm_set_gpio_level(pin1, duty_c);    // Define o nível do ciclo de trabalho
    pwm_set_gpio_level(pin2, duty_c);
}

// Função para tocar a música
void tocar_musica()
{
    uint buzzer1_pin = 21; // Pino conectado ao buzzer
    uint buzzer2_pin = 10;

    // Toca a melodia
    for (int i = 0; i < 33; i++)
    {
        int freq = melodia[i];
        int duracao = duracoes[i];

        if (freq > 0)
        {
            // Configura e toca a nota com 50% de duty cycle
            set_pwm_pin(buzzer1_pin, buzzer2_pin, freq, 5000);
        }
        else
        {
            // Pausa (silêncio)
            pwm_set_gpio_level(buzzer1_pin, 0);
            pwm_set_gpio_level(buzzer2_pin, 0);
        }

        // Espera pela duração da nota
        sleep_ms(duracao);

        // Pausa entre as notas
        pwm_set_gpio_level(buzzer1_pin, 0);
        pwm_set_gpio_level(buzzer2_pin, 0);
        sleep_ms(50);
    }
}

// Define um LED com cores específicas
void npSetLED2(const uint index, const uint8_t r, const uint8_t g, const uint8_t b)
{
    leds2[index].R = r * 0.3;
    leds2[index].G = g * 0.3;
    leds2[index].B = b * 0.3;
}

// Limpa todos os LEDs
void npClear2()
{
    for (uint i = 0; i < LED_COUNT; ++i)
        npSetLED2(i, 0, 0, 0);
}

// Atualiza o hardware dos LEDs
void npWrite2(PIO np_pio, uint sm)
{
    for (uint i = 0; i < LED_COUNT; ++i)
    {
        pio_sm_put_blocking(np_pio, sm, leds2[i].G<<24 | leds2[i].R<<16 | leds2[i].B<<8);
    }
}

// Mostra letras para formar "LOVE"
void desenharLetras(PIO pio, uint sm)
{
    // Letra L
    npClear2();
    npSetLED2(1, 255, 0, 0);
    npSetLED2(2, 255, 0, 0);
    npSetLED2(3, 255, 0, 0);
    npSetLED2(6, 255, 0, 0);
    npSetLED2(13, 255, 0, 0);
    npSetLED2(16, 255, 0, 0);
    npSetLED2(23, 255, 0, 0);
    npWrite2(pio,sm);
    sleep_ms(1000);
    // Letra O
    npClear2();
    npSetLED2(1, 0, 255, 0);
    npSetLED2(2, 0, 255, 0);
    npSetLED2(3, 0, 255, 0);
    npSetLED2(6, 0, 255, 0);
    npSetLED2(13, 0, 255, 0);
    npSetLED2(16, 0, 255, 0);
    npSetLED2(23, 0, 255, 0);
    npSetLED2(22, 0, 255, 0);
    npSetLED2(21, 0, 255, 0);
    npSetLED2(18, 0, 255, 0);
    npSetLED2(11, 0, 255, 0);
    npSetLED2(8, 0, 255, 0);
    npWrite2(pio,sm);
    sleep_ms(1000);
    // Letra V
    npClear2();
    npSetLED2(24, 0, 0, 255);
    npSetLED2(16, 0, 0, 255);
    npSetLED2(13, 0, 0, 255);
    npSetLED2(7, 0, 0, 255);
    npSetLED2(2, 0, 0, 255);
    npSetLED2(11, 0, 0, 255);
    npSetLED2(18, 0, 0, 255);
    npSetLED2(20, 0, 0, 255);
    npWrite2(pio,sm);
    sleep_ms(1000);
    // Letra E
    npClear2();
    npSetLED2(1, 255, 255, 0);
    npSetLED2(2, 255, 255, 0);
    npSetLED2(3, 255, 255, 0);
    npSetLED2(6, 255, 255, 0);
    npSetLED2(16, 255, 255, 0);
    npSetLED2(13, 255, 255, 0);
    npSetLED2(12, 255, 255, 0);
    npSetLED2(11, 255, 255, 0);
    npSetLED2(23, 255, 255, 0);
    npSetLED2(22, 255, 255, 0);
    npSetLED2(21, 255, 255, 0);
    npWrite2(pio,sm);
    sleep_ms(1000);
}

void desenharCoracao(PIO pio, uint sm)
{
    for (int i = 0; i < 3; i++)
    { // Piscar 3 vezes
        // Desenha o coração
        npClear2();
        npSetLED2(23, 255, 0, 0);
        npSetLED2(21, 255, 0, 0);
        npSetLED2(15, 255, 0, 0);
        npSetLED2(17, 255, 0, 0);
        npSetLED2(19, 255, 0, 0);
        npSetLED2(14, 255, 0, 0);
        npSetLED2(10, 255, 0, 0);
        npSetLED2(6, 255, 0, 0);
        npSetLED2(8, 255, 0, 0);
        npSetLED2(2, 255, 0, 0);
        npSetLED2(16, 255, 102, 204);
        npSetLED2(18, 255, 102, 204);
        npSetLED2(13, 255, 102, 204);
        npSetLED2(12, 255, 102, 204);
        npSetLED2(11, 255, 102, 204);
        npSetLED2(7, 255, 102, 204);
        npWrite2(pio,sm);
        sleep_ms(500); // Coração visível por 500 ms

        // Apaga todos os LEDs
        npClear2();
        npWrite2(pio,sm);
        sleep_ms(200); // Coração apagado por 500 ms
    }
}

// Exibe bandeira arco-íris, linha por linha
void desenharBandeira(PIO pio, uint sm)
{

    uint8_t colors[5][3] = {
        {255, 0, 0},   // Vermelho
        {255, 165, 0}, // Laranja
        {255, 255, 0}, // Amarelo
        {0, 255, 0},   // Verde
        {0, 0, 255}    // Azul
    };

    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            // Calcula o índice e acende os LEDs da linha atual
            npSetLED2(row * 5 + col, colors[row][0], colors[row][1], colors[row][2]);
        }
        npWrite2(pio,sm);     // Atualiza os LEDs da linha atual
        sleep_ms(500); // Espera 500 ms antes de passar para a próxima linha
    }

    sleep_ms(1000); // Mantém a bandeira acesa por 2 segundos
}

// Função para gerar uma onda colorida
void desenharOnda(PIO pio, uint sm)
{
    for (int t = 0; t < LED_COUNT; t++)
    {
        for (int i = 0; i < LED_COUNT; i++)
        {
            uint8_t r = (i + t) % 3 == 0 ? 255 : 0; // Vermelho em padrão cíclico
            uint8_t g = (i + t) % 3 == 1 ? 255 : 0; // Verde em padrão cíclico
            uint8_t b = (i + t) % 3 == 2 ? 255 : 0; // Azul em padrão cíclico
            npSetLED2(i, r, g, b);
        }
        npWrite2(pio,sm);
        sleep_ms(100);
    }
}

// Animação principal
void animar(PIO pio, uint sm)
{
    desenharBandeira(pio,sm);
    desenharLetras(pio,sm);
    desenharCoracao(pio,sm);
    desenharOnda(pio,sm);
    npClear2(pio,sm);
}

void music_thread()
{
    while(1){
        tocar_musica();
    }
}
