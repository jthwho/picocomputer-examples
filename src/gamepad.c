/*
 * Copyright (c) 2023 Rumbledethumps
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * SPDX-License-Identifier: Unlicense
 */

#include <rp6502.h>
#include <stdio.h>
#include <stdint.h>

#define xreg_ria_gamepad(...) xreg(0, 0, 2, __VA_ARGS__)

void main()
{
    const char *dpad[] = {"N ", "NE ", "E ", "SE ", "S ", "SW ", "W ", "NW ", ""};
    uint8_t btns1, btns2, btns3;
    unsigned u;
    xreg_ria_gamepad(0xFF00);

    // Detect if gamepad connected
    // Set dpad to 0xF, which is invalid, and wait for it to change
    RIA.addr0 = 0xFF04;
    RIA.step0 = 0;
    RIA.rw0 = 0xFF;
    printf("Waiting on gamepad.\n");
    while (RIA.rw0 == 0xFF)
        ;

    while (1)
    {
        // Read all the values. Note that you can ignore the analog inputs
        // and any button set you don't care about.
        RIA.addr0 = 0xFF00;
        RIA.step0 = 1;
        printf("lx:%3u ly:%3u rx:%3u ry:%3u ", RIA.rw0, RIA.rw0, RIA.rw0, RIA.rw0);
        btns1 = RIA.rw0;
        btns2 = RIA.rw0;
        btns3 = RIA.rw0;
        printf("l2:%3u r2:%3u ", RIA.rw0, RIA.rw0);

        printf("%s", dpad[btns1 & 0xf]);
        if (btns1 & 0x10)
            printf("Square ");
        if (btns1 & 0x20)
            printf("Cross ");
        if (btns1 & 0x40)
            printf("Circle ");
        if (btns1 & 0x80)
            printf("Triangle ");

        if (btns2 & 0x01)
            printf("L1 ");
        if (btns2 & 0x02)
            printf("R1 ");
        if (btns2 & 0x04)
            printf("L2 ");
        if (btns2 & 0x08)
            printf("R2 ");
        if (btns2 & 0x10)
            printf("Share ");
        if (btns2 & 0x20)
            printf("Option ");
        if (btns2 & 0x40)
            printf("L3 ");
        if (btns2 & 0x80)
            printf("R3 ");

        if (btns3 & 0x01)
            printf("PS ");
        if (btns3 & 0x02)
            printf("Tpad ");

        printf("\n");
    }
}
