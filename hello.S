.text
.globl main
main:
block_3:
add t2, x0, x0
sw t2, 4(sp)
li t2, 1
sw t2, 8(sp)
lw t2, 8(sp)
sw t2, 12(sp)
li t2, 2
sw t2, 16(sp)
lw t2, 16(sp)
sw t2, 20(sp)
lw t2, 4(sp)
sw t2, 24(sp)
lw t0, 24(sp)
add t1, x0, x0
sub t1, t0, t1
snez t2, t1
sw t2, 28(sp)
add t0, x0, x0
add t1, x0, x0
sub t1, t0, t1
snez t2, t1
sw t2, 32(sp)
lw t0, 28(sp)
lw t1, 32(sp)
or t2, t0, t1
sw t2, 36(sp)
lw t2, 36(sp)
bnez t2, block_0
j block_1
block_0:
li t2, 3
sw t2, 40(sp)
lw t2, 40(sp)
sw t2, 12(sp)
j block_2
block_1:
lw t2, 40(sp)
sw t2, 20(sp)
lw t2, 8(sp)
sw t2, 44(sp)
lw t2, 44(sp)
sw t2, 48(sp)
lw t0, 48(sp)
add t1, x0, x0
sub t1, t0, t1
snez t2, t1
sw t2, 52(sp)
add t0, x0, x0
add t1, x0, x0
sub t1, t0, t1
snez t2, t1
sw t2, 56(sp)
lw t0, 52(sp)
lw t1, 56(sp)
or t2, t0, t1
sw t2, 60(sp)
lw t2, 60(sp)
bnez t2, block_4
j block_5
block_4:
li t2, 4
sw t2, 64(sp)
lw t2, 64(sp)
sw t2, 12(sp)
j block_6
block_5:
lw t2, 64(sp)
sw t2, 20(sp)
j block_6
block_6:
lw t2, 44(sp)
sw t2, 68(sp)
lw t0, 68(sp)
add t1, x0, x0
sub t1, t0, t1
seqz t2, t1
sw t2, 72(sp)
lw t2, 72(sp)
bnez t2, block_7
j block_8
block_7:
lw t2, 8(sp)
add a0, t2, x0
ret
block_10:
j block_9
block_8:
lw t2, 44(sp)
sw t2, 76(sp)
lw t0, 76(sp)
add t1, x0, x0
sub t1, t0, t1
seqz t2, t1
sw t2, 80(sp)
lw t2, 44(sp)
sw t2, 84(sp)
add t0, x0, x0
lw t1, 8(sp)
sub t2, t0, t1
sw t2, 88(sp)
lw t0, 84(sp)
lw t1, 88(sp)
sub t1, t0, t1
seqz t2, t1
sw t2, 92(sp)
lw t0, 80(sp)
add t1, x0, x0
sub t1, t0, t1
snez t2, t1
sw t2, 96(sp)
lw t0, 92(sp)
add t1, x0, x0
sub t1, t0, t1
snez t2, t1
sw t2, 100(sp)
lw t0, 96(sp)
lw t1, 100(sp)
and t2, t0, t1
sw t2, 104(sp)
lw t2, 104(sp)
bnez t2, block_11
j block_12
block_11:
lw t2, 16(sp)
add a0, t2, x0
ret
block_13:
j block_12
block_12:
j block_9
block_9:
j block_2
block_2:
lw t2, 4(sp)
sw t2, 108(sp)
lw t0, 108(sp)
add t1, x0, x0
add t2, t0, t1
sw t2, 112(sp)
lw t2, 12(sp)
sw t2, 116(sp)
lw t0, 112(sp)
lw t1, 116(sp)
add t2, t0, t1
sw t2, 120(sp)
lw t2, 20(sp)
sw t2, 124(sp)
lw t0, 120(sp)
lw t1, 124(sp)
add t2, t0, t1
sw t2, 128(sp)
lw t2, 128(sp)
add a0, t2, x0
ret
