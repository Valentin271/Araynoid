#include "level.h"


void LoadLevel(unsigned short number)
{
    level lvl = {number};
    char lvlPath[30];
    int c, x = 0, y = 0;
    FILE *fd;

    sprintf(lvlPath, "resources/levels/level%02d", number);

    TraceLog(LOG_INFO, "LEVEL: %s loaded", lvlPath);

    fd = fopen(lvlPath, "r");

    while ((c = fgetc(fd)) != EOF) {
        switch (c) {
            case BRICK_CYAN:
                lvl.data[x][y] = (brick) {
                        BRICK_CYAN,
                        1,
                };
                x++;
                break;
            case BRICK_RED:
                lvl.data[x][y] = (brick) {
                        BRICK_RED,
                        1,
                };
                x++;
                break;
            case BRICK_VIOLET:
                lvl.data[x][y] = (brick) {
                        BRICK_VIOLET,
                        1,
                };
                x++;
                break;
            case BRICK_WHITE:
                lvl.data[x][y] = (brick) {
                        BRICK_WHITE,
                        1,
                };
                x++;
                break;
            case BRICK_GREEN:
                lvl.data[x][y] = (brick) {
                        BRICK_GREEN,
                        1,
                };
                x++;
                break;
            case BRICK_BLUE:
                lvl.data[x][y] = (brick) {
                        BRICK_BLUE,
                        1,
                };
                x++;
                break;
            case BRICK_YELLOW:
                lvl.data[x][y] = (brick) {
                        BRICK_YELLOW,
                        1,
                };
                x++;
                break;
            case BRICK_SILVER:
                lvl.data[x][y] = (brick) {
                        BRICK_SILVER,
                        2 + truncf(number/8.0f),
                };
                x++;
                break;
            case BRICK_GOLD:
                lvl.data[x][y] = (brick) {
                        BRICK_GOLD,
                        BRICK_UNBREAKABLE,
                };
                x++;
                break;
            case BRICK_NONE:
                lvl.data[x][y] = (brick) {
                        BRICK_NONE,
                        BRICK_TRANSPARENT,
                };
                x++;
                break;
            default:
                y++;
                x = 0;
                break;
        }
    }

    fclose(fd);

    currentLvl = lvl;
    InitBonus();
}

void UpdateLevel()
{
    // TODO: Do not check collision for every brick / every side

    brick *brk = NULL;
    short sideBrickHits;
    Rectangle rect;
    RECT_SIDE hitSides;
    RECT_SIDE visibleSides;

    for (int y = 0; y < LEVEL_HEIGHT; ++y) {
        for (int x = 0; x < LEVEL_WIDTH; ++x) {
            brk = &currentLvl.data[x][y];

            // skip destroyed or no brick
            if (brk->hitsLeft == BRICK_DESTROYED || brk->hitsLeft == BRICK_TRANSPARENT) continue;

            // brick rect
            rect = (Rectangle) {x*BRICK_WIDTH + OUTLINE_WIDTH, y*BRICK_HEIGHT + TOP_OFFSET, BRICK_WIDTH, BRICK_HEIGHT};
            visibleSides = RECT_SIDE_NONE;

            if (x - 1 >= 0) {
                sideBrickHits = currentLvl.data[x - 1][y].hitsLeft;
                if (sideBrickHits <= 0 && sideBrickHits != BRICK_UNBREAKABLE) {
                    visibleSides |= RECT_SIDE_LEFT;
                }
            } else {
                visibleSides |= RECT_SIDE_LEFT;
            }

            if (y - 1 >= 0) {
                sideBrickHits = currentLvl.data[x][y - 1].hitsLeft;
                if (sideBrickHits <= 0 && sideBrickHits != BRICK_UNBREAKABLE) {
                    visibleSides |= RECT_SIDE_TOP;
                }
            } else {
                visibleSides |= RECT_SIDE_TOP;
            }

            if (x + 1 < LEVEL_WIDTH) {
                sideBrickHits = currentLvl.data[x + 1][y].hitsLeft;
                if (sideBrickHits <= 0 && sideBrickHits != BRICK_UNBREAKABLE) {
                    visibleSides |= RECT_SIDE_RIGHT;
                }
            } else {
                visibleSides |= RECT_SIDE_RIGHT;
            }

            if (y + 1 < LEVEL_HEIGHT) {
                sideBrickHits = currentLvl.data[x][y + 1].hitsLeft;
                if (sideBrickHits <= 0 && sideBrickHits != BRICK_UNBREAKABLE) {
                    visibleSides |= RECT_SIDE_BOTTOM;
                }
            } else {
                visibleSides |= RECT_SIDE_BOTTOM;
            }

            hitSides = CheckCollisionRectSideCircle(rect, visibleSides, ball.position, BALL_RADIUS);

            if (brk->hitsLeft != BRICK_UNBREAKABLE && hitSides != RECT_SIDE_NONE) {
                if (--brk->hitsLeft == 0) {
                    player.score += brickPoints(brk);
                    DestroyedBrickBonus(rect.x, rect.y);
                }
            }

            switch (hitSides) {
                case RECT_SIDE_BOTTOM:
                    ball.speed.y = fabsf(ball.speed.y);
                    ball.position.y = rect.y + rect.height + BALL_RADIUS;
                    return;
                case RECT_SIDE_TOP:
                    ball.speed.y = -fabsf(ball.speed.y);
                    ball.position.y = rect.y - BALL_RADIUS;
                    return;
                case RECT_SIDE_LEFT:
                    ball.speed.x = -fabsf(ball.speed.x);
                    ball.position.x = rect.x - BALL_RADIUS;
                    return;
                case RECT_SIDE_RIGHT:
                    ball.speed.x = fabsf(ball.speed.x);
                    ball.position.x = rect.x + rect.width + BALL_RADIUS;
                    return;
                case RECT_SIDE_NONE:
                default:
                    break;
            }
        }
    }
}

void DrawLevel()
{
    brick brk;
    Rectangle rect;

    for (int y = 0; y < LEVEL_HEIGHT; ++y) {
        for (int x = 0; x < LEVEL_WIDTH; ++x) {
            brk = currentLvl.data[x][y];

            if (brk.hitsLeft == BRICK_DESTROYED || brk.hitsLeft == BRICK_TRANSPARENT) continue;

            rect = (Rectangle) {
                    x*BRICK_WIDTH + OUTLINE_WIDTH + 1,
                    y*BRICK_HEIGHT + TOP_OFFSET + 1,
                    BRICK_WIDTH - 2,
                    BRICK_HEIGHT - 2
            };

            DrawRectangleRec(rect, brickColor(&brk));

#ifdef DEBUG
            if (brk.code == BRICK_SILVER) {
                DrawT(
                        TextFormat("%d", brk.hitsLeft),
                        x*BRICK_WIDTH + OUTLINE_WIDTH + 1,
                        y*BRICK_HEIGHT + TOP_OFFSET + 1,
                        8,
                        YELLOW
                );
            }
#endif
        }
    }
}

bool IsLevelCleared()
{
    for (int y = 0; y < LEVEL_HEIGHT; ++y) {
        for (int x = 0; x < LEVEL_WIDTH; ++x) {
            if (currentLvl.data[x][y].hitsLeft > 0) {
                return false;
            }
        }
    }

    return true;
}