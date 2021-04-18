#include "pm.h"
#include <stdint.h>

#include "tiles.h"
#include "sprites.h"
#include "misc.h"

volatile enum State state = STATE_NORMAL;
extern const int8_t sin_table[];
extern uint8_t sin_table_offset;

enum Board_type { BOARD_EMPTY = 0, BOARD_CORNER_RD, BOARD_CORNER_RU, BOARD_CORNER_LD, BOARD_CORNER_LU, BOARD_EDGE_H, BOARD_EDGE_V };

const _rom uint8_t try_again[] = {
    19, 43, 50, 0xBF,
    26, 32, 26, 34, 39, 0x42, 0x42, 0x42
};

const _rom uint8_t flag_data[] = {
    15, 57, 42, 9, 53, 58, 0, 59, 51, 10, 33, 3, 58, 58, 17, 12, 60, 60, 13, 60, 13, 0, 9, 54
};

#define NUM_B 7
const _rom uint8_t black_pearl[] = {
    0, 0,
    2, 0,
    6, 2,
    2, 6,
    7, 6,
    1, 7,
    8, 7,
};

#define NUM_W 14
const _rom uint8_t white_pearl[] = {
    4, 0,
    0, 3,
    3, 3,
    4, 3,
    2, 4,
    7, 4,
    8, 4,
    3, 5,
    5, 5,
    6, 5,
    3, 8,
    4, 8,
    3, 9,
    6, 9,
};

uint8_t flag[24] = {0};
uint8_t loop[46] = {0};
uint8_t board[100] = {0};

enum State check_flag(void) {
    uint8_t i, j;
    uint8_t firstindex, curx, cury, index;

    // check flag
    for (i = 0; i < 12; i++) {
        flag[i] = TILEMAP[16*3+i];
        flag[i+12] = TILEMAP[16*5+i];
    }

    for (i = 0; i < 24; i++) {
        flag[i] ^= flag_data[i];
    }

    // decode into masyu coords
    // big endian base 64 -> little endian base 10
    // x1, y1, x2, y2, ...
    // (x1,y1) -- (x2,y1) -- (x2,y2) -- ...
    for (i = 0; i < 42; i++) {
        uint16_t accum = 0;
        for (j = 0; j < 24; j++) {
            accum = accum*64 + flag[j];
            flag[j] = accum/10;
            accum = accum%10;
        }
        loop[i] = accum;
    }

    // check for no remainder
    for (i = 0; i < 24; i++) {
        if (flag[i]) {
            return STATE_WRONG;
        }
    }

    // debug: print out digits
    /*
    for (i = 0; i < 42; i++) {
        uint8_t x = i % 12;
        uint8_t y = 3 + (i / 12);
        TILEMAP[16*y+x] = 52 + loop[i];
    }
    */

    // wrap so no special cases in later checks
    // loop starts at loop[2]
    for (i = 0; i < 4; i++) {
        loop[42+i] = loop[i];
    }

    // check loop starts with upper-left corner
    firstindex = loop[2]*10 + loop[3];
    curx = loop[0];
    cury = loop[1];
    for (i = 2; i < 44; i += 2) {
        curx = loop[i];
        if (cury*10 + curx < firstindex) {
            return STATE_WRONG;
        }
        cury = loop[i+1];
        if (cury*10 + curx < firstindex) {
            return STATE_WRONG;
        }
    }

    // check that corners are 90 degree corners
    for (i = 2; i < 44; i += 2) {
        if (loop[i] == loop[i+2] || loop[i+1] == loop[i+3]) {
            return STATE_WRONG;
        }
    }

    // draw loop on board
    // also check loop doesn't intersect itself
    for (i = 2; i < 44; i += 2) {
        // (i, i-1) --v-> (i, i+1) --h-> (i+2, i+1)
        index = loop[i+1]*10 + loop[i];
        if (board[index] != BOARD_EMPTY) {
            return STATE_WRONG;
        }
        if (loop[i] < loop[i+2]) {
            // right
            if (loop[i-1] < loop[i+1]) {
                // up
                board[index] = BOARD_CORNER_RU;
            } else {
                // down
                board[index] = BOARD_CORNER_RD;
            }
            for (j = 1; j < loop[i+2]-loop[i]; j++) {
                if (board[index+j] != BOARD_EMPTY) {
                    return STATE_WRONG;
                }
                board[index+j] = BOARD_EDGE_H;
            }
        } else {
            // left
            if (loop[i-1] < loop[i+1]) {
                // up
                board[index] = BOARD_CORNER_LU;
            } else {
                // down
                board[index] = BOARD_CORNER_LD;
            }
            for (j = 1; j < loop[i]-loop[i+2]; j++) {
                if (board[index-j] != BOARD_EMPTY) {
                    return STATE_WRONG;
                }
                board[index-j] = BOARD_EDGE_H;
            }
        }

        // (i, i+1) --h-> (i+2, i+1) --v-> (i+2, i+3)
        index = loop[i+1]*10 + loop[i+2];
        if (board[index] != BOARD_EMPTY) {
            return STATE_WRONG;
        }
        if (loop[i+1] < loop[i+3]) {
            // down
            if (loop[i] < loop[i+2]) {
                // left
                board[index] = BOARD_CORNER_LD;
            } else {
                // right
                board[index] = BOARD_CORNER_RD;
            }
            for (j = 1; j < loop[i+3]-loop[i+1]; j++) {
                if (board[index+10*j] != BOARD_EMPTY) {
                    return STATE_WRONG;
                }
                board[index+10*j] = BOARD_EDGE_V;
            }
        } else {
            // up
            if (loop[i] < loop[i+2]) {
                // left
                board[index] = BOARD_CORNER_LU;
            } else {
                // right
                board[index] = BOARD_CORNER_RU;
            }
            for (j = 1; j < loop[i+1]-loop[i+3]; j++) {
                if (board[index-10*j] != BOARD_EMPTY) {
                    return STATE_WRONG;
                }
                board[index-10*j] = BOARD_EDGE_V;
            }
        }
    }

    // masyu black pearls
    for (i = 0; i < NUM_B; i++) {
        index = black_pearl[2*i] + 10*black_pearl[2*i+1];
        switch (board[index]) {
            case BOARD_CORNER_RD:
                if (board[index+1] != BOARD_EDGE_H && board[index+1] != BOARD_EDGE_V) {
                    return STATE_WRONG;
                }
                if (board[index+10] != BOARD_EDGE_H && board[index+10] != BOARD_EDGE_V) {
                    return STATE_WRONG;
                }
                break;
            case BOARD_CORNER_RU:
                if (board[index+1] != BOARD_EDGE_H && board[index+1] != BOARD_EDGE_V) {
                    return STATE_WRONG;
                }
                if (board[index-10] != BOARD_EDGE_H && board[index-10] != BOARD_EDGE_V) {
                    return STATE_WRONG;
                }
                break;
            case BOARD_CORNER_LD:
                if (board[index-1] != BOARD_EDGE_H && board[index-1] != BOARD_EDGE_V) {
                    return STATE_WRONG;
                }
                if (board[index+10] != BOARD_EDGE_H && board[index+10] != BOARD_EDGE_V) {
                    return STATE_WRONG;
                }
                break;
            case BOARD_CORNER_LU:
                if (board[index-1] != BOARD_EDGE_H && board[index-1] != BOARD_EDGE_V) {
                    return STATE_WRONG;
                }
                if (board[index-10] != BOARD_EDGE_H && board[index-10] != BOARD_EDGE_V) {
                    return STATE_WRONG;
                }
                break;
            default:
                return STATE_WRONG;
                break;
        }
    }

    // masyu white pearls
    for (i = 0; i < NUM_W; i++) {
        index = white_pearl[2*i] + 10*white_pearl[2*i+1];
        switch (board[index]) {
            case BOARD_EDGE_H:
                if (board[index+1] == BOARD_EDGE_H && board[index-1] == BOARD_EDGE_H) {
                    return STATE_WRONG;
                }
                break;
            case BOARD_EDGE_V:
                if (board[index+10] == BOARD_EDGE_V && board[index-10] == BOARD_EDGE_V) {
                    return STATE_WRONG;
                }
                break;
            default:
                return STATE_WRONG;
                break;
        }
    }

    return STATE_CORRECT;
}

int main(void) {
    uint8_t i, j;
    uint8_t furret_frame = 0;
    uint16_t fail_counter = 0;

    PRC_MODE = COPY_ENABLE|SPRITE_ENABLE|MAP_ENABLE|MAP_16X12;
    PRC_RATE = RATE_36FPS;

    PRC_MAP = tiles;
    PRC_SPR = sprites;

    for (i = 0; i < 16*12; i++) {
        TILEMAP[i] = 0xBF; // blank
    }

    TILEMAP[16*2+0] = 0x40;
    TILEMAP[16*4+0] = 0x41;
    for (i = 0; i < 12; i++) {
        TILEMAP[16*3+i] = 0;
        TILEMAP[16*5+i] = 0;
    }

    for (i = 0; i < 10; i++) {
        OAM[i].x = 24+8*i;
        OAM[i].tile = i;
        OAM[i].ctrl |= OAM_ENABLE;
    }

    TMR1_OSC = 0x30; // Enable Oscillator 1, Oscillator 2, use oscillator 1 (2000000 Hz)
    TMR1_SCALE = 0x08 | 0x03; // enable timer, scale 3: 62500 Hz
    TMR1_CTRL = 0x04 | 0x02; // TMR_ENABLE | TMR_PRESET

    TMR3_OSC = 0; // Oscillator 1 (2000000 Hz)
    TMR3_SCALE = 0x08; // enable timer, scale 0: 2000000 Hz
    TMR3_CTRL_L = 0x80 | 0x04 | 0x02; // TMR_16BITS | TMR_ENABLE | TMR_PRESET
    AUD_VOL = 0x03; // 100% volume 

    // enable prc complete irq: used for animating the "ENTER FLAG" so flag checking doesn't freeze animation
    PRI_PRC(3);
    IRQ_ENA1 |= IRQ1_PRC_COMPLETE;

    // enable timer 1 irq: used to control music
    PRI_TIM1(2);
    IRQ_ENA1 |= IRQ1_TIM1_LO_UF;

    // enable timer 3 irq: used to output music
    PRI_TIM3(1);
    IRQ_ENA1 |= IRQ1_TIM3_HI_UF;

    // enable key irqs
    PRI_KEY(1);
    IRQ_ENA3 |= IRQ3_KEYA | IRQ3_KEYUP | IRQ3_KEYDOWN | IRQ3_KEYLEFT | IRQ3_KEYRIGHT;

    // wait for KEY A irq to change state
    while (state != STATE_CHECK) {}

    for (i = 0; i < 12; i++) {
        // clear cursors
        TILEMAP[16*2+i] = 0xBF;
        TILEMAP[16*4+i] = 0xBF;
        TILEMAP[16*6+i] = 0xBF;
    }

    state = check_flag();

    // disable prc complete irq, since it slows down music
    IRQ_ENA1 &= ~IRQ1_PRC_COMPLETE;

    if (state == STATE_CORRECT) {
        // enable furret
        for (i = 0; i < 15; i++) {
            OAM[i].x = 30 + 16*(i/3);
            OAM[i].y = 24 + 16*(i%3);
            OAM[i].tile = i+18;
            OAM[i].ctrl |= OAM_ENABLE;
        }
        for (i = 0; i < 8; i++) {
            OAM[i+16].x = 27+8*(i+1);
            OAM[i+16].tile = i+10;
            OAM[i+16].ctrl |= OAM_ENABLE;
        }
        for(;;) {
            // drawing furret
            for (i = 16; i < 24; i++) {
                OAM[i].y = 19 + sin_table[(uint8_t)(sin_table_offset + (i << 5))];
            }
            for (i = 0; i < 15; i++) {
                OAM[i].x--;
                OAM[i].tile = i+18+15*((furret_frame >> 1) & 7);
            }
            furret_frame++;
            sin_table_offset += 8;
            wait_vsync();
        }
    } else {
        for(;;) {
            // drawing "try again..."
            for (i = 0; i < 10; i++) {
                OAM[i].y = 19 + sin_table[(uint8_t)(sin_table_offset + (i << 5))];
            }
            if (fail_counter < 0xC0) {
                if (!(fail_counter & 0xF)) {
                    TILEMAP[16*7+(fail_counter >> 4)] = try_again[fail_counter >> 4];
                }
                fail_counter++;
            }
            sin_table_offset += 8;
            wait_vsync();
        }
    }
}
