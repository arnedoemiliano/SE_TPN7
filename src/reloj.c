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

//

typedef struct reloj_s {

    uint8_t hora_actual[6];
    bool hora_valida : 1;
    int ticks; // cantidad de interrupciones antes de aumentar un segundo
    int tick_actual;
    /***********************/
    uint8_t alarma[4];
    bool alarma_habilitada : 1;
    callback_disparar disparar_alarma;

} reloj_s;
/* === Private variable declarations =========================================================== */

// uint8_t hora_actual[] = {0};

/* === Private function declarations =========================================================== */
void NuevoSegundo(reloj_t reloj);
/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */
void NuevoSegundo(reloj_t reloj) {

    reloj->hora_actual[5]++; // incrementa en 1 los segundos
                             // false: si se superaron las 10 horas

    if (reloj->hora_actual[5] == 10) {
        reloj->hora_actual[5] = 0;
        reloj->hora_actual[4]++; // incrementan las decenas de segundos
        if (reloj->hora_actual[4] == 6) {
            reloj->hora_actual[4] = 0;
            reloj->hora_actual[3]++; // incrementan los minutos
            if (reloj->hora_actual[3] == 10) {
                reloj->hora_actual[3] = 0;
                reloj->hora_actual[2]++; // incrementan las decenas de minutos
                if (reloj->hora_actual[2] == 6) {
                    reloj->hora_actual[2] = 0;
                    reloj->hora_actual[1]++; // incrementan las horas
                    if (reloj->hora_actual[1] == 10 && reloj->hora_actual[0] < 2) {
                        reloj->hora_actual[1] = 0;
                        reloj->hora_actual[0]++; // incrementan las decenas
                    } else if (reloj->hora_actual[1] == 4 && reloj->hora_actual[0] == 2) {
                        reloj->hora_actual[1] = 0;
                        reloj->hora_actual[0] = 0;
                    }
                }
            }
        }
    }
}
/* === Public function implementation ========================================================== */

reloj_t ClockCreate(int ticks_por_segundo, callback_disparar funcion_de_disparo) {

    static reloj_s self[1];
    memset(self, 0, sizeof(self));
    self->ticks = ticks_por_segundo;
    self->disparar_alarma = funcion_de_disparo;
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
// En principio esta funcion es la que llama el systick en cada interrupcion
void RelojNuevoTick(reloj_t reloj) {

    if (reloj->tick_actual + 1 >= reloj->ticks) {
        NuevoSegundo(reloj);
        VerificarAlarma(reloj);
        reloj->tick_actual = 0;
    } else {
        reloj->tick_actual++;
    }
}

bool SetAlarmTime(reloj_t reloj, const uint8_t * alarma) {

    memcpy(reloj->alarma, alarma, 4);
    reloj->alarma_habilitada = true;
    return true;
}

bool GetAlarmTime(reloj_t reloj, uint8_t * alarma) {

    memcpy(alarma, reloj->alarma, 4);
    return reloj->alarma_habilitada;
}

void VerificarAlarma(reloj_t reloj) {

    if ((memcmp(reloj->hora_actual, reloj->alarma, sizeof(reloj->alarma)) == 0) &&
        (reloj->hora_valida) && (reloj->alarma_habilitada)) {
        reloj->disparar_alarma(reloj, true);
    }
}

void DeshabilitarAlarma(reloj_t reloj) {
    reloj->alarma_habilitada = false;
}

void PosponerAlarma(reloj_t reloj, uint8_t minutos) {

    uint16_t snooze_seg = 60 * minutos;
    uint32_t tiempo_actual_seg = (reloj->alarma[0] * 10 * 3600) + (reloj->alarma[1] * 3600) +
                                 (reloj->alarma[2] * 10 * 60) + (reloj->alarma[3] * 60);
    uint32_t nuevo_tiempo_seg = snooze_seg + tiempo_actual_seg;

    // Se controla que el total no sea mayor a 24 hs
    if (nuevo_tiempo_seg >= 86400) {
        nuevo_tiempo_seg -= 86400;
    }

    // se obtienen las horas que hay en nuevo_tiempo_seg
    uint32_t nuevas_horas = (nuevo_tiempo_seg / 3600);

    // se obtienen los minutos con las horas ya restadas
    uint32_t nuevos_minutos = nuevo_tiempo_seg - (nuevas_horas * 3600);

    reloj->alarma[0] = (nuevas_horas) / 10;
    reloj->alarma[1] = (nuevas_horas) % 10;
    reloj->alarma[2] = (nuevos_minutos / 60) / 10;
    reloj->alarma[3] = ((nuevos_minutos) - ((reloj->alarma[2]) * 600));

    reloj->disparar_alarma(reloj, false);
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */