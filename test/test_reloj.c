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

// el nombre del archivo debe comenzar con "test_"
#include "unity.h"

// la funcion debe comenzar con "test_"
void test_inicializacion(void) {

    TEST_FAIL_MESSAGE("Funciona");
}