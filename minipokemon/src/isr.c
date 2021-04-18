#include "pm.h"
#include <stdint.h>

#include "music.h"
#include "misc.h"

const _rom char game_code[4] _at(0x21AC) = "MPKM";
const _rom char game_title[12] _at(0x21B0) = "minipokemon";

const int8_t sin_table[] = {
    0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -2,
    -2, -2, -2, -2, -2, -2, -2, -2, -3, -3, -3, -3, -3, -3, -3, -3,
    -3, -3, -3, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4,
    -4, -4, -4, -4, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5,
    -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -4, -4, -4,
    -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -3, -3,
    -3, -3, -3, -3, -3, -3, -3, -3, -3, -2, -2, -2, -2, -2, -2, -2,
    -2, -2, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0
};

extern enum State state;

// i hope stack vars don't interfere with PUSH/POP ALE...

// music
volatile uint16_t music_tick = 0;
//volatile uint8_t making_noise = 0;
//volatile uint16_t noise = 1;
volatile uint8_t vibrato_counter = 0;
volatile uint8_t is_vibrato = 0;
volatile uint16_t preset, note;

// graphics
volatile uint8_t sin_table_offset = 0;
volatile uint8_t cursor = 0;

void _interrupt(0) prc_frame_copy_irq(void) {
    #pragma asm
        PUSH ALE
    #pragma endasm
    uint8_t i;
    // draw "ENTER FLAG"
    for (i = 0; i < 10; i++) {
        OAM[i].y = 19 + sin_table[(uint8_t)(sin_table_offset + (i << 5))];
    }
    sin_table_offset += 8;
    IRQ_ACT1 = IRQ1_PRC_COMPLETE;
    #pragma asm
        POP ALE
    #pragma endasm
}
void _interrupt(0) prc_render_irq(void) {
    _slp();
}
void _interrupt(0) timer_2h_underflow_irq(void) {
    _slp();
}
void _interrupt(0) timer_2l_underflow_irq(void) {
    _slp();
}
void _interrupt(0) timer_1h_underflow_irq(void) {
    _slp();
}
void _interrupt(0) timer_1l_underflow_irq(void) {
    #pragma asm
        PUSH ALE
    #pragma endasm
    music_tick++;
    if (music_tick >= 6144) {
        music_tick = 0;
    }
    note = song[music_tick];
    if (note == M_STOP) {
        AUD_VOL = 0;

        /*making_noise = 0;
        TMR3_PRE = 8000;
        TMR3_PVT = 0;
    } else if (note & M_NOISE) {
        AUD_VOL = 0x03;
        making_noise = 1;
        TMR3_PRE = 100; // if too short, will hang*/

    } else if (note != 0) {
        if (note & M_HALF_VOLUME) {
            AUD_VOL = 0x01;
        } else {
            AUD_VOL = 0x03;
        }
        if (note & M_VIBRATO) {
            is_vibrato = 1;
            vibrato_counter = 0;
        } else {
            is_vibrato = 0;
        }
        //making_noise = 0;
        preset = presets[note & 127];
        TMR3_PRE = preset;
        if (note & M_QUARTER_DUTY) {
            TMR3_PVT = preset >> 2;
        } else {
            TMR3_PVT = preset >> 1;
        }
    }
    IRQ_ACT1 = IRQ1_TIM1_LO_UF;
    #pragma asm
        POP ALE
    #pragma endasm
}
void _interrupt(0) timer_3h_underflow_irq(void) {
    #pragma asm
        PUSH ALE
    #pragma endasm
    /*
    // NES-style LFSR noise (period 63457)
    if (making_noise) {
        // noise = (noise >> 1) | (((noise ^ (noise >> 7)) & 1) << 15);
        #pragma asm
            LD A, [_noise]
            LD B, A
            RLC A
            XOR A, B
            EX A, B
            RR B
            LD B, [_noise+1]
            RR B
            RR A
            LD [_noise], BA
            JRS C, noise_one
        noise_zero:
            LD BA, #0000h
            JRS noise_end
        noise_one:
            LD BA, [204Ah]
        noise_end:
            LD [204Ch], BA
        #pragma endasm
    }
    */
    if (is_vibrato) {
        vibrato_counter++;
        TMR3_PRE += vibrato_table[vibrato_counter];
    }
    IRQ_ACT1 = IRQ1_TIM3_HI_UF;
    #pragma asm
        POP ALE
    #pragma endasm
}
void _interrupt(0) timer_3_cmp_irq(void) {
    _slp();
}
void _interrupt(0) timer_32hz_irq(void) {
    _slp();
}
void _interrupt(0) timer_8hz_irq(void) {
    _slp();
}
void _interrupt(0) timer_2hz_irq(void) {
    _slp();
}
void _interrupt(0) timer_1hz_irq(void) {
    _slp();
}
void _interrupt(0) ir_rx_irq(void) {
    _slp();
}
void _interrupt(0) shake_irq(void) {
    _slp();
}
void _interrupt(0) key_power_irq(void) {
    IRQ_ACT3 = IRQ3_KEYPOWER;
    if (KEY_PAD & KEY_POWER) return;
    _int(0x48);
}
void _interrupt(0) key_right_irq(void) {
    #pragma asm
        PUSH ALE
    #pragma endasm
    uint8_t tmp;
    if (cursor < 23) {
        tmp = cursor;
        if (tmp >= 12) {
            tmp += 20;
        }
        TILEMAP[16*2+tmp] = 0xBF;
        TILEMAP[16*4+tmp] = 0xBF;
        cursor++;
        tmp = cursor;
        if (tmp >= 12) {
            tmp += 20;
        }
        TILEMAP[16*2+tmp] = 0x40;
        TILEMAP[16*4+tmp] = 0x41;
    }
    IRQ_ACT3 = IRQ3_KEYRIGHT;
    #pragma asm
        POP ALE
    #pragma endasm
}
void _interrupt(0) key_left_irq(void) {
    #pragma asm
        PUSH ALE
    #pragma endasm
    uint8_t tmp;
    if (cursor > 0) {
        tmp = cursor;
        if (tmp >= 12) {
            tmp += 20;
        }
        TILEMAP[16*2+tmp] = 0xBF;
        TILEMAP[16*4+tmp] = 0xBF;
        cursor--;
        tmp = cursor;
        if (tmp >= 12) {
            tmp += 20;
        }
        TILEMAP[16*2+tmp] = 0x40;
        TILEMAP[16*4+tmp] = 0x41;
    }
    IRQ_ACT3 = IRQ3_KEYLEFT;
    #pragma asm
        POP ALE
    #pragma endasm
}
void _interrupt(0) key_down_irq(void) {
    #pragma asm
        PUSH ALE
    #pragma endasm
    uint8_t tmp;
    tmp = cursor;
    if (tmp >= 12) {
        tmp += 20;
    }
    TILEMAP[16*3+tmp] = (TILEMAP[16*3+tmp] - 1) & 0x3F;
    IRQ_ACT3 = IRQ3_KEYDOWN;
    #pragma asm
        POP ALE
    #pragma endasm
}
void _interrupt(0) key_up_irq(void) {
    #pragma asm
        PUSH ALE
    #pragma endasm
    uint8_t tmp;
    tmp = cursor;
    if (tmp >= 12) {
        tmp += 20;
    }
    TILEMAP[16*3+tmp] = (TILEMAP[16*3+tmp] + 1) & 0x3F;
    IRQ_ACT3 = IRQ3_KEYUP;
    #pragma asm
        POP ALE
    #pragma endasm
}
void _interrupt(0) key_c_irq(void) {
    _slp();
}
void _interrupt(0) key_b_irq(void) {
    _slp();
}
void _interrupt(0) key_a_irq(void) {
    #pragma asm
        PUSH ALE
    #pragma endasm
    state = STATE_CHECK;
    // disable all keys
    IRQ_ENA3 &= ~IRQ3_KEYA;
    IRQ_ENA3 &= ~IRQ3_KEYUP;
    IRQ_ENA3 &= ~IRQ3_KEYDOWN;
    IRQ_ENA3 &= ~IRQ3_KEYLEFT;
    IRQ_ENA3 &= ~IRQ3_KEYRIGHT;
    IRQ_ACT3 = IRQ3_KEYA;
    #pragma asm
        POP ALE
    #pragma endasm
}
void _interrupt(0) unknown_irq(void) {
    _slp();
}
void _interrupt(0) cartridge_irq(void) {
    _slp();
}

void _exit(int i)
{
    _int(0x48);
}
