#include <Arduino.h>
#include <drivers/led.h>
#include <drivers/screen.h>
#include <drivers/touch.h>
#include <kernel/mm.h>
#include <kernel/packages.h>
#include <lib/ui.h>

void boot()
{
    bool boot_failed = false;
    bootlog("Initializing screen...", screen_init());
    bootlog("Initializing touch...", touch_init());
    bootlog("Failed test...", BOOT_LVL_FAILED);

#ifdef LED_RGB
    bootlog("Initializing RGB LED...", led_init());
    bootlog("RGB LED blinking test!", BOOT_LVL_INFO);
    blink(3, 1, 1, 1);
#else
    bootlog("Initializing Generic LED...", led_init());
#endif
    bootlog("Creating GUI structs.....", BOOT_LVL_OK);
    // bootlog("Starting Apps subsystem...", apps_init());
    // bootlog("Load system apps.", apps_system());
    // bootlog("Load user apps.", apps_user());
    // if (apps_loaded() != 0)
    // {
    //     char buff[64];
    //     sprintf(buff, "Loaded: %d apps", apps_loaded());
    //     bootlog(buff, BOOT_LVL_OK);
    // }
    // else
    // {
    //     boot_failed = true;
    //     bootlog("Loaded: 0 apps (Check it)", BOOT_LVL_FAILED);
    // }
    bootlogf(BOOT_LVL_INFO, "Free heap: %lu KB", mem_free_get_kb());
    bootlogf(BOOT_LVL_INFO, "Kernel Version: %d.%d.%d", KERNEL_MAJOR, KERNEL_MINOR, KERNEL_PATCH);
    bootlogf(BOOT_LVL_INFO, "Packages Build: %d", PACKAGES_BUILD);

    bootlog("!!!Welcome to ESP-Ninja!!!", BOOT_LVL_INFO);

    if (boot_failed)
    {
        bootlog("Check log", BOOT_LVL_FAILED);
        bootlog("CLICK TO CONTINUE!", BOOT_LVL_FAILED);
    }

    for (uint8_t i = 0; i < 20; i++)
    {
        if (touch_touched())
            i--;
        if (boot_failed)
            i--;
        if (boot_failed && touch_touched())
            break;

        delay(100);
    }
    // timely dissabled
    // Simple executor
    // for (int i = 1; i < apps->count + 1; i++)
    // {
    //     if (apps->list[i].app_name == "Main")
    //     {
    //         apps->list[i].entry(NULL);
    //         break;
    //     }
    // }
    // // if Main app not found
    // bootlog("Started App NOT FOUND!", BOOT_LVL_FAILED);
    screen_clear();
}
