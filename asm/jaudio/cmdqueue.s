.include "macros.inc"

.section .text, "ax"  # 0x80005560 - 0x80221F60
.global Jal_SendCmdQueue_Noblock
Jal_SendCmdQueue_Noblock:
/* 8001BA00 00018960  7C 08 02 A6 */	mflr r0
/* 8001BA04 00018964  90 01 00 04 */	stw r0, 4(r1)
/* 8001BA08 00018968  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8001BA0C 0001896C  90 61 00 08 */	stw r3, 8(r1)
/* 8001BA10 00018970  B0 81 00 0C */	sth r4, 0xc(r1)
/* 8001BA14 00018974  80 61 00 08 */	lwz r3, 8(r1)
/* 8001BA18 00018978  A0 81 00 0C */	lhz r4, 0xc(r1)
/* 8001BA1C 0001897C  4B FE C7 65 */	bl Jac_SendMessage__FP16Jac_MessageQueuePv
/* 8001BA20 00018980  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8001BA24 00018984  38 21 00 18 */	addi r1, r1, 0x18
/* 8001BA28 00018988  7C 08 03 A6 */	mtlr r0
/* 8001BA2C 0001898C  4E 80 00 20 */	blr 
/* 8001BA30 00018990  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8001BA34 00018994  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8001BA38 00018998  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8001BA3C 0001899C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */

.global Jal_SendCmdQueue_Force
Jal_SendCmdQueue_Force:
/* 8001BA40 000189A0  7C 08 02 A6 */	mflr r0
/* 8001BA44 000189A4  90 01 00 04 */	stw r0, 4(r1)
/* 8001BA48 000189A8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8001BA4C 000189AC  BF C1 00 18 */	stmw r30, 0x18(r1)
/* 8001BA50 000189B0  54 9F 04 3E */	clrlwi r31, r4, 0x10
/* 8001BA54 000189B4  3B C3 00 00 */	addi r30, r3, 0
/* 8001BA58 000189B8  38 9F 00 00 */	addi r4, r31, 0
/* 8001BA5C 000189BC  4B FE C7 25 */	bl Jac_SendMessage__FP16Jac_MessageQueuePv
/* 8001BA60 000189C0  2C 03 00 00 */	cmpwi r3, 0
/* 8001BA64 000189C4  40 82 00 1C */	bne lbl_8001BA80
/* 8001BA68 000189C8  38 7E 00 00 */	addi r3, r30, 0
/* 8001BA6C 000189CC  38 81 00 10 */	addi r4, r1, 0x10
/* 8001BA70 000189D0  4B FE C7 91 */	bl Jac_ReceiveMessage__FP16Jac_MessageQueuePPv
/* 8001BA74 000189D4  38 7E 00 00 */	addi r3, r30, 0
/* 8001BA78 000189D8  38 9F 00 00 */	addi r4, r31, 0
/* 8001BA7C 000189DC  4B FE C7 05 */	bl Jac_SendMessage__FP16Jac_MessageQueuePv
lbl_8001BA80:
/* 8001BA80 000189E0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8001BA84 000189E4  BB C1 00 18 */	lmw r30, 0x18(r1)
/* 8001BA88 000189E8  38 21 00 20 */	addi r1, r1, 0x20
/* 8001BA8C 000189EC  7C 08 03 A6 */	mtlr r0
/* 8001BA90 000189F0  4E 80 00 20 */	blr 
/* 8001BA94 000189F4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8001BA98 000189F8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8001BA9C 000189FC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */

.global Jal_FrameWork__FPv
Jal_FrameWork__FPv:
/* 8001BAA0 00018A00  7C 08 02 A6 */	mflr r0
/* 8001BAA4 00018A04  90 01 00 04 */	stw r0, 4(r1)
/* 8001BAA8 00018A08  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8001BAAC 00018A0C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8001BAB0 00018A10  83 ED 2C 50 */	lwz r31, queue_list@sda21(r13)
/* 8001BAB4 00018A14  48 00 00 48 */	b lbl_8001BAFC
lbl_8001BAB8:
/* 8001BAB8 00018A18  80 7F 00 60 */	lwz r3, 0x60(r31)
/* 8001BABC 00018A1C  38 A0 00 01 */	li r5, 1
/* 8001BAC0 00018A20  88 9F 00 64 */	lbz r4, 0x64(r31)
/* 8001BAC4 00018A24  4B FF 49 7D */	bl Jam_CheckPortAppDirect
/* 8001BAC8 00018A28  2C 03 00 01 */	cmpwi r3, 1
/* 8001BACC 00018A2C  40 82 00 2C */	bne lbl_8001BAF8
/* 8001BAD0 00018A30  38 7F 00 00 */	addi r3, r31, 0
/* 8001BAD4 00018A34  38 81 00 10 */	addi r4, r1, 0x10
/* 8001BAD8 00018A38  4B FE C7 89 */	bl Jac_ReceiveMessage_Fast__FP16Jac_MessageQueuePPv
/* 8001BADC 00018A3C  2C 03 00 01 */	cmpwi r3, 1
/* 8001BAE0 00018A40  40 82 00 18 */	bne lbl_8001BAF8
/* 8001BAE4 00018A44  80 01 00 10 */	lwz r0, 0x10(r1)
/* 8001BAE8 00018A48  80 7F 00 60 */	lwz r3, 0x60(r31)
/* 8001BAEC 00018A4C  88 9F 00 64 */	lbz r4, 0x64(r31)
/* 8001BAF0 00018A50  54 05 04 3E */	clrlwi r5, r0, 0x10
/* 8001BAF4 00018A54  4B FF 48 8D */	bl Jam_WritePortAppDirect
lbl_8001BAF8:
/* 8001BAF8 00018A58  83 FF 00 68 */	lwz r31, 0x68(r31)
lbl_8001BAFC:
/* 8001BAFC 00018A5C  28 1F 00 00 */	cmplwi r31, 0
/* 8001BB00 00018A60  40 82 FF B8 */	bne lbl_8001BAB8
/* 8001BB04 00018A64  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8001BB08 00018A68  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8001BB0C 00018A6C  38 21 00 20 */	addi r1, r1, 0x20
/* 8001BB10 00018A70  7C 08 03 A6 */	mtlr r0
/* 8001BB14 00018A74  4E 80 00 20 */	blr 
/* 8001BB18 00018A78  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8001BB1C 00018A7C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */

.global Jal_CmdQueue_Init
Jal_CmdQueue_Init:
/* 8001BB20 00018A80  7C 08 02 A6 */	mflr r0
/* 8001BB24 00018A84  3C 60 80 02 */	lis r3, Jal_FrameWork__FPv@ha
/* 8001BB28 00018A88  90 01 00 04 */	stw r0, 4(r1)
/* 8001BB2C 00018A8C  38 80 00 00 */	li r4, 0
/* 8001BB30 00018A90  38 63 BA A0 */	addi r3, r3, Jal_FrameWork__FPv@l
/* 8001BB34 00018A94  94 21 FF F8 */	stwu r1, -8(r1)
/* 8001BB38 00018A98  4B FE B6 E9 */	bl Jac_RegisterPlayerCallback
/* 8001BB3C 00018A9C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8001BB40 00018AA0  38 21 00 08 */	addi r1, r1, 8
/* 8001BB44 00018AA4  7C 08 03 A6 */	mtlr r0
/* 8001BB48 00018AA8  4E 80 00 20 */	blr 
/* 8001BB4C 00018AAC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8001BB50 00018AB0  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8001BB54 00018AB4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8001BB58 00018AB8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8001BB5C 00018ABC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */

.global V3D_GetAngle__FP9Vector3D_
V3D_GetAngle__FP9Vector3D_:
/* 8001BB60 00018AC0  7C 08 02 A6 */	mflr r0
/* 8001BB64 00018AC4  90 01 00 04 */	stw r0, 4(r1)
/* 8001BB68 00018AC8  94 21 FF F8 */	stwu r1, -8(r1)
/* 8001BB6C 00018ACC  C0 23 00 00 */	lfs f1, 0(r3)
/* 8001BB70 00018AD0  C0 43 00 04 */	lfs f2, 4(r3)
/* 8001BB74 00018AD4  4B FF 21 4D */	bl atanf2__Fff
/* 8001BB78 00018AD8  C8 02 82 00 */	lfd f0, "@79"@sda21(r2)
/* 8001BB7C 00018ADC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8001BB80 00018AE0  FC 20 08 2A */	fadd f1, f0, f1
/* 8001BB84 00018AE4  FC 20 08 18 */	frsp f1, f1
/* 8001BB88 00018AE8  38 21 00 08 */	addi r1, r1, 8
/* 8001BB8C 00018AEC  7C 08 03 A6 */	mtlr r0
/* 8001BB90 00018AF0  4E 80 00 20 */	blr 
/* 8001BB94 00018AF4  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8001BB98 00018AF8  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8001BB9C 00018AFC  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */

.global V3D_Abs__FP9Vector3D_
V3D_Abs__FP9Vector3D_:
/* 8001BBA0 00018B00  7C 08 02 A6 */	mflr r0
/* 8001BBA4 00018B04  90 01 00 04 */	stw r0, 4(r1)
/* 8001BBA8 00018B08  94 21 FF F8 */	stwu r1, -8(r1)
/* 8001BBAC 00018B0C  C0 23 00 00 */	lfs f1, 0(r3)
/* 8001BBB0 00018B10  C0 03 00 04 */	lfs f0, 4(r3)
/* 8001BBB4 00018B14  EC 21 00 72 */	fmuls f1, f1, f1
/* 8001BBB8 00018B18  C0 43 00 08 */	lfs f2, 8(r3)
/* 8001BBBC 00018B1C  EC 00 00 32 */	fmuls f0, f0, f0
/* 8001BBC0 00018B20  EC 42 00 B2 */	fmuls f2, f2, f2
/* 8001BBC4 00018B24  EC 01 00 2A */	fadds f0, f1, f0
/* 8001BBC8 00018B28  EC 22 00 2A */	fadds f1, f2, f0
/* 8001BBCC 00018B2C  4B FF 20 55 */	bl sqrtf2__Ff
/* 8001BBD0 00018B30  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8001BBD4 00018B34  38 21 00 08 */	addi r1, r1, 8
/* 8001BBD8 00018B38  7C 08 03 A6 */	mtlr r0
/* 8001BBDC 00018B3C  4E 80 00 20 */	blr 

.global Stop_DirectPCM__FP6dspch_
Stop_DirectPCM__FP6dspch_:
/* 8001BBE0 00018B40  7C 08 02 A6 */	mflr r0
/* 8001BBE4 00018B44  90 01 00 04 */	stw r0, 4(r1)
/* 8001BBE8 00018B48  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8001BBEC 00018B4C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8001BBF0 00018B50  7C 7F 1B 78 */	mr r31, r3
/* 8001BBF4 00018B54  88 63 00 00 */	lbz r3, 0(r3)
/* 8001BBF8 00018B58  4B FE FC 29 */	bl DSP_PlayStop__FUc
/* 8001BBFC 00018B5C  88 7F 00 00 */	lbz r3, 0(r31)

.section .text, "ax"  # 0x80005560 - 0x80221F60
/* 8005A594 000574F4  2C 00 00 00 */	cmpwi r0, 0
/* 8005A598 000574F8  40 82 00 08 */	bne lbl_8005A5A0
/* 8005A59C 000574FC  7F 59 D3 78 */	mr r25, r26
lbl_8005A5A0:
/* 8005A5A0 00057500  57 20 06 3F */	clrlwi. r0, r25, 0x18
/* 8005A5A4 00057504  41 82 00 14 */	beq lbl_8005A5B8
/* 8005A5A8 00057508  3C 60 80 3A */	lis r3, gameflow@ha
/* 8005A5AC 0005750C  38 63 D7 B8 */	addi r3, r3, gameflow@l
/* 8005A5B0 00057510  C0 23 02 F0 */	lfs f1, 0x2f0(r3)
/* 8005A5B4 00057514  48 00 00 08 */	b lbl_8005A5BC
lbl_8005A5B8:
/* 8005A5B8 00057518  C0 22 85 A8 */	lfs f1, lbl_803E87A8@sda21(r2)
lbl_8005A5BC:
/* 8005A5BC 0005751C  80 6D 2F 00 */	lwz r3, mapMgr@sda21(r13)
/* 8005A5C0 00057520  7F E4 FB 78 */	mr r4, r31
/* 8005A5C4 00057524  38 A0 00 08 */	li r5, 8
/* 8005A5C8 00057528  80 63 00 04 */	lwz r3, 4(r3)
/* 8005A5CC 0005752C  48 01 3F 91 */	bl refresh__6DayMgrFR8Graphicsfi
/* 8005A5D0 00057530  C0 02 85 CC */	lfs f0, lbl_803E87CC@sda21(r2)
/* 8005A5D4 00057534  38 7E 00 00 */	addi r3, r30, 0
/* 8005A5D8 00057538  38 9F 00 00 */	addi r4, r31, 0
/* 8005A5DC 0005753C  D0 1E 03 A4 */	stfs f0, 0x3a4(r30)
/* 8005A5E0 00057540  4B FE 61 F1 */	bl draw__4NodeFR8Graphics
/* 8005A5E4 00057544  48 00 00 68 */	b lbl_8005A64C
lbl_8005A5E8:
/* 8005A5E8 00057548  80 6D 2F 00 */	lwz r3, mapMgr@sda21(r13)
/* 8005A5EC 0005754C  7F E4 FB 78 */	mr r4, r31
/* 8005A5F0 00057550  C0 22 85 D0 */	lfs f1, lbl_803E87D0@sda21(r2)
/* 8005A5F4 00057554  38 A0 00 08 */	li r5, 8
/* 8005A5F8 00057558  80 63 00 04 */	lwz r3, 4(r3)
/* 8005A5FC 0005755C  48 01 3F 61 */	bl refresh__6DayMgrFR8Graphicsfi
/* 8005A600 00057560  80 7D 00 00 */	lwz r3, 0(r29)
/* 8005A604 00057564  7F E4 FB 78 */	mr r4, r31
/* 8005A608 00057568  48 01 D8 15 */	bl addLights__11MoviePlayerFR8Graphics
/* 8005A60C 0005756C  7F E3 FB 78 */	mr r3, r31
/* 8005A610 00057570  C0 22 85 80 */	lfs f1, lbl_803E8780@sda21(r2)
/* 8005A614 00057574  4B FC F1 C9 */	bl calcLighting__8GraphicsFf
/* 8005A618 00057578  80 7D 00 00 */	lwz r3, 0(r29)
/* 8005A61C 0005757C  7F E4 FB 78 */	mr r4, r31
/* 8005A620 00057580  48 01 D8 5D */	bl refresh__11MoviePlayerFR8Graphics
/* 8005A624 00057584  81 9F 03 B4 */	lwz r12, 0x3b4(r31)
/* 8005A628 00057588  3C 80 80 3A */	lis r4, ident__8Matrix4f@ha
/* 8005A62C 0005758C  7F E3 FB 78 */	mr r3, r31
/* 8005A630 00057590  81 8C 00 74 */	lwz r12, 0x74(r12)
/* 8005A634 00057594  38 84 88 40 */	addi r4, r4, ident__8Matrix4f@l
/* 8005A638 00057598  38 A0 00 00 */	li r5, 0
/* 8005A63C 0005759C  7D 88 03 A6 */	mtlr r12
/* 8005A640 000575A0  4E 80 00 21 */	blrl 
/* 8005A644 000575A4  7F E3 FB 78 */	mr r3, r31
/* 8005A648 000575A8  4B FC E0 85 */	bl flushCachedShapes__8GraphicsFv
lbl_8005A64C:
/* 8005A64C 000575AC  80 6D 31 80 */	lwz r3, effectMgr@sda21(r13)
/* 8005A650 000575B0  28 03 00 00 */	cmplwi r3, 0
/* 8005A654 000575B4  41 82 00 68 */	beq lbl_8005A6BC
/* 8005A658 000575B8  3C 80 80 3A */	lis r4, gameflow@ha
/* 8005A65C 000575BC  38 84 D7 B8 */	addi r4, r4, gameflow@l
/* 8005A660 000575C0  80 04 03 3C */	lwz r0, 0x33c(r4)
/* 8005A664 000575C4  2C 00 00 00 */	cmpwi r0, 0
/* 8005A668 000575C8  40 82 00 10 */	bne lbl_8005A678
/* 8005A66C 000575CC  80 1B 00 00 */	lwz r0, 0(r27)
/* 8005A670 000575D0  2C 00 00 00 */	cmpwi r0, 0
/* 8005A674 000575D4  41 82 00 18 */	beq lbl_8005A68C
lbl_8005A678:
/* 8005A678 000575D8  3C 80 80 3A */	lis r4, gameflow@ha
/* 8005A67C 000575DC  38 84 D7 B8 */	addi r4, r4, gameflow@l
/* 8005A680 000575E0  80 04 03 40 */	lwz r0, 0x340(r4)
/* 8005A684 000575E4  2C 00 00 00 */	cmpwi r0, 0
/* 8005A688 000575E8  41 82 00 28 */	beq lbl_8005A6B0
lbl_8005A68C:
/* 8005A68C 000575EC  80 8D 2D EC */	lwz r4, gsys@sda21(r13)
/* 8005A690 000575F0  38 A0 00 01 */	li r5, 1
/* 8005A694 000575F4  80 04 02 58 */	lwz r0, 0x258(r4)
/* 8005A698 000575F8  2C 00 00 00 */	cmpwi r0, 0
/* 8005A69C 000575FC  41 80 00 08 */	blt lbl_8005A6A4
/* 8005A6A0 00057600  38 A0 00 00 */	li r5, 0
lbl_8005A6A4:
/* 8005A6A4 00057604  54 A0 06 3F */	clrlwi. r0, r5, 0x18
/* 8005A6A8 00057608  41 82 00 08 */	beq lbl_8005A6B0
/* 8005A6AC 0005760C  48 14 22 8D */	bl update__9EffectMgrFv
lbl_8005A6B0:
/* 8005A6B0 00057610  80 6D 31 80 */	lwz r3, effectMgr@sda21(r13)
/* 8005A6B4 00057614  7F E4 FB 78 */	mr r4, r31
/* 8005A6B8 00057618  48 14 22 FD */	bl draw__9EffectMgrFR8Graphics
lbl_8005A6BC:
/* 8005A6BC 0005761C  80 1C 00 00 */	lwz r0, 0(r28)
/* 8005A6C0 00057620  54 00 06 31 */	rlwinm. r0, r0, 0, 0x18, 0x18
/* 8005A6C4 00057624  40 82 01 44 */	bne lbl_8005A808
/* 8005A6C8 00057628  3B 40 00 00 */	li r26, 0
/* 8005A6CC 0005762C  9B 4D 2E 80 */	stb r26, menuOn@sda21(r13)
/* 8005A6D0 00057630  38 A1 01 E4 */	addi r5, r1, 0x1e4
/* 8005A6D4 00057634  38 7F 00 00 */	addi r3, r31, 0
/* 8005A6D8 00057638  80 DF 03 10 */	lwz r6, 0x310(r31)
/* 8005A6DC 0005763C  38 81 02 34 */	addi r4, r1, 0x234
/* 8005A6E0 00057640  80 1F 03 0C */	lwz r0, 0x30c(r31)
/* 8005A6E4 00057644  93 41 01 E4 */	stw r26, 0x1e4(r1)
/* 8005A6E8 00057648  93 41 01 E8 */	stw r26, 0x1e8(r1)
/* 8005A6EC 0005764C  90 01 01 EC */	stw r0, 0x1ec(r1)
/* 8005A6F0 00057650  90 C1 01 F0 */	stw r6, 0x1f0(r1)
/* 8005A6F4 00057654  81 9F 03 B4 */	lwz r12, 0x3b4(r31)
/* 8005A6F8 00057658  81 8C 00 40 */	lwz r12, 0x40(r12)
/* 8005A6FC 0005765C  7D 88 03 A6 */	mtlr r12
/* 8005A700 00057660  4E 80 00 21 */	blrl 
/* 8005A704 00057664  7F E3 FB 78 */	mr r3, r31
/* 8005A708 00057668  80 BF 02 E4 */	lwz r5, 0x2e4(r31)
/* 8005A70C 0005766C  81 9F 03 B4 */	lwz r12, 0x3b4(r31)
/* 8005A710 00057670  C0 62 85 80 */	lfs f3, lbl_803E8780@sda21(r2)
/* 8005A714 00057674  38 85 02 60 */	addi r4, r5, 0x260
/* 8005A718 00057678  81 8C 00 3C */	lwz r12, 0x3c(r12)
/* 8005A71C 0005767C  FC A0 18 90 */	fmr f5, f3
/* 8005A720 00057680  C0 22 85 AC */	lfs f1, lbl_803E87AC@sda21(r2)
/* 8005A724 00057684  7D 88 03 A6 */	mtlr r12
/* 8005A728 00057688  C0 45 01 C4 */	lfs f2, 0x1c4(r5)
/* 8005A72C 0005768C  C0 85 01 D4 */	lfs f4, 0x1d4(r5)
/* 8005A730 00057690  4E 80 00 21 */	blrl 
/* 8005A734 00057694  C0 4D 8D D8 */	lfs f2, lbl_803DDAF8@sda21(r13)
/* 8005A738 00057698  38 C1 01 1C */	addi r6, r1, 0x11c
/* 8005A73C 0005769C  C0 2D 8D CC */	lfs f1, lbl_803DDAEC@sda21(r13)
/* 8005A740 000576A0  38 A1 01 10 */	addi r5, r1, 0x110
/* 8005A744 000576A4  C0 0D 8D C0 */	lfs f0, lbl_803DDAE0@sda21(r13)
/* 8005A748 000576A8  D0 41 01 1C */	stfs f2, 0x11c(r1)
/* 8005A74C 000576AC  38 81 01 04 */	addi r4, r1, 0x104
/* 8005A750 000576B0  C0 4D 8D DC */	lfs f2, lbl_803DDAFC@sda21(r13)
/* 8005A754 000576B4  38 61 00 84 */	addi r3, r1, 0x84
/* 8005A758 000576B8  D0 21 01 10 */	stfs f1, 0x110(r1)
/* 8005A75C 000576BC  C0 2D 8D D0 */	lfs f1, lbl_803DDAF0@sda21(r13)
/* 8005A760 000576C0  D0 01 01 04 */	stfs f0, 0x104(r1)
/* 8005A764 000576C4  C0 0D 8D C4 */	lfs f0, lbl_803DDAE4@sda21(r13)
/* 8005A768 000576C8  D0 41 01 20 */	stfs f2, 0x120(r1)
/* 8005A76C 000576CC  C0 4D 8D E0 */	lfs f2, lbl_803DDB00@sda21(r13)
/* 8005A770 000576D0  D0 21 01 14 */	stfs f1, 0x114(r1)
/* 8005A774 000576D4  C0 2D 8D D4 */	lfs f1, lbl_803DDAF4@sda21(r13)
/* 8005A778 000576D8  D0 01 01 08 */	stfs f0, 0x108(r1)
/* 8005A77C 000576DC  C0 0D 8D C8 */	lfs f0, lbl_803DDAE8@sda21(r13)
/* 8005A780 000576E0  D0 41 01 24 */	stfs f2, 0x124(r1)
/* 8005A784 000576E4  D0 21 01 18 */	stfs f1, 0x118(r1)
/* 8005A788 000576E8  D0 01 01 0C */	stfs f0, 0x10c(r1)
/* 8005A78C 000576EC  4B FE 39 69 */	bl makeSRT__8Matrix4fFR8Vector3fR8Vector3fR8Vector3f
/* 8005A790 000576F0  38 00 07 00 */	li r0, 0x700

.section .text, "ax"  # 0x80005560 - 0x80221F60
/* 801706C4 0016D624  C0 02 AC 70 */	lfs f0, lbl_803EAE70@sda21(r2)
/* 801706C8 0016D628  80 84 03 C0 */	lwz r4, 0x3c0(r4)
/* 801706CC 0016D62C  D0 04 00 20 */	stfs f0, 0x20(r4)
/* 801706D0 0016D630  4B FF D9 F9 */	bl setAttackPriority__6KingAiFv
/* 801706D4 0016D634  80 7F 00 04 */	lwz r3, 4(r31)
/* 801706D8 0016D638  4B FD EC E9 */	bl insideAndInSearch__4BossFv
/* 801706DC 0016D63C  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 801706E0 0016D640  41 82 26 20 */	beq lbl_80172D00
/* 801706E4 0016D644  80 6D 2F 6C */	lwz r3, playerState@sda21(r13)
/* 801706E8 0016D648  38 80 00 31 */	li r4, 0x31
/* 801706EC 0016D64C  38 63 00 70 */	addi r3, r3, 0x70
/* 801706F0 0016D650  4B F1 33 11 */	bl setOn__11ResultFlagsFi
/* 801706F4 0016D654  48 00 26 0C */	b lbl_80172D00
lbl_801706F8:
/* 801706F8 0016D658  80 7F 00 04 */	lwz r3, 4(r31)
/* 801706FC 0016D65C  88 03 02 BD */	lbz r0, 0x2bd(r3)
/* 80170700 0016D660  28 00 00 00 */	cmplwi r0, 0
/* 80170704 0016D664  41 82 25 FC */	beq lbl_80172D00
/* 80170708 0016D668  38 00 00 0C */	li r0, 0xc
/* 8017070C 0016D66C  90 03 02 E8 */	stw r0, 0x2e8(r3)
/* 80170710 0016D670  38 00 00 00 */	li r0, 0
/* 80170714 0016D674  80 7F 00 04 */	lwz r3, 4(r31)
/* 80170718 0016D678  98 03 02 BD */	stb r0, 0x2bd(r3)
/* 8017071C 0016D67C  80 7F 00 04 */	lwz r3, 4(r31)
/* 80170720 0016D680  90 03 02 EC */	stw r0, 0x2ec(r3)
/* 80170724 0016D684  80 7F 00 04 */	lwz r3, 4(r31)
/* 80170728 0016D688  90 03 03 18 */	stw r0, 0x318(r3)
/* 8017072C 0016D68C  80 7F 00 04 */	lwz r3, 4(r31)
/* 80170730 0016D690  80 03 02 E4 */	lwz r0, 0x2e4(r3)
/* 80170734 0016D694  2C 00 00 09 */	cmpwi r0, 9
/* 80170738 0016D698  41 80 00 0C */	blt lbl_80170744
/* 8017073C 0016D69C  2C 00 00 0C */	cmpwi r0, 0xc
/* 80170740 0016D6A0  40 81 00 30 */	ble lbl_80170770
lbl_80170744:
/* 80170744 0016D6A4  38 BF 00 00 */	addi r5, r31, 0
/* 80170748 0016D6A8  38 61 0A 40 */	addi r3, r1, 0xa40
/* 8017074C 0016D6AC  38 80 00 06 */	li r4, 6
/* 80170750 0016D6B0  4B FA E8 3D */	bl __ct__14PaniMotionInfoFiP19PaniAnimKeyListener
/* 80170754 0016D6B4  80 BF 00 04 */	lwz r5, 4(r31)
/* 80170758 0016D6B8  38 83 00 00 */	addi r4, r3, 0
/* 8017075C 0016D6BC  38 65 03 3C */	addi r3, r5, 0x33c
/* 80170760 0016D6C0  4B FA EA 61 */	bl startMotion__12PaniAnimatorFR14PaniMotionInfo
/* 80170764 0016D6C4  C0 02 AC 74 */	lfs f0, lbl_803EAE74@sda21(r2)
/* 80170768 0016D6C8  80 7F 00 04 */	lwz r3, 4(r31)
/* 8017076C 0016D6CC  D0 03 02 D8 */	stfs f0, 0x2d8(r3)
lbl_80170770:
/* 80170770 0016D6D0  80 7F 00 04 */	lwz r3, 4(r31)
/* 80170774 0016D6D4  80 83 02 24 */	lwz r4, 0x224(r3)
/* 80170778 0016D6D8  80 63 03 C0 */	lwz r3, 0x3c0(r3)
/* 8017077C 0016D6DC  C0 04 02 10 */	lfs f0, 0x210(r4)
/* 80170780 0016D6E0  D0 03 00 20 */	stfs f0, 0x20(r3)
/* 80170784 0016D6E4  80 7F 00 04 */	lwz r3, 4(r31)
/* 80170788 0016D6E8  4B FD EC 39 */	bl insideAndInSearch__4BossFv
/* 8017078C 0016D6EC  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 80170790 0016D6F0  41 82 25 70 */	beq lbl_80172D00
/* 80170794 0016D6F4  80 6D 2F 6C */	lwz r3, playerState@sda21(r13)
/* 80170798 0016D6F8  38 80 00 31 */	li r4, 0x31
/* 8017079C 0016D6FC  38 63 00 70 */	addi r3, r3, 0x70
/* 801707A0 0016D700  4B F1 32 61 */	bl setOn__11ResultFlagsFi
/* 801707A4 0016D704  48 00 25 5C */	b lbl_80172D00
.global lbl_801707A8
lbl_801707A8:
/* 801707A8 0016D708  80 05 03 18 */	lwz r0, 0x318(r5)
/* 801707AC 0016D70C  28 00 00 00 */	cmplwi r0, 0
/* 801707B0 0016D710  40 82 00 14 */	bne lbl_801707C4
/* 801707B4 0016D714  7F E3 FB 78 */	mr r3, r31
/* 801707B8 0016D718  4B FF DF 09 */	bl chasePikiTransit__6KingAiFv
/* 801707BC 0016D71C  7F E3 FB 78 */	mr r3, r31
/* 801707C0 0016D720  4B FF DC 01 */	bl chaseNaviTransit__6KingAiFv
lbl_801707C4:
/* 801707C4 0016D724  80 7F 00 04 */	lwz r3, 4(r31)
/* 801707C8 0016D728  4B FD DD D1 */	bl makeTargetCreature__4BossFv
/* 801707CC 0016D72C  80 7F 00 04 */	lwz r3, 4(r31)
/* 801707D0 0016D730  80 83 02 24 */	lwz r4, 0x224(r3)
/* 801707D4 0016D734  C0 24 02 30 */	lfs f1, 0x230(r4)
/* 801707D8 0016D738  4B FD DB D9 */	bl changeDirection__4BossFf
/* 801707DC 0016D73C  7F E3 FB 78 */	mr r3, r31
/* 801707E0 0016D740  4B FF DB 15 */	bl inTurnAngleTransit__6KingAiFv
/* 801707E4 0016D744  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 801707E8 0016D748  40 82 00 24 */	bne lbl_8017080C
/* 801707EC 0016D74C  38 BF 00 00 */	addi r5, r31, 0
/* 801707F0 0016D750  38 61 0A 38 */	addi r3, r1, 0xa38
/* 801707F4 0016D754  38 80 FF FF */	li r4, -1
/* 801707F8 0016D758  4B FA E7 95 */	bl __ct__14PaniMotionInfoFiP19PaniAnimKeyListener
/* 801707FC 0016D75C  80 BF 00 04 */	lwz r5, 4(r31)
/* 80170800 0016D760  38 83 00 00 */	addi r4, r3, 0
/* 80170804 0016D764  38 65 03 3C */	addi r3, r5, 0x33c
/* 80170808 0016D768  4B FA EA 29 */	bl finishMotion__12PaniAnimatorFR14PaniMotionInfo
lbl_8017080C:
/* 8017080C 0016D76C  80 7F 00 04 */	lwz r3, 4(r31)
/* 80170810 0016D770  C0 02 AC 70 */	lfs f0, lbl_803EAE70@sda21(r2)
/* 80170814 0016D774  C0 23 02 C4 */	lfs f1, 0x2c4(r3)
/* 80170818 0016D778  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8017081C 0016D77C  7C 00 00 26 */	mfcr r0
/* 80170820 0016D780  54 00 17 FF */	rlwinm. r0, r0, 2, 0x1f, 0x1f
/* 80170824 0016D784  40 82 00 14 */	bne lbl_80170838
/* 80170828 0016D788  38 7F 00 00 */	addi r3, r31, 0
/* 8017082C 0016D78C  38 80 00 00 */	li r4, 0
/* 80170830 0016D790  4B FF F2 19 */	bl initDie__6KingAiFi
/* 80170834 0016D794  48 00 24 CC */	b lbl_80172D00
lbl_80170838:
/* 80170838 0016D798  4B FD E7 5D */	bl flickPikiTransit__4BossFv
/* 8017083C 0016D79C  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 80170840 0016D7A0  41 82 00 98 */	beq lbl_801708D8
/* 80170844 0016D7A4  80 7F 00 04 */	lwz r3, 4(r31)
/* 80170848 0016D7A8  38 80 00 0D */	li r4, 0xd
/* 8017084C 0016D7AC  38 00 00 00 */	li r0, 0
/* 80170850 0016D7B0  90 83 02 E8 */	stw r4, 0x2e8(r3)
/* 80170854 0016D7B4  38 BF 00 00 */	addi r5, r31, 0
/* 80170858 0016D7B8  38 61 0A 30 */	addi r3, r1, 0xa30
/* 8017085C 0016D7BC  80 DF 00 04 */	lwz r6, 4(r31)
/* 80170860 0016D7C0  38 80 00 09 */	li r4, 9
/* 80170864 0016D7C4  98 06 02 BD */	stb r0, 0x2bd(r6)
/* 80170868 0016D7C8  80 DF 00 04 */	lwz r6, 4(r31)
/* 8017086C 0016D7CC  90 06 02 EC */	stw r0, 0x2ec(r6)
/* 80170870 0016D7D0  80 DF 00 04 */	lwz r6, 4(r31)
/* 80170874 0016D7D4  90 06 03 18 */	stw r0, 0x318(r6)
/* 80170878 0016D7D8  4B FA E7 15 */	bl __ct__14PaniMotionInfoFiP19PaniAnimKeyListener
/* 8017087C 0016D7DC  80 BF 00 04 */	lwz r5, 4(r31)
/* 80170880 0016D7E0  38 83 00 00 */	addi r4, r3, 0
/* 80170884 0016D7E4  38 65 03 3C */	addi r3, r5, 0x33c
/* 80170888 0016D7E8  4B FA E9 39 */	bl startMotion__12PaniAnimatorFR14PaniMotionInfo
/* 8017088C 0016D7EC  80 7F 00 04 */	lwz r3, 4(r31)
/* 80170890 0016D7F0  C0 22 AC BC */	lfs f1, lbl_803EAEBC@sda21(r2)
/* 80170894 0016D7F4  80 63 03 C0 */	lwz r3, 0x3c0(r3)
/* 80170898 0016D7F8  48 00 32 01 */	bl initBlending__8KingBodyFf
/* 8017089C 0016D7FC  80 9F 00 04 */	lwz r4, 4(r31)
/* 801708A0 0016D800  7F E3 FB 78 */	mr r3, r31
/* 801708A4 0016D804  C0 02 AC 70 */	lfs f0, lbl_803EAE70@sda21(r2)
/* 801708A8 0016D808  80 84 03 C0 */	lwz r4, 0x3c0(r4)
/* 801708AC 0016D80C  D0 04 00 20 */	stfs f0, 0x20(r4)
/* 801708B0 0016D810  4B FF D8 19 */	bl setAttackPriority__6KingAiFv
/* 801708B4 0016D814  80 7F 00 04 */	lwz r3, 4(r31)
/* 801708B8 0016D818  4B FD EB 09 */	bl insideAndInSearch__4BossFv
/* 801708BC 0016D81C  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 801708C0 0016D820  41 82 24 40 */	beq lbl_80172D00
