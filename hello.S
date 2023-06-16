
    .data
    .global luoji
luoji:
    .word 0

    .data
    .global x
x:
    .zero 4

    .data
    .global init
init:
    .word 1

    .text
    .globl main
main:
    addi sp, sp, -16
    sw ra, 12(sp)
block_34:
    la t0 , x
    lw t0, 0(t0)
    sw t0, 0(sp)
    lw t2, 0(sp)
    sw t2, 4(sp)
    lw t2, 4(sp)
    add a0,t2 ,x0
    call putint
    li t2, 32
    add a0,t2 ,x0
    call putch
    li t2, 10
    add a0,t2 ,x0
    call putint
    li t2, 32
    add a0,t2 ,x0
    call putch
    li t2, 11
    add a0,t2 ,x0
    call putint
    li t2, 32
    add a0,t2 ,x0
    call putch
    la t0 , init
    lw t0, 0(t0)
    sw t0, 8(sp)
    lw t2, 8(sp)
    sw t2, 12(sp)
    lw t2, 12(sp)
    add a0,t2 ,x0
    call putint
    li t2, 10
    add a0,t2 ,x0
    call putch
    li t2, 0
    add a0, t2, x0
    lw ra, 12(sp)
    addi sp, sp, 16
    ret
