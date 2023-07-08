
    .data
    .global luoji
luoji:
    .zero 4

    .data
    .global dp
dp:
    .zero 52907904

    .data
    .global list
list:
    .zero 800

    .data
    .global cns
cns:
    .zero 80

    .text
    .globl equal
equal:
    addi sp, sp, -32
block_2:
    sw a0, 0(sp)
    sw a1, 4(sp)
    lw t2, 0(sp)
    sw t2, 8(sp)
    lw t2, 4(sp)
    sw t2, 12(sp)
    lw t5, 8(sp)
    lw t6, 12(sp)
    mv t0, t5
    mv t1, t6
    sub t2, t0, t1
    seqz t2, t2
    mv s0 , t2
    mv t2, s0
    bnez t2, block_0
    j block_1
block_0:
    li t2, 1
    add a0, t2, x0
    addi sp, sp, 32
    ret
block_1:
    li t2, 0
    add a0, t2, x0
    addi sp, sp, 32
    ret

    .text
    .globl dfs
dfs:
    addi sp, sp, -640
    sw ra, 636(sp)
block_38:
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    sw a3, 12(sp)
    sw a4, 16(sp)
    sw a5, 20(sp)
    lw t2, 0(sp)
    sw t2, 24(sp)
    lw t2, 24(sp)
    add a0,t2 ,x0
    call putint
    li t2, 32
    add a0,t2 ,x0
    call putch
    lw t2, 4(sp)
    sw t2, 28(sp)
    lw t2, 28(sp)
    add a0,t2 ,x0
    call putint
    li t2, 10
    add a0,t2 ,x0
    call putch
    lw t2, 0(sp)
    sw t2, 32(sp)
    la t4 , dp
    lw t1, 32(sp)
    li t2, 2939328
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 36(sp)
    lw t2, 4(sp)
    sw t2, 40(sp)
    lw t0, 36(sp)
    mv t4, t0
    lw t1, 40(sp)
    li t2, 163296
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 44(sp)
    lw t2, 8(sp)
    sw t2, 48(sp)
    lw t0, 44(sp)
    mv t4, t0
    lw t1, 48(sp)
    li t2, 9072
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 52(sp)
    lw t2, 12(sp)
    sw t2, 56(sp)
    lw t0, 52(sp)
    mv t4, t0
    lw t1, 56(sp)
    li t2, 504
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 60(sp)
    lw t2, 16(sp)
    sw t2, 64(sp)
    lw t0, 60(sp)
    mv t4, t0
    lw t1, 64(sp)
    li t2, 28
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 68(sp)
    lw t2, 20(sp)
    sw t2, 72(sp)
    lw t0, 68(sp)
    mv t4, t0
    lw t1, 72(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 76(sp)
    lw t0, 76(sp)
    lw t2, 0(t0)
    sw t2, 80(sp)
    li t0, 0
    li t1, 1
    sub t2, t0, t1
    mv t5 , t2
    lw t6, 80(sp)
    mv t0, t6
    mv t1, t5
    sub t2, t0, t1
    snez t2, t2
    mv s0 , t2
    mv t2, s0
    bnez t2, block_24
    j block_25
block_24:
    lw t2, 0(sp)
    sw t2, 92(sp)
    la t4 , dp
    lw t1, 92(sp)
    li t2, 2939328
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 96(sp)
    lw t2, 4(sp)
    sw t2, 100(sp)
    lw t0, 96(sp)
    mv t4, t0
    lw t1, 100(sp)
    li t2, 163296
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 104(sp)
    lw t2, 8(sp)
    sw t2, 108(sp)
    lw t0, 104(sp)
    mv t4, t0
    lw t1, 108(sp)
    li t2, 9072
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 112(sp)
    lw t2, 12(sp)
    sw t2, 116(sp)
    lw t0, 112(sp)
    mv t4, t0
    lw t1, 116(sp)
    li t2, 504
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 120(sp)
    lw t2, 16(sp)
    sw t2, 124(sp)
    lw t0, 120(sp)
    mv t4, t0
    lw t1, 124(sp)
    li t2, 28
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 128(sp)
    lw t2, 20(sp)
    sw t2, 132(sp)
    lw t0, 128(sp)
    mv t4, t0
    lw t1, 132(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 136(sp)
    lw t0, 136(sp)
    lw t2, 0(t0)
    sw t2, 140(sp)
    lw t2, 140(sp)
    add a0, t2, x0
    lw ra, 636(sp)
    addi sp, sp, 640
    ret
block_25:
    lw t2, 0(sp)
    sw t2, 144(sp)
    lw t2, 4(sp)
    sw t2, 148(sp)
    lw t5, 144(sp)
    lw t6, 148(sp)
    mv t0, t5
    mv t1, t6
    add t2, t0, t1
    mv s0 , t2
    lw t2, 8(sp)
    sw t2, 156(sp)
    lw s1, 156(sp)
    mv t0, s0
    mv t1, s1
    add t2, t0, t1
    mv s2 , t2
    lw t2, 12(sp)
    sw t2, 164(sp)
    lw s3, 164(sp)
    mv t0, s2
    mv t1, s3
    add t2, t0, t1
    mv s4 , t2
    lw t2, 16(sp)
    sw t2, 172(sp)
    lw s5, 172(sp)
    mv t0, s4
    mv t1, s5
    add t2, t0, t1
    mv s6 , t2
    mv t0, s6
    li t1, 0
    sub t2, t0, t1
    seqz t2, t2
    mv s7 , t2
    mv t2, s7
    bnez t2, block_54
    j block_55
block_54:
    li t2, 1
    add a0, t2, x0
    lw ra, 636(sp)
    addi sp, sp, 640
    ret
block_55:
    li t2, 0
    sw t2, 184(sp)
    lw t2, 0(sp)
    sw t2, 188(sp)
    lw t2, 188(sp)
    bnez t2, block_61
    j block_62
block_61:
    lw t2, 184(sp)
    sw t2, 192(sp)
    lw t2, 0(sp)
    sw t2, 196(sp)
    lw t2, 20(sp)
    sw t2, 200(sp)
    lw t2, 200(sp)
    add a0,t2 ,x0
    li t2, 2
    add a1,t2 ,x0
    call equal
    sw a0, 204(sp)
    lw t5, 196(sp)
    lw t6, 204(sp)
    mv t0, t5
    mv t1, t6
    sub t2, t0, t1
    mv s0 , t2
    lw t2, 0(sp)
    sw t2, 212(sp)
    lw s1, 212(sp)
    mv t0, s1
    li t1, 1
    sub t2, t0, t1
    mv s2 , t2
    lw t2, 4(sp)
    sw t2, 220(sp)
    lw t2, 8(sp)
    sw t2, 224(sp)
    lw t2, 12(sp)
    sw t2, 228(sp)
    lw t2, 16(sp)
    sw t2, 232(sp)
    mv t2, s2
    add a0,t2 ,x0
    lw t2, 220(sp)
    add a1,t2 ,x0
    lw t2, 224(sp)
    add a2,t2 ,x0
    lw t2, 228(sp)
    add a3,t2 ,x0
    lw t2, 232(sp)
    add a4,t2 ,x0
    li t2, 1
    add a5,t2 ,x0
    call dfs
    sw a0, 236(sp)
    lw s3, 236(sp)
    mv t0, s0
    mv t1, s3
    mul t2, t0, t1
    mv s4 , t2
    lw s5, 192(sp)
    mv t0, s5
    mv t1, s4
    add t2, t0, t1
    mv s6 , t2
    mv t0, s6
    li t1, 1000000007
    rem t2, t0, t1
    mv s7 , t2
    mv t2, s7
    sw t2, 184(sp)
    j block_62
block_62:
    lw t2, 4(sp)
    sw t2, 252(sp)
    lw t2, 252(sp)
    bnez t2, block_85
    j block_86
block_85:
    lw t2, 184(sp)
    sw t2, 256(sp)
    lw t2, 4(sp)
    sw t2, 260(sp)
    lw t2, 20(sp)
    sw t2, 264(sp)
    lw t2, 264(sp)
    add a0,t2 ,x0
    li t2, 3
    add a1,t2 ,x0
    call equal
    sw a0, 268(sp)
    lw t5, 260(sp)
    lw t6, 268(sp)
    mv t0, t5
    mv t1, t6
    sub t2, t0, t1
    mv s0 , t2
    lw t2, 0(sp)
    sw t2, 276(sp)
    lw s1, 276(sp)
    mv t0, s1
    li t1, 1
    add t2, t0, t1
    mv s2 , t2
    lw t2, 4(sp)
    sw t2, 284(sp)
    lw s3, 284(sp)
    mv t0, s3
    li t1, 1
    sub t2, t0, t1
    mv s4 , t2
    lw t2, 8(sp)
    sw t2, 292(sp)
    lw t2, 12(sp)
    sw t2, 296(sp)
    lw t2, 16(sp)
    sw t2, 300(sp)
    mv t2, s2
    add a0,t2 ,x0
    mv t2, s4
    add a1,t2 ,x0
    lw t2, 292(sp)
    add a2,t2 ,x0
    lw t2, 296(sp)
    add a3,t2 ,x0
    lw t2, 300(sp)
    add a4,t2 ,x0
    li t2, 2
    add a5,t2 ,x0
    call dfs
    sw a0, 304(sp)
    lw s5, 304(sp)
    mv t0, s0
    mv t1, s5
    mul t2, t0, t1
    mv s6 , t2
    lw s7, 256(sp)
    mv t0, s7
    mv t1, s6
    add t2, t0, t1
    mv s8 , t2
    mv t0, s8
    li t1, 1000000007
    rem t2, t0, t1
    mv s9 , t2
    mv t2, s9
    sw t2, 184(sp)
    j block_86
block_86:
    lw t2, 8(sp)
    sw t2, 320(sp)
    lw t2, 320(sp)
    bnez t2, block_109
    j block_110
block_109:
    lw t2, 184(sp)
    sw t2, 324(sp)
    lw t2, 8(sp)
    sw t2, 328(sp)
    lw t2, 20(sp)
    sw t2, 332(sp)
    lw t2, 332(sp)
    add a0,t2 ,x0
    li t2, 4
    add a1,t2 ,x0
    call equal
    sw a0, 336(sp)
    lw t5, 328(sp)
    lw t6, 336(sp)
    mv t0, t5
    mv t1, t6
    sub t2, t0, t1
    mv s0 , t2
    lw t2, 0(sp)
    sw t2, 344(sp)
    lw t2, 4(sp)
    sw t2, 348(sp)
    lw s1, 348(sp)
    mv t0, s1
    li t1, 1
    add t2, t0, t1
    mv s2 , t2
    lw t2, 8(sp)
    sw t2, 356(sp)
    lw s3, 356(sp)
    mv t0, s3
    li t1, 1
    sub t2, t0, t1
    mv s4 , t2
    lw t2, 12(sp)
    sw t2, 364(sp)
    lw t2, 16(sp)
    sw t2, 368(sp)
    lw t2, 344(sp)
    add a0,t2 ,x0
    mv t2, s2
    add a1,t2 ,x0
    mv t2, s4
    add a2,t2 ,x0
    lw t2, 364(sp)
    add a3,t2 ,x0
    lw t2, 368(sp)
    add a4,t2 ,x0
    li t2, 3
    add a5,t2 ,x0
    call dfs
    sw a0, 372(sp)
    lw s5, 372(sp)
    mv t0, s0
    mv t1, s5
    mul t2, t0, t1
    mv s6 , t2
    lw s7, 324(sp)
    mv t0, s7
    mv t1, s6
    add t2, t0, t1
    mv s8 , t2
    mv t0, s8
    li t1, 1000000007
    rem t2, t0, t1
    mv s9 , t2
    mv t2, s9
    sw t2, 184(sp)
    j block_110
block_110:
    lw t2, 12(sp)
    sw t2, 388(sp)
    lw t2, 388(sp)
    bnez t2, block_133
    j block_134
block_133:
    lw t2, 184(sp)
    sw t2, 392(sp)
    lw t2, 12(sp)
    sw t2, 396(sp)
    lw t2, 20(sp)
    sw t2, 400(sp)
    lw t2, 400(sp)
    add a0,t2 ,x0
    li t2, 5
    add a1,t2 ,x0
    call equal
    sw a0, 404(sp)
    lw t5, 396(sp)
    lw t6, 404(sp)
    mv t0, t5
    mv t1, t6
    sub t2, t0, t1
    mv s0 , t2
    lw t2, 0(sp)
    sw t2, 412(sp)
    lw t2, 4(sp)
    sw t2, 416(sp)
    lw t2, 8(sp)
    sw t2, 420(sp)
    lw s1, 420(sp)
    mv t0, s1
    li t1, 1
    add t2, t0, t1
    mv s2 , t2
    lw t2, 12(sp)
    sw t2, 428(sp)
    lw s3, 428(sp)
    mv t0, s3
    li t1, 1
    sub t2, t0, t1
    mv s4 , t2
    lw t2, 16(sp)
    sw t2, 436(sp)
    lw t2, 412(sp)
    add a0,t2 ,x0
    lw t2, 416(sp)
    add a1,t2 ,x0
    mv t2, s2
    add a2,t2 ,x0
    mv t2, s4
    add a3,t2 ,x0
    lw t2, 436(sp)
    add a4,t2 ,x0
    li t2, 4
    add a5,t2 ,x0
    call dfs
    sw a0, 440(sp)
    lw s5, 440(sp)
    mv t0, s0
    mv t1, s5
    mul t2, t0, t1
    mv s6 , t2
    lw s7, 392(sp)
    mv t0, s7
    mv t1, s6
    add t2, t0, t1
    mv s8 , t2
    mv t0, s8
    li t1, 1000000007
    rem t2, t0, t1
    mv s9 , t2
    mv t2, s9
    sw t2, 184(sp)
    j block_134
block_134:
    lw t2, 16(sp)
    sw t2, 456(sp)
    lw t2, 456(sp)
    bnez t2, block_157
    j block_158
block_157:
    lw t2, 184(sp)
    sw t2, 460(sp)
    lw t2, 16(sp)
    sw t2, 464(sp)
    lw t2, 0(sp)
    sw t2, 468(sp)
    lw t2, 4(sp)
    sw t2, 472(sp)
    lw t2, 8(sp)
    sw t2, 476(sp)
    lw t2, 12(sp)
    sw t2, 480(sp)
    lw t5, 480(sp)
    mv t0, t5
    li t1, 1
    add t2, t0, t1
    mv t6 , t2
    lw t2, 16(sp)
    sw t2, 488(sp)
    lw s0, 488(sp)
    mv t0, s0
    li t1, 1
    sub t2, t0, t1
    mv s1 , t2
    lw t2, 468(sp)
    add a0,t2 ,x0
    lw t2, 472(sp)
    add a1,t2 ,x0
    lw t2, 476(sp)
    add a2,t2 ,x0
    mv t2, t6
    add a3,t2 ,x0
    mv t2, s1
    add a4,t2 ,x0
    li t2, 5
    add a5,t2 ,x0
    call dfs
    sw a0, 496(sp)
    lw s2, 464(sp)
    lw s3, 496(sp)
    mv t0, s2
    mv t1, s3
    mul t2, t0, t1
    mv s4 , t2
    lw s5, 460(sp)
    mv t0, s5
    mv t1, s4
    add t2, t0, t1
    mv s6 , t2
    mv t0, s6
    li t1, 1000000007
    rem t2, t0, t1
    mv s7 , t2
    mv t2, s7
    sw t2, 184(sp)
    j block_158
block_158:
    lw t2, 184(sp)
    sw t2, 512(sp)
    lw t2, 512(sp)
    add a0,t2 ,x0
    call putint
    li t2, 10
    add a0,t2 ,x0
    call putch
    lw t2, 184(sp)
    sw t2, 516(sp)
    lw t5, 516(sp)
    mv t0, t5
    li t1, 1000000007
    rem t2, t0, t1
    mv t6 , t2
    lw t2, 0(sp)
    sw t2, 524(sp)
    la t4 , dp
    lw t1, 524(sp)
    li t2, 2939328
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 528(sp)
    lw t2, 4(sp)
    sw t2, 532(sp)
    lw t0, 528(sp)
    mv t4, t0
    lw t1, 532(sp)
    li t2, 163296
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 536(sp)
    lw t2, 8(sp)
    sw t2, 540(sp)
    lw t0, 536(sp)
    mv t4, t0
    lw t1, 540(sp)
    li t2, 9072
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 544(sp)
    lw t2, 12(sp)
    sw t2, 548(sp)
    lw t0, 544(sp)
    mv t4, t0
    lw t1, 548(sp)
    li t2, 504
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 552(sp)
    lw t2, 16(sp)
    sw t2, 556(sp)
    lw t0, 552(sp)
    mv t4, t0
    lw t1, 556(sp)
    li t2, 28
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 560(sp)
    lw t2, 20(sp)
    sw t2, 564(sp)
    lw t0, 560(sp)
    mv t4, t0
    lw t1, 564(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 568(sp)
    mv t2, t6
    lw t0, 568(sp)
    sw t2, 0(t0)
    lw t2, 0(sp)
    sw t2, 572(sp)
    la t4 , dp
    lw t1, 572(sp)
    li t2, 2939328
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 576(sp)
    lw t2, 4(sp)
    sw t2, 580(sp)
    lw t0, 576(sp)
    mv t4, t0
    lw t1, 580(sp)
    li t2, 163296
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 584(sp)
    lw t2, 8(sp)
    sw t2, 588(sp)
    lw t0, 584(sp)
    mv t4, t0
    lw t1, 588(sp)
    li t2, 9072
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 592(sp)
    lw t2, 12(sp)
    sw t2, 596(sp)
    lw t0, 592(sp)
    mv t4, t0
    lw t1, 596(sp)
    li t2, 504
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 600(sp)
    lw t2, 16(sp)
    sw t2, 604(sp)
    lw t0, 600(sp)
    mv t4, t0
    lw t1, 604(sp)
    li t2, 28
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 608(sp)
    lw t2, 20(sp)
    sw t2, 612(sp)
    lw t0, 608(sp)
    mv t4, t0
    lw t1, 612(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 616(sp)
    lw t0, 616(sp)
    lw t2, 0(t0)
    sw t2, 620(sp)
    lw t2, 620(sp)
    add a0, t2, x0
    lw ra, 636(sp)
    addi sp, sp, 640
    ret

    .text
    .globl main
main:
    addi sp, sp, -304
    sw ra, 300(sp)
block_218:
    li t2, 5
    sw t2, 0(sp)
    li t2, 0
    sw t2, 4(sp)
    j block_217
block_217:
    lw t2, 4(sp)
    sw t2, 8(sp)
    lw t5, 8(sp)
    mv t0, t5
    li t1, 18
    slt t2, t0, t1
    mv t6 , t2
    mv t2, t6
    bnez t2, block_215
    j block_216
block_215:
    li t2, 0
    sw t2, 16(sp)
    j block_223
block_223:
    lw t2, 16(sp)
    sw t2, 20(sp)
    lw t5, 20(sp)
    mv t0, t5
    li t1, 18
    slt t2, t0, t1
    mv t6 , t2
    mv t2, t6
    bnez t2, block_221
    j block_222
block_221:
    li t2, 0
    sw t2, 28(sp)
    j block_228
block_228:
    lw t2, 28(sp)
    sw t2, 32(sp)
    lw t5, 32(sp)
    mv t0, t5
    li t1, 18
    slt t2, t0, t1
    mv t6 , t2
    mv t2, t6
    bnez t2, block_226
    j block_227
block_226:
    li t2, 0
    sw t2, 40(sp)
    j block_233
block_233:
    lw t2, 40(sp)
    sw t2, 44(sp)
    lw t5, 44(sp)
    mv t0, t5
    li t1, 18
    slt t2, t0, t1
    mv t6 , t2
    mv t2, t6
    bnez t2, block_231
    j block_232
block_231:
    li t2, 0
    sw t2, 52(sp)
    j block_238
block_238:
    lw t2, 52(sp)
    sw t2, 56(sp)
    lw t5, 56(sp)
    mv t0, t5
    li t1, 18
    slt t2, t0, t1
    mv t6 , t2
    mv t2, t6
    bnez t2, block_236
    j block_237
block_236:
    li t2, 0
    sw t2, 64(sp)
    j block_243
block_243:
    lw t2, 64(sp)
    sw t2, 68(sp)
    lw t5, 68(sp)
    mv t0, t5
    li t1, 7
    slt t2, t0, t1
    mv t6 , t2
    mv t2, t6
    bnez t2, block_241
    j block_242
block_241:
    li t0, 0
    li t1, 1
    sub t2, t0, t1
    mv t5 , t2
    lw t2, 4(sp)
    sw t2, 80(sp)
    la t4 , dp
    lw t1, 80(sp)
    li t2, 2939328
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 84(sp)
    lw t2, 16(sp)
    sw t2, 88(sp)
    lw t0, 84(sp)
    mv t4, t0
    lw t1, 88(sp)
    li t2, 163296
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 92(sp)
    lw t2, 28(sp)
    sw t2, 96(sp)
    lw t0, 92(sp)
    mv t4, t0
    lw t1, 96(sp)
    li t2, 9072
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 100(sp)
    lw t2, 40(sp)
    sw t2, 104(sp)
    lw t0, 100(sp)
    mv t4, t0
    lw t1, 104(sp)
    li t2, 504
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 108(sp)
    lw t2, 52(sp)
    sw t2, 112(sp)
    lw t0, 108(sp)
    mv t4, t0
    lw t1, 112(sp)
    li t2, 28
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 116(sp)
    lw t2, 64(sp)
    sw t2, 120(sp)
    lw t0, 116(sp)
    mv t4, t0
    lw t1, 120(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 124(sp)
    mv t2, t5
    lw t0, 124(sp)
    sw t2, 0(t0)
    lw t2, 64(sp)
    sw t2, 128(sp)
    lw t6, 128(sp)
    mv t0, t6
    li t1, 1
    add t2, t0, t1
    mv s0 , t2
    mv t2, s0
    sw t2, 64(sp)
    j block_243
block_242:
    lw t2, 52(sp)
    sw t2, 136(sp)
    lw t5, 136(sp)
    mv t0, t5
    li t1, 1
    add t2, t0, t1
    mv t6 , t2
    mv t2, t6
    sw t2, 52(sp)
    j block_238
block_237:
    lw t2, 40(sp)
    sw t2, 144(sp)
    lw t5, 144(sp)
    mv t0, t5
    li t1, 1
    add t2, t0, t1
    mv t6 , t2
    mv t2, t6
    sw t2, 40(sp)
    j block_233
block_232:
    lw t2, 28(sp)
    sw t2, 152(sp)
    lw t5, 152(sp)
    mv t0, t5
    li t1, 1
    add t2, t0, t1
    mv t6 , t2
    mv t2, t6
    sw t2, 28(sp)
    j block_228
block_227:
    lw t2, 16(sp)
    sw t2, 160(sp)
    lw t5, 160(sp)
    mv t0, t5
    li t1, 1
    add t2, t0, t1
    mv t6 , t2
    mv t2, t6
    sw t2, 16(sp)
    j block_223
block_222:
    lw t2, 4(sp)
    sw t2, 168(sp)
    lw t5, 168(sp)
    mv t0, t5
    li t1, 1
    add t2, t0, t1
    mv t6 , t2
    mv t2, t6
    sw t2, 4(sp)
    j block_217
block_216:
    li t2, 0
    sw t2, 4(sp)
    j block_274
block_274:
    lw t2, 4(sp)
    sw t2, 176(sp)
    lw t2, 0(sp)
    sw t2, 180(sp)
    lw t5, 176(sp)
    lw t6, 180(sp)
    mv t0, t5
    mv t1, t6
    slt t2, t0, t1
    mv s0 , t2
    mv t2, s0
    bnez t2, block_272
    j block_273
block_272:
    lw t2, 4(sp)
    sw t2, 188(sp)
    la t4 , list
    lw t1, 188(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 192(sp)
    li t2, 2
    lw t0, 192(sp)
    sw t2, 0(t0)
    lw t2, 4(sp)
    sw t2, 196(sp)
    la t4 , list
    lw t1, 196(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 200(sp)
    lw t0, 200(sp)
    lw t2, 0(t0)
    sw t2, 204(sp)
    la t4 , cns
    lw t1, 204(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 208(sp)
    lw t0, 208(sp)
    lw t2, 0(t0)
    sw t2, 212(sp)
    lw t5, 212(sp)
    mv t0, t5
    li t1, 1
    add t2, t0, t1
    mv t6 , t2
    lw t2, 4(sp)
    sw t2, 220(sp)
    la t4 , list
    lw t1, 220(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 224(sp)
    lw t0, 224(sp)
    lw t2, 0(t0)
    sw t2, 228(sp)
    la t4 , cns
    lw t1, 228(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 232(sp)
    mv t2, t6
    lw t0, 232(sp)
    sw t2, 0(t0)
    lw t2, 4(sp)
    sw t2, 236(sp)
    lw s0, 236(sp)
    mv t0, s0
    li t1, 1
    add t2, t0, t1
    mv s1 , t2
    mv t2, s1
    sw t2, 4(sp)
    j block_274
block_273:
    la t4 , cns
    li t1, 1
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 244(sp)
    lw t0, 244(sp)
    lw t2, 0(t0)
    sw t2, 248(sp)
    la t4 , cns
    li t1, 2
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 252(sp)
    lw t0, 252(sp)
    lw t2, 0(t0)
    sw t2, 256(sp)
    la t4 , cns
    li t1, 3
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 260(sp)
    lw t0, 260(sp)
    lw t2, 0(t0)
    sw t2, 264(sp)
    la t4 , cns
    li t1, 4
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 268(sp)
    lw t0, 268(sp)
    lw t2, 0(t0)
    sw t2, 272(sp)
    la t4 , cns
    li t1, 5
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 276(sp)
    lw t0, 276(sp)
    lw t2, 0(t0)
    sw t2, 280(sp)
    lw t2, 248(sp)
    add a0,t2 ,x0
    lw t2, 256(sp)
    add a1,t2 ,x0
    lw t2, 264(sp)
    add a2,t2 ,x0
    lw t2, 272(sp)
    add a3,t2 ,x0
    lw t2, 280(sp)
    add a4,t2 ,x0
    li t2, 0
    add a5,t2 ,x0
    call dfs
    sw a0, 284(sp)
    lw t2, 284(sp)
    sw t2, 288(sp)
    lw t2, 288(sp)
    sw t2, 292(sp)
    lw t2, 292(sp)
    add a0,t2 ,x0
    call putint
    lw t2, 288(sp)
    sw t2, 296(sp)
    lw t2, 296(sp)
    add a0, t2, x0
    lw ra, 300(sp)
    addi sp, sp, 304
    ret
