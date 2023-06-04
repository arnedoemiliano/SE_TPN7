#include "src/reloj.h"
#include "/var/lib/gems/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"








void test_inicio_hora_invalida(void) {



    static const uint8_t hora_esperada[] = {0, 0, 0, 0, 0, 0};

    uint8_t hora[6] = {0xFF};

    reloj_t reloj = ClockCreate(5);



    do {if (!(GetClockTime(reloj, hora, 6))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(46)));}} while(0);

    UnityAssertEqualIntArray(( const void*)((hora_esperada)), ( const void*)((hora)), (UNITY_UINT32)((6)), (

   ((void *)0)

   ), (UNITY_UINT)(47), UNITY_DISPLAY_STYLE_UINT8, UNITY_ARRAY_TO_ARRAY);

}







void test_ajuste_validacion_hora(void) {



    static const uint8_t hora_esperada[] = {1, 2, 3, 4, 0, 0};

    reloj_t reloj = ClockCreate(3);

    uint8_t hora[6];



    do {if ((SetClockTime(reloj, hora_esperada, 4))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(58)));}} while(0);

    do {if ((GetClockTime(reloj, hora, 6))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(59)));}} while(0);

    UnityAssertEqualIntArray(( const void*)((hora_esperada)), ( const void*)((hora)), (UNITY_UINT32)((6)), (

   ((void *)0)

   ), (UNITY_UINT)(60), UNITY_DISPLAY_STYLE_UINT8, UNITY_ARRAY_TO_ARRAY);

}







void test_hora_avanza_un_segundo(void) {



    static const uint8_t hora_esperada[] = {1, 2, 3, 4, 0, 0};

    reloj_t reloj = ClockCreate(5);

    uint8_t hora_actual[6];



    do {if ((SetClockTime(reloj, hora_esperada, 4))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(71)));}} while(0);

    do {if ((GetClockTime(reloj, hora_actual, 6))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(72)));}} while(0);



    RelojNuevoTick(reloj);

    RelojNuevoTick(reloj);

    RelojNuevoTick(reloj);

    RelojNuevoTick(reloj);









    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((hora_actual[5])), (UNITY_INT)(UNITY_UINT8 )((hora_esperada[5])), (

   ((void *)0)

   ), (UNITY_UINT)(82), UNITY_DISPLAY_STYLE_UINT8);



    RelojNuevoTick(reloj);



    do {if ((GetClockTime(reloj, hora_actual, 6))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(86)));}} while(0);





    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((hora_actual[5])), (UNITY_INT)(UNITY_UINT8 )((hora_esperada[5] + 1)), (

   ((void *)0)

   ), (UNITY_UINT)(89), UNITY_DISPLAY_STYLE_UINT8);

}
