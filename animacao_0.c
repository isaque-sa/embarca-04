#include "pico/stdlib.h"
#include "hardware/pio.h"

void animacao_0(uint8_t num_pix, PIO pio, uint sm, uint32_t (* urgb)(uint8_t,uint8_t,uint8_t), void (*put_p)(PIO,uint,uint32_t))
{

#define DELAY 500

    uint8_t frame1_r[25] = {
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,85,0,0,
        0,0,0,0,0,
        0,0,0,0,0
    };

    uint8_t frame1_b[25] = {
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,127,0,0,
        0,0,0,0,0,
        0,0,0,0,0
    };

    uint8_t frame2_r[25] = {
        0,0,0,0,0,
        0,85,85,85,0,
        0,85,0,85,0,
        0,85,85,85,0,
        0,0,0,0,0
    };

    uint8_t frame2_b[25] = {
        0,0,0,0,0,
        0,127,127,127,0,
        0,127,0,127,0,
        0,127,127,127,0,
        0,0,0,0,0
    };

    uint8_t frame3_r[25] = {
        85,85,85,85,85,
        85,0,0,0,85,
        85,0,0,0,85,
        85,0,0,0,85,
        85,85,85,85,85
    };

    uint8_t frame3_b[25] = {
        127,127,127,127,127,
        127,0,0,0,127,
        127,0,0,0,127,
        127,0,0,0,127,
        127,127,127,127,127
    };

    uint8_t frame4_g[25] = {
        127,127,127,127,127,
        127,127,127,127,127,
        127,127,127,127,127,
        127,127,127,127,127,
        127,127,127,127,127
    };

    uint8_t frame4_b[25] = {
        127,127,127,127,127,
        127,127,127,127,127,
        127,127,127,127,127,
        127,127,127,127,127,
        127,127,127,127,127
    };

    uint8_t frame5_g[25] = {
        0,0,0,0,0,
        0,127,127,127,0,
        0,127,127,127,0,
        0,127,127,127,0,
        0,0,0,0,0
    };

    uint8_t frame5_b[25] = {
        0,0,0,0,0,
        0,127,127,127,0,
        0,127,127,127,0,
        0,127,127,127,0,
        0,0,0,0,0
    };

    uint8_t frame6_g[25] = {
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,127,0,0,
        0,0,0,0,0,
        0,0,0,0,0
    };

    uint8_t frame6_b[25] = {
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,127,0,0,
        0,0,0,0,0,
        0,0,0,0,0
    };

    for(int i=0; i<num_pix; i++){
        put_p(pio,sm,urgb(frame1_r[i],0,frame1_b[i]));
    }
    sleep_ms(DELAY);

    for(int i=0; i<num_pix; i++){
        put_p(pio,sm,urgb(frame2_r[i],0,frame2_b[i]));
    }
    sleep_ms(DELAY);

    for(int i=0; i<num_pix; i++){
        put_p(pio,sm,urgb(frame3_r[i],0,frame3_b[i]));
    }
    sleep_ms(DELAY);

    for(int i=0; i<num_pix; i++){
        put_p(pio,sm,urgb(0,frame4_g[i],frame4_b[i]));
    }
    sleep_ms(DELAY);

    for(int i=0; i<num_pix; i++){
        put_p(pio,sm,urgb(0,frame5_g[i],frame5_b[i]));
    }
    sleep_ms(DELAY);

    for(int i=0; i<num_pix; i++){
        put_p(pio,sm,urgb(0,frame6_g[i],frame6_b[i]));
    }
    sleep_ms(DELAY);
}