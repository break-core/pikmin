.include "macros.inc"
.section .text, "ax"  # 0x80005560 - 0x80221F60
.fn set__7PUTRectFiiii, global
/* 801B3628 001B0588  7C 80 07 34 */	extsh r0, r4
/* 801B362C 001B058C  B0 03 00 00 */	sth r0, 0(r3)
/* 801B3630 001B0590  7C A0 07 34 */	extsh r0, r5
/* 801B3634 001B0594  7C C4 07 34 */	extsh r4, r6
/* 801B3638 001B0598  B0 03 00 02 */	sth r0, 2(r3)
/* 801B363C 001B059C  7C E0 07 34 */	extsh r0, r7
/* 801B3640 001B05A0  B0 83 00 04 */	sth r4, 4(r3)
/* 801B3644 001B05A4  B0 03 00 06 */	sth r0, 6(r3)
/* 801B3648 001B05A8  4E 80 00 20 */	blr 
.endfn set__7PUTRectFiiii

.fn copy__7PUTRectFRC7PUTRect, global
/* 801B364C 001B05AC  A8 04 00 00 */	lha r0, 0(r4)
/* 801B3650 001B05B0  B0 03 00 00 */	sth r0, 0(r3)
/* 801B3654 001B05B4  A8 04 00 02 */	lha r0, 2(r4)
/* 801B3658 001B05B8  B0 03 00 02 */	sth r0, 2(r3)
/* 801B365C 001B05BC  A8 04 00 04 */	lha r0, 4(r4)
/* 801B3660 001B05C0  B0 03 00 04 */	sth r0, 4(r3)
/* 801B3664 001B05C4  A8 04 00 06 */	lha r0, 6(r4)
/* 801B3668 001B05C8  B0 03 00 06 */	sth r0, 6(r3)
/* 801B366C 001B05CC  4E 80 00 20 */	blr 
.endfn copy__7PUTRectFRC7PUTRect

.fn add__7PUTRectFii, global
/* 801B3670 001B05D0  A8 03 00 00 */	lha r0, 0(r3)
/* 801B3674 001B05D4  7C 00 22 14 */	add r0, r0, r4
/* 801B3678 001B05D8  B0 03 00 00 */	sth r0, 0(r3)
/* 801B367C 001B05DC  A8 03 00 04 */	lha r0, 4(r3)
/* 801B3680 001B05E0  7C 00 22 14 */	add r0, r0, r4
/* 801B3684 001B05E4  B0 03 00 04 */	sth r0, 4(r3)
/* 801B3688 001B05E8  A8 03 00 02 */	lha r0, 2(r3)
/* 801B368C 001B05EC  7C 00 2A 14 */	add r0, r0, r5
/* 801B3690 001B05F0  B0 03 00 02 */	sth r0, 2(r3)
/* 801B3694 001B05F4  A8 03 00 06 */	lha r0, 6(r3)
/* 801B3698 001B05F8  7C 00 2A 14 */	add r0, r0, r5
/* 801B369C 001B05FC  B0 03 00 06 */	sth r0, 6(r3)
/* 801B36A0 001B0600  4E 80 00 20 */	blr 
.endfn add__7PUTRectFii

.fn intersect__7PUTRectFRC7PUTRect, global
/* 801B36A4 001B0604  7C 08 02 A6 */	mflr r0
/* 801B36A8 001B0608  90 01 00 04 */	stw r0, 4(r1)
/* 801B36AC 001B060C  94 21 FF F8 */	stwu r1, -8(r1)
/* 801B36B0 001B0610  A8 A4 00 00 */	lha r5, 0(r4)
/* 801B36B4 001B0614  A8 03 00 00 */	lha r0, 0(r3)
/* 801B36B8 001B0618  7C 00 28 00 */	cmpw r0, r5
/* 801B36BC 001B061C  40 80 00 08 */	bge .L_801B36C4
/* 801B36C0 001B0620  B0 A3 00 00 */	sth r5, 0(r3)
.L_801B36C4:
/* 801B36C4 001B0624  A8 03 00 02 */	lha r0, 2(r3)
/* 801B36C8 001B0628  A8 A4 00 02 */	lha r5, 2(r4)
/* 801B36CC 001B062C  7C 00 28 00 */	cmpw r0, r5
/* 801B36D0 001B0630  40 80 00 08 */	bge .L_801B36D8
/* 801B36D4 001B0634  B0 A3 00 02 */	sth r5, 2(r3)
.L_801B36D8:
/* 801B36D8 001B0638  A8 03 00 04 */	lha r0, 4(r3)
/* 801B36DC 001B063C  A8 A4 00 04 */	lha r5, 4(r4)
/* 801B36E0 001B0640  7C 00 28 00 */	cmpw r0, r5
/* 801B36E4 001B0644  40 81 00 08 */	ble .L_801B36EC
/* 801B36E8 001B0648  B0 A3 00 04 */	sth r5, 4(r3)
.L_801B36EC:
/* 801B36EC 001B064C  A8 03 00 06 */	lha r0, 6(r3)
/* 801B36F0 001B0650  A8 84 00 06 */	lha r4, 6(r4)
/* 801B36F4 001B0654  7C 00 20 00 */	cmpw r0, r4
/* 801B36F8 001B0658  40 81 00 08 */	ble .L_801B3700
/* 801B36FC 001B065C  B0 83 00 06 */	sth r4, 6(r3)
.L_801B3700:
/* 801B3700 001B0660  48 00 00 C1 */	bl isEmpty__7PUTRectCFv
/* 801B3704 001B0664  54 60 06 3E */	clrlwi r0, r3, 0x18
/* 801B3708 001B0668  7C 00 00 34 */	cntlzw r0, r0
/* 801B370C 001B066C  54 00 D9 7E */	srwi r0, r0, 5
/* 801B3710 001B0670  7C 03 03 78 */	mr r3, r0
/* 801B3714 001B0674  80 01 00 0C */	lwz r0, 0xc(r1)
/* 801B3718 001B0678  38 21 00 08 */	addi r1, r1, 8
/* 801B371C 001B067C  7C 08 03 A6 */	mtlr r0
/* 801B3720 001B0680  4E 80 00 20 */	blr 
.endfn intersect__7PUTRectFRC7PUTRect

.fn move__7PUTRectFii, global
/* 801B3724 001B0684  A9 03 00 00 */	lha r8, 0(r3)
/* 801B3728 001B0688  7C 84 07 34 */	extsh r4, r4
/* 801B372C 001B068C  A8 E3 00 04 */	lha r7, 4(r3)
/* 801B3730 001B0690  7C A0 07 34 */	extsh r0, r5
/* 801B3734 001B0694  A8 C3 00 02 */	lha r6, 2(r3)
/* 801B3738 001B0698  A8 A3 00 06 */	lha r5, 6(r3)
/* 801B373C 001B069C  7C E8 38 50 */	subf r7, r8, r7
/* 801B3740 001B06A0  B0 83 00 00 */	sth r4, 0(r3)
/* 801B3744 001B06A4  7C 86 28 50 */	subf r4, r6, r5
/* 801B3748 001B06A8  B0 03 00 02 */	sth r0, 2(r3)
/* 801B374C 001B06AC  A8 03 00 00 */	lha r0, 0(r3)
/* 801B3750 001B06B0  7C 00 3A 14 */	add r0, r0, r7
/* 801B3754 001B06B4  B0 03 00 04 */	sth r0, 4(r3)
/* 801B3758 001B06B8  A8 03 00 02 */	lha r0, 2(r3)
/* 801B375C 001B06BC  7C 00 22 14 */	add r0, r0, r4
/* 801B3760 001B06C0  B0 03 00 06 */	sth r0, 6(r3)
/* 801B3764 001B06C4  4E 80 00 20 */	blr 
.endfn move__7PUTRectFii

.fn resize__7PUTRectFii, global
/* 801B3768 001B06C8  A8 03 00 00 */	lha r0, 0(r3)
/* 801B376C 001B06CC  7C 00 22 14 */	add r0, r0, r4
/* 801B3770 001B06D0  B0 03 00 04 */	sth r0, 4(r3)
/* 801B3774 001B06D4  A8 03 00 02 */	lha r0, 2(r3)
/* 801B3778 001B06D8  7C 00 2A 14 */	add r0, r0, r5
/* 801B377C 001B06DC  B0 03 00 06 */	sth r0, 6(r3)
/* 801B3780 001B06E0  4E 80 00 20 */	blr 
.endfn resize__7PUTRectFii

.fn normalize__7PUTRectFv, global
/* 801B3784 001B06E4  A8 83 00 00 */	lha r4, 0(r3)
/* 801B3788 001B06E8  A8 03 00 04 */	lha r0, 4(r3)
/* 801B378C 001B06EC  7C 04 00 00 */	cmpw r4, r0
/* 801B3790 001B06F0  40 81 00 10 */	ble .L_801B37A0
/* 801B3794 001B06F4  B0 83 00 04 */	sth r4, 4(r3)
/* 801B3798 001B06F8  7C 00 07 34 */	extsh r0, r0
/* 801B379C 001B06FC  B0 03 00 00 */	sth r0, 0(r3)
.L_801B37A0:
/* 801B37A0 001B0700  A8 83 00 02 */	lha r4, 2(r3)
/* 801B37A4 001B0704  A8 03 00 06 */	lha r0, 6(r3)
/* 801B37A8 001B0708  7C 04 00 00 */	cmpw r4, r0
/* 801B37AC 001B070C  4C 81 00 20 */	blelr 
/* 801B37B0 001B0710  B0 83 00 06 */	sth r4, 6(r3)
/* 801B37B4 001B0714  7C 00 07 34 */	extsh r0, r0
/* 801B37B8 001B0718  B0 03 00 02 */	sth r0, 2(r3)
/* 801B37BC 001B071C  4E 80 00 20 */	blr 
.endfn normalize__7PUTRectFv

.fn isEmpty__7PUTRectCFv, global
/* 801B37C0 001B0720  A8 83 00 00 */	lha r4, 0(r3)
/* 801B37C4 001B0724  38 A0 00 01 */	li r5, 1
/* 801B37C8 001B0728  A8 03 00 04 */	lha r0, 4(r3)
/* 801B37CC 001B072C  7C 04 00 00 */	cmpw r4, r0
/* 801B37D0 001B0730  40 80 00 18 */	bge .L_801B37E8
/* 801B37D4 001B0734  A8 83 00 02 */	lha r4, 2(r3)
/* 801B37D8 001B0738  A8 03 00 06 */	lha r0, 6(r3)
/* 801B37DC 001B073C  7C 04 00 00 */	cmpw r4, r0
/* 801B37E0 001B0740  40 80 00 08 */	bge .L_801B37E8
/* 801B37E4 001B0744  38 A0 00 00 */	li r5, 0
.L_801B37E8:
/* 801B37E8 001B0748  7C A3 2B 78 */	mr r3, r5
/* 801B37EC 001B074C  4E 80 00 20 */	blr 
.endfn isEmpty__7PUTRectCFv
