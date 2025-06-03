// bateria.s
// 6 de junio del 2025
// Arqui I - UCC

.text
.global bateria

bateria:
    PUSH {R4, R5, R6, R7, LR} // Guardar registros que se usarán
    LDR R7, = array        // Dirección base del array en R3
    MOV R4, #9            // Cantidad de bytes (elementos)
    MOV R5, #0            // Índice

loop:
    LDRB R6, [R3, R5]     // Cargar un byte del array (R6 = array[R5])
    MOV R0, R6            // Mover el byte a R0 para mostrarlo
    BL disp_binary
    BL leds
    BL delaymillis            // Llamar a rutina de espera (ver más abajo)
    ADD R5, R5, #1        // Incrementar índice
    CMP R5, R4
    BLT loop              // Si R5 < R4, seguir
    MOV PC, LR            // Volver al llamador
.data
array:
    .byte 0x00
    .byte 0x80
    .byte 0xC0
    .byte 0xE0
    .byte 0xF0
    .byte 0xF8
    .byte 0xFC
    .byte 0xFE
    .byte 0xFF
.end
