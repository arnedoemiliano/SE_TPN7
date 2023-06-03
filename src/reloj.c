/************************************************************************************************
Copyright (c) 2023, Emiliano Arnedo <emiarnedo@gmail.com>
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
SPDX-License-Identifier: MIT
*************************************************************************************************/

/* === Headers files inclusions =============================================================== */

#include "reloj.h"
#include <string.h>

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */

typedef struct reloj_s {

    uint8_t hora_actual[6];
    bool hora_valida : 1;

} reloj_s;

/* === Private variable declarations =========================================================== */

// uint8_t hora_actual[] = {0};

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================== */

reloj_t ClockCreate(int ticks_por_segundo) {

    static reloj_s self[1];
    memset(self, 0, sizeof(self));
    return self;
}

bool GetClockTime(reloj_t reloj, uint8_t * hora, int size) {

    // memset(hora, 0, size);
    memcpy(hora, reloj->hora_actual, size);

    return reloj->hora_valida;
}

bool SetClockTime(reloj_t reloj, const uint8_t * hora_nueva, int size) {

    memcpy(reloj->hora_actual, hora_nueva, size);
    reloj->hora_valida = true; // indica que la hora actual del reloj es válida

    return true; // hace falta retornar una confirmacion?
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */