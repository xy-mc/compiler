block_8:
    lw t2, 0(sp)
    sw t2, 84(sp)
    la t4 , dp
    lw t1, 84(sp)
    li t2, 2939328
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 88(sp)
    lw t2, 4(sp)
    sw t2, 92(sp)
    lw t0, 88(sp)
    mv t4, t0
    lw t1, 92(sp)
    li t2, 163296
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 96(sp)
    lw t2, 8(sp)
    sw t2, 100(sp)
    lw t0, 96(sp)
    mv t4, t0
    lw t1, 100(sp)
    li t2, 9072
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 104(sp)
    lw t2, 12(sp)
    sw t2, 108(sp)
    lw t0, 104(sp)
    mv t4, t0
    lw t1, 108(sp)
    li t2, 504
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 112(sp)
    lw t2, 16(sp)
    sw t2, 116(sp)
    lw t0, 112(sp)
    mv t4, t0
    lw t1, 116(sp)
    li t2, 28
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 120(sp)
    lw t2, 20(sp)
    sw t2, 124(sp)
    lw t0, 120(sp)
    mv t4, t0
    lw t1, 124(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 128(sp)
    lw t0, 128(sp)
    lw t2, 0(t0)
    sw t2, 132(sp)
    lw t2, 132(sp)
    add a0, t2, x0
    lw ra, 620(sp)
    addi sp, sp, 624
    ret
block_9:
    lw t2, 0(sp)
    sw t2, 136(sp)
    lw t2, 4(sp)
    sw t2, 140(sp)
    lw t0, 136(sp)
    lw t1, 140(sp)
    add t2, t0, t1
    sw t2, 144(sp)
    lw t2, 8(sp)
    sw t2, 148(sp)
    lw t0, 144(sp)
    lw t1, 148(sp)
    add t2, t0, t1
    sw t2, 152(sp)
    lw t2, 12(sp)
    sw t2, 156(sp)
    lw t0, 152(sp)
    lw t1, 156(sp)
    add t2, t0, t1
    sw t2, 160(sp)
    lw t2, 16(sp)
    sw t2, 164(sp)
    lw t0, 160(sp)
    lw t1, 164(sp)
    add t2, t0, t1
    sw t2, 168(sp)
    lw t0, 168(sp)
    li t1, 0
    sub t2, t0, t1
    seqz t2, t2
    sw t2, 172(sp)
    lw t2, 172(sp)
    bnez t2, block_38
    j block_39
block_38:
    li t2, 1
    add a0, t2, x0
    lw ra, 620(sp)
    addi sp, sp, 624
    ret
block_39:
    li t2, 0
    sw t2, 176(sp)
    lw t2, 0(sp)
    sw t2, 180(sp)
    lw t2, 180(sp)
    bnez t2, block_45
    j block_46
block_45:
    lw t2, 176(sp)
    sw t2, 184(sp)
    lw t2, 0(sp)
    sw t2, 188(sp)
    lw t2, 20(sp)
    sw t2, 192(sp)
    lw t2, 192(sp)
    add a0,t2 ,x0
    li t2, 2
    add a1,t2 ,x0
    call equal
    sw a0, 196(sp)
    lw t0, 188(sp)
    lw t1, 196(sp)
    sub t2, t0, t1
    sw t2, 200(sp)
    lw t2, 0(sp)
    sw t2, 204(sp)
    lw t0, 204(sp)
    li t1, 1
    sub t2, t0, t1
    sw t2, 208(sp)
    lw t2, 4(sp)
    sw t2, 212(sp)
    lw t2, 8(sp)
    sw t2, 216(sp)
    lw t2, 12(sp)
    sw t2, 220(sp)
    lw t2, 16(sp)
    sw t2, 224(sp)
    lw t2, 208(sp)
    add a0,t2 ,x0
    lw t2, 212(sp)
    add a1,t2 ,x0
    lw t2, 216(sp)
    add a2,t2 ,x0
    lw t2, 220(sp)
    add a3,t2 ,x0
    lw t2, 224(sp)
    add a4,t2 ,x0
    li t2, 1
    add a5,t2 ,x0
    call dfs
    sw a0, 228(sp)
    lw t0, 200(sp)
    lw t1, 228(sp)
    mul t2, t0, t1
    sw t2, 232(sp)
    lw t0, 184(sp)
    lw t1, 232(sp)
    add t2, t0, t1
    sw t2, 236(sp)
    lw t0, 236(sp)
    li t1, 1000000007
    rem t2, t0, t1
    sw t2, 240(sp)
    lw t2, 240(sp)
    sw t2, 176(sp)
    j block_46
block_46:
    lw t2, 4(sp)
    sw t2, 244(sp)
    lw t2, 244(sp)
    bnez t2, block_69
    j block_70
block_69:
    lw t2, 176(sp)
    sw t2, 248(sp)
    lw t2, 4(sp)
    sw t2, 252(sp)
    lw t2, 20(sp)
    sw t2, 256(sp)
    lw t2, 256(sp)
    add a0,t2 ,x0
    li t2, 3
    add a1,t2 ,x0
    call equal
    sw a0, 260(sp)
    lw t0, 252(sp)
    lw t1, 260(sp)
    sub t2, t0, t1
    sw t2, 264(sp)
    lw t2, 0(sp)
    sw t2, 268(sp)
    lw t0, 268(sp)
    li t1, 1
    add t2, t0, t1
    sw t2, 272(sp)
    lw t2, 4(sp)
    sw t2, 276(sp)
    lw t0, 276(sp)
    li t1, 1
    sub t2, t0, t1
    sw t2, 280(sp)
    lw t2, 8(sp)
    sw t2, 284(sp)
    lw t2, 12(sp)
    sw t2, 288(sp)
    lw t2, 16(sp)
    sw t2, 292(sp)
    lw t2, 272(sp)
    add a0,t2 ,x0
    lw t2, 280(sp)
    add a1,t2 ,x0
    lw t2, 284(sp)
    add a2,t2 ,x0
    lw t2, 288(sp)
    add a3,t2 ,x0
    lw t2, 292(sp)
    add a4,t2 ,x0
    li t2, 2
    add a5,t2 ,x0
    call dfs
    sw a0, 296(sp)
    lw t0, 264(sp)
    lw t1, 296(sp)
    mul t2, t0, t1
    sw t2, 300(sp)
    lw t0, 248(sp)
    lw t1, 300(sp)
    add t2, t0, t1
    sw t2, 304(sp)
    lw t0, 304(sp)
    li t1, 1000000007
    rem t2, t0, t1
    sw t2, 308(sp)
    lw t2, 308(sp)
    sw t2, 176(sp)
    j block_70
block_70:
    lw t2, 8(sp)
    sw t2, 312(sp)
    lw t2, 312(sp)
    bnez t2, block_93
    j block_94
block_93:
    lw t2, 176(sp)
    sw t2, 316(sp)
    lw t2, 8(sp)
    sw t2, 320(sp)
    lw t2, 20(sp)
    sw t2, 324(sp)
    lw t2, 324(sp)
    add a0,t2 ,x0
    li t2, 4
    add a1,t2 ,x0
    call equal
    sw a0, 328(sp)
    lw t0, 320(sp)
    lw t1, 328(sp)
    sub t2, t0, t1
    sw t2, 332(sp)
    lw t2, 0(sp)
    sw t2, 336(sp)
    lw t2, 4(sp)
    sw t2, 340(sp)
    lw t0, 340(sp)
    li t1, 1
    add t2, t0, t1
    sw t2, 344(sp)
    lw t2, 8(sp)
    sw t2, 348(sp)
    lw t0, 348(sp)
    li t1, 1
    sub t2, t0, t1
    sw t2, 352(sp)
    lw t2, 12(sp)
    sw t2, 356(sp)
    lw t2, 16(sp)
    sw t2, 360(sp)
    lw t2, 336(sp)
    add a0,t2 ,x0
    lw t2, 344(sp)
    add a1,t2 ,x0
    lw t2, 352(sp)
    add a2,t2 ,x0
    lw t2, 356(sp)
    add a3,t2 ,x0
    lw t2, 360(sp)
    add a4,t2 ,x0
    li t2, 3
    add a5,t2 ,x0
    call dfs
    sw a0, 364(sp)
    lw t0, 332(sp)
    lw t1, 364(sp)
    mul t2, t0, t1
    sw t2, 368(sp)
    lw t0, 316(sp)
    lw t1, 368(sp)
    add t2, t0, t1
    sw t2, 372(sp)
    lw t0, 372(sp)
    li t1, 1000000007
    rem t2, t0, t1
    sw t2, 376(sp)
    lw t2, 376(sp)
    sw t2, 176(sp)
    j block_94
block_94:
    lw t2, 12(sp)
    sw t2, 380(sp)
    lw t2, 380(sp)
    bnez t2, block_117
    j block_118
block_117:
    lw t2, 176(sp)
    sw t2, 384(sp)
    lw t2, 12(sp)
    sw t2, 388(sp)
    lw t2, 20(sp)
    sw t2, 392(sp)
    lw t2, 392(sp)
    add a0,t2 ,x0
    li t2, 5
    add a1,t2 ,x0
    call equal
    sw a0, 396(sp)
    lw t0, 388(sp)
    lw t1, 396(sp)
    sub t2, t0, t1
    sw t2, 400(sp)
    lw t2, 0(sp)
    sw t2, 404(sp)
    lw t2, 4(sp)
    sw t2, 408(sp)
    lw t2, 8(sp)
    sw t2, 412(sp)
    lw t0, 412(sp)
    li t1, 1
    add t2, t0, t1
    sw t2, 416(sp)
    lw t2, 12(sp)
    sw t2, 420(sp)
    lw t0, 420(sp)
    li t1, 1
    sub t2, t0, t1
    sw t2, 424(sp)
    lw t2, 16(sp)
    sw t2, 428(sp)
    lw t2, 404(sp)
    add a0,t2 ,x0
    lw t2, 408(sp)
    add a1,t2 ,x0
    lw t2, 416(sp)
    add a2,t2 ,x0
    lw t2, 424(sp)
    add a3,t2 ,x0
    lw t2, 428(sp)
    add a4,t2 ,x0
    li t2, 4
    add a5,t2 ,x0
    call dfs
    sw a0, 432(sp)
    lw t0, 400(sp)
    lw t1, 432(sp)
    mul t2, t0, t1
    sw t2, 436(sp)
    lw t0, 384(sp)
    lw t1, 436(sp)
    add t2, t0, t1
    sw t2, 440(sp)
    lw t0, 440(sp)
    li t1, 1000000007
    rem t2, t0, t1
    sw t2, 444(sp)
    lw t2, 444(sp)
    sw t2, 176(sp)
    j block_118
block_118:
    lw t2, 16(sp)
    sw t2, 448(sp)
    lw t2, 448(sp)
    bnez t2, block_141
    j block_142
block_141:
    lw t2, 176(sp)
    sw t2, 452(sp)
    lw t2, 16(sp)
    sw t2, 456(sp)
    lw t2, 0(sp)
    sw t2, 460(sp)
    lw t2, 4(sp)
    sw t2, 464(sp)
    lw t2, 8(sp)
    sw t2, 468(sp)
    lw t2, 12(sp)
    sw t2, 472(sp)
    lw t0, 472(sp)
    li t1, 1
    add t2, t0, t1
    sw t2, 476(sp)
    lw t2, 16(sp)
    sw t2, 480(sp)
    lw t0, 480(sp)
    li t1, 1
    sub t2, t0, t1
    sw t2, 484(sp)
    lw t2, 460(sp)
    add a0,t2 ,x0
    lw t2, 464(sp)
    add a1,t2 ,x0
    lw t2, 468(sp)
    add a2,t2 ,x0
    lw t2, 476(sp)
    add a3,t2 ,x0
    lw t2, 484(sp)
    add a4,t2 ,x0
    li t2, 5
    add a5,t2 ,x0
    call dfs
    sw a0, 488(sp)
    lw t0, 456(sp)
    lw t1, 488(sp)
    mul t2, t0, t1
    sw t2, 492(sp)
    lw t0, 452(sp)
    lw t1, 492(sp)
    add t2, t0, t1
    sw t2, 496(sp)
    lw t0, 496(sp)
    li t1, 1000000007
    rem t2, t0, t1
    sw t2, 500(sp)
    lw t2, 500(sp)
    sw t2, 176(sp)
    j block_142
block_142:
    lw t2, 176(sp)
    sw t2, 504(sp)
    lw t0, 504(sp)
    li t1, 1000000007
    rem t2, t0, t1
    sw t2, 508(sp)
    lw t2, 0(sp)
    sw t2, 512(sp)
    la t4 , dp
    lw t1, 512(sp)
    li t2, 2939328
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 516(sp)
    lw t2, 4(sp)
    sw t2, 520(sp)
    lw t0, 516(sp)
    mv t4, t0
    lw t1, 520(sp)
    li t2, 163296
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 524(sp)
    lw t2, 8(sp)
    sw t2, 528(sp)
    lw t0, 524(sp)
    mv t4, t0
    lw t1, 528(sp)
    li t2, 9072
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 532(sp)
    lw t2, 12(sp)
    sw t2, 536(sp)
    lw t0, 532(sp)
    mv t4, t0
    lw t1, 536(sp)
    li t2, 504
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 540(sp)
    lw t2, 16(sp)
    sw t2, 544(sp)
    lw t0, 540(sp)
    mv t4, t0
    lw t1, 544(sp)
    li t2, 28
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 548(sp)
    lw t2, 20(sp)
    sw t2, 552(sp)
    lw t0, 548(sp)
    mv t4, t0
    lw t1, 552(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 556(sp)
    lw t2, 508(sp)
    lw t0, 556(sp)
    sw t2, 0(t0)
    lw t2, 0(sp)
    sw t2, 560(sp)
    la t4 , dp
    lw t1, 560(sp)
    li t2, 2939328
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 564(sp)
    lw t2, 4(sp)
    sw t2, 568(sp)
    lw t0, 564(sp)
    mv t4, t0
    lw t1, 568(sp)
    li t2, 163296
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 572(sp)
    lw t2, 8(sp)
    sw t2, 576(sp)
    lw t0, 572(sp)
    mv t4, t0
    lw t1, 576(sp)
    li t2, 9072
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 580(sp)
    lw t2, 12(sp)
    sw t2, 584(sp)
    lw t0, 580(sp)
    mv t4, t0
    lw t1, 584(sp)
    li t2, 504
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 588(sp)
    lw t2, 16(sp)
    sw t2, 592(sp)
    lw t0, 588(sp)
    mv t4, t0
    lw t1, 592(sp)
    li t2, 28
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 596(sp)
    lw t2, 20(sp)
    sw t2, 600(sp)
    lw t0, 596(sp)
    mv t4, t0
    lw t1, 600(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 604(sp)
    lw t0, 604(sp)
    lw t2, 0(t0)
    sw t2, 608(sp)
    lw t2, 608(sp)
    add a0, t2, x0
    lw ra, 620(sp)
    addi sp, sp, 624
    ret

    .text
    .globl main
main:
    addi sp, sp, -320
    sw ra, 316(sp)
block_194:
    call getint
    sw a0, 0(sp)
    lw t2, 0(sp)
    sw t2, 4(sp)
    li t2, 0
    sw t2, 8(sp)
    j block_193
block_193:
    lw t2, 8(sp)
    sw t2, 12(sp)
    lw t0, 12(sp)
    li t1, 18
    slt t2, t0, t1
    sw t2, 16(sp)
    lw t2, 16(sp)
    bnez t2, block_191
    j block_192
block_191:
    li t2, 0
    sw t2, 20(sp)
    j block_199
block_199:
    lw t2, 20(sp)
    sw t2, 24(sp)
    lw t0, 24(sp)
    li t1, 18
    slt t2, t0, t1
    sw t2, 28(sp)
    lw t2, 28(sp)
    bnez t2, block_197
    j block_198
block_197:
    li t2, 0
    sw t2, 32(sp)
    j block_204
block_204:
    lw t2, 32(sp)
    sw t2, 36(sp)
    lw t0, 36(sp)
    li t1, 18
    slt t2, t0, t1
    sw t2, 40(sp)
    lw t2, 40(sp)
    bnez t2, block_202
    j block_203
block_202:
    li t2, 0
    sw t2, 44(sp)
    j block_209
block_209:
    lw t2, 44(sp)
    sw t2, 48(sp)
    lw t0, 48(sp)
    li t1, 18
    slt t2, t0, t1
    sw t2, 52(sp)
    lw t2, 52(sp)
    bnez t2, block_207
    j block_208
block_207:
    li t2, 0
    sw t2, 56(sp)
    j block_214
block_214:
    lw t2, 56(sp)
    sw t2, 60(sp)
    lw t0, 60(sp)
    li t1, 18
    slt t2, t0, t1
    sw t2, 64(sp)
    lw t2, 64(sp)
    bnez t2, block_212
    j block_213
block_212:
    li t2, 0
    sw t2, 68(sp)
    j block_219
block_219:
    lw t2, 68(sp)
    sw t2, 72(sp)
    lw t0, 72(sp)
    li t1, 7
    slt t2, t0, t1
    sw t2, 76(sp)
    lw t2, 76(sp)
    bnez t2, block_217
    j block_218
block_217:
    li t0, 0
    li t1, 1
    sub t2, t0, t1
    sw t2, 80(sp)
    lw t2, 8(sp)
    sw t2, 84(sp)
    la t4 , dp
    lw t1, 84(sp)
    li t2, 2939328
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 88(sp)
    lw t2, 20(sp)
    sw t2, 92(sp)
    lw t0, 88(sp)
    mv t4, t0
    lw t1, 92(sp)
    li t2, 163296
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 96(sp)
    lw t2, 32(sp)
    sw t2, 100(sp)
    lw t0, 96(sp)
    mv t4, t0
    lw t1, 100(sp)
    li t2, 9072
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 104(sp)
    lw t2, 44(sp)
    sw t2, 108(sp)
    lw t0, 104(sp)
    mv t4, t0
    lw t1, 108(sp)
    li t2, 504
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 112(sp)
    lw t2, 56(sp)
    sw t2, 116(sp)
    lw t0, 112(sp)
    mv t4, t0
    lw t1, 116(sp)
    li t2, 28
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 120(sp)
    lw t2, 68(sp)
    sw t2, 124(sp)
    lw t0, 120(sp)
    mv t4, t0
    lw t1, 124(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 128(sp)
    lw t2, 80(sp)
    lw t0, 128(sp)
    sw t2, 0(t0)
    lw t2, 68(sp)
    sw t2, 132(sp)
    lw t0, 132(sp)
    li t1, 1
    add t2, t0, t1
    sw t2, 136(sp)
    lw t2, 136(sp)
    sw t2, 68(sp)
    j block_219
block_218:
    lw t2, 56(sp)
    sw t2, 140(sp)
    lw t0, 140(sp)
    li t1, 1
    add t2, t0, t1
    sw t2, 144(sp)
    lw t2, 144(sp)
    sw t2, 56(sp)
    j block_214
block_213:
    lw t2, 44(sp)
    sw t2, 148(sp)
    lw t0, 148(sp)
    li t1, 1
    add t2, t0, t1
    sw t2, 152(sp)
    lw t2, 152(sp)
    sw t2, 44(sp)
    j block_209
block_208:
    lw t2, 32(sp)
    sw t2, 156(sp)
    lw t0, 156(sp)
    li t1, 1
    add t2, t0, t1
    sw t2, 160(sp)
    lw t2, 160(sp)
    sw t2, 32(sp)
    j block_204
block_203:
    lw t2, 20(sp)
    sw t2, 164(sp)
    lw t0, 164(sp)
    li t1, 1
    add t2, t0, t1
    sw t2, 168(sp)
    lw t2, 168(sp)
    sw t2, 20(sp)
    j block_199
block_198:
    lw t2, 8(sp)
    sw t2, 172(sp)
    lw t0, 172(sp)
    li t1, 1
    add t2, t0, t1
    sw t2, 176(sp)
    lw t2, 176(sp)
    sw t2, 8(sp)
    j block_193
block_192:
    li t2, 0
    sw t2, 8(sp)
    j block_250
block_250:
    lw t2, 8(sp)
    sw t2, 180(sp)
    lw t2, 4(sp)
    sw t2, 184(sp)
    lw t0, 180(sp)
    lw t1, 184(sp)
    slt t2, t0, t1
    sw t2, 188(sp)
    lw t2, 188(sp)
    bnez t2, block_248
    j block_249
block_248:
    call getint
    sw a0, 192(sp)
    lw t2, 8(sp)
    sw t2, 196(sp)
    la t4 , list
    lw t1, 196(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 200(sp)
    lw t2, 192(sp)
    lw t0, 200(sp)
    sw t2, 0(t0)
    lw t2, 8(sp)
    sw t2, 204(sp)
    la t4 , list
    lw t1, 204(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 208(sp)
    lw t0, 208(sp)
    lw t2, 0(t0)
    sw t2, 212(sp)
    la t4 , cns
    lw t1, 212(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 216(sp)
    lw t0, 216(sp)
    lw t2, 0(t0)
    sw t2, 220(sp)
    lw t0, 220(sp)
    li t1, 1
    add t2, t0, t1
    sw t2, 224(sp)
    lw t2, 8(sp)
    sw t2, 228(sp)
    la t4 , list
    lw t1, 228(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 232(sp)
    lw t0, 232(sp)
    lw t2, 0(t0)
    sw t2, 236(sp)
    la t4 , cns
    lw t1, 236(sp)
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 240(sp)
    lw t2, 224(sp)
    lw t0, 240(sp)
    sw t2, 0(t0)
    lw t2, 8(sp)
    sw t2, 244(sp)
    lw t0, 244(sp)
    li t1, 1
    add t2, t0, t1
    sw t2, 248(sp)
    lw t2, 248(sp)
    sw t2, 8(sp)
    j block_250
block_249:
    la t4 , cns
    li t1, 1
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 252(sp)
    lw t0, 252(sp)
    lw t2, 0(t0)
    sw t2, 256(sp)
    la t4 , cns
    li t1, 2
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 260(sp)
    lw t0, 260(sp)
    lw t2, 0(t0)
    sw t2, 264(sp)
    la t4 , cns
    li t1, 3
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 268(sp)
    lw t0, 268(sp)
    lw t2, 0(t0)
    sw t2, 272(sp)
    la t4 , cns
    li t1, 4
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 276(sp)
    lw t0, 276(sp)
    lw t2, 0(t0)
    sw t2, 280(sp)
    la t4 , cns
    li t1, 5
    li t2, 4
    mul t1, t1, t2
    add t2, t4, t1
    sw t2, 284(sp)
    lw t0, 284(sp)
    lw t2, 0(t0)
    sw t2, 288(sp)
    lw t2, 256(sp)
    add a0,t2 ,x0
    lw t2, 264(sp)
    add a1,t2 ,x0
    lw t2, 272(sp)
    add a2,t2 ,x0
    lw t2, 280(sp)
    add a3,t2 ,x0
    lw t2, 288(sp)
    add a4,t2 ,x0
    li t2, 0
    add a5,t2 ,x0
    call dfs
    sw a0, 292(sp)
    lw t2, 292(sp)
    sw t2, 296(sp)
    lw t2, 296(sp)
    sw t2, 300(sp)
    lw t2, 300(sp)
    add a0,t2 ,x0
    call putint
    lw t2, 296(sp)
    sw t2, 304(sp)
    lw t2, 304(sp)
    add a0, t2, x0
    lw ra, 316(sp)
    addi sp, sp, 320
    ret
