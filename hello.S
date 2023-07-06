
    .data
    .global luoji
luoji:
    .zero 4

    .data
    .global temp
temp:
    .zero 8388608

    .data
    .global w
w:
    .zero 8388608

    .data
    .global dst
dst:
    .zero 8388608

    .data
    .global c
c:
    .zero 8388608

    .text
    .globl getvalue
getvalue:
    addi sp, sp, -96
block_5:
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    sw a3, 12(sp)
    lw t2, 8(sp)
    sw t2, 16(sp)
    lw t0, 16(sp)
    li t1, 0
    slt t2, t0, t1
    sw t2, 20(sp)
    lw t2, 20(sp)
    bnez t2, block_0
    j block_4
block_4:
    lw t2, 8(sp)
    sw t2, 24(sp)
    lw t2, 4(sp)
    sw t2, 28(sp)
    lw t0, 24(sp)
    lw t1, 28(sp)
    slt t2, t0, t1
    seqz  t2, t2
    sw t2, 32(sp)
    lw t2, 32(sp)
    bnez t2, block_0
    j block_3
block_3:
    lw t2, 12(sp)
    sw t2, 36(sp)
    lw t0, 36(sp)
    li t1, 0
    slt t2, t0, t1
    sw t2, 40(sp)
    lw t2, 40(sp)
    bnez t2, block_0
    j block_2
block_2:
    lw t2, 12(sp)
    sw t2, 44(sp)
    lw t2, 4(sp)
    sw t2, 48(sp)
    lw t0, 44(sp)
    lw t1, 48(sp)
    slt t2, t0, t1
    seqz  t2, t2
    sw t2, 52(sp)
    lw t2, 52(sp)
    bnez t2, block_0
    j block_1
block_0:
    li t0, 0
    li t1, 1
    sub t2, t0, t1
    sw t2, 56(sp)
    lw t2, 56(sp)
    add a0, t2, x0
    addi sp, sp, 96
    ret
block_1:
    lw t2, 0(sp)
    sw t2, 60(sp)
    lw t2, 8(sp)
    sw t2, 64(sp)
    lw t2, 4(sp)
    sw t2, 68(sp)
    lw t0, 64(sp)
    lw t1, 68(sp)
    mul t2, t0, t1
    sw t2, 72(sp)
    lw t2, 12(sp)
    sw t2, 76(sp)
    lw t0, 72(sp)
    lw t1, 76(sp)
    add t2, t0, t1
    sw t2, 80(sp)
    lw t0, 0(sp)
    mv t4, t0
    lw t1, 80(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 84(sp)
    lw t0, 84(sp)
    lw t2, 0(t0)
    sw t2, 88(sp)
    lw t2, 88(sp)
    add a0, t2, x0
    addi sp, sp, 96
    ret

    .text
    .globl mem_move
mem_move:
    addi sp, sp, -64
block_18:
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    li t2, 0
    sw t2, 12(sp)
    j block_17
block_17:
    lw t2, 12(sp)
    sw t2, 16(sp)
    lw t2, 8(sp)
    sw t2, 20(sp)
    lw t0, 16(sp)
    lw t1, 20(sp)
    slt t2, t0, t1
    sw t2, 24(sp)
    lw t2, 24(sp)
    bnez t2, block_15
    j block_16
block_15:
    lw t2, 0(sp)
    sw t2, 28(sp)
    lw t2, 12(sp)
    sw t2, 32(sp)
    lw t0, 0(sp)
    mv t4, t0
    lw t1, 32(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 36(sp)
    lw t0, 36(sp)
    lw t2, 0(t0)
    sw t2, 40(sp)
    lw t2, 4(sp)
    sw t2, 44(sp)
    lw t2, 12(sp)
    sw t2, 48(sp)
    lw t0, 4(sp)
    mv t4, t0
    lw t1, 48(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 52(sp)
    lw t2, 40(sp)
    lw t0, 52(sp)
    sw t2, 0(t0)
    lw t2, 12(sp)
    sw t2, 56(sp)
    lw t0, 56(sp)
    li t1, 1
    add t2, t0, t1
    sw t2, 60(sp)
    lw t2, 60(sp)
    sw t2, 12(sp)
    j block_17
block_16:
    addi sp, sp, 64
    ret

    .text
    .globl floyd
floyd:
    addi sp, sp, -480
    sw ra, 476(sp)
block_32:
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    li t2, 0
    sw t2, 12(sp)
    j block_31
block_31:
    lw t2, 12(sp)
    sw t2, 16(sp)
    lw t2, 8(sp)
    sw t2, 20(sp)
    lw t0, 16(sp)
    lw t1, 20(sp)
    slt t2, t0, t1
    sw t2, 24(sp)
    lw t2, 24(sp)
    bnez t2, block_29
    j block_30
block_29:
    li t2, 0
    sw t2, 28(sp)
    j block_37
block_37:
    lw t2, 28(sp)
    sw t2, 32(sp)
    lw t2, 8(sp)
    sw t2, 36(sp)
    lw t0, 32(sp)
    lw t1, 36(sp)
    slt t2, t0, t1
    sw t2, 40(sp)
    lw t2, 40(sp)
    bnez t2, block_35
    j block_36
block_35:
    lw t2, 0(sp)
    sw t2, 44(sp)
    lw t2, 8(sp)
    sw t2, 48(sp)
    lw t2, 28(sp)
    sw t2, 52(sp)
    lw t2, 12(sp)
    sw t2, 56(sp)
    lw t2, 44(sp)
    add a0,t2 ,x0
    lw t2, 48(sp)
    add a1,t2 ,x0
    lw t2, 52(sp)
    add a2,t2 ,x0
    lw t2, 56(sp)
    add a3,t2 ,x0
    call getvalue
    sw a0, 60(sp)
    lw t2, 28(sp)
    sw t2, 64(sp)
    lw t2, 8(sp)
    sw t2, 68(sp)
    lw t0, 64(sp)
    lw t1, 68(sp)
    mul t2, t0, t1
    sw t2, 72(sp)
    lw t2, 12(sp)
    sw t2, 76(sp)
    lw t0, 72(sp)
    lw t1, 76(sp)
    add t2, t0, t1
    sw t2, 80(sp)
    la t4 , temp
    lw t1, 80(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 84(sp)
    lw t2, 60(sp)
    lw t0, 84(sp)
    sw t2, 0(t0)
    lw t2, 28(sp)
    sw t2, 88(sp)
    lw t0, 88(sp)
    li t1, 1
    add t2, t0, t1
    sw t2, 92(sp)
    lw t2, 92(sp)
    sw t2, 28(sp)
    j block_37
block_36:
    lw t2, 12(sp)
    sw t2, 96(sp)
    lw t0, 96(sp)
    li t1, 1
    add t2, t0, t1
    sw t2, 100(sp)
    lw t2, 100(sp)
    sw t2, 12(sp)
    j block_31
block_30:
    li t2, 0
    sw t2, 12(sp)
    j block_58
block_58:
    lw t2, 12(sp)
    sw t2, 104(sp)
    lw t2, 8(sp)
    sw t2, 108(sp)
    lw t0, 104(sp)
    lw t1, 108(sp)
    slt t2, t0, t1
    sw t2, 112(sp)
    lw t2, 112(sp)
    bnez t2, block_56
    j block_57
block_56:
    li t2, 0
    sw t2, 116(sp)
    j block_63
block_63:
    lw t2, 116(sp)
    sw t2, 120(sp)
    lw t2, 8(sp)
    sw t2, 124(sp)
    lw t0, 120(sp)
    lw t1, 124(sp)
    slt t2, t0, t1
    sw t2, 128(sp)
    lw t2, 128(sp)
    bnez t2, block_61
    j block_62
block_61:
    li t2, 0
    sw t2, 132(sp)
    j block_68
block_68:
    lw t2, 132(sp)
    sw t2, 136(sp)
    lw t2, 8(sp)
    sw t2, 140(sp)
    lw t0, 136(sp)
    lw t1, 140(sp)
    slt t2, t0, t1
    sw t2, 144(sp)
    lw t2, 144(sp)
    bnez t2, block_66
    j block_67
block_66:
    la t4 , temp
    li t1, 0
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 148(sp)
    lw t2, 8(sp)
    sw t2, 152(sp)
    lw t2, 116(sp)
    sw t2, 156(sp)
    lw t2, 12(sp)
    sw t2, 160(sp)
    lw t2, 148(sp)
    add a0,t2 ,x0
    lw t2, 152(sp)
    add a1,t2 ,x0
    lw t2, 156(sp)
    add a2,t2 ,x0
    lw t2, 160(sp)
    add a3,t2 ,x0
    call getvalue
    sw a0, 164(sp)
    lw t0, 164(sp)
    li t1, 0
    slt t2, t0, t1
    seqz  t2, t2
    sw t2, 168(sp)
    lw t2, 168(sp)
    bnez t2, block_71
    j block_70
block_71:
    la t4 , temp
    li t1, 0
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 172(sp)
    lw t2, 8(sp)
    sw t2, 176(sp)
    lw t2, 12(sp)
    sw t2, 180(sp)
    lw t2, 132(sp)
    sw t2, 184(sp)
    lw t2, 172(sp)
    add a0,t2 ,x0
    lw t2, 176(sp)
    add a1,t2 ,x0
    lw t2, 180(sp)
    add a2,t2 ,x0
    lw t2, 184(sp)
    add a3,t2 ,x0
    call getvalue
    sw a0, 188(sp)
    lw t0, 188(sp)
    li t1, 0
    slt t2, t0, t1
    seqz  t2, t2
    sw t2, 192(sp)
    lw t2, 192(sp)
    bnez t2, block_69
    j block_70
block_69:
    la t4 , temp
    li t1, 0
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 196(sp)
    lw t2, 8(sp)
    sw t2, 200(sp)
    lw t2, 116(sp)
    sw t2, 204(sp)
    lw t2, 132(sp)
    sw t2, 208(sp)
    lw t2, 196(sp)
    add a0,t2 ,x0
    lw t2, 200(sp)
    add a1,t2 ,x0
    lw t2, 204(sp)
    add a2,t2 ,x0
    lw t2, 208(sp)
    add a3,t2 ,x0
    call getvalue
    sw a0, 212(sp)
    lw t0, 212(sp)
    li t1, 0
    slt t2, t0, t1
    sw t2, 216(sp)
    lw t2, 216(sp)
    bnez t2, block_88
    j block_89
block_88:
    la t4 , temp
    li t1, 0
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 220(sp)
    lw t2, 8(sp)
    sw t2, 224(sp)
    lw t2, 116(sp)
    sw t2, 228(sp)
    lw t2, 12(sp)
    sw t2, 232(sp)
    lw t2, 220(sp)
    add a0,t2 ,x0
    lw t2, 224(sp)
    add a1,t2 ,x0
    lw t2, 228(sp)
    add a2,t2 ,x0
    lw t2, 232(sp)
    add a3,t2 ,x0
    call getvalue
    sw a0, 236(sp)
    la t4 , temp
    li t1, 0
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 240(sp)
    lw t2, 8(sp)
    sw t2, 244(sp)
    lw t2, 12(sp)
    sw t2, 248(sp)
    lw t2, 132(sp)
    sw t2, 252(sp)
    lw t2, 240(sp)
    add a0,t2 ,x0
    lw t2, 244(sp)
    add a1,t2 ,x0
    lw t2, 248(sp)
    add a2,t2 ,x0
    lw t2, 252(sp)
    add a3,t2 ,x0
    call getvalue
    sw a0, 256(sp)
    lw t0, 236(sp)
    lw t1, 256(sp)
    add t2, t0, t1
    sw t2, 260(sp)
    lw t2, 116(sp)
    sw t2, 264(sp)
    lw t2, 8(sp)
    sw t2, 268(sp)
    lw t0, 264(sp)
    lw t1, 268(sp)
    mul t2, t0, t1
    sw t2, 272(sp)
    lw t2, 132(sp)
    sw t2, 276(sp)
    lw t0, 272(sp)
    lw t1, 276(sp)
    add t2, t0, t1
    sw t2, 280(sp)
    la t4 , temp
    lw t1, 280(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 284(sp)
    lw t2, 260(sp)
    lw t0, 284(sp)
    sw t2, 0(t0)
    j block_90
block_89:
    lw t2, 116(sp)
    sw t2, 288(sp)
    lw t2, 8(sp)
    sw t2, 292(sp)
    lw t0, 288(sp)
    lw t1, 292(sp)
    mul t2, t0, t1
    sw t2, 296(sp)
    lw t2, 132(sp)
    sw t2, 300(sp)
    lw t0, 296(sp)
    lw t1, 300(sp)
    add t2, t0, t1
    sw t2, 304(sp)
    la t4 , temp
    lw t1, 304(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 308(sp)
    lw t0, 308(sp)
    lw t2, 0(t0)
    sw t2, 312(sp)
    la t4 , temp
    li t1, 0
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 316(sp)
    lw t2, 8(sp)
    sw t2, 320(sp)
    lw t2, 116(sp)
    sw t2, 324(sp)
    lw t2, 12(sp)
    sw t2, 328(sp)
    lw t2, 316(sp)
    add a0,t2 ,x0
    lw t2, 320(sp)
    add a1,t2 ,x0
    lw t2, 324(sp)
    add a2,t2 ,x0
    lw t2, 328(sp)
    add a3,t2 ,x0
    call getvalue
    sw a0, 332(sp)
    la t4 , temp
    li t1, 0
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 336(sp)
    lw t2, 8(sp)
    sw t2, 340(sp)
    lw t2, 12(sp)
    sw t2, 344(sp)
    lw t2, 132(sp)
    sw t2, 348(sp)
    lw t2, 336(sp)
    add a0,t2 ,x0
    lw t2, 340(sp)
    add a1,t2 ,x0
    lw t2, 344(sp)
    add a2,t2 ,x0
    lw t2, 348(sp)
    add a3,t2 ,x0
    call getvalue
    sw a0, 352(sp)
    lw t0, 332(sp)
    lw t1, 352(sp)
    add t2, t0, t1
    sw t2, 356(sp)
    lw t0, 312(sp)
    lw t1, 356(sp)
    sgt t2, t0, t1
    sw t2, 360(sp)
    lw t2, 360(sp)
    bnez t2, block_119
    j block_120
block_119:
    la t4 , temp
    li t1, 0
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 364(sp)
    lw t2, 8(sp)
    sw t2, 368(sp)
    lw t2, 116(sp)
    sw t2, 372(sp)
    lw t2, 12(sp)
    sw t2, 376(sp)
    lw t2, 364(sp)
    add a0,t2 ,x0
    lw t2, 368(sp)
    add a1,t2 ,x0
    lw t2, 372(sp)
    add a2,t2 ,x0
    lw t2, 376(sp)
    add a3,t2 ,x0
    call getvalue
    sw a0, 380(sp)
    la t4 , temp
    li t1, 0
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 384(sp)
    lw t2, 8(sp)
    sw t2, 388(sp)
    lw t2, 12(sp)
    sw t2, 392(sp)
    lw t2, 132(sp)
    sw t2, 396(sp)
    lw t2, 384(sp)
    add a0,t2 ,x0
    lw t2, 388(sp)
    add a1,t2 ,x0
    lw t2, 392(sp)
    add a2,t2 ,x0
    lw t2, 396(sp)
    add a3,t2 ,x0
    call getvalue
    sw a0, 400(sp)
    lw t0, 380(sp)
    lw t1, 400(sp)
    add t2, t0, t1
    sw t2, 404(sp)
    lw t2, 116(sp)
    sw t2, 408(sp)
    lw t2, 8(sp)
    sw t2, 412(sp)
    lw t0, 408(sp)
    lw t1, 412(sp)
    mul t2, t0, t1
    sw t2, 416(sp)
    lw t2, 132(sp)
    sw t2, 420(sp)
    lw t0, 416(sp)
    lw t1, 420(sp)
    add t2, t0, t1
    sw t2, 424(sp)
    la t4 , temp
    lw t1, 424(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 428(sp)
    lw t2, 404(sp)
    lw t0, 428(sp)
    sw t2, 0(t0)
    j block_120
block_120:
    j block_90
block_90:
    j block_70
block_70:
    lw t2, 132(sp)
    sw t2, 432(sp)
    lw t0, 432(sp)
    li t1, 1
    add t2, t0, t1
    sw t2, 436(sp)
    lw t2, 436(sp)
    sw t2, 132(sp)
    j block_68
block_67:
    lw t2, 116(sp)
    sw t2, 440(sp)
    lw t0, 440(sp)
    li t1, 1
    add t2, t0, t1
    sw t2, 444(sp)
    lw t2, 444(sp)
    sw t2, 116(sp)
    j block_63
block_62:
    lw t2, 12(sp)
    sw t2, 448(sp)
    lw t0, 448(sp)
    li t1, 1
    add t2, t0, t1
    sw t2, 452(sp)
    lw t2, 452(sp)
    sw t2, 12(sp)
    j block_58
block_57:
    la t4 , temp
    li t1, 0
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 456(sp)
    lw t2, 4(sp)
    sw t2, 460(sp)
    lw t2, 8(sp)
    sw t2, 464(sp)
    lw t2, 8(sp)
    sw t2, 468(sp)
    lw t0, 464(sp)
    lw t1, 468(sp)
    mul t2, t0, t1
    sw t2, 472(sp)
    lw t2, 456(sp)
    add a0,t2 ,x0
    lw t2, 460(sp)
    add a1,t2 ,x0
    lw t2, 472(sp)
    add a2,t2 ,x0
    call mem_move
    lw ra, 476(sp)
    addi sp, sp, 480
    ret

    .text
    .globl main
main:
    addi sp, sp, -48
    sw ra, 44(sp)
block_199:
    call getint
    sw a0, 0(sp)
    lw t2, 0(sp)
    sw t2, 4(sp)
    la t4 , w
    li t1, 0
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 8(sp)
    lw t2, 8(sp)
    add a0,t2 ,x0
    call getarray
    sw a0, 12(sp)
    call starttime
    la t4 , w
    li t1, 0
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 16(sp)
    la t4 , dst
    li t1, 0
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 20(sp)
    lw t2, 4(sp)
    sw t2, 24(sp)
    lw t2, 16(sp)
    add a0,t2 ,x0
    lw t2, 20(sp)
    add a1,t2 ,x0
    lw t2, 24(sp)
    add a2,t2 ,x0
    call floyd
    call stoptime
    lw t2, 4(sp)
    sw t2, 28(sp)
    lw t2, 4(sp)
    sw t2, 32(sp)
    lw t0, 28(sp)
    lw t1, 32(sp)
    mul t2, t0, t1
    sw t2, 36(sp)
    la t4 , dst
    li t1, 0
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 40(sp)
    lw t2, 36(sp)
    add a0,t2 ,x0
    lw t2, 40(sp)
    add a1,t2 ,x0
    call putarray
    li t2, 0
    add a0, t2, x0
    lw ra, 44(sp)
    addi sp, sp, 48
    ret
