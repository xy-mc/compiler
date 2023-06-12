
    .data
    .global luoji
luoji:
    .word 0

    .text
    .globl square
square:
    addi sp, sp, -16
block_2:
    sw a0, 
    lw t2, 
    sw t2, 0(sp)
    lw t2, 
    sw t2, 4(sp)
    lw t0, 0(sp)
    lw t1, 4(sp)
    mul t2, t0, t1
    sw t2, 8(sp)
    lw t2, 8(sp)
    add a0, t2, x0
    addi sp, sp, 16
    ret
