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

/************************************************************************************************
PRUEBAS
‣ Al inicializar el reloj está en 00:00 y con hora invalida.
‣ Al ajustar la hora el reloj queda en hora y es válida.
‣ Después de n ciclos de reloj la hora avanza un segundo,
diez segundos, un minutos, diez minutos, una hora, diez
horas y un día completo.
‣ Fijar la hora de la alarma y consultarla.
‣ Fijar la alarma y avanzar el reloj para que suene.
‣ Fijar la alarma, deshabilitarla y avanzar el reloj para no
suene.
‣ Hacer sonar la alarma y posponerla.
‣ Hacer sonar la alarma y cancelarla hasta el otro dia..
*************************************************************************************************/

/* === Headers files inclusions =============================================================== */

#include <unity.h>
#include <reloj.h>

/* === Macros definitions ====================================================================== */

#define TICKS_PER_SECOND 5 // define cuantas interrupciones del systick habrá por segundo

/* === Variable definitions ==================================================================== */

reloj_t reloj;

/* === Private function implementation ========================================================= */

void adelantar_ticks(reloj_t reloj, int numero_ticks) {

    for (int i = 1; i <= numero_ticks; i++) {

        RelojNuevoTick(reloj);
    }
}

void adelantar_segundos(reloj_t reloj, int segundos) {

    for (int i = 1; i <= segundos; i++) {

        adelantar_ticks(reloj, TICKS_PER_SECOND);
    }
}

void adelantar_minutos(reloj_t reloj, int minutos) {

    for (int i = 1; i <= minutos; i++) {

        adelantar_segundos(reloj, 60);
    }
}

void adelantar_horas(reloj_t reloj, int horas) {

    for (int i = 1; i <= horas; i++) {

        adelantar_minutos(reloj, 60);
    }
}

/* === Test function implementation ============================================================ */

void setUp(void) {
    reloj = ClockCreate(TICKS_PER_SECOND);
}

// Al inicializar el reloj está en 00:00 y con hora invalida.
void test_inicio_hora_invalida(void) {

    static const uint8_t hora_esperada[] = {0, 0, 0, 0, 0, 0};
    uint8_t hora[6] = {0xFF};

    // Estoy esperando una hora invalida o no real (ya que es la hora inicial)
    TEST_ASSERT_FALSE(GetClockTime(reloj, hora, 6));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(hora_esperada, hora, 6);
}

// Al ajustar la hora el reloj queda en hora y es válida.

void test_ajuste_validacion_hora(void) {

    static const uint8_t hora_esperada[] = {1, 2, 3, 4, 0, 0};
    uint8_t hora[6];

    TEST_ASSERT_TRUE(SetClockTime(reloj, hora_esperada, 4));
    TEST_ASSERT_TRUE(GetClockTime(reloj, hora, 6));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(hora_esperada, hora, 6);
}

// ‣ Después de n ciclos de reloj la hora avanza un segundo,
// diez segundos, un minutos, diez minutos, una hora, diez
// horas y un día completo.

void test_hora_avanza_un_segundo(void) {

    static const uint8_t hora_esperada[] = {0, 1, 0, 0, 0, 0}; // 1am
    uint8_t hora_actual[6];

    TEST_ASSERT_TRUE(SetClockTime(reloj, hora_esperada, 4));
    adelantar_segundos(reloj, 1);
    adelantar_segundos(reloj, 10);
    adelantar_minutos(reloj, 1);
    adelantar_minutos(reloj, 10);
    adelantar_horas(reloj, 1);
    adelantar_horas(reloj, 10);
    TEST_ASSERT_TRUE(GetClockTime(reloj, hora_actual, 6));

    // prueba de tiempos

    TEST_ASSERT_EQUAL_UINT8(hora_actual[5], hora_esperada[5] + 1); // seg
    TEST_ASSERT_EQUAL_UINT8(hora_actual[4], hora_esperada[4] + 1); // dseg
    TEST_ASSERT_EQUAL_UINT8(hora_actual[3], hora_esperada[3] + 1); // min
    TEST_ASSERT_EQUAL_UINT8(hora_actual[2], hora_esperada[2] + 1); // dmin
    TEST_ASSERT_EQUAL_UINT8(hora_actual[1], hora_esperada[1] + 1); // hor
    TEST_ASSERT_EQUAL_UINT8(hora_actual[0], hora_esperada[0] + 1); // dhor

    // prueba de que pase un día
    // debería seguir todo igual
    adelantar_horas(reloj, 24);
    TEST_ASSERT_TRUE(GetClockTime(reloj, hora_actual, 6));
    TEST_ASSERT_EQUAL_UINT8(hora_actual[5], hora_esperada[5] + 1); // seg
    TEST_ASSERT_EQUAL_UINT8(hora_actual[4], hora_esperada[4] + 1); // dseg
    TEST_ASSERT_EQUAL_UINT8(hora_actual[3], hora_esperada[3] + 1); // min
    TEST_ASSERT_EQUAL_UINT8(hora_actual[2], hora_esperada[2] + 1); // dmin
    TEST_ASSERT_EQUAL_UINT8(hora_actual[1], hora_esperada[1] + 1); // hor
    TEST_ASSERT_EQUAL_UINT8(hora_actual[0], hora_esperada[0] + 1); // dhor
}

//‣ Fijar la hora de la alarma y consultarla.
// asumo que la alarma nunca tendrá precision de segundos
void test_fijar_consultar_alarma(void) {
    static const uint8_t alarma_esperada[] = {0, 8, 0, 0};
    uint8_t alarma[4];

    TEST_ASSERT_TRUE(SetAlarmTime(reloj, alarma_esperada));
    TEST_ASSERT_TRUE(GetAlarmTime(reloj, alarma));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(alarma, alarma_esperada, 4);
}

//‣ Fijar la alarma y avanzar el reloj para que suene.
void avanzar_reloj_para_alarma(void) {

    static const uint8_t hora_esperada[] = {0, 1, 0, 0, 0, 0};
    static const uint8_t alarma_esperada[] = {0, 8, 0, 0};

    TEST_ASSERT_TRUE(SetClockTime(reloj, hora_esperada, 4));
    TEST_ASSERT_TRUE(SetAlarmTime(reloj, alarma_esperada));

    adelantar_horas(reloj, 7);
    // testear que se activó la alarma (que está sonando)
    VerificarAlarma()
}