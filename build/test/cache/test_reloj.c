#include "src/reloj.h"
#include "/var/lib/gems/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"














reloj_t reloj;



_Bool 

    alarma_activada;

static const uint8_t hora_esperada[] = {0, 0, 0, 0, 0, 0};

static const uint8_t alarma_esperada[] = {0, 8, 0, 0};







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



void activar_alarma(reloj_t reloj) {



    alarma_activada = 

                     1

                         ;

}







void setUp(void) {



    reloj = ClockCreate(5, activar_alarma);

    alarma_activada = 

                     0

                          ;

}





void test_inicio_hora_invalida(void) {





    uint8_t hora[6] = {0xFF};





    do {if (!(GetClockTime(reloj, hora, 6))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(103)));}} while(0);

    UnityAssertEqualIntArray(( const void*)((hora_esperada)), ( const void*)((hora)), (UNITY_UINT32)((6)), (

   ((void *)0)

   ), (UNITY_UINT)(104), UNITY_DISPLAY_STYLE_UINT8, UNITY_ARRAY_TO_ARRAY);

}







void test_ajuste_validacion_hora(void) {





    uint8_t hora[6];



    do {if ((SetClockTime(reloj, hora_esperada, 4))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(114)));}} while(0);

    do {if ((GetClockTime(reloj, hora, 6))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(115)));}} while(0);

    UnityAssertEqualIntArray(( const void*)((hora_esperada)), ( const void*)((hora)), (UNITY_UINT32)((6)), (

   ((void *)0)

   ), (UNITY_UINT)(116), UNITY_DISPLAY_STYLE_UINT8, UNITY_ARRAY_TO_ARRAY);

}











void test_hora_avanza_un_segundo(void) {





    uint8_t hora_actual[6];



    do {if ((SetClockTime(reloj, hora_esperada, 4))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(128)));}} while(0);

    adelantar_segundos(reloj, 1);

    adelantar_segundos(reloj, 10);

    adelantar_minutos(reloj, 1);

    adelantar_minutos(reloj, 10);

    adelantar_horas(reloj, 1);

    adelantar_horas(reloj, 10);

    do {if ((GetClockTime(reloj, hora_actual, 6))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(135)));}} while(0);







    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((hora_actual[5])), (UNITY_INT)(UNITY_UINT8 )((hora_esperada[5] + 1)), (

   ((void *)0)

   ), (UNITY_UINT)(139), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((hora_actual[4])), (UNITY_INT)(UNITY_UINT8 )((hora_esperada[4] + 1)), (

   ((void *)0)

   ), (UNITY_UINT)(140), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((hora_actual[3])), (UNITY_INT)(UNITY_UINT8 )((hora_esperada[3] + 1)), (

   ((void *)0)

   ), (UNITY_UINT)(141), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((hora_actual[2])), (UNITY_INT)(UNITY_UINT8 )((hora_esperada[2] + 1)), (

   ((void *)0)

   ), (UNITY_UINT)(142), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((hora_actual[1])), (UNITY_INT)(UNITY_UINT8 )((hora_esperada[1] + 1)), (

   ((void *)0)

   ), (UNITY_UINT)(143), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((hora_actual[0])), (UNITY_INT)(UNITY_UINT8 )((hora_esperada[0] + 1)), (

   ((void *)0)

   ), (UNITY_UINT)(144), UNITY_DISPLAY_STYLE_UINT8);





    adelantar_horas(reloj, 24);

    do {if ((GetClockTime(reloj, hora_actual, 6))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(148)));}} while(0);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((hora_actual[5])), (UNITY_INT)(UNITY_UINT8 )((hora_esperada[5] + 1)), (

   ((void *)0)

   ), (UNITY_UINT)(149), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((hora_actual[4])), (UNITY_INT)(UNITY_UINT8 )((hora_esperada[4] + 1)), (

   ((void *)0)

   ), (UNITY_UINT)(150), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((hora_actual[3])), (UNITY_INT)(UNITY_UINT8 )((hora_esperada[3] + 1)), (

   ((void *)0)

   ), (UNITY_UINT)(151), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((hora_actual[2])), (UNITY_INT)(UNITY_UINT8 )((hora_esperada[2] + 1)), (

   ((void *)0)

   ), (UNITY_UINT)(152), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((hora_actual[1])), (UNITY_INT)(UNITY_UINT8 )((hora_esperada[1] + 1)), (

   ((void *)0)

   ), (UNITY_UINT)(153), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((hora_actual[0])), (UNITY_INT)(UNITY_UINT8 )((hora_esperada[0] + 1)), (

   ((void *)0)

   ), (UNITY_UINT)(154), UNITY_DISPLAY_STYLE_UINT8);

}







void test_fijar_consultar_alarma(void) {



    uint8_t alarma[4];



    do {if ((SetAlarmTime(reloj, alarma_esperada))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(163)));}} while(0);

    do {if ((GetAlarmTime(reloj, alarma))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(164)));}} while(0);

    UnityAssertEqualIntArray(( const void*)((alarma)), ( const void*)((alarma_esperada)), (UNITY_UINT32)((4)), (

   ((void *)0)

   ), (UNITY_UINT)(165), UNITY_DISPLAY_STYLE_UINT8, UNITY_ARRAY_TO_ARRAY);

}





void test_avanzar_reloj_para_alarma(void) {







    do {if ((SetClockTime(reloj, hora_esperada, 4))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(173)));}} while(0);

    do {if ((SetAlarmTime(reloj, alarma_esperada))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(174)));}} while(0);

    adelantar_horas(reloj, 7);

    do {if (!(alarma_activada)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(176)));}} while(0);

    adelantar_minutos(reloj, 59);

    do {if (!(alarma_activada)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(178)));}} while(0);

    adelantar_minutos(reloj, 1);

    do {if ((alarma_activada)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(180)));}} while(0);

}
