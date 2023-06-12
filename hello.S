
    .data
    .global luoji
luoji:
    .word 0

    .data
    .global var
var:
    .word 0

    .text
    .globl main
main:
    addi sp, sp, -16
block_2:
    la t0 , var
    lw t0, 0(t0)
    sw t0, 4(sp)
    lw t2, 0(sp)
    sw t2, 0(sp)
    lw t0, 0(sp)
    li t1, 1
    add t2, t0, t1
    sw t2, 8(sp)
    lw t2, 8(sp)
    add a0, t2, x0
    addi sp, sp, 16
    ret
