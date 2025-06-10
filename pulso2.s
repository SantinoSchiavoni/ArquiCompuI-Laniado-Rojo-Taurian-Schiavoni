// pulso2.s
// 3 de Junio de 2025
// Arqui I UCC

.text

.global pulso2
pulso2:
    push {r4,r5 lr}           @ Guardar registros
    mov r5, r0


    mov r4, #0xAA             @ Cargar patrón
    mov r0, r4
    bl disp_binary            @ Llamar a C: void disp_binary(int)

    mvn r0, r4                @ Complemento de r4
    bl leds                   @ Llamar a C: void leds(int)

    ldr r0, [r5]              @ traemos el valor de tiempo
    mov r1,r5                   @ pasamos la direccion del puntero tiempo
    bl delay_controlado            @ Llamar a C: void delay_controlado()

    cmp r0,#1
    beq fin_pulso

    lsr r4, r4, #1            @ Desplazar r4 una posición a la derecha
    mov r0, r4
    bl disp_binary

    mvn r0, r4
    bl leds

    ldr r0, [r5]
    mov r1,r5
    bl delay_controlado

    cmp r0,#1
    beq fin_pulso

fin_pulso:
    mov r0, #1
    pop {r4,r5, pc}              @ Restaurar y retornar


.data
array:
.end
