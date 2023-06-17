
    .data
    .global luoji
luoji:
    .word 0

    .data
    .global arr
arr:
    .zero 262144

    .text
    .globl main
main:
    addi sp, sp, -32
block_6:
    addi t0, sp, 0
    li t1, 0
    li t2, 4
    mul t1, t1, t2
    add t2, t0, t1
    sw t2, 8(sp)
    li t2, 1
    sw t2, 8(sp)
    addi t0, sp, 0
    li t1, 1
    li t2, 4
    mul t1, t1, t2
    add t2, t0, t1
    sw t2, 12(sp)
    li t2, 0
    sw t2, 12(sp)
    addi t0, sp, 0
    li t1, 0
    li t2, 4
    mul t1, t1, t2
    add t2, t0, t1
    sw t2, 16(sp)
    lw t2, 16(sp)
    sw t2, 20(sp)
    lw t2, 20(sp)
    add a0, t2, x0
    addi sp, sp, 32
    ret
