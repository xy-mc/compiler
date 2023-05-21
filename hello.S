.text
.globl main
main:
li t2, 21
sw t2, 4(sp)
lw t2, 4(sp)
sw t2, 8(sp)
lw t2, 8(sp)
sw t2, 12(sp)
lw t0, 12(sp)
li t2, 1
sw t2, 16(sp)
lw t1, 16(sp)
add t2, t0, t1
sw t2, 20(sp)
lw t2, 20(sp)
sw t2, 24(sp)
lw t2, 24(sp)
sw t2, 28(sp)
li t2, 147
sw t2, 32(sp)
lw t0, 32(sp)
lw t1, 28(sp)
sub t2, t0, t1
sw t2, 36(sp)
lw t2, 36(sp)
sw t2, 40(sp)
lw t2, 8(sp)
sw t2, 44(sp)
lw t0, 32(sp)
lw t1, 44(sp)
sub t2, t0, t1
sw t2, 48(sp)
lw t2, 48(sp)
sw t2, 52(sp)
lw t2, 52(sp)
sw t2, 56(sp)
lw t0, 56(sp)
lw t1, 16(sp)
mul t2, t0, t1
sw t2, 60(sp)
lw t0, 60(sp)
lw t1, 16(sp)
mul t2, t0, t1
sw t2, 64(sp)
lw t0, 64(sp)
lw t1, 16(sp)
mul t2, t0, t1
sw t2, 68(sp)
lw t2, 68(sp)
sw t2, 52(sp)
lw t2, 40(sp)
sw t2, 72(sp)
lw t2, 52(sp)
sw t2, 76(sp)
lw t0, 72(sp)
lw t1, 76(sp)
add t2, t0, t1
sw t2, 80(sp)
lw t2, 80(sp)
add a0, t2, x0
ret