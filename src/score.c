#include "score.h"

int scorePos;
int scoreCenter;

void DrawScore()
{
    scorePos = LEVEL_WIDTH*BRICK_WIDTH + OUTLINE_WIDTH*2;
    scoreCenter = (GetScreenWidth() - scorePos)/2;

    // SCORE
    DrawT(
        "SCORE",
        scorePos + scoreCenter - MeasureT("SCORE", SCORE_FONTSIZE).x/2,
        150,
        SCORE_FONTSIZE,
        BLUE
    );
    DrawT(
        TextFormat("%06d", player.score),
        scorePos + scoreCenter - MeasureT("000000", SCORE_FONTSIZE).x/2,
        175,
        SCORE_FONTSIZE,
        WHITE
    );

    // HIGH SCORE
    DrawT(
        "HIGH SCORE",
        scorePos + scoreCenter - MeasureT("HIGH SCORE", SCORE_FONTSIZE).x/2,
        250,
        SCORE_FONTSIZE,
        BLUE
    );
    // TODO: handle and display highscore
    DrawT(
        TextFormat("%06d", 50000),
        scorePos + scoreCenter - MeasureT("000000", SCORE_FONTSIZE).x/2,
        275,
        SCORE_FONTSIZE,
        LIGHTGRAY
    );

    // LEVEL
    DrawT(
        "ROUND",
        scorePos + scoreCenter - MeasureT("ROUND", SCORE_FONTSIZE).x/2,
        350,
        SCORE_FONTSIZE,
        PINK
    );
    DrawT(
        TextFormat("%2d", currentLvl.number),
        scorePos + scoreCenter - MeasureT("00", SCORE_FONTSIZE).x/2,
        375,
        SCORE_FONTSIZE,
        WHITE
    );

    if (!TimerDone(&levelBegin)) {
        const char *rnd = TextFormat("ROUND %d", currentLvl.number);
        DrawT(
            rnd,
            scorePos/2 - MeasureT(rnd, SCORE_FONTSIZE).x/2,
            GetScreenHeight() - 200,
            SCORE_FONTSIZE,
            BLUE
        );
    }

    // CREDITS
    DrawT(
        "Programmed by:",
        scorePos + scoreCenter - MeasureT("Programmed by:", SCORE_FONTSIZE/2.f).x/2,
        565,
        SCORE_FONTSIZE/2.f,
        RED
    );
    DrawT(
        "Valentin271",
        scorePos + scoreCenter - MeasureT("Valentin271", SCORE_FONTSIZE/2.f).x/2,
        580,
        SCORE_FONTSIZE/2.f,
        LIGHTGRAY
    );
}

void LoadScore()
{
    char *fileText = LoadFileText(SCORES_FILENAME);
    char *originalText = fileText;

    char *line = strsep(&fileText, "\n");

    score_t *scores = NULL;
    uint size = 0;

    while (line) {
        scores = reallocarray(scores, size + 1, sizeof(score_t));

        scores[size] = (score_t) {
            .player_name = strsep(&line, ","),
            .round = (ushort) strtoul(strsep(&line, ","), NULL, 10),
            .score = (uint) strtoul(strsep(&line, ","), NULL, 10)
        };

        line = strsep(&fileText, "\n");
        ++size;
    }

    free(scores);
    UnloadFileText(originalText);
}

void SortScore()
{
    // qsort();
}

void WriteScore()
{
    SaveFileText(SCORES_FILENAME, "");
}