// pulso2.s
// 3 de Junio de 2025
// Arqui I UCC

.text

.global pulso2
pulso2:
      push {r4,lr}
      mov r4, #0xAA
      mov r0,r4
      bl disp_binary
      mvn r0,r4
      bl leds
      mov r0,#150
      bl delaymillis
      mov r4,r4, lsr#1
      mov r0,r4
      bl disp_binary
      mvn r0,r4
      bl leds
      mov r0,#150
      bl delaymillis
      pop {r4,pc}
.data
array:
.end
