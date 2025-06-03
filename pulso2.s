// pulso2.s
// 3 de Junio de 2025
// Arqui I UCC

.text

.global pulso2
pulso2:
    push {r4, lr}             @ Guardar registros

    mov r4, #0xAA             @ Cargar patrón
    mov r0, r4
    bl disp_binary            @ Llamar a C: void disp_binary(int)

    mvn r0, r4                @ Complemento de r4
    bl leds                   @ Llamar a C: void leds(int)

    mov r0, #150              @ Delay de 150 ms
    bl delaymillis            @ Llamar a C: void delaymillis(int)

    lsr r4, r4, #1            @ Desplazar r4 una posición a la derecha
    mov r0, r4
    bl disp_binary

    mvn r0, r4
    bl leds

    mov r0, #150
    bl delaymillis

    pop {r4, pc}              @ Restaurar y retornar
.data
array:
.end
