.text
.globl half
half:
addi sp, sp, -16
block_2:
sw a0, 0(sp)
lw t2, 0(sp)
sw t2, 4(sp)
lw t0, 4(sp)
li t1, 2
div t2, t0, t1
sw t2, 8(sp)
lw t2, 8(sp)
add a0, t2, x0
addi sp, sp, 16
ret
.text
.globl f
f:
block_3:
lw t2, 
add a0, t2, x0
ret
.text
.globl main
main:
addi sp, sp, -16
block_10:
call f
li t2, 10
add a0,t2 ,x0
call half
sw a0, 12(sp)
lw t2, 12(sp)
add a0, t2, x0
addi sp, sp, 16
ret
