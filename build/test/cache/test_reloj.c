#include "src/reloj.h"
#include "/var/lib/gems/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"














reloj_t reloj;







void adelantar_ticks(reloj_t reloj, int numero_ticks) {



    for (int i = 1; i <= numero_ticks; i++) {



        RelojNuevoTick(reloj);

    }

}



void adelantar_segundos(reloj_t reloj, int segundos) {



    for (int i = 1; i <= segundos; i++) {



        adelantar_ticks(reloj, 5);

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







void setUp(void) {

    reloj = ClockCreate(5);

}





void test_inicio_hora_invalida(void) {



    static const uint8_t hora_esperada[] = {0, 0, 0, 0, 0, 0};

    uint8_t hora[6] = {0xFF};





    do {if (!(GetClockTime(reloj, hora, 6))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(93)));}} while(0);

    UnityAssertEqualIntArray(( const void*)((hora_esperada)), ( const void*)((hora)), (UNITY_UINT32)((6)), (

   ((void *)0)

   ), (UNITY_UINT)(94), UNITY_DISPLAY_STYLE_UINT8, UNITY_ARRAY_TO_ARRAY);

}







void test_ajuste_validacion_hora(void) {



    static const uint8_t hora_esperada[] = {1, 2, 3, 4, 0, 0};

    uint8_t hora[6];



    do {if ((SetClockTime(reloj, hora_esperada, 4))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(104)));}} while(0);

    do {if ((GetClockTime(reloj, hora, 6))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(105)));}} while(0);

    UnityAssertEqualIntArray(( const void*)((hora_esperada)), ( const void*)((hora)), (UNITY_UINT32)((6)), (

   ((void *)0)

   ), (UNITY_UINT)(106), UNITY_DISPLAY_STYLE_UINT8, UNITY_ARRAY_TO_ARRAY);

}











void test_hora_avanza_un_segundo(void) {



    static const uint8_t hora_esperada[] = {0, 1, 0, 0, 0, 0};

    uint8_t hora_actual[6];



    do {if ((SetClockTime(reloj, hora_esperada, 4))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(118)));}} while(0);

    adelantar_segundos(reloj, 1);

    adelantar_segundos(reloj, 10);

    adelantar_minutos(reloj, 1);

    adelantar_minutos(reloj, 10);

    adelantar_horas(reloj, 1);

    adelantar_horas(reloj, 10);

    do {if ((GetClockTime(reloj, hora_actual, 6))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(125)));}} while(0);







    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((hora_actual[5])), (UNITY_INT)(UNITY_UINT8 )((hora_esperada[5] + 1)), (

   ((void *)0)

   ), (UNITY_UINT)(129), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((hora_actual[4])), (UNITY_INT)(UNITY_UINT8 )((hora_esperada[4] + 1)), (

   ((void *)0)

   ), (UNITY_UINT)(130), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((hora_actual[3])), (UNITY_INT)(UNITY_UINT8 )((hora_esperada[3] + 1)), (

   ((void *)0)

   ), (UNITY_UINT)(131), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((hora_actual[2])), (UNITY_INT)(UNITY_UINT8 )((hora_esperada[2] + 1)), (

   ((void *)0)

   ), (UNITY_UINT)(132), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((hora_actual[1])), (UNITY_INT)(UNITY_UINT8 )((hora_esperada[1] + 1)), (

   ((void *)0)

   ), (UNITY_UINT)(133), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((hora_actual[0])), (UNITY_INT)(UNITY_UINT8 )((hora_esperada[0] + 1)), (

   ((void *)0)

   ), (UNITY_UINT)(134), UNITY_DISPLAY_STYLE_UINT8);







    adelantar_horas(reloj, 24);

    do {if ((GetClockTime(reloj, hora_actual, 6))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(139)));}} while(0);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((hora_actual[5])), (UNITY_INT)(UNITY_UINT8 )((hora_esperada[5] + 1)), (

   ((void *)0)

   ), (UNITY_UINT)(140), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((hora_actual[4])), (UNITY_INT)(UNITY_UINT8 )((hora_esperada[4] + 1)), (

   ((void *)0)

   ), (UNITY_UINT)(141), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((hora_actual[3])), (UNITY_INT)(UNITY_UINT8 )((hora_esperada[3] + 1)), (

   ((void *)0)

   ), (UNITY_UINT)(142), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((hora_actual[2])), (UNITY_INT)(UNITY_UINT8 )((hora_esperada[2] + 1)), (

   ((void *)0)

   ), (UNITY_UINT)(143), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((hora_actual[1])), (UNITY_INT)(UNITY_UINT8 )((hora_esperada[1] + 1)), (

   ((void *)0)

   ), (UNITY_UINT)(144), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((hora_actual[0])), (UNITY_INT)(UNITY_UINT8 )((hora_esperada[0] + 1)), (

   ((void *)0)

   ), (UNITY_UINT)(145), UNITY_DISPLAY_STYLE_UINT8);

}







void test_fijar_consultar_alarma(void) {

    static const uint8_t alarma_esperada[] = {0, 8, 0, 0};

    uint8_t alarma[4];



    do {if ((SetAlarmTime(reloj, alarma_esperada))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(154)));}} while(0);

    do {if ((GetAlarmTime(reloj, alarma))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(155)));}} while(0);

    UnityAssertEqualIntArray(( const void*)((alarma)), ( const void*)((alarma_esperada)), (UNITY_UINT32)((4)), (

   ((void *)0)

   ), (UNITY_UINT)(156), UNITY_DISPLAY_STYLE_UINT8, UNITY_ARRAY_TO_ARRAY);

}
