#include "brick.h"


Color brickColor(const brick *brk)
{
    switch (brk->code) {
        case BRICK_CYAN:
            return CYAN;
        case BRICK_RED:
            return RED;
        case BRICK_VIOLET:
            return MAGENTA;
        case BRICK_WHITE:
            return WHITE;
        case BRICK_GREEN:
            return GREEN;
        case BRICK_BLUE:
            return BLUE;
        case BRICK_YELLOW:
            return YELLOW;
        case BRICK_SILVER:
            return GRAY;
        case BRICK_GOLD:
            return GOLD;
        default:
            return BLANK;
    }
}

unsigned int brickPoints(const brick *brk)
{
    switch (brk->code) {
        case BRICK_CYAN:
            return 70;
        case BRICK_RED:
            return 80;
        case BRICK_VIOLET:
            return 90;
        case BRICK_WHITE:
            return 100;
        case BRICK_GREEN:
            return 110;
        case BRICK_BLUE:
            return 120;
        case BRICK_YELLOW:
            return 130;
        case BRICK_SILVER:
            return 100;
        default:
            return 0;
    }
}

