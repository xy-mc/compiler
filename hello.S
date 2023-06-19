
    .data
    .global luoji
luoji:
    .word 0

    .data
    .global n
n:
    .zero 4

    .text
    .globl counting_sort
counting_sort:
    addi sp, sp, -352
block_9:
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    li t2, 0
    sw t2, 60(sp)
    li t2, 0
    sw t2, 52(sp)
    li t2, 0
    sw t2, 56(sp)
    j block_8
block_8:
    lw t2, 60(sp)
    sw t2, 64(sp)
    lw t0, 64(sp)
    li t1, 10
    slt t2, t0, t1
    sw t2, 68(sp)
    lw t2, 68(sp)
    bnez t2, block_6
    j block_7
block_6:
    lw t2, 60(sp)
    sw t2, 72(sp)
    addi t4, sp, 12
    lw t1, 72(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 76(sp)
    li t2, 0
    lw t0, 76(sp)
    sw t2, 0(t0)
    lw t2, 60(sp)
    sw t2, 80(sp)
    lw t0, 80(sp)
    li t1, 1
    add t2, t0, t1
    sw t2, 84(sp)
    lw t2, 84(sp)
    sw t2, 60(sp)
    j block_8
block_7:
    j block_18
block_18:
    lw t2, 52(sp)
    sw t2, 88(sp)
    lw t2, 8(sp)
    sw t2, 92(sp)
    lw t0, 88(sp)
    lw t1, 92(sp)
    slt t2, t0, t1
    sw t2, 96(sp)
    lw t2, 96(sp)
    bnez t2, block_16
    j block_17
block_16:
    lw t2, 0(sp)
    sw t2, 100(sp)
    lw t2, 52(sp)
    sw t2, 104(sp)
    lw t0, 0(sp)
    mv t4, t0
    lw t1, 104(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 108(sp)
    lw t0, 108(sp)
    lw t2, 0(t0)
    sw t2, 112(sp)
    addi t4, sp, 12
    lw t1, 112(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 116(sp)
    lw t0, 116(sp)
    lw t2, 0(t0)
    sw t2, 120(sp)
    lw t0, 120(sp)
    li t1, 1
    add t2, t0, t1
    sw t2, 124(sp)
    lw t2, 0(sp)
    sw t2, 128(sp)
    lw t2, 52(sp)
    sw t2, 132(sp)
    lw t0, 0(sp)
    mv t4, t0
    lw t1, 132(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 136(sp)
    lw t0, 136(sp)
    lw t2, 0(t0)
    sw t2, 140(sp)
    addi t4, sp, 12
    lw t1, 140(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 144(sp)
    lw t2, 124(sp)
    lw t0, 144(sp)
    sw t2, 0(t0)
    lw t2, 52(sp)
    sw t2, 148(sp)
    lw t0, 148(sp)
    li t1, 1
    add t2, t0, t1
    sw t2, 152(sp)
    lw t2, 152(sp)
    sw t2, 52(sp)
    j block_18
block_17:
    li t2, 1
    sw t2, 60(sp)
    j block_35
block_35:
    lw t2, 60(sp)
    sw t2, 156(sp)
    lw t0, 156(sp)
    li t1, 10
    slt t2, t0, t1
    sw t2, 160(sp)
    lw t2, 160(sp)
    bnez t2, block_33
    j block_34
block_33:
    lw t2, 60(sp)
    sw t2, 164(sp)
    addi t4, sp, 12
    lw t1, 164(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 168(sp)
    lw t0, 168(sp)
    lw t2, 0(t0)
    sw t2, 172(sp)
    lw t2, 60(sp)
    sw t2, 176(sp)
    lw t0, 176(sp)
    li t1, 1
    sub t2, t0, t1
    sw t2, 180(sp)
    addi t4, sp, 12
    lw t1, 180(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 184(sp)
    lw t0, 184(sp)
    lw t2, 0(t0)
    sw t2, 188(sp)
    lw t0, 172(sp)
    lw t1, 188(sp)
    add t2, t0, t1
    sw t2, 192(sp)
    lw t2, 60(sp)
    sw t2, 196(sp)
    addi t4, sp, 12
    lw t1, 196(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 200(sp)
    lw t2, 192(sp)
    lw t0, 200(sp)
    sw t2, 0(t0)
    lw t2, 60(sp)
    sw t2, 204(sp)
    lw t0, 204(sp)
    li t1, 1
    add t2, t0, t1
    sw t2, 208(sp)
    lw t2, 208(sp)
    sw t2, 60(sp)
    j block_35
block_34:
    lw t2, 8(sp)
    sw t2, 212(sp)
    lw t2, 212(sp)
    sw t2, 56(sp)
    j block_50
block_50:
    lw t2, 56(sp)
    sw t2, 216(sp)
    lw t0, 216(sp)
    li t1, 0
    sgt t2, t0, t1
    sw t2, 220(sp)
    lw t2, 220(sp)
    bnez t2, block_48
    j block_49
block_48:
    lw t2, 0(sp)
    sw t2, 224(sp)
    lw t2, 56(sp)
    sw t2, 228(sp)
    lw t0, 228(sp)
    li t1, 1
    sub t2, t0, t1
    sw t2, 232(sp)
    lw t0, 0(sp)
    mv t4, t0
    lw t1, 232(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 236(sp)
    lw t0, 236(sp)
    lw t2, 0(t0)
    sw t2, 240(sp)
    addi t4, sp, 12
    lw t1, 240(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 244(sp)
    lw t0, 244(sp)
    lw t2, 0(t0)
    sw t2, 248(sp)
    lw t0, 248(sp)
    li t1, 1
    sub t2, t0, t1
    sw t2, 252(sp)
    lw t2, 0(sp)
    sw t2, 256(sp)
    lw t2, 56(sp)
    sw t2, 260(sp)
    lw t0, 260(sp)
    li t1, 1
    sub t2, t0, t1
    sw t2, 264(sp)
    lw t0, 0(sp)
    mv t4, t0
    lw t1, 264(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 268(sp)
    lw t0, 268(sp)
    lw t2, 0(t0)
    sw t2, 272(sp)
    addi t4, sp, 12
    lw t1, 272(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 276(sp)
    lw t2, 252(sp)
    lw t0, 276(sp)
    sw t2, 0(t0)
    lw t2, 0(sp)
    sw t2, 280(sp)
    lw t2, 56(sp)
    sw t2, 284(sp)
    lw t0, 284(sp)
    li t1, 1
    sub t2, t0, t1
    sw t2, 288(sp)
    lw t0, 0(sp)
    mv t4, t0
    lw t1, 288(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 292(sp)
    lw t0, 292(sp)
    lw t2, 0(t0)
    sw t2, 296(sp)
    lw t2, 4(sp)
    sw t2, 300(sp)
    lw t2, 0(sp)
    sw t2, 304(sp)
    lw t2, 56(sp)
    sw t2, 308(sp)
    lw t0, 308(sp)
    li t1, 1
    sub t2, t0, t1
    sw t2, 312(sp)
    lw t0, 0(sp)
    mv t4, t0
    lw t1, 312(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 316(sp)
    lw t0, 316(sp)
    lw t2, 0(t0)
    sw t2, 320(sp)
    addi t4, sp, 12
    lw t1, 320(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 324(sp)
    lw t0, 324(sp)
    lw t2, 0(t0)
    sw t2, 328(sp)
    lw t0, 4(sp)
    mv t4, t0
    lw t1, 328(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 332(sp)
    lw t2, 296(sp)
    lw t0, 332(sp)
    sw t2, 0(t0)
    lw t2, 56(sp)
    sw t2, 336(sp)
    lw t0, 336(sp)
    li t1, 1
    sub t2, t0, t1
    sw t2, 340(sp)
    lw t2, 340(sp)
    sw t2, 56(sp)
    j block_50
block_49:
    li t2, 0
    add a0, t2, x0
    addi sp, sp, 352
    ret

    .text
    .globl main
main:
    addi sp, sp, -208
    sw ra, 204(sp)
block_130:
    li t2, 10
    la t0 , n
    sw t2 , 0(t0)
    addi t4, sp, 0
    li t1, 0
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 40(sp)
    li t2, 4
    lw t0, 40(sp)
    sw t2, 0(t0)
    addi t4, sp, 0
    li t1, 1
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 44(sp)
    li t2, 3
    lw t0, 44(sp)
    sw t2, 0(t0)
    addi t4, sp, 0
    li t1, 2
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 48(sp)
    li t2, 9
    lw t0, 48(sp)
    sw t2, 0(t0)
    addi t4, sp, 0
    li t1, 3
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 52(sp)
    li t2, 2
    lw t0, 52(sp)
    sw t2, 0(t0)
    addi t4, sp, 0
    li t1, 4
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 56(sp)
    li t2, 0
    lw t0, 56(sp)
    sw t2, 0(t0)
    addi t4, sp, 0
    li t1, 5
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 60(sp)
    li t2, 1
    lw t0, 60(sp)
    sw t2, 0(t0)
    addi t4, sp, 0
    li t1, 6
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 64(sp)
    li t2, 6
    lw t0, 64(sp)
    sw t2, 0(t0)
    addi t4, sp, 0
    li t1, 7
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 68(sp)
    li t2, 5
    lw t0, 68(sp)
    sw t2, 0(t0)
    addi t4, sp, 0
    li t1, 8
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 72(sp)
    li t2, 7
    lw t0, 72(sp)
    sw t2, 0(t0)
    addi t4, sp, 0
    li t1, 9
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 76(sp)
    li t2, 8
    lw t0, 76(sp)
    sw t2, 0(t0)
    li t2, 0
    sw t2, 80(sp)
    addi t4, sp, 0
    li t1, 0
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 124(sp)
    addi t4, sp, 84
    li t1, 0
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 128(sp)
    la t0 , n
    lw t0, 0(t0)
    sw t0, 132(sp)
    lw t2, 132(sp)
    sw t2, 132(sp)
    lw t2, 124(sp)
    add a0,t2 ,x0
    lw t2, 128(sp)
    add a1,t2 ,x0
    lw t2, 132(sp)
    add a2,t2 ,x0
    call counting_sort
    sw a0, 136(sp)
    lw t2, 136(sp)
    sw t2, 80(sp)
    j block_129
block_129:
    lw t2, 80(sp)
    sw t2, 140(sp)
    la t0 , n
    lw t0, 0(t0)
    sw t0, 144(sp)
    lw t2, 144(sp)
    sw t2, 144(sp)
    lw t0, 140(sp)
    lw t1, 144(sp)
    slt t2, t0, t1
    sw t2, 148(sp)
    lw t2, 148(sp)
    bnez t2, block_127
    j block_128
block_127:
    lw t2, 80(sp)
    sw t2, 156(sp)
    addi t4, sp, 84
    lw t1, 156(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 160(sp)
    lw t0, 160(sp)
    lw t2, 0(t0)
    sw t2, 164(sp)
    lw t2, 164(sp)
    sw t2, 152(sp)
    lw t2, 152(sp)
    sw t2, 168(sp)
    lw t2, 168(sp)
    add a0,t2 ,x0
    call putint
    li t2, 10
    sw t2, 152(sp)
    lw t2, 152(sp)
    sw t2, 172(sp)
    lw t2, 172(sp)
    add a0,t2 ,x0
    call putch
    lw t2, 80(sp)
    sw t2, 176(sp)
    lw t0, 176(sp)
    li t1, 1
    add t2, t0, t1
    sw t2, 180(sp)
    lw t2, 180(sp)
    sw t2, 80(sp)
    j block_129
block_128:
    li t2, 0
    add a0, t2, x0
    lw ra, 204(sp)
    addi sp, sp, 208
    ret
