.include "macros.inc"
.section .text, "ax"  # 0x80005560 - 0x80221F60
.fn __ct__5LightFv, global
/* 80029A48 000269A8  7C 08 02 A6 */	mflr r0
/* 80029A4C 000269AC  3C 80 80 22 */	lis r4, __vt__5ANode@ha
/* 80029A50 000269B0  90 01 00 04 */	stw r0, 4(r1)
/* 80029A54 000269B4  38 04 73 8C */	addi r0, r4, __vt__5ANode@l
/* 80029A58 000269B8  38 CD 82 E4 */	addi r6, r13, lbl_803DD004@sda21
/* 80029A5C 000269BC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80029A60 000269C0  3C A0 80 23 */	lis r5, __vt__5Light@ha
/* 80029A64 000269C4  38 E0 00 06 */	li r7, 6
/* 80029A68 000269C8  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80029A6C 000269CC  3B E0 00 00 */	li r31, 0
/* 80029A70 000269D0  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80029A74 000269D4  3B C3 00 00 */	addi r30, r3, 0
/* 80029A78 000269D8  3C 60 80 22 */	lis r3, __vt__8CoreNode@ha
/* 80029A7C 000269DC  90 1E 00 00 */	stw r0, 0(r30)
/* 80029A80 000269E0  38 03 73 7C */	addi r0, r3, __vt__8CoreNode@l
/* 80029A84 000269E4  3C 60 80 03 */	lis r3, __ct__12CullingPlaneFv@ha
/* 80029A88 000269E8  90 1E 00 00 */	stw r0, 0(r30)
/* 80029A8C 000269EC  38 05 82 F4 */	addi r0, r5, __vt__5Light@l
/* 80029A90 000269F0  38 83 9C 48 */	addi r4, r3, __ct__12CullingPlaneFv@l
/* 80029A94 000269F4  93 FE 00 10 */	stw r31, 0x10(r30)
/* 80029A98 000269F8  38 7E 00 80 */	addi r3, r30, 0x80
/* 80029A9C 000269FC  38 A0 00 00 */	li r5, 0
/* 80029AA0 00026A00  93 FE 00 0C */	stw r31, 0xc(r30)
/* 80029AA4 00026A04  93 FE 00 08 */	stw r31, 8(r30)
/* 80029AA8 00026A08  90 DE 00 04 */	stw r6, 4(r30)
/* 80029AAC 00026A0C  38 C0 00 2C */	li r6, 0x2c
/* 80029AB0 00026A10  90 1E 00 00 */	stw r0, 0(r30)
/* 80029AB4 00026A14  C0 02 82 90 */	lfs f0, lbl_803E8490@sda21(r2)
/* 80029AB8 00026A18  D0 1E 00 5C */	stfs f0, 0x5c(r30)
/* 80029ABC 00026A1C  D0 1E 00 58 */	stfs f0, 0x58(r30)
/* 80029AC0 00026A20  D0 1E 00 54 */	stfs f0, 0x54(r30)
/* 80029AC4 00026A24  D0 1E 00 68 */	stfs f0, 0x68(r30)
/* 80029AC8 00026A28  D0 1E 00 64 */	stfs f0, 0x64(r30)
/* 80029ACC 00026A2C  D0 1E 00 60 */	stfs f0, 0x60(r30)
/* 80029AD0 00026A30  48 1E AF A1 */	bl __construct_array
/* 80029AD4 00026A34  C0 42 82 90 */	lfs f2, lbl_803E8490@sda21(r2)
/* 80029AD8 00026A38  38 C0 03 02 */	li r6, 0x302
/* 80029ADC 00026A3C  38 A0 00 03 */	li r5, 3
/* 80029AE0 00026A40  D0 5E 01 D4 */	stfs f2, 0x1d4(r30)
/* 80029AE4 00026A44  38 80 00 02 */	li r4, 2
/* 80029AE8 00026A48  38 00 00 FF */	li r0, 0xff
/* 80029AEC 00026A4C  D0 5E 01 D0 */	stfs f2, 0x1d0(r30)
/* 80029AF0 00026A50  7F C3 F3 78 */	mr r3, r30
/* 80029AF4 00026A54  D0 5E 01 CC */	stfs f2, 0x1cc(r30)
/* 80029AF8 00026A58  D0 5E 01 E0 */	stfs f2, 0x1e0(r30)
/* 80029AFC 00026A5C  D0 5E 01 DC */	stfs f2, 0x1dc(r30)
/* 80029B00 00026A60  D0 5E 01 D8 */	stfs f2, 0x1d8(r30)
/* 80029B04 00026A64  D0 5E 01 EC */	stfs f2, 0x1ec(r30)
/* 80029B08 00026A68  D0 5E 01 E8 */	stfs f2, 0x1e8(r30)
/* 80029B0C 00026A6C  D0 5E 01 E4 */	stfs f2, 0x1e4(r30)
/* 80029B10 00026A70  D0 5E 01 F8 */	stfs f2, 0x1f8(r30)
/* 80029B14 00026A74  D0 5E 01 F4 */	stfs f2, 0x1f4(r30)
/* 80029B18 00026A78  D0 5E 01 F0 */	stfs f2, 0x1f0(r30)
/* 80029B1C 00026A7C  D0 5E 02 04 */	stfs f2, 0x204(r30)
/* 80029B20 00026A80  D0 5E 02 00 */	stfs f2, 0x200(r30)
/* 80029B24 00026A84  D0 5E 01 FC */	stfs f2, 0x1fc(r30)
/* 80029B28 00026A88  D0 5E 02 10 */	stfs f2, 0x210(r30)
/* 80029B2C 00026A8C  D0 5E 02 0C */	stfs f2, 0x20c(r30)
/* 80029B30 00026A90  D0 5E 02 08 */	stfs f2, 0x208(r30)
/* 80029B34 00026A94  D0 5E 02 1C */	stfs f2, 0x21c(r30)
/* 80029B38 00026A98  D0 5E 02 18 */	stfs f2, 0x218(r30)
/* 80029B3C 00026A9C  D0 5E 02 14 */	stfs f2, 0x214(r30)
/* 80029B40 00026AA0  D0 5E 02 28 */	stfs f2, 0x228(r30)
/* 80029B44 00026AA4  D0 5E 02 24 */	stfs f2, 0x224(r30)
/* 80029B48 00026AA8  D0 5E 02 20 */	stfs f2, 0x220(r30)
/* 80029B4C 00026AAC  D0 5E 02 34 */	stfs f2, 0x234(r30)
/* 80029B50 00026AB0  D0 5E 02 30 */	stfs f2, 0x230(r30)
/* 80029B54 00026AB4  D0 5E 02 2C */	stfs f2, 0x22c(r30)
/* 80029B58 00026AB8  9B FE 01 C9 */	stb r31, 0x1c9(r30)
/* 80029B5C 00026ABC  C0 0D 82 C0 */	lfs f0, lbl_803DCFE0@sda21(r13)
/* 80029B60 00026AC0  D0 1E 01 D8 */	stfs f0, 0x1d8(r30)
/* 80029B64 00026AC4  C0 0D 82 C4 */	lfs f0, lbl_803DCFE4@sda21(r13)
/* 80029B68 00026AC8  D0 1E 01 DC */	stfs f0, 0x1dc(r30)
/* 80029B6C 00026ACC  C0 0D 82 C8 */	lfs f0, lbl_803DCFE8@sda21(r13)
/* 80029B70 00026AD0  D0 1E 01 E0 */	stfs f0, 0x1e0(r30)
/* 80029B74 00026AD4  C0 02 82 94 */	lfs f0, lbl_803E8494@sda21(r2)
/* 80029B78 00026AD8  D0 1E 02 40 */	stfs f0, 0x240(r30)
/* 80029B7C 00026ADC  C0 22 82 98 */	lfs f1, lbl_803E8498@sda21(r2)
/* 80029B80 00026AE0  D0 3E 02 44 */	stfs f1, 0x244(r30)
/* 80029B84 00026AE4  C0 02 82 9C */	lfs f0, lbl_803E849C@sda21(r2)
/* 80029B88 00026AE8  D0 1E 02 48 */	stfs f0, 0x248(r30)
/* 80029B8C 00026AEC  90 DE 00 14 */	stw r6, 0x14(r30)
/* 80029B90 00026AF0  90 BE 00 24 */	stw r5, 0x24(r30)
/* 80029B94 00026AF4  C0 02 82 A0 */	lfs f0, lbl_803E84A0@sda21(r2)
/* 80029B98 00026AF8  D0 1E 00 18 */	stfs f0, 0x18(r30)
/* 80029B9C 00026AFC  C0 02 82 A4 */	lfs f0, lbl_803E84A4@sda21(r2)
/* 80029BA0 00026B00  D0 1E 00 1C */	stfs f0, 0x1c(r30)
/* 80029BA4 00026B04  90 9E 00 28 */	stw r4, 0x28(r30)
/* 80029BA8 00026B08  C0 02 82 A8 */	lfs f0, lbl_803E84A8@sda21(r2)
/* 80029BAC 00026B0C  D0 1E 00 20 */	stfs f0, 0x20(r30)
/* 80029BB0 00026B10  D0 5E 00 2C */	stfs f2, 0x2c(r30)
/* 80029BB4 00026B14  D0 5E 00 30 */	stfs f2, 0x30(r30)
/* 80029BB8 00026B18  C0 02 82 AC */	lfs f0, lbl_803E84AC@sda21(r2)
/* 80029BBC 00026B1C  D0 1E 00 34 */	stfs f0, 0x34(r30)
/* 80029BC0 00026B20  D0 3E 00 38 */	stfs f1, 0x38(r30)
/* 80029BC4 00026B24  D0 5E 00 3C */	stfs f2, 0x3c(r30)
/* 80029BC8 00026B28  D0 5E 00 40 */	stfs f2, 0x40(r30)
/* 80029BCC 00026B2C  C0 02 82 B0 */	lfs f0, lbl_803E84B0@sda21(r2)
/* 80029BD0 00026B30  D0 1E 00 48 */	stfs f0, 0x48(r30)
/* 80029BD4 00026B34  C0 02 82 B4 */	lfs f0, lbl_803E84B4@sda21(r2)
/* 80029BD8 00026B38  D0 1E 00 44 */	stfs f0, 0x44(r30)
/* 80029BDC 00026B3C  C0 0D 82 CC */	lfs f0, lbl_803DCFEC@sda21(r13)
/* 80029BE0 00026B40  D0 1E 00 54 */	stfs f0, 0x54(r30)
/* 80029BE4 00026B44  C0 0D 82 D0 */	lfs f0, lbl_803DCFF0@sda21(r13)
/* 80029BE8 00026B48  D0 1E 00 58 */	stfs f0, 0x58(r30)
/* 80029BEC 00026B4C  C0 0D 82 D4 */	lfs f0, lbl_803DCFF4@sda21(r13)
/* 80029BF0 00026B50  D0 1E 00 5C */	stfs f0, 0x5c(r30)
/* 80029BF4 00026B54  C0 0D 82 D8 */	lfs f0, lbl_803DCFF8@sda21(r13)
/* 80029BF8 00026B58  D0 1E 00 60 */	stfs f0, 0x60(r30)
/* 80029BFC 00026B5C  C0 0D 82 DC */	lfs f0, lbl_803DCFFC@sda21(r13)
/* 80029C00 00026B60  D0 1E 00 64 */	stfs f0, 0x64(r30)
/* 80029C04 00026B64  C0 0D 82 E0 */	lfs f0, lbl_803DD000@sda21(r13)
/* 80029C08 00026B68  D0 1E 00 68 */	stfs f0, 0x68(r30)
/* 80029C0C 00026B6C  98 1E 00 6C */	stb r0, 0x6c(r30)
/* 80029C10 00026B70  98 1E 00 6D */	stb r0, 0x6d(r30)
/* 80029C14 00026B74  98 1E 00 6E */	stb r0, 0x6e(r30)
/* 80029C18 00026B78  98 1E 00 6F */	stb r0, 0x6f(r30)
/* 80029C1C 00026B7C  C0 3E 00 18 */	lfs f1, 0x18(r30)
/* 80029C20 00026B80  C0 5E 00 1C */	lfs f2, 0x1c(r30)
/* 80029C24 00026B84  80 9E 00 24 */	lwz r4, 0x24(r30)
/* 80029C28 00026B88  48 00 00 35 */	bl setLightDistAttn__5LightFffi
/* 80029C2C 00026B8C  7F C3 F3 78 */	mr r3, r30
/* 80029C30 00026B90  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80029C34 00026B94  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80029C38 00026B98  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80029C3C 00026B9C  38 21 00 18 */	addi r1, r1, 0x18
/* 80029C40 00026BA0  7C 08 03 A6 */	mtlr r0
/* 80029C44 00026BA4  4E 80 00 20 */	blr 
.endfn __ct__5LightFv

.fn __ct__12CullingPlaneFv, weak
/* 80029C48 00026BA8  C0 02 82 90 */	lfs f0, lbl_803E8490@sda21(r2)
/* 80029C4C 00026BAC  D0 03 00 08 */	stfs f0, 8(r3)
/* 80029C50 00026BB0  D0 03 00 04 */	stfs f0, 4(r3)
/* 80029C54 00026BB4  D0 03 00 00 */	stfs f0, 0(r3)
/* 80029C58 00026BB8  4E 80 00 20 */	blr 
.endfn __ct__12CullingPlaneFv

.fn setLightDistAttn__5LightFffi, global
/* 80029C5C 00026BBC  D0 23 00 18 */	stfs f1, 0x18(r3)
/* 80029C60 00026BC0  D0 43 00 1C */	stfs f2, 0x1c(r3)
/* 80029C64 00026BC4  90 83 00 24 */	stw r4, 0x24(r3)
/* 80029C68 00026BC8  C0 02 82 90 */	lfs f0, lbl_803E8490@sda21(r2)
/* 80029C6C 00026BCC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80029C70 00026BD0  40 80 00 08 */	bge .L_80029C78
/* 80029C74 00026BD4  38 80 00 00 */	li r4, 0
.L_80029C78:
/* 80029C78 00026BD8  C0 02 82 90 */	lfs f0, lbl_803E8490@sda21(r2)
/* 80029C7C 00026BDC  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80029C80 00026BE0  4C 40 13 82 */	cror 2, 0, 2
/* 80029C84 00026BE4  41 82 00 14 */	beq .L_80029C98
/* 80029C88 00026BE8  C0 02 82 98 */	lfs f0, lbl_803E8498@sda21(r2)
/* 80029C8C 00026BEC  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80029C90 00026BF0  4C 41 13 82 */	cror 2, 1, 2
/* 80029C94 00026BF4  40 82 00 08 */	bne .L_80029C9C
.L_80029C98:
/* 80029C98 00026BF8  38 80 00 00 */	li r4, 0
.L_80029C9C:
/* 80029C9C 00026BFC  2C 04 00 02 */	cmpwi r4, 2
/* 80029CA0 00026C00  41 82 00 3C */	beq .L_80029CDC
/* 80029CA4 00026C04  40 80 00 14 */	bge .L_80029CB8
/* 80029CA8 00026C08  2C 04 00 00 */	cmpwi r4, 0
/* 80029CAC 00026C0C  41 82 00 70 */	beq .L_80029D1C
/* 80029CB0 00026C10  40 80 00 14 */	bge .L_80029CC4
/* 80029CB4 00026C14  48 00 00 68 */	b .L_80029D1C
.L_80029CB8:
/* 80029CB8 00026C18  2C 04 00 04 */	cmpwi r4, 4
/* 80029CBC 00026C1C  40 80 00 60 */	bge .L_80029D1C
/* 80029CC0 00026C20  48 00 00 40 */	b .L_80029D00
.L_80029CC4:
/* 80029CC4 00026C24  C0 A2 82 98 */	lfs f5, lbl_803E8498@sda21(r2)
/* 80029CC8 00026C28  EC 02 00 72 */	fmuls f0, f2, f1
/* 80029CCC 00026C2C  C0 82 82 90 */	lfs f4, lbl_803E8490@sda21(r2)
/* 80029CD0 00026C30  EC 25 10 28 */	fsubs f1, f5, f2
/* 80029CD4 00026C34  EC 61 00 24 */	fdivs f3, f1, f0
/* 80029CD8 00026C38  48 00 00 50 */	b .L_80029D28
.L_80029CDC:
/* 80029CDC 00026C3C  C0 A2 82 98 */	lfs f5, lbl_803E8498@sda21(r2)
/* 80029CE0 00026C40  EC 82 00 72 */	fmuls f4, f2, f1
/* 80029CE4 00026C44  C0 62 82 B8 */	lfs f3, lbl_803E84B8@sda21(r2)
/* 80029CE8 00026C48  EC 45 10 28 */	fsubs f2, f5, f2
/* 80029CEC 00026C4C  EC 01 01 32 */	fmuls f0, f1, f4
/* 80029CF0 00026C50  EC 23 00 B2 */	fmuls f1, f3, f2
/* 80029CF4 00026C54  EC 61 20 24 */	fdivs f3, f1, f4
/* 80029CF8 00026C58  EC 81 00 24 */	fdivs f4, f1, f0
/* 80029CFC 00026C5C  48 00 00 2C */	b .L_80029D28
.L_80029D00:
/* 80029D00 00026C60  EC 02 00 72 */	fmuls f0, f2, f1
/* 80029D04 00026C64  C0 A2 82 98 */	lfs f5, lbl_803E8498@sda21(r2)
/* 80029D08 00026C68  C0 62 82 90 */	lfs f3, lbl_803E8490@sda21(r2)
/* 80029D0C 00026C6C  EC 45 10 28 */	fsubs f2, f5, f2
/* 80029D10 00026C70  EC 01 00 32 */	fmuls f0, f1, f0
/* 80029D14 00026C74  EC 82 00 24 */	fdivs f4, f2, f0
/* 80029D18 00026C78  48 00 00 10 */	b .L_80029D28
.L_80029D1C:
/* 80029D1C 00026C7C  C0 62 82 90 */	lfs f3, lbl_803E8490@sda21(r2)
/* 80029D20 00026C80  C0 A2 82 98 */	lfs f5, lbl_803E8498@sda21(r2)
/* 80029D24 00026C84  FC 80 18 90 */	fmr f4, f3
.L_80029D28:
/* 80029D28 00026C88  D0 A3 00 2C */	stfs f5, 0x2c(r3)
/* 80029D2C 00026C8C  38 00 00 01 */	li r0, 1
/* 80029D30 00026C90  D0 63 00 30 */	stfs f3, 0x30(r3)
/* 80029D34 00026C94  D0 83 00 34 */	stfs f4, 0x34(r3)
/* 80029D38 00026C98  90 03 00 70 */	stw r0, 0x70(r3)
/* 80029D3C 00026C9C  4E 80 00 20 */	blr 
.endfn setLightDistAttn__5LightFffi

.fn setLightSpot__5LightFfi, global
/* 80029D40 00026CA0  7C 08 02 A6 */	mflr r0
/* 80029D44 00026CA4  90 01 00 04 */	stw r0, 4(r1)
/* 80029D48 00026CA8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80029D4C 00026CAC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80029D50 00026CB0  3B E4 00 00 */	addi r31, r4, 0
/* 80029D54 00026CB4  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80029D58 00026CB8  3B C3 00 00 */	addi r30, r3, 0
/* 80029D5C 00026CBC  C0 02 82 90 */	lfs f0, lbl_803E8490@sda21(r2)
/* 80029D60 00026CC0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80029D64 00026CC4  4C 40 13 82 */	cror 2, 0, 2
/* 80029D68 00026CC8  41 82 00 10 */	beq .L_80029D78
/* 80029D6C 00026CCC  C0 02 82 BC */	lfs f0, lbl_803E84BC@sda21(r2)
/* 80029D70 00026CD0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80029D74 00026CD4  40 81 00 08 */	ble .L_80029D7C
.L_80029D78:
/* 80029D78 00026CD8  3B E0 00 00 */	li r31, 0
.L_80029D7C:
/* 80029D7C 00026CDC  C0 42 82 C0 */	lfs f2, lbl_803E84C0@sda21(r2)
/* 80029D80 00026CE0  C0 02 82 C4 */	lfs f0, lbl_803E84C4@sda21(r2)
/* 80029D84 00026CE4  EC 22 00 72 */	fmuls f1, f2, f1
/* 80029D88 00026CE8  EC 21 00 24 */	fdivs f1, f1, f0
/* 80029D8C 00026CEC  48 1F 1D C9 */	bl cosf
/* 80029D90 00026CF0  28 1F 00 06 */	cmplwi r31, 6
/* 80029D94 00026CF4  41 81 00 FC */	bgt .L_80029E90
/* 80029D98 00026CF8  3C 60 80 23 */	lis r3, lbl_802282AC@ha
/* 80029D9C 00026CFC  38 63 82 AC */	addi r3, r3, lbl_802282AC@l
/* 80029DA0 00026D00  57 E0 10 3A */	slwi r0, r31, 2
/* 80029DA4 00026D04  7C 03 00 2E */	lwzx r0, r3, r0
/* 80029DA8 00026D08  7C 09 03 A6 */	mtctr r0
/* 80029DAC 00026D0C  4E 80 04 20 */	bctr 
.L_80029DB0:
/* 80029DB0 00026D10  C0 02 82 C8 */	lfs f0, lbl_803E84C8@sda21(r2)
/* 80029DB4 00026D14  C0 42 82 9C */	lfs f2, lbl_803E849C@sda21(r2)
/* 80029DB8 00026D18  EC A0 00 72 */	fmuls f5, f0, f1
/* 80029DBC 00026D1C  C0 62 82 90 */	lfs f3, lbl_803E8490@sda21(r2)
/* 80029DC0 00026D20  48 00 00 DC */	b .L_80029E9C
.L_80029DC4:
/* 80029DC4 00026D24  C0 02 82 98 */	lfs f0, lbl_803E8498@sda21(r2)
/* 80029DC8 00026D28  FC 40 08 50 */	fneg f2, f1
/* 80029DCC 00026D2C  C0 62 82 90 */	lfs f3, lbl_803E8490@sda21(r2)
/* 80029DD0 00026D30  EC 20 08 28 */	fsubs f1, f0, f1
/* 80029DD4 00026D34  EC A2 08 24 */	fdivs f5, f2, f1
/* 80029DD8 00026D38  EC 40 08 24 */	fdivs f2, f0, f1
/* 80029DDC 00026D3C  48 00 00 C0 */	b .L_80029E9C
.L_80029DE0:
/* 80029DE0 00026D40  C0 02 82 98 */	lfs f0, lbl_803E8498@sda21(r2)
/* 80029DE4 00026D44  FC 40 08 50 */	fneg f2, f1
/* 80029DE8 00026D48  C0 A2 82 90 */	lfs f5, lbl_803E8490@sda21(r2)
/* 80029DEC 00026D4C  EC 20 08 28 */	fsubs f1, f0, f1
/* 80029DF0 00026D50  EC 42 08 24 */	fdivs f2, f2, f1
/* 80029DF4 00026D54  EC 60 08 24 */	fdivs f3, f0, f1
/* 80029DF8 00026D58  48 00 00 A4 */	b .L_80029E9C
.L_80029DFC:
/* 80029DFC 00026D5C  C0 02 82 98 */	lfs f0, lbl_803E8498@sda21(r2)
/* 80029E00 00026D60  C0 62 82 CC */	lfs f3, lbl_803E84CC@sda21(r2)
/* 80029E04 00026D64  EC 80 08 28 */	fsubs f4, f0, f1
/* 80029E08 00026D68  C0 02 82 D0 */	lfs f0, lbl_803E84D0@sda21(r2)
/* 80029E0C 00026D6C  EC 41 18 28 */	fsubs f2, f1, f3
/* 80029E10 00026D70  EC 84 01 32 */	fmuls f4, f4, f4
/* 80029E14 00026D74  EC 21 00 B2 */	fmuls f1, f1, f2
/* 80029E18 00026D78  EC 43 20 24 */	fdivs f2, f3, f4
/* 80029E1C 00026D7C  EC A1 20 24 */	fdivs f5, f1, f4
/* 80029E20 00026D80  EC 60 20 24 */	fdivs f3, f0, f4
/* 80029E24 00026D84  48 00 00 78 */	b .L_80029E9C
.L_80029E28:
/* 80029E28 00026D88  C0 02 82 98 */	lfs f0, lbl_803E8498@sda21(r2)
/* 80029E2C 00026D8C  C0 62 82 D4 */	lfs f3, lbl_803E84D4@sda21(r2)
/* 80029E30 00026D90  EC 80 08 28 */	fsubs f4, f0, f1
/* 80029E34 00026D94  C0 42 82 D8 */	lfs f2, lbl_803E84D8@sda21(r2)
/* 80029E38 00026D98  EC 00 08 2A */	fadds f0, f0, f1
/* 80029E3C 00026D9C  EC 23 00 72 */	fmuls f1, f3, f1
/* 80029E40 00026DA0  EC 84 01 32 */	fmuls f4, f4, f4
/* 80029E44 00026DA4  EC 02 00 32 */	fmuls f0, f2, f0
/* 80029E48 00026DA8  EC A1 20 24 */	fdivs f5, f1, f4
/* 80029E4C 00026DAC  EC 40 20 24 */	fdivs f2, f0, f4
/* 80029E50 00026DB0  EC 63 20 24 */	fdivs f3, f3, f4
/* 80029E54 00026DB4  48 00 00 48 */	b .L_80029E9C
.L_80029E58:
/* 80029E58 00026DB8  C0 82 82 98 */	lfs f4, lbl_803E8498@sda21(r2)
/* 80029E5C 00026DBC  C0 02 82 CC */	lfs f0, lbl_803E84CC@sda21(r2)
/* 80029E60 00026DC0  EC A4 08 28 */	fsubs f5, f4, f1
/* 80029E64 00026DC4  C0 42 82 D8 */	lfs f2, lbl_803E84D8@sda21(r2)
/* 80029E68 00026DC8  EC 60 00 72 */	fmuls f3, f0, f1
/* 80029E6C 00026DCC  C0 02 82 DC */	lfs f0, lbl_803E84DC@sda21(r2)
/* 80029E70 00026DD0  EC 42 00 72 */	fmuls f2, f2, f1
/* 80029E74 00026DD4  EC A5 01 72 */	fmuls f5, f5, f5
/* 80029E78 00026DD8  EC 23 00 72 */	fmuls f1, f3, f1
/* 80029E7C 00026DDC  EC 42 28 24 */	fdivs f2, f2, f5
/* 80029E80 00026DE0  EC 21 28 24 */	fdivs f1, f1, f5
/* 80029E84 00026DE4  EC 60 28 24 */	fdivs f3, f0, f5
/* 80029E88 00026DE8  EC A4 08 28 */	fsubs f5, f4, f1
/* 80029E8C 00026DEC  48 00 00 10 */	b .L_80029E9C
.L_80029E90:
/* 80029E90 00026DF0  C0 42 82 90 */	lfs f2, lbl_803E8490@sda21(r2)
/* 80029E94 00026DF4  C0 A2 82 98 */	lfs f5, lbl_803E8498@sda21(r2)
/* 80029E98 00026DF8  FC 60 10 90 */	fmr f3, f2
.L_80029E9C:
/* 80029E9C 00026DFC  D0 BE 00 38 */	stfs f5, 0x38(r30)
/* 80029EA0 00026E00  38 00 00 01 */	li r0, 1
/* 80029EA4 00026E04  D0 5E 00 3C */	stfs f2, 0x3c(r30)
/* 80029EA8 00026E08  D0 7E 00 40 */	stfs f3, 0x40(r30)
/* 80029EAC 00026E0C  90 1E 00 70 */	stw r0, 0x70(r30)
/* 80029EB0 00026E10  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80029EB4 00026E14  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80029EB8 00026E18  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80029EBC 00026E1C  38 21 00 20 */	addi r1, r1, 0x20
/* 80029EC0 00026E20  7C 08 03 A6 */	mtlr r0
/* 80029EC4 00026E24  4E 80 00 20 */	blr 
.endfn setLightSpot__5LightFfi

.fn update__5LightFv, global
/* 80029EC8 00026E28  7C 08 02 A6 */	mflr r0
/* 80029ECC 00026E2C  90 01 00 04 */	stw r0, 4(r1)
/* 80029ED0 00026E30  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80029ED4 00026E34  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80029ED8 00026E38  7C 7F 1B 78 */	mr r31, r3
/* 80029EDC 00026E3C  80 03 00 14 */	lwz r0, 0x14(r3)
/* 80029EE0 00026E40  54 00 06 3E */	clrlwi r0, r0, 0x18
/* 80029EE4 00026E44  2C 00 00 02 */	cmpwi r0, 2
/* 80029EE8 00026E48  41 82 00 4C */	beq .L_80029F34
/* 80029EEC 00026E4C  40 80 00 10 */	bge .L_80029EFC
/* 80029EF0 00026E50  2C 00 00 01 */	cmpwi r0, 1
/* 80029EF4 00026E54  40 80 00 14 */	bge .L_80029F08
/* 80029EF8 00026E58  48 00 00 8C */	b .L_80029F84
.L_80029EFC:
/* 80029EFC 00026E5C  2C 00 00 04 */	cmpwi r0, 4
/* 80029F00 00026E60  40 80 00 84 */	bge .L_80029F84
/* 80029F04 00026E64  48 00 00 5C */	b .L_80029F60
.L_80029F08:
/* 80029F08 00026E68  C0 22 82 98 */	lfs f1, lbl_803E8498@sda21(r2)
/* 80029F0C 00026E6C  38 00 00 01 */	li r0, 1
/* 80029F10 00026E70  D0 3F 00 2C */	stfs f1, 0x2c(r31)
/* 80029F14 00026E74  C0 02 82 90 */	lfs f0, lbl_803E8490@sda21(r2)
/* 80029F18 00026E78  D0 1F 00 34 */	stfs f0, 0x34(r31)
/* 80029F1C 00026E7C  D0 1F 00 30 */	stfs f0, 0x30(r31)
/* 80029F20 00026E80  D0 3F 00 38 */	stfs f1, 0x38(r31)
/* 80029F24 00026E84  D0 1F 00 40 */	stfs f0, 0x40(r31)
/* 80029F28 00026E88  D0 1F 00 3C */	stfs f0, 0x3c(r31)
/* 80029F2C 00026E8C  90 1F 00 70 */	stw r0, 0x70(r31)
/* 80029F30 00026E90  48 00 00 54 */	b .L_80029F84
.L_80029F34:
/* 80029F34 00026E94  C0 3F 00 18 */	lfs f1, 0x18(r31)
/* 80029F38 00026E98  7F E3 FB 78 */	mr r3, r31
/* 80029F3C 00026E9C  C0 5F 00 1C */	lfs f2, 0x1c(r31)
/* 80029F40 00026EA0  80 9F 00 24 */	lwz r4, 0x24(r31)
/* 80029F44 00026EA4  4B FF FD 19 */	bl setLightDistAttn__5LightFffi
/* 80029F48 00026EA8  C0 02 82 98 */	lfs f0, lbl_803E8498@sda21(r2)
/* 80029F4C 00026EAC  D0 1F 00 38 */	stfs f0, 0x38(r31)
/* 80029F50 00026EB0  C0 02 82 90 */	lfs f0, lbl_803E8490@sda21(r2)
/* 80029F54 00026EB4  D0 1F 00 40 */	stfs f0, 0x40(r31)
/* 80029F58 00026EB8  D0 1F 00 3C */	stfs f0, 0x3c(r31)
/* 80029F5C 00026EBC  48 00 00 28 */	b .L_80029F84
.L_80029F60:
/* 80029F60 00026EC0  C0 3F 00 20 */	lfs f1, 0x20(r31)
/* 80029F64 00026EC4  7F E3 FB 78 */	mr r3, r31
/* 80029F68 00026EC8  80 9F 00 28 */	lwz r4, 0x28(r31)
/* 80029F6C 00026ECC  4B FF FD D5 */	bl setLightSpot__5LightFfi
/* 80029F70 00026ED0  C0 02 82 98 */	lfs f0, lbl_803E8498@sda21(r2)
/* 80029F74 00026ED4  D0 1F 00 2C */	stfs f0, 0x2c(r31)
/* 80029F78 00026ED8  C0 02 82 90 */	lfs f0, lbl_803E8490@sda21(r2)
/* 80029F7C 00026EDC  D0 1F 00 34 */	stfs f0, 0x34(r31)
/* 80029F80 00026EE0  D0 1F 00 30 */	stfs f0, 0x30(r31)
.L_80029F84:
/* 80029F84 00026EE4  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80029F88 00026EE8  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80029F8C 00026EEC  38 21 00 18 */	addi r1, r1, 0x18
/* 80029F90 00026EF0  7C 08 03 A6 */	mtlr r0
/* 80029F94 00026EF4  4E 80 00 20 */	blr 
.endfn update__5LightFv

.section .data, "wa"  # 0x80222DC0 - 0x802E9640
.balign 8
.obj lbl_802282A0, local
	.asciz "grLight.cpp"
.endobj lbl_802282A0
.balign 4
.obj lbl_802282AC, local
	.4byte .L_80029E90
	.4byte .L_80029DB0
	.4byte .L_80029DC4
	.4byte .L_80029DE0
	.4byte .L_80029DFC
	.4byte .L_80029E28
	.4byte .L_80029E58
.endobj lbl_802282AC
.balign 4
.obj lbl_802282C8, local
	.asciz "CoreNode"
.endobj lbl_802282C8
.balign 4
.obj lbl_802282D4, local
	.4byte __RTTI__5ANode
	.4byte 0
	.4byte 0
.endobj lbl_802282D4
.obj lbl_802282E0, local
	.4byte __RTTI__5ANode
	.4byte 0
	.4byte __RTTI__8CoreNode
	.4byte 0
	.4byte 0
.endobj lbl_802282E0
.obj __vt__5Light, weak
	.4byte __RTTI__5Light
	.4byte 0
	.4byte getAgeNodeType__5ANodeFv
	.4byte read__8CoreNodeFR18RandomAccessStream
.endobj __vt__5Light
	.skip 28 #padding

.section .sdata, "wa"  # 0x803DCD20 - 0x803E7820
.balign 8
.obj lbl_803DCFE0, local
	.float 0.0
.endobj lbl_803DCFE0
.obj lbl_803DCFE4, local
	.float 0.0
.endobj lbl_803DCFE4
.obj lbl_803DCFE8, local
	.float 0.0
.endobj lbl_803DCFE8
.obj lbl_803DCFEC, local
	.float 0.0
.endobj lbl_803DCFEC
.obj lbl_803DCFF0, local
	.float 100.0
.endobj lbl_803DCFF0
.obj lbl_803DCFF4, local
	.float 0.0
.endobj lbl_803DCFF4
.obj lbl_803DCFF8, local
	.float 0.0
.endobj lbl_803DCFF8
.obj lbl_803DCFFC, local
	.float -1.0
.endobj lbl_803DCFFC
.obj lbl_803DD000, local
	.float 0.0
.endobj lbl_803DD000
.balign 4
.obj lbl_803DD004, local
	.asciz "light"
.endobj lbl_803DD004
.balign 4
.obj lbl_803DD00C, local
	.asciz "Light"
.endobj lbl_803DD00C
.balign 4
.obj lbl_803DD014, local
	.asciz "ANode"
.endobj lbl_803DD014
.balign 4
.obj __RTTI__5ANode, local
	.4byte lbl_803DD014
	.4byte 0
.endobj __RTTI__5ANode
.obj __RTTI__8CoreNode, local
	.4byte lbl_802282C8
	.4byte lbl_802282D4
.endobj __RTTI__8CoreNode
.obj __RTTI__5Light, local
	.4byte lbl_803DD00C
	.4byte lbl_802282E0
.endobj __RTTI__5Light

.section .sdata2, "a"  # 0x803E8200 - 0x803EC840
.balign 8
.obj lbl_803E8490, local
	.float 0.0
.endobj lbl_803E8490
.obj lbl_803E8494, local
	.float 60.0
.endobj lbl_803E8494
.obj lbl_803E8498, local
	.float 1.0
.endobj lbl_803E8498
.obj lbl_803E849C, local
	.float 1000.0
.endobj lbl_803E849C
.obj lbl_803E84A0, local
	.float 3005.0
.endobj lbl_803E84A0
.obj lbl_803E84A4, local
	.float 0.5036
.endobj lbl_803E84A4
.obj lbl_803E84A8, local
	.float 45.0
.endobj lbl_803E84A8
.obj lbl_803E84AC, local
	.float 0.9956
.endobj lbl_803E84AC
.obj lbl_803E84B0, local
	.float 0.15
.endobj lbl_803E84B0
.obj lbl_803E84B4, local
	.float 0.05
.endobj lbl_803E84B4
.obj lbl_803E84B8, local
	.float 0.5
.endobj lbl_803E84B8
.obj lbl_803E84BC, local
	.float 90.0
.endobj lbl_803E84BC
.obj lbl_803E84C0, local # pi
	.float 3.1415927
.endobj lbl_803E84C0
.obj lbl_803E84C4, local
	.float 180.0
.endobj lbl_803E84C4
.obj lbl_803E84C8, local
	.float -1000.0
.endobj lbl_803E84C8
.obj lbl_803E84CC, local
	.float 2.0
.endobj lbl_803E84CC
.obj lbl_803E84D0, local
	.float -1.0
.endobj lbl_803E84D0
.obj lbl_803E84D4, local
	.float -4.0
.endobj lbl_803E84D4
.obj lbl_803E84D8, local
	.float 4.0
.endobj lbl_803E84D8
.obj lbl_803E84DC, local
	.float -2.0
.endobj lbl_803E84DC
