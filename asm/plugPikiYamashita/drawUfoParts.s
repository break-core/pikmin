.include "macros.inc"
.section .text, "ax"  # 0x80005560 - 0x80221F60
.fn __ct__Q23zen12DrawUfoPartsFv, global
/* 801F1D60 001EECC0  7C 08 02 A6 */	mflr r0
/* 801F1D64 001EECC4  90 01 00 04 */	stw r0, 4(r1)
/* 801F1D68 001EECC8  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 801F1D6C 001EECCC  93 E1 00 24 */	stw r31, 0x24(r1)
/* 801F1D70 001EECD0  93 C1 00 20 */	stw r30, 0x20(r1)
/* 801F1D74 001EECD4  3B C3 00 00 */	addi r30, r3, 0
/* 801F1D78 001EECD8  38 7E 00 0C */	addi r3, r30, 0xc
/* 801F1D7C 001EECDC  4B FF FC 5D */	bl __ct__Q23zen9AlphaWipeFv
/* 801F1D80 001EECE0  38 C0 00 00 */	li r6, 0
/* 801F1D84 001EECE4  90 DE 00 34 */	stw r6, 0x34(r30)
/* 801F1D88 001EECE8  3C 60 80 22 */	lis r3, __ptmf_null@ha
/* 801F1D8C 001EECEC  38 A3 27 58 */	addi r5, r3, __ptmf_null@l
/* 801F1D90 001EECF0  90 DE 00 38 */	stw r6, 0x38(r30)
/* 801F1D94 001EECF4  38 60 01 00 */	li r3, 0x100
/* 801F1D98 001EECF8  90 DE 00 3C */	stw r6, 0x3c(r30)
/* 801F1D9C 001EECFC  80 85 00 00 */	lwz r4, 0(r5)
/* 801F1DA0 001EED00  80 05 00 04 */	lwz r0, 4(r5)
/* 801F1DA4 001EED04  90 9E 00 44 */	stw r4, 0x44(r30)
/* 801F1DA8 001EED08  90 1E 00 48 */	stw r0, 0x48(r30)
/* 801F1DAC 001EED0C  80 05 00 08 */	lwz r0, 8(r5)
/* 801F1DB0 001EED10  90 1E 00 4C */	stw r0, 0x4c(r30)
/* 801F1DB4 001EED14  90 DE 00 40 */	stw r6, 0x40(r30)
/* 801F1DB8 001EED18  4B E5 52 4D */	bl alloc__6SystemFUl
/* 801F1DBC 001EED1C  3B E3 00 00 */	addi r31, r3, 0
/* 801F1DC0 001EED20  7F E3 FB 79 */	or. r3, r31, r31
/* 801F1DC4 001EED24  41 82 00 1C */	beq .L_801F1DE0
/* 801F1DC8 001EED28  3C 80 80 2E */	lis r4, lbl_802E7148@ha
/* 801F1DCC 001EED2C  38 84 71 48 */	addi r4, r4, lbl_802E7148@l
/* 801F1DD0 001EED30  38 A0 00 00 */	li r5, 0
/* 801F1DD4 001EED34  38 C0 00 01 */	li r6, 1
/* 801F1DD8 001EED38  38 E0 00 01 */	li r7, 1
/* 801F1DDC 001EED3C  4B FC D7 99 */	bl __ct__Q23zen10DrawScreenFPcP14P2DGrafContextbb
.L_801F1DE0:
/* 801F1DE0 001EED40  93 FE 00 08 */	stw r31, 8(r30)
/* 801F1DE4 001EED44  38 7E 00 34 */	addi r3, r30, 0x34
/* 801F1DE8 001EED48  80 9E 00 08 */	lwz r4, 8(r30)
/* 801F1DEC 001EED4C  38 84 00 04 */	addi r4, r4, 4
/* 801F1DF0 001EED50  4B FF C7 25 */	bl init__Q23zen10DrawCMbestFP9P2DScreen
/* 801F1DF4 001EED54  38 00 00 00 */	li r0, 0
/* 801F1DF8 001EED58  90 1E 00 04 */	stw r0, 4(r30)
/* 801F1DFC 001EED5C  7F C3 F3 78 */	mr r3, r30
/* 801F1E00 001EED60  90 1E 00 00 */	stw r0, 0(r30)
/* 801F1E04 001EED64  98 01 00 1C */	stb r0, 0x1c(r1)
/* 801F1E08 001EED68  98 01 00 18 */	stb r0, 0x18(r1)
/* 801F1E0C 001EED6C  98 01 00 1D */	stb r0, 0x1d(r1)
/* 801F1E10 001EED70  98 01 00 19 */	stb r0, 0x19(r1)
/* 801F1E14 001EED74  98 01 00 1E */	stb r0, 0x1e(r1)
/* 801F1E18 001EED78  98 01 00 1A */	stb r0, 0x1a(r1)
/* 801F1E1C 001EED7C  98 01 00 1F */	stb r0, 0x1f(r1)
/* 801F1E20 001EED80  98 01 00 1B */	stb r0, 0x1b(r1)
/* 801F1E24 001EED84  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 801F1E28 001EED88  90 1E 00 2C */	stw r0, 0x2c(r30)
/* 801F1E2C 001EED8C  80 01 00 18 */	lwz r0, 0x18(r1)
/* 801F1E30 001EED90  90 1E 00 30 */	stw r0, 0x30(r30)
/* 801F1E34 001EED94  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 801F1E38 001EED98  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 801F1E3C 001EED9C  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 801F1E40 001EEDA0  38 21 00 28 */	addi r1, r1, 0x28
/* 801F1E44 001EEDA4  7C 08 03 A6 */	mtlr r0
/* 801F1E48 001EEDA8  4E 80 00 20 */	blr 
.endfn __ct__Q23zen12DrawUfoPartsFv

.fn update__Q23zen12DrawUfoPartsFP10Controller, global
/* 801F1E4C 001EEDAC  7C 08 02 A6 */	mflr r0
/* 801F1E50 001EEDB0  90 01 00 04 */	stw r0, 4(r1)
/* 801F1E54 001EEDB4  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 801F1E58 001EEDB8  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 801F1E5C 001EEDBC  3B E0 00 00 */	li r31, 0
/* 801F1E60 001EEDC0  93 C1 00 18 */	stw r30, 0x18(r1)
/* 801F1E64 001EEDC4  3B C4 00 00 */	addi r30, r4, 0
/* 801F1E68 001EEDC8  93 A1 00 14 */	stw r29, 0x14(r1)
/* 801F1E6C 001EEDCC  7C 7D 1B 78 */	mr r29, r3
/* 801F1E70 001EEDD0  80 03 00 00 */	lwz r0, 0(r3)
/* 801F1E74 001EEDD4  2C 00 00 00 */	cmpwi r0, 0
/* 801F1E78 001EEDD8  41 82 00 E4 */	beq .L_801F1F5C
/* 801F1E7C 001EEDDC  38 7D 00 0C */	addi r3, r29, 0xc
/* 801F1E80 001EEDE0  4B FF FB A1 */	bl update__Q23zen9AlphaWipeFv
/* 801F1E84 001EEDE4  80 1D 00 00 */	lwz r0, 0(r29)
/* 801F1E88 001EEDE8  2C 00 00 02 */	cmpwi r0, 2
/* 801F1E8C 001EEDEC  41 82 00 38 */	beq .L_801F1EC4
/* 801F1E90 001EEDF0  40 80 00 10 */	bge .L_801F1EA0
/* 801F1E94 001EEDF4  2C 00 00 01 */	cmpwi r0, 1
/* 801F1E98 001EEDF8  40 80 00 14 */	bge .L_801F1EAC
/* 801F1E9C 001EEDFC  48 00 00 A4 */	b .L_801F1F40
.L_801F1EA0:
/* 801F1EA0 001EEE00  2C 00 00 04 */	cmpwi r0, 4
/* 801F1EA4 001EEE04  40 80 00 9C */	bge .L_801F1F40
/* 801F1EA8 001EEE08  48 00 00 80 */	b .L_801F1F28
.L_801F1EAC:
/* 801F1EAC 001EEE0C  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 801F1EB0 001EEE10  2C 00 00 00 */	cmpwi r0, 0
/* 801F1EB4 001EEE14  40 82 00 8C */	bne .L_801F1F40
/* 801F1EB8 001EEE18  38 00 00 02 */	li r0, 2
/* 801F1EBC 001EEE1C  90 1D 00 00 */	stw r0, 0(r29)
/* 801F1EC0 001EEE20  48 00 00 80 */	b .L_801F1F40
.L_801F1EC4:
/* 801F1EC4 001EEE24  3C 60 01 00 */	lis r3, 0x01001000@ha
/* 801F1EC8 001EEE28  80 9E 00 28 */	lwz r4, 0x28(r30)
/* 801F1ECC 001EEE2C  38 03 10 00 */	addi r0, r3, 0x01001000@l
/* 801F1ED0 001EEE30  7C 80 00 39 */	and. r0, r4, r0
/* 801F1ED4 001EEE34  41 82 00 18 */	beq .L_801F1EEC
/* 801F1ED8 001EEE38  38 60 01 11 */	li r3, 0x111
/* 801F1EDC 001EEE3C  4B EB 34 99 */	bl playSysSe__8SeSystemFi
/* 801F1EE0 001EEE40  38 00 00 02 */	li r0, 2
/* 801F1EE4 001EEE44  90 1D 00 04 */	stw r0, 4(r29)
/* 801F1EE8 001EEE48  3B E0 00 01 */	li r31, 1
.L_801F1EEC:
/* 801F1EEC 001EEE4C  80 1E 00 28 */	lwz r0, 0x28(r30)
/* 801F1EF0 001EEE50  54 00 04 A5 */	rlwinm. r0, r0, 0, 0x12, 0x12
/* 801F1EF4 001EEE54  41 82 00 4C */	beq .L_801F1F40
/* 801F1EF8 001EEE58  38 60 01 1D */	li r3, 0x11d
/* 801F1EFC 001EEE5C  4B EB 34 79 */	bl playSysSe__8SeSystemFi
/* 801F1F00 001EEE60  38 00 00 01 */	li r0, 1
/* 801F1F04 001EEE64  90 1D 00 04 */	stw r0, 4(r29)
/* 801F1F08 001EEE68  38 7D 00 0C */	addi r3, r29, 0xc
/* 801F1F0C 001EEE6C  38 80 00 01 */	li r4, 1
/* 801F1F10 001EEE70  C0 22 C2 48 */	lfs f1, lbl_803EC448@sda21(r2)
/* 801F1F14 001EEE74  C0 42 C2 4C */	lfs f2, lbl_803EC44C@sda21(r2)
/* 801F1F18 001EEE78  4B FF FD F9 */	bl start__Q23zen9AlphaWipeFffQ33zen9AlphaWipe8typeFlag
/* 801F1F1C 001EEE7C  38 00 00 03 */	li r0, 3
/* 801F1F20 001EEE80  90 1D 00 00 */	stw r0, 0(r29)
/* 801F1F24 001EEE84  48 00 00 1C */	b .L_801F1F40
.L_801F1F28:
/* 801F1F28 001EEE88  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 801F1F2C 001EEE8C  2C 00 00 00 */	cmpwi r0, 0
/* 801F1F30 001EEE90  40 82 00 10 */	bne .L_801F1F40
/* 801F1F34 001EEE94  38 00 00 00 */	li r0, 0
/* 801F1F38 001EEE98  90 1D 00 00 */	stw r0, 0(r29)
/* 801F1F3C 001EEE9C  3B E0 00 01 */	li r31, 1
.L_801F1F40:
/* 801F1F40 001EEEA0  80 7D 00 08 */	lwz r3, 8(r29)
/* 801F1F44 001EEEA4  81 83 00 00 */	lwz r12, 0(r3)
/* 801F1F48 001EEEA8  81 8C 00 08 */	lwz r12, 8(r12)
/* 801F1F4C 001EEEAC  7D 88 03 A6 */	mtlr r12
/* 801F1F50 001EEEB0  4E 80 00 21 */	blrl 
/* 801F1F54 001EEEB4  38 7D 00 34 */	addi r3, r29, 0x34
/* 801F1F58 001EEEB8  4B FF C8 45 */	bl update__Q23zen10DrawCMbestFv
.L_801F1F5C:
/* 801F1F5C 001EEEBC  7F E3 FB 78 */	mr r3, r31
/* 801F1F60 001EEEC0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 801F1F64 001EEEC4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 801F1F68 001EEEC8  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 801F1F6C 001EEECC  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 801F1F70 001EEED0  38 21 00 20 */	addi r1, r1, 0x20
/* 801F1F74 001EEED4  7C 08 03 A6 */	mtlr r0
/* 801F1F78 001EEED8  4E 80 00 20 */	blr 
.endfn update__Q23zen12DrawUfoPartsFP10Controller

.fn draw__Q23zen12DrawUfoPartsFR8Graphics, global
/* 801F1F7C 001EEEDC  7C 08 02 A6 */	mflr r0
/* 801F1F80 001EEEE0  90 01 00 04 */	stw r0, 4(r1)
/* 801F1F84 001EEEE4  94 21 FF 78 */	stwu r1, -0x88(r1)
/* 801F1F88 001EEEE8  93 E1 00 84 */	stw r31, 0x84(r1)
/* 801F1F8C 001EEEEC  3B E4 00 00 */	addi r31, r4, 0
/* 801F1F90 001EEEF0  93 C1 00 80 */	stw r30, 0x80(r1)
/* 801F1F94 001EEEF4  7C 7E 1B 78 */	mr r30, r3
/* 801F1F98 001EEEF8  93 A1 00 7C */	stw r29, 0x7c(r1)
/* 801F1F9C 001EEEFC  93 81 00 78 */	stw r28, 0x78(r1)
/* 801F1FA0 001EEF00  80 03 00 00 */	lwz r0, 0(r3)
/* 801F1FA4 001EEF04  38 60 00 00 */	li r3, 0
/* 801F1FA8 001EEF08  2C 00 00 00 */	cmpwi r0, 0
/* 801F1FAC 001EEF0C  41 82 01 64 */	beq .L_801F2110
/* 801F1FB0 001EEF10  2C 00 00 02 */	cmpwi r0, 2
/* 801F1FB4 001EEF14  41 82 00 48 */	beq .L_801F1FFC
/* 801F1FB8 001EEF18  40 80 00 10 */	bge .L_801F1FC8
/* 801F1FBC 001EEF1C  2C 00 00 01 */	cmpwi r0, 1
/* 801F1FC0 001EEF20  40 80 00 14 */	bge .L_801F1FD4
/* 801F1FC4 001EEF24  48 00 00 64 */	b .L_801F2028
.L_801F1FC8:
/* 801F1FC8 001EEF28  2C 00 00 04 */	cmpwi r0, 4
/* 801F1FCC 001EEF2C  40 80 00 5C */	bge .L_801F2028
/* 801F1FD0 001EEF30  48 00 00 34 */	b .L_801F2004
.L_801F1FD4:
/* 801F1FD4 001EEF34  80 1E 00 10 */	lwz r0, 0x10(r30)
/* 801F1FD8 001EEF38  54 00 07 BD */	rlwinm. r0, r0, 0, 0x1e, 0x1e
/* 801F1FDC 001EEF3C  41 82 00 0C */	beq .L_801F1FE8
/* 801F1FE0 001EEF40  38 00 00 01 */	li r0, 1
/* 801F1FE4 001EEF44  48 00 00 08 */	b .L_801F1FEC
.L_801F1FE8:
/* 801F1FE8 001EEF48  38 00 00 00 */	li r0, 0
.L_801F1FEC:
/* 801F1FEC 001EEF4C  2C 00 00 00 */	cmpwi r0, 0
/* 801F1FF0 001EEF50  41 82 00 38 */	beq .L_801F2028
/* 801F1FF4 001EEF54  38 60 00 01 */	li r3, 1
/* 801F1FF8 001EEF58  48 00 00 30 */	b .L_801F2028
.L_801F1FFC:
/* 801F1FFC 001EEF5C  38 60 00 01 */	li r3, 1
/* 801F2000 001EEF60  48 00 00 28 */	b .L_801F2028
.L_801F2004:
/* 801F2004 001EEF64  80 1E 00 10 */	lwz r0, 0x10(r30)
/* 801F2008 001EEF68  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 801F200C 001EEF6C  41 82 00 0C */	beq .L_801F2018
/* 801F2010 001EEF70  38 00 00 01 */	li r0, 1
/* 801F2014 001EEF74  48 00 00 08 */	b .L_801F201C
.L_801F2018:
/* 801F2018 001EEF78  38 00 00 00 */	li r0, 0
.L_801F201C:
/* 801F201C 001EEF7C  2C 00 00 00 */	cmpwi r0, 0
/* 801F2020 001EEF80  41 82 00 08 */	beq .L_801F2028
/* 801F2024 001EEF84  38 60 00 01 */	li r3, 1
.L_801F2028:
/* 801F2028 001EEF88  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 801F202C 001EEF8C  41 82 00 D8 */	beq .L_801F2104
/* 801F2030 001EEF90  80 DF 03 10 */	lwz r6, 0x310(r31)
/* 801F2034 001EEF94  3B 80 00 00 */	li r28, 0
/* 801F2038 001EEF98  80 1F 03 0C */	lwz r0, 0x30c(r31)
/* 801F203C 001EEF9C  38 A1 00 28 */	addi r5, r1, 0x28
/* 801F2040 001EEFA0  38 7F 00 00 */	addi r3, r31, 0
/* 801F2044 001EEFA4  93 81 00 28 */	stw r28, 0x28(r1)
/* 801F2048 001EEFA8  38 81 00 38 */	addi r4, r1, 0x38
/* 801F204C 001EEFAC  93 81 00 2C */	stw r28, 0x2c(r1)
/* 801F2050 001EEFB0  90 01 00 30 */	stw r0, 0x30(r1)
/* 801F2054 001EEFB4  90 C1 00 34 */	stw r6, 0x34(r1)
/* 801F2058 001EEFB8  81 9F 03 B4 */	lwz r12, 0x3b4(r31)
/* 801F205C 001EEFBC  81 8C 00 40 */	lwz r12, 0x40(r12)
/* 801F2060 001EEFC0  7D 88 03 A6 */	mtlr r12
/* 801F2064 001EEFC4  4E 80 00 21 */	blrl 
/* 801F2068 001EEFC8  9B 81 00 24 */	stb r28, 0x24(r1)
/* 801F206C 001EEFCC  3B A0 00 FF */	li r29, 0xff
/* 801F2070 001EEFD0  38 81 00 24 */	addi r4, r1, 0x24
/* 801F2074 001EEFD4  9B 81 00 25 */	stb r28, 0x25(r1)
/* 801F2078 001EEFD8  7F E3 FB 78 */	mr r3, r31
/* 801F207C 001EEFDC  38 A0 00 01 */	li r5, 1
/* 801F2080 001EEFE0  9B 81 00 26 */	stb r28, 0x26(r1)
/* 801F2084 001EEFE4  9B A1 00 27 */	stb r29, 0x27(r1)
/* 801F2088 001EEFE8  81 9F 03 B4 */	lwz r12, 0x3b4(r31)
/* 801F208C 001EEFEC  81 8C 00 A8 */	lwz r12, 0xa8(r12)
/* 801F2090 001EEFF0  7D 88 03 A6 */	mtlr r12
/* 801F2094 001EEFF4  4E 80 00 21 */	blrl 
/* 801F2098 001EEFF8  9B 81 00 20 */	stb r28, 0x20(r1)
/* 801F209C 001EEFFC  38 81 00 20 */	addi r4, r1, 0x20
/* 801F20A0 001EF000  38 7F 00 00 */	addi r3, r31, 0
/* 801F20A4 001EF004  9B 81 00 21 */	stb r28, 0x21(r1)
/* 801F20A8 001EF008  9B 81 00 22 */	stb r28, 0x22(r1)
/* 801F20AC 001EF00C  9B A1 00 23 */	stb r29, 0x23(r1)
/* 801F20B0 001EF010  81 9F 03 B4 */	lwz r12, 0x3b4(r31)
/* 801F20B4 001EF014  81 8C 00 AC */	lwz r12, 0xac(r12)
/* 801F20B8 001EF018  7D 88 03 A6 */	mtlr r12
/* 801F20BC 001EF01C  4E 80 00 21 */	blrl 
/* 801F20C0 001EF020  80 BF 03 10 */	lwz r5, 0x310(r31)
/* 801F20C4 001EF024  38 81 00 10 */	addi r4, r1, 0x10
/* 801F20C8 001EF028  80 1F 03 0C */	lwz r0, 0x30c(r31)
/* 801F20CC 001EF02C  7F E3 FB 78 */	mr r3, r31
/* 801F20D0 001EF030  93 81 00 10 */	stw r28, 0x10(r1)
/* 801F20D4 001EF034  93 81 00 14 */	stw r28, 0x14(r1)
/* 801F20D8 001EF038  90 01 00 18 */	stw r0, 0x18(r1)
/* 801F20DC 001EF03C  90 A1 00 1C */	stw r5, 0x1c(r1)
/* 801F20E0 001EF040  81 9F 03 B4 */	lwz r12, 0x3b4(r31)
/* 801F20E4 001EF044  81 8C 00 D4 */	lwz r12, 0xd4(r12)
/* 801F20E8 001EF048  7D 88 03 A6 */	mtlr r12
/* 801F20EC 001EF04C  4E 80 00 21 */	blrl 
/* 801F20F0 001EF050  80 7E 00 08 */	lwz r3, 8(r30)
/* 801F20F4 001EF054  81 83 00 00 */	lwz r12, 0(r3)
/* 801F20F8 001EF058  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 801F20FC 001EF05C  7D 88 03 A6 */	mtlr r12
/* 801F2100 001EF060  4E 80 00 21 */	blrl 
.L_801F2104:
/* 801F2104 001EF064  38 7E 00 0C */	addi r3, r30, 0xc
/* 801F2108 001EF068  38 9F 00 00 */	addi r4, r31, 0
/* 801F210C 001EF06C  4B FF FB 21 */	bl draw__Q23zen9AlphaWipeFR8Graphics
.L_801F2110:
/* 801F2110 001EF070  80 01 00 8C */	lwz r0, 0x8c(r1)
/* 801F2114 001EF074  83 E1 00 84 */	lwz r31, 0x84(r1)
/* 801F2118 001EF078  83 C1 00 80 */	lwz r30, 0x80(r1)
/* 801F211C 001EF07C  83 A1 00 7C */	lwz r29, 0x7c(r1)
/* 801F2120 001EF080  83 81 00 78 */	lwz r28, 0x78(r1)
/* 801F2124 001EF084  38 21 00 88 */	addi r1, r1, 0x88
/* 801F2128 001EF088  7C 08 03 A6 */	mtlr r0
/* 801F212C 001EF08C  4E 80 00 20 */	blr 
.endfn draw__Q23zen12DrawUfoPartsFR8Graphics

.fn sleep__Q23zen12DrawUfoPartsFv, global
/* 801F2130 001EF090  7C 08 02 A6 */	mflr r0
/* 801F2134 001EF094  38 83 00 00 */	addi r4, r3, 0
/* 801F2138 001EF098  90 01 00 04 */	stw r0, 4(r1)
/* 801F213C 001EF09C  38 00 00 00 */	li r0, 0
/* 801F2140 001EF0A0  94 21 FF F8 */	stwu r1, -8(r1)
/* 801F2144 001EF0A4  90 03 00 00 */	stw r0, 0(r3)
/* 801F2148 001EF0A8  38 64 00 34 */	addi r3, r4, 0x34
/* 801F214C 001EF0AC  90 04 00 04 */	stw r0, 4(r4)
/* 801F2150 001EF0B0  4B FF C6 29 */	bl sleep__Q23zen10DrawCMbestFv
/* 801F2154 001EF0B4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 801F2158 001EF0B8  38 21 00 08 */	addi r1, r1, 8
/* 801F215C 001EF0BC  7C 08 03 A6 */	mtlr r0
/* 801F2160 001EF0C0  4E 80 00 20 */	blr 
.endfn sleep__Q23zen12DrawUfoPartsFv

.fn start__Q23zen12DrawUfoPartsFv, global
/* 801F2164 001EF0C4  7C 08 02 A6 */	mflr r0
/* 801F2168 001EF0C8  90 01 00 04 */	stw r0, 4(r1)
/* 801F216C 001EF0CC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 801F2170 001EF0D0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 801F2174 001EF0D4  7C 7F 1B 78 */	mr r31, r3
/* 801F2178 001EF0D8  80 63 00 08 */	lwz r3, 8(r3)
/* 801F217C 001EF0DC  38 63 00 04 */	addi r3, r3, 4
/* 801F2180 001EF0E0  4B FC D6 25 */	bl makeResident__Q23zen14P2DPaneLibraryFP7P2DPane
/* 801F2184 001EF0E4  38 00 00 01 */	li r0, 1
/* 801F2188 001EF0E8  90 1F 00 00 */	stw r0, 0(r31)
/* 801F218C 001EF0EC  38 00 00 00 */	li r0, 0
/* 801F2190 001EF0F0  38 7F 00 00 */	addi r3, r31, 0
/* 801F2194 001EF0F4  90 1F 00 04 */	stw r0, 4(r31)
/* 801F2198 001EF0F8  48 00 00 81 */	bl dataSet__Q23zen12DrawUfoPartsFv
/* 801F219C 001EF0FC  C0 22 C2 50 */	lfs f1, lbl_803EC450@sda21(r2)
/* 801F21A0 001EF100  38 7F 00 0C */	addi r3, r31, 0xc
/* 801F21A4 001EF104  C0 42 C2 4C */	lfs f2, lbl_803EC44C@sda21(r2)
/* 801F21A8 001EF108  38 80 00 00 */	li r4, 0
/* 801F21AC 001EF10C  4B FF FB 65 */	bl start__Q23zen9AlphaWipeFffQ33zen9AlphaWipe8typeFlag
/* 801F21B0 001EF110  38 7F 00 34 */	addi r3, r31, 0x34
/* 801F21B4 001EF114  4B FF C6 65 */	bl appear__Q23zen10DrawCMbestFv
/* 801F21B8 001EF118  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 801F21BC 001EF11C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 801F21C0 001EF120  38 21 00 18 */	addi r1, r1, 0x18
/* 801F21C4 001EF124  7C 08 03 A6 */	mtlr r0
/* 801F21C8 001EF128  4E 80 00 20 */	blr 
.endfn start__Q23zen12DrawUfoPartsFv

.fn operation__Q23zen12DrawUfoPartsFv, global
/* 801F21CC 001EF12C  7C 08 02 A6 */	mflr r0
/* 801F21D0 001EF130  90 01 00 04 */	stw r0, 4(r1)
/* 801F21D4 001EF134  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 801F21D8 001EF138  93 E1 00 14 */	stw r31, 0x14(r1)
/* 801F21DC 001EF13C  7C 7F 1B 78 */	mr r31, r3
/* 801F21E0 001EF140  80 63 00 08 */	lwz r3, 8(r3)
/* 801F21E4 001EF144  38 63 00 04 */	addi r3, r3, 4
/* 801F21E8 001EF148  4B FC D5 BD */	bl makeResident__Q23zen14P2DPaneLibraryFP7P2DPane
/* 801F21EC 001EF14C  38 00 00 02 */	li r0, 2
/* 801F21F0 001EF150  90 1F 00 00 */	stw r0, 0(r31)
/* 801F21F4 001EF154  38 00 00 00 */	li r0, 0
/* 801F21F8 001EF158  38 7F 00 00 */	addi r3, r31, 0
/* 801F21FC 001EF15C  90 1F 00 04 */	stw r0, 4(r31)
/* 801F2200 001EF160  48 00 00 19 */	bl dataSet__Q23zen12DrawUfoPartsFv
/* 801F2204 001EF164  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 801F2208 001EF168  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 801F220C 001EF16C  38 21 00 18 */	addi r1, r1, 0x18
/* 801F2210 001EF170  7C 08 03 A6 */	mtlr r0
/* 801F2214 001EF174  4E 80 00 20 */	blr 
.endfn operation__Q23zen12DrawUfoPartsFv

.fn dataSet__Q23zen12DrawUfoPartsFv, global
/* 801F2218 001EF178  7C 08 02 A6 */	mflr r0
/* 801F221C 001EF17C  90 01 00 04 */	stw r0, 4(r1)
/* 801F2220 001EF180  94 21 FF 70 */	stwu r1, -0x90(r1)
/* 801F2224 001EF184  93 E1 00 8C */	stw r31, 0x8c(r1)
/* 801F2228 001EF188  93 C1 00 88 */	stw r30, 0x88(r1)
/* 801F222C 001EF18C  93 A1 00 84 */	stw r29, 0x84(r1)
/* 801F2230 001EF190  3B A0 00 00 */	li r29, 0
/* 801F2234 001EF194  93 81 00 80 */	stw r28, 0x80(r1)
/* 801F2238 001EF198  80 63 00 08 */	lwz r3, 8(r3)
/* 801F223C 001EF19C  3B 83 00 04 */	addi r28, r3, 4
.L_801F2240:
/* 801F2240 001EF1A0  38 61 00 78 */	addi r3, r1, 0x78
/* 801F2244 001EF1A4  4C C6 31 82 */	crclr 6
/* 801F2248 001EF1A8  38 BD 00 01 */	addi r5, r29, 1
/* 801F224C 001EF1AC  38 8D 29 98 */	addi r4, r13, lbl_803E76B8@sda21
/* 801F2250 001EF1B0  48 02 43 49 */	bl sprintf
/* 801F2254 001EF1B4  81 9C 00 00 */	lwz r12, 0(r28)
/* 801F2258 001EF1B8  7F 83 E3 78 */	mr r3, r28
/* 801F225C 001EF1BC  88 01 00 79 */	lbz r0, 0x79(r1)
/* 801F2260 001EF1C0  38 A0 00 01 */	li r5, 1
/* 801F2264 001EF1C4  81 8C 00 34 */	lwz r12, 0x34(r12)
/* 801F2268 001EF1C8  88 81 00 78 */	lbz r4, 0x78(r1)
/* 801F226C 001EF1CC  54 00 80 1E */	slwi r0, r0, 0x10
/* 801F2270 001EF1D0  88 C1 00 7A */	lbz r6, 0x7a(r1)
/* 801F2274 001EF1D4  7D 88 03 A6 */	mtlr r12
/* 801F2278 001EF1D8  50 80 C0 0E */	rlwimi r0, r4, 0x18, 0, 7
/* 801F227C 001EF1DC  88 E1 00 7B */	lbz r7, 0x7b(r1)
/* 801F2280 001EF1E0  50 C0 44 2E */	rlwimi r0, r6, 8, 0x10, 0x17
/* 801F2284 001EF1E4  7C E4 03 78 */	or r4, r7, r0
/* 801F2288 001EF1E8  4E 80 00 21 */	blrl 
/* 801F228C 001EF1EC  3B C3 00 00 */	addi r30, r3, 0
/* 801F2290 001EF1F0  4C C6 31 82 */	crclr 6
/* 801F2294 001EF1F4  38 61 00 78 */	addi r3, r1, 0x78
/* 801F2298 001EF1F8  38 BD 00 01 */	addi r5, r29, 1
/* 801F229C 001EF1FC  38 8D 29 A0 */	addi r4, r13, lbl_803E76C0@sda21
/* 801F22A0 001EF200  48 02 42 F9 */	bl sprintf
/* 801F22A4 001EF204  81 9C 00 00 */	lwz r12, 0(r28)
/* 801F22A8 001EF208  7F 83 E3 78 */	mr r3, r28
/* 801F22AC 001EF20C  88 01 00 79 */	lbz r0, 0x79(r1)
/* 801F22B0 001EF210  38 A0 00 01 */	li r5, 1
/* 801F22B4 001EF214  81 8C 00 34 */	lwz r12, 0x34(r12)
/* 801F22B8 001EF218  88 81 00 78 */	lbz r4, 0x78(r1)
/* 801F22BC 001EF21C  54 00 80 1E */	slwi r0, r0, 0x10
/* 801F22C0 001EF220  88 C1 00 7A */	lbz r6, 0x7a(r1)
/* 801F22C4 001EF224  7D 88 03 A6 */	mtlr r12
/* 801F22C8 001EF228  50 80 C0 0E */	rlwimi r0, r4, 0x18, 0, 7
/* 801F22CC 001EF22C  88 E1 00 7B */	lbz r7, 0x7b(r1)
/* 801F22D0 001EF230  50 C0 44 2E */	rlwimi r0, r6, 8, 0x10, 0x17
/* 801F22D4 001EF234  7C E4 03 78 */	or r4, r7, r0
/* 801F22D8 001EF238  4E 80 00 21 */	blrl 
/* 801F22DC 001EF23C  80 0D 2F 6C */	lwz r0, playerState@sda21(r13)
/* 801F22E0 001EF240  3B E3 00 00 */	addi r31, r3, 0
/* 801F22E4 001EF244  28 00 00 00 */	cmplwi r0, 0
/* 801F22E8 001EF248  41 82 00 90 */	beq .L_801F2378
/* 801F22EC 001EF24C  7F A3 EB 78 */	mr r3, r29
/* 801F22F0 001EF250  4B EA 28 69 */	bl getUfoIDFromIndex__9PelletMgrFi
/* 801F22F4 001EF254  7C 64 1B 78 */	mr r4, r3
/* 801F22F8 001EF258  80 6D 2F 6C */	lwz r3, playerState@sda21(r13)
/* 801F22FC 001EF25C  4B E8 E3 09 */	bl hasUfoParts__11PlayerStateFUl
/* 801F2300 001EF260  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 801F2304 001EF264  40 82 00 F4 */	bne .L_801F23F8
/* 801F2308 001EF268  38 60 00 30 */	li r3, 0x30
/* 801F230C 001EF26C  98 61 00 70 */	stb r3, 0x70(r1)
/* 801F2310 001EF270  38 80 00 00 */	li r4, 0
/* 801F2314 001EF274  38 00 00 FF */	li r0, 0xff
/* 801F2318 001EF278  98 61 00 71 */	stb r3, 0x71(r1)
/* 801F231C 001EF27C  98 61 00 72 */	stb r3, 0x72(r1)
/* 801F2320 001EF280  98 81 00 73 */	stb r4, 0x73(r1)
/* 801F2324 001EF284  80 61 00 70 */	lwz r3, 0x70(r1)
/* 801F2328 001EF288  90 7E 01 0C */	stw r3, 0x10c(r30)
/* 801F232C 001EF28C  98 81 00 68 */	stb r4, 0x68(r1)
/* 801F2330 001EF290  98 81 00 69 */	stb r4, 0x69(r1)
/* 801F2334 001EF294  98 81 00 6A */	stb r4, 0x6a(r1)
/* 801F2338 001EF298  98 01 00 6B */	stb r0, 0x6b(r1)
/* 801F233C 001EF29C  80 01 00 68 */	lwz r0, 0x68(r1)
/* 801F2340 001EF2A0  90 1E 01 08 */	stw r0, 0x108(r30)
/* 801F2344 001EF2A4  98 81 00 60 */	stb r4, 0x60(r1)
/* 801F2348 001EF2A8  98 81 00 61 */	stb r4, 0x61(r1)
/* 801F234C 001EF2AC  98 81 00 62 */	stb r4, 0x62(r1)
/* 801F2350 001EF2B0  98 81 00 63 */	stb r4, 0x63(r1)
/* 801F2354 001EF2B4  80 01 00 60 */	lwz r0, 0x60(r1)
/* 801F2358 001EF2B8  90 1F 00 F4 */	stw r0, 0xf4(r31)
/* 801F235C 001EF2BC  98 81 00 58 */	stb r4, 0x58(r1)
/* 801F2360 001EF2C0  98 81 00 59 */	stb r4, 0x59(r1)
/* 801F2364 001EF2C4  98 81 00 5A */	stb r4, 0x5a(r1)
/* 801F2368 001EF2C8  98 81 00 5B */	stb r4, 0x5b(r1)
/* 801F236C 001EF2CC  80 01 00 58 */	lwz r0, 0x58(r1)
/* 801F2370 001EF2D0  90 1F 00 F8 */	stw r0, 0xf8(r31)
/* 801F2374 001EF2D4  48 00 00 84 */	b .L_801F23F8
.L_801F2378:
/* 801F2378 001EF2D8  7F A0 0E 70 */	srawi r0, r29, 1
/* 801F237C 001EF2DC  7C 00 01 94 */	addze r0, r0
/* 801F2380 001EF2E0  54 00 08 3C */	slwi r0, r0, 1
/* 801F2384 001EF2E4  7C 00 E8 11 */	subfc. r0, r0, r29
/* 801F2388 001EF2E8  40 82 00 70 */	bne .L_801F23F8
/* 801F238C 001EF2EC  38 60 00 30 */	li r3, 0x30
/* 801F2390 001EF2F0  98 61 00 50 */	stb r3, 0x50(r1)
/* 801F2394 001EF2F4  38 80 00 00 */	li r4, 0
/* 801F2398 001EF2F8  38 00 00 FF */	li r0, 0xff
/* 801F239C 001EF2FC  98 61 00 51 */	stb r3, 0x51(r1)
/* 801F23A0 001EF300  98 61 00 52 */	stb r3, 0x52(r1)
/* 801F23A4 001EF304  98 81 00 53 */	stb r4, 0x53(r1)
/* 801F23A8 001EF308  80 61 00 50 */	lwz r3, 0x50(r1)
/* 801F23AC 001EF30C  90 7E 01 0C */	stw r3, 0x10c(r30)
/* 801F23B0 001EF310  98 81 00 48 */	stb r4, 0x48(r1)
/* 801F23B4 001EF314  98 81 00 49 */	stb r4, 0x49(r1)
/* 801F23B8 001EF318  98 81 00 4A */	stb r4, 0x4a(r1)
/* 801F23BC 001EF31C  98 01 00 4B */	stb r0, 0x4b(r1)
/* 801F23C0 001EF320  80 01 00 48 */	lwz r0, 0x48(r1)
/* 801F23C4 001EF324  90 1E 01 08 */	stw r0, 0x108(r30)
/* 801F23C8 001EF328  98 81 00 40 */	stb r4, 0x40(r1)
/* 801F23CC 001EF32C  98 81 00 41 */	stb r4, 0x41(r1)
/* 801F23D0 001EF330  98 81 00 42 */	stb r4, 0x42(r1)
/* 801F23D4 001EF334  98 81 00 43 */	stb r4, 0x43(r1)
/* 801F23D8 001EF338  80 01 00 40 */	lwz r0, 0x40(r1)
/* 801F23DC 001EF33C  90 1F 00 F4 */	stw r0, 0xf4(r31)
/* 801F23E0 001EF340  98 81 00 38 */	stb r4, 0x38(r1)
/* 801F23E4 001EF344  98 81 00 39 */	stb r4, 0x39(r1)
/* 801F23E8 001EF348  98 81 00 3A */	stb r4, 0x3a(r1)
/* 801F23EC 001EF34C  98 81 00 3B */	stb r4, 0x3b(r1)
/* 801F23F0 001EF350  80 01 00 38 */	lwz r0, 0x38(r1)
/* 801F23F4 001EF354  90 1F 00 F8 */	stw r0, 0xf8(r31)
.L_801F23F8:
/* 801F23F8 001EF358  3B BD 00 01 */	addi r29, r29, 1
/* 801F23FC 001EF35C  2C 1D 00 1E */	cmpwi r29, 0x1e
/* 801F2400 001EF360  41 80 FE 40 */	blt .L_801F2240
/* 801F2404 001EF364  80 01 00 94 */	lwz r0, 0x94(r1)
/* 801F2408 001EF368  83 E1 00 8C */	lwz r31, 0x8c(r1)
/* 801F240C 001EF36C  83 C1 00 88 */	lwz r30, 0x88(r1)
/* 801F2410 001EF370  83 A1 00 84 */	lwz r29, 0x84(r1)
/* 801F2414 001EF374  83 81 00 80 */	lwz r28, 0x80(r1)
/* 801F2418 001EF378  38 21 00 90 */	addi r1, r1, 0x90
/* 801F241C 001EF37C  7C 08 03 A6 */	mtlr r0
/* 801F2420 001EF380  4E 80 00 20 */	blr 
.endfn dataSet__Q23zen12DrawUfoPartsFv

.section .data, "wa"  # 0x80222DC0 - 0x802E9640
.balign 8
.obj lbl_802E7148, local
	.asciz "screen/blo/ufo_p.blo"
.endobj lbl_802E7148

.section .sdata, "wa"  # 0x803DCD20 - 0x803E7820
.balign 8
.obj lbl_803E76B8, local
	.asciz "ui%02d"
.endobj lbl_803E76B8
.balign 4
.obj lbl_803E76C0, local
	.asciz "un%02d"
.endobj lbl_803E76C0

.section .sdata2, "a"  # 0x803E8200 - 0x803EC840
.balign 8
.obj lbl_803EC448, local
	.float 0.5
.endobj lbl_803EC448
.obj lbl_803EC44C, local
	.float 0.25
.endobj lbl_803EC44C
.obj lbl_803EC450, local
	.float 0.75
.endobj lbl_803EC450
