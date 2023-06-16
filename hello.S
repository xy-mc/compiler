
    .data
    .global luoji
luoji:
    .word 0

    .data
    .global x
x:
    .zero 4

    .data
    .global y
y:
    .zero 4

    .text
    .globl t
t:
    addi sp, sp, -16
block_4:
    la t0 , x
    lw t0, 0(t0)
    sw t0, 0(sp)
    lw t2, 0(sp)
    sw t2, 4(sp)
    lw t0, 4(sp)
    li t1, 1
    add t2, t0, t1
    sw t2, 8(sp)
    lw t2, 8(sp)
    sw t2, 0(sp)
    li t2, 1
    add a0, t2, x0
    addi sp, sp, 16
    ret

    .text
    .globl f
f:
    addi sp, sp, -16
block_9:
    la t0 , y
    lw t0, 0(t0)
    sw t0, 0(sp)
    lw t2, 0(sp)
    sw t2, 4(sp)
    lw t0, 4(sp)
    li t1, 1
    add t2, t0, t1
    sw t2, 8(sp)
    lw t2, 8(sp)
    sw t2, 0(sp)
    li t2, 0
    add a0, t2, x0
    addi sp, sp, 16
    ret

    .text
    .globl main
main:
    addi sp, sp, -288
    sw ra, 284(sp)
block_17:
    li t2, 0
    sw t2, 0(sp)
    lw t2, 0(sp)
    sw t2, 4(sp)
    call f
    sw a0, 8(sp)
    lw t2, 8(sp)
    bnez t2, block_14
    j block_16
block_16:
    call f
    sw a0, 12(sp)
    lw t2, 12(sp)
    bnez t2, block_14
    j block_15
block_14:
    li t2, 1
    la t0 , luoji
    lw t0, 0(t0)
    sw t0, 16(sp)
    sw t2, 16(sp)
    j block_18
block_15:
    li t2, 0
    sw t2, 16(sp)
    j block_18
block_18:
    lw t2, 16(sp)
    sw t2, 20(sp)
    lw t0, 4(sp)
    lw t1, 20(sp)
    add t2, t0, t1
    sw t2, 24(sp)
    lw t2, 24(sp)
    sw t2, 0(sp)
    lw t2, 0(sp)
    sw t2, 28(sp)
    call f
    sw a0, 32(sp)
    lw t2, 32(sp)
    bnez t2, block_21
    j block_23
block_23:
    call t
    sw a0, 36(sp)
    lw t2, 36(sp)
    bnez t2, block_21
    j block_22
block_21:
    li t2, 1
    sw t2, 16(sp)
    j block_24
block_22:
    li t2, 0
    sw t2, 16(sp)
    j block_24
block_24:
    lw t2, 16(sp)
    sw t2, 40(sp)
    lw t0, 28(sp)
    lw t1, 40(sp)
    add t2, t0, t1
    sw t2, 44(sp)
    lw t2, 44(sp)
    sw t2, 0(sp)
    lw t2, 0(sp)
    sw t2, 48(sp)
    call t
    sw a0, 52(sp)
    lw t2, 52(sp)
    bnez t2, block_27
    j block_29
block_29:
    call f
    sw a0, 56(sp)
    lw t2, 56(sp)
    bnez t2, block_27
    j block_28
block_27:
    li t2, 1
    sw t2, 16(sp)
    j block_30
block_28:
    li t2, 0
    sw t2, 16(sp)
    j block_30
block_30:
    lw t2, 16(sp)
    sw t2, 60(sp)
    lw t0, 48(sp)
    lw t1, 60(sp)
    add t2, t0, t1
    sw t2, 64(sp)
    lw t2, 64(sp)
    sw t2, 0(sp)
    lw t2, 0(sp)
    sw t2, 68(sp)
    call t
    sw a0, 72(sp)
    lw t2, 72(sp)
    bnez t2, block_33
    j block_35
block_35:
    call t
    sw a0, 76(sp)
    lw t2, 76(sp)
    bnez t2, block_33
    j block_34
block_33:
    li t2, 1
    sw t2, 16(sp)
    j block_36
block_34:
    li t2, 0
    sw t2, 16(sp)
    j block_36
block_36:
    lw t2, 16(sp)
    sw t2, 80(sp)
    lw t0, 68(sp)
    lw t1, 80(sp)
    add t2, t0, t1
    sw t2, 84(sp)
    lw t2, 84(sp)
    sw t2, 0(sp)
    lw t2, 0(sp)
    sw t2, 88(sp)
    call f
    sw a0, 92(sp)
    lw t2, 92(sp)
    bnez t2, block_41
    j block_40
block_41:
    call f
    sw a0, 96(sp)
    lw t2, 96(sp)
    bnez t2, block_39
    j block_40
block_39:
    li t2, 1
    sw t2, 16(sp)
    j block_42
block_40:
    li t2, 0
    sw t2, 16(sp)
    j block_42
block_42:
    lw t2, 16(sp)
    sw t2, 100(sp)
    lw t0, 88(sp)
    lw t1, 100(sp)
    add t2, t0, t1
    sw t2, 104(sp)
    lw t2, 104(sp)
    sw t2, 0(sp)
    lw t2, 0(sp)
    sw t2, 108(sp)
    call f
    sw a0, 112(sp)
    lw t2, 112(sp)
    bnez t2, block_47
    j block_46
block_47:
    call t
    sw a0, 116(sp)
    lw t2, 116(sp)
    bnez t2, block_45
    j block_46
block_45:
    li t2, 1
    sw t2, 16(sp)
    j block_48
block_46:
    li t2, 0
    sw t2, 16(sp)
    j block_48
block_48:
    lw t2, 16(sp)
    sw t2, 120(sp)
    lw t0, 108(sp)
    lw t1, 120(sp)
    add t2, t0, t1
    sw t2, 124(sp)
    lw t2, 124(sp)
    sw t2, 0(sp)
    lw t2, 0(sp)
    sw t2, 128(sp)
    call t
    sw a0, 132(sp)
    lw t2, 132(sp)
    bnez t2, block_53
    j block_52
block_53:
    call f
    sw a0, 136(sp)
    lw t2, 136(sp)
    bnez t2, block_51
    j block_52
block_51:
    li t2, 1
    sw t2, 16(sp)
    j block_54
block_52:
    li t2, 0
    sw t2, 16(sp)
    j block_54
block_54:
    lw t2, 16(sp)
    sw t2, 140(sp)
    lw t0, 128(sp)
    lw t1, 140(sp)
    add t2, t0, t1
    sw t2, 144(sp)
    lw t2, 144(sp)
    sw t2, 0(sp)
    lw t2, 0(sp)
    sw t2, 148(sp)
    call t
    sw a0, 152(sp)
    lw t2, 152(sp)
    bnez t2, block_59
    j block_58
block_59:
    call t
    sw a0, 156(sp)
    lw t2, 156(sp)
    bnez t2, block_57
    j block_58
block_57:
    li t2, 1
    sw t2, 16(sp)
    j block_60
block_58:
    li t2, 0
    sw t2, 16(sp)
    j block_60
block_60:
    lw t2, 16(sp)
    sw t2, 160(sp)
    lw t0, 148(sp)
    lw t1, 160(sp)
    add t2, t0, t1
    sw t2, 164(sp)
    lw t2, 164(sp)
    sw t2, 0(sp)
    call t
    sw a0, 168(sp)
    lw t2, 168(sp)
    bnez t2, block_61
    j block_63
block_63:
    call t
    sw a0, 172(sp)
    lw t2, 172(sp)
    bnez t2, block_64
    j block_62
block_64:
    call t
    sw a0, 176(sp)
    lw t2, 176(sp)
    bnez t2, block_61
    j block_62
block_61:
    li t2, 1
    sw t2, 16(sp)
    j block_65
block_62:
    li t2, 0
    sw t2, 16(sp)
    j block_65
block_65:
    lw t2, 16(sp)
    sw t2, 180(sp)
    call f
    sw a0, 184(sp)
    lw t2, 184(sp)
    bnez t2, block_66
    j block_68
block_68:
    call t
    sw a0, 188(sp)
    lw t2, 188(sp)
    bnez t2, block_69
    j block_67
block_69:
    call t
    sw a0, 192(sp)
    lw t2, 192(sp)
    bnez t2, block_66
    j block_67
block_66:
    li t2, 1
    sw t2, 16(sp)
    j block_70
block_67:
    li t2, 0
    sw t2, 16(sp)
    j block_70
block_70:
    lw t2, 16(sp)
    sw t2, 196(sp)
    call f
    sw a0, 200(sp)
    lw t2, 200(sp)
    bnez t2, block_71
    j block_73
block_73:
    call f
    sw a0, 204(sp)
    lw t2, 204(sp)
    bnez t2, block_74
    j block_72
block_74:
    call t
    sw a0, 208(sp)
    lw t2, 208(sp)
    bnez t2, block_71
    j block_72
block_71:
    li t2, 1
    sw t2, 16(sp)
    j block_75
block_72:
    li t2, 0
    sw t2, 16(sp)
    j block_75
block_75:
    lw t2, 16(sp)
    sw t2, 212(sp)
    call t
    sw a0, 216(sp)
    lw t2, 216(sp)
    bnez t2, block_79
    j block_78
block_79:
    call t
    sw a0, 220(sp)
    lw t2, 220(sp)
    bnez t2, block_76
    j block_78
block_78:
    call t
    sw a0, 224(sp)
    lw t2, 224(sp)
    bnez t2, block_76
    j block_77
block_76:
    li t2, 1
    sw t2, 16(sp)
    j block_80
block_77:
    li t2, 0
    sw t2, 16(sp)
    j block_80
block_80:
    lw t2, 16(sp)
    sw t2, 228(sp)
    call f
    sw a0, 232(sp)
    lw t2, 232(sp)
    bnez t2, block_84
    j block_83
block_84:
    call t
    sw a0, 236(sp)
    lw t2, 236(sp)
    bnez t2, block_81
    j block_83
block_83:
    call t
    sw a0, 240(sp)
    lw t2, 240(sp)
    bnez t2, block_81
    j block_82
block_81:
    li t2, 1
    sw t2, 16(sp)
    j block_85
block_82:
    li t2, 0
    sw t2, 16(sp)
    j block_85
block_85:
    lw t2, 16(sp)
    sw t2, 244(sp)
    call f
    sw a0, 248(sp)
    lw t2, 248(sp)
    bnez t2, block_89
    j block_88
block_89:
    call f
    sw a0, 252(sp)
    lw t2, 252(sp)
    bnez t2, block_86
    j block_88
block_88:
    call f
    sw a0, 256(sp)
    lw t2, 256(sp)
    bnez t2, block_86
    j block_87
block_86:
    li t2, 1
    sw t2, 16(sp)
    j block_90
block_87:
    li t2, 0
    sw t2, 16(sp)
    j block_90
block_90:
    lw t2, 16(sp)
    sw t2, 260(sp)
    la t0 , x
    lw t0, 0(t0)
    sw t0, 264(sp)
    lw t2, 264(sp)
    sw t2, 268(sp)
    lw t2, 268(sp)
    add a0,t2 ,x0
    call putint
    li t2, 32
    add a0,t2 ,x0
    call putch
    la t0 , y
    lw t0, 0(t0)
    sw t0, 272(sp)
    lw t2, 272(sp)
    sw t2, 276(sp)
    lw t2, 276(sp)
    add a0,t2 ,x0
    call putint
    li t2, 10
    add a0,t2 ,x0
    call putch
    lw t2, 0(sp)
    sw t2, 280(sp)
    lw t2, 280(sp)
    add a0, t2, x0
    lw ra, 284(sp)
    addi sp, sp, 288
    ret
