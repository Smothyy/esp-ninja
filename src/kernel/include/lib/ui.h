#ifndef LIB_UI_H
#define LIB_UI_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <drivers/screen.h>

// colors
#define TFT_GREY1     0x2985
#define TFT_GREY2     0x18c3
#define TFT_GREY3     0x9492
#define TFT_DARKGREY1 0x0861

#define BOOT_LVL_OK     0
#define BOOT_LVL_FAILED 1
#define BOOT_LVL_INFO   2

typedef struct grid_t
{
    uint32_t blk_width;
    uint32_t blk_height;
    uint32_t blks_y;
    uint32_t blks_x;
} grid_t;

typedef struct widget_t
{

} widget_t;

void navbar();
void statusbar();

// Bootlogging
void bootlog(const char *log, uint8_t lvl);
void bootlogf(uint8_t l, const char *format, ...);

#endif
