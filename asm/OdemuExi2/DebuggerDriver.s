.include "macros.inc"
.section .text, "ax"  # 0x80005560 - 0x80221F60
.global DBGEXIImm
DBGEXIImm:
/* 802214D8 0021E438  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 802214DC 0021E43C  28 05 00 00 */	cmplwi r5, 0
/* 802214E0 0021E440  BE C1 00 20 */	stmw r22, 0x20(r1)
/* 802214E4 0021E444  41 82 01 38 */	beq lbl_8022161C
/* 802214E8 0021E448  3B A0 00 00 */	li r29, 0
/* 802214EC 0021E44C  7C 1D 20 00 */	cmpw r29, r4
/* 802214F0 0021E450  3B C0 00 00 */	li r30, 0
/* 802214F4 0021E454  40 80 01 20 */	bge lbl_80221614
/* 802214F8 0021E458  2C 04 00 08 */	cmpwi r4, 8
/* 802214FC 0021E45C  38 C4 FF F8 */	addi r6, r4, -8
/* 80221500 0021E460  40 81 02 5C */	ble lbl_8022175C
/* 80221504 0021E464  38 06 00 07 */	addi r0, r6, 7
/* 80221508 0021E468  54 00 E8 FE */	srwi r0, r0, 3
/* 8022150C 0021E46C  2C 06 00 00 */	cmpwi r6, 0
/* 80221510 0021E470  7C 09 03 A6 */	mtctr r0
/* 80221514 0021E474  3B E3 00 00 */	addi r31, r3, 0
/* 80221518 0021E478  40 81 02 44 */	ble lbl_8022175C
lbl_8022151C:
/* 8022151C 0021E47C  20 DD 00 03 */	subfic r6, r29, 3
/* 80221520 0021E480  89 9F 00 00 */	lbz r12, 0(r31)
/* 80221524 0021E484  38 1D 00 01 */	addi r0, r29, 1
/* 80221528 0021E488  89 7F 00 01 */	lbz r11, 1(r31)
/* 8022152C 0021E48C  54 CA 18 38 */	slwi r10, r6, 3
/* 80221530 0021E490  89 3F 00 02 */	lbz r9, 2(r31)
/* 80221534 0021E494  21 00 00 03 */	subfic r8, r0, 3
/* 80221538 0021E498  88 FF 00 03 */	lbz r7, 3(r31)
/* 8022153C 0021E49C  38 DD 00 02 */	addi r6, r29, 2
/* 80221540 0021E4A0  88 1F 00 04 */	lbz r0, 4(r31)
/* 80221544 0021E4A4  7D 8C 50 30 */	slw r12, r12, r10
/* 80221548 0021E4A8  8A FF 00 05 */	lbz r23, 5(r31)
/* 8022154C 0021E4AC  55 0A 18 38 */	slwi r10, r8, 3
/* 80221550 0021E4B0  8B 3F 00 06 */	lbz r25, 6(r31)
/* 80221554 0021E4B4  20 C6 00 03 */	subfic r6, r6, 3
/* 80221558 0021E4B8  8B 7F 00 07 */	lbz r27, 7(r31)
/* 8022155C 0021E4BC  54 C8 18 38 */	slwi r8, r6, 3
/* 80221560 0021E4C0  7C DD 00 D0 */	neg r6, r29
/* 80221564 0021E4C4  3A DD 00 04 */	addi r22, r29, 4
/* 80221568 0021E4C8  54 C6 18 38 */	slwi r6, r6, 3
/* 8022156C 0021E4CC  22 D6 00 03 */	subfic r22, r22, 3
/* 80221570 0021E4D0  3B 1D 00 05 */	addi r24, r29, 5
/* 80221574 0021E4D4  56 D6 18 38 */	slwi r22, r22, 3
/* 80221578 0021E4D8  23 18 00 03 */	subfic r24, r24, 3
/* 8022157C 0021E4DC  3B 5D 00 06 */	addi r26, r29, 6
/* 80221580 0021E4E0  57 18 18 38 */	slwi r24, r24, 3
/* 80221584 0021E4E4  23 5A 00 03 */	subfic r26, r26, 3
/* 80221588 0021E4E8  3B 9D 00 07 */	addi r28, r29, 7
/* 8022158C 0021E4EC  57 5A 18 38 */	slwi r26, r26, 3
/* 80221590 0021E4F0  23 9C 00 03 */	subfic r28, r28, 3
/* 80221594 0021E4F4  57 9C 18 38 */	slwi r28, r28, 3
/* 80221598 0021E4F8  7F DE 63 78 */	or r30, r30, r12
/* 8022159C 0021E4FC  7D 6A 50 30 */	slw r10, r11, r10
/* 802215A0 0021E500  7F DE 53 78 */	or r30, r30, r10
/* 802215A4 0021E504  7D 28 40 30 */	slw r8, r9, r8
/* 802215A8 0021E508  7F DE 43 78 */	or r30, r30, r8
/* 802215AC 0021E50C  7C E6 30 30 */	slw r6, r7, r6
/* 802215B0 0021E510  7F DE 33 78 */	or r30, r30, r6
/* 802215B4 0021E514  7C 00 B0 30 */	slw r0, r0, r22
/* 802215B8 0021E518  7F DE 03 78 */	or r30, r30, r0
/* 802215BC 0021E51C  7E E0 C0 30 */	slw r0, r23, r24
/* 802215C0 0021E520  7F DE 03 78 */	or r30, r30, r0
/* 802215C4 0021E524  7F 20 D0 30 */	slw r0, r25, r26
/* 802215C8 0021E528  7F DE 03 78 */	or r30, r30, r0
/* 802215CC 0021E52C  7F 60 E0 30 */	slw r0, r27, r28
/* 802215D0 0021E530  7F DE 03 78 */	or r30, r30, r0
/* 802215D4 0021E534  3B FF 00 08 */	addi r31, r31, 8
/* 802215D8 0021E538  3B BD 00 08 */	addi r29, r29, 8
/* 802215DC 0021E53C  42 00 FF 40 */	bdnz lbl_8022151C
/* 802215E0 0021E540  48 00 01 7C */	b lbl_8022175C
lbl_802215E4:
/* 802215E4 0021E544  7C 1D 20 50 */	subf r0, r29, r4
/* 802215E8 0021E548  7C 1D 20 00 */	cmpw r29, r4
/* 802215EC 0021E54C  7C 09 03 A6 */	mtctr r0
/* 802215F0 0021E550  40 80 00 24 */	bge lbl_80221614
lbl_802215F4:
/* 802215F4 0021E554  20 1D 00 03 */	subfic r0, r29, 3
/* 802215F8 0021E558  88 C7 00 00 */	lbz r6, 0(r7)
/* 802215FC 0021E55C  54 00 18 38 */	slwi r0, r0, 3
/* 80221600 0021E560  7C C0 00 30 */	slw r0, r6, r0
/* 80221604 0021E564  7F DE 03 78 */	or r30, r30, r0
/* 80221608 0021E568  38 E7 00 01 */	addi r7, r7, 1
/* 8022160C 0021E56C  3B BD 00 01 */	addi r29, r29, 1
/* 80221610 0021E570  42 00 FF E4 */	bdnz lbl_802215F4
lbl_80221614:
/* 80221614 0021E574  3C C0 CC 00 */	lis r6, 0xCC006838@ha
/* 80221618 0021E578  93 C6 68 38 */	stw r30, 0xCC006838@l(r6)
lbl_8022161C:
/* 8022161C 0021E57C  38 04 FF FF */	addi r0, r4, -1
/* 80221620 0021E580  3C C0 CC 00 */	lis r6, 0xCC006800@ha
/* 80221624 0021E584  54 A7 10 3A */	slwi r7, r5, 2
/* 80221628 0021E588  39 06 68 00 */	addi r8, r6, 0xCC006800@l
/* 8022162C 0021E58C  60 E6 00 01 */	ori r6, r7, 1
/* 80221630 0021E590  54 00 20 36 */	slwi r0, r0, 4
/* 80221634 0021E594  7C C0 03 78 */	or r0, r6, r0
/* 80221638 0021E598  94 08 00 34 */	stwu r0, 0x34(r8)
lbl_8022163C:
/* 8022163C 0021E59C  80 08 00 00 */	lwz r0, 0(r8)
/* 80221640 0021E5A0  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 80221644 0021E5A4  40 82 FF F8 */	bne lbl_8022163C
/* 80221648 0021E5A8  28 05 00 00 */	cmplwi r5, 0
/* 8022164C 0021E5AC  40 82 01 08 */	bne lbl_80221754
/* 80221650 0021E5B0  38 A0 00 00 */	li r5, 0
/* 80221654 0021E5B4  3C C0 CC 00 */	lis r6, 0xCC006838@ha
/* 80221658 0021E5B8  7C 05 20 00 */	cmpw r5, r4
/* 8022165C 0021E5BC  80 06 68 38 */	lwz r0, 0xCC006838@l(r6)
/* 80221660 0021E5C0  40 80 00 F4 */	bge lbl_80221754
/* 80221664 0021E5C4  2C 04 00 08 */	cmpwi r4, 8
/* 80221668 0021E5C8  38 E4 FF F8 */	addi r7, r4, -8
/* 8022166C 0021E5CC  40 81 00 BC */	ble lbl_80221728
/* 80221670 0021E5D0  38 C7 00 07 */	addi r6, r7, 7
/* 80221674 0021E5D4  54 C6 E8 FE */	srwi r6, r6, 3
/* 80221678 0021E5D8  2C 07 00 00 */	cmpwi r7, 0
/* 8022167C 0021E5DC  7C C9 03 A6 */	mtctr r6
/* 80221680 0021E5E0  40 81 00 A8 */	ble lbl_80221728
lbl_80221684:
/* 80221684 0021E5E4  20 C5 00 03 */	subfic r6, r5, 3
/* 80221688 0021E5E8  54 C7 18 38 */	slwi r7, r6, 3
/* 8022168C 0021E5EC  38 C5 00 01 */	addi r6, r5, 1
/* 80221690 0021E5F0  7C 08 3C 30 */	srw r8, r0, r7
/* 80221694 0021E5F4  20 C6 00 03 */	subfic r6, r6, 3
/* 80221698 0021E5F8  99 03 00 00 */	stb r8, 0(r3)
/* 8022169C 0021E5FC  54 C7 18 38 */	slwi r7, r6, 3
/* 802216A0 0021E600  38 C5 00 02 */	addi r6, r5, 2
/* 802216A4 0021E604  7C 0C 3C 30 */	srw r12, r0, r7
/* 802216A8 0021E608  20 C6 00 03 */	subfic r6, r6, 3
/* 802216AC 0021E60C  99 83 00 01 */	stb r12, 1(r3)
/* 802216B0 0021E610  54 C6 18 38 */	slwi r6, r6, 3
/* 802216B4 0021E614  7C 0B 34 30 */	srw r11, r0, r6
/* 802216B8 0021E618  7C C5 00 D0 */	neg r6, r5
/* 802216BC 0021E61C  99 63 00 02 */	stb r11, 2(r3)
/* 802216C0 0021E620  54 C7 18 38 */	slwi r7, r6, 3
/* 802216C4 0021E624  38 C5 00 04 */	addi r6, r5, 4
/* 802216C8 0021E628  7C 0A 3C 30 */	srw r10, r0, r7
/* 802216CC 0021E62C  20 C6 00 03 */	subfic r6, r6, 3
/* 802216D0 0021E630  99 43 00 03 */	stb r10, 3(r3)
/* 802216D4 0021E634  54 C7 18 38 */	slwi r7, r6, 3
/* 802216D8 0021E638  38 C5 00 05 */	addi r6, r5, 5
/* 802216DC 0021E63C  7C 09 3C 30 */	srw r9, r0, r7
/* 802216E0 0021E640  20 C6 00 03 */	subfic r6, r6, 3
/* 802216E4 0021E644  99 23 00 04 */	stb r9, 4(r3)
/* 802216E8 0021E648  54 C7 18 38 */	slwi r7, r6, 3
/* 802216EC 0021E64C  7C 08 3C 30 */	srw r8, r0, r7
/* 802216F0 0021E650  38 C5 00 06 */	addi r6, r5, 6
/* 802216F4 0021E654  99 03 00 05 */	stb r8, 5(r3)
/* 802216F8 0021E658  20 E6 00 03 */	subfic r7, r6, 3
/* 802216FC 0021E65C  38 C5 00 07 */	addi r6, r5, 7
/* 80221700 0021E660  54 E7 18 38 */	slwi r7, r7, 3
/* 80221704 0021E664  7C 07 3C 30 */	srw r7, r0, r7
/* 80221708 0021E668  20 C6 00 03 */	subfic r6, r6, 3
/* 8022170C 0021E66C  98 E3 00 06 */	stb r7, 6(r3)
/* 80221710 0021E670  54 C6 18 38 */	slwi r6, r6, 3
/* 80221714 0021E674  7C 06 34 30 */	srw r6, r0, r6
/* 80221718 0021E678  98 C3 00 07 */	stb r6, 7(r3)
/* 8022171C 0021E67C  38 63 00 08 */	addi r3, r3, 8
/* 80221720 0021E680  38 A5 00 08 */	addi r5, r5, 8
/* 80221724 0021E684  42 00 FF 60 */	bdnz lbl_80221684
lbl_80221728:
/* 80221728 0021E688  7C C5 20 50 */	subf r6, r5, r4
/* 8022172C 0021E68C  7C 05 20 00 */	cmpw r5, r4
/* 80221730 0021E690  7C C9 03 A6 */	mtctr r6
/* 80221734 0021E694  40 80 00 20 */	bge lbl_80221754
lbl_80221738:
/* 80221738 0021E698  20 85 00 03 */	subfic r4, r5, 3
/* 8022173C 0021E69C  54 84 18 38 */	slwi r4, r4, 3
/* 80221740 0021E6A0  7C 04 24 30 */	srw r4, r0, r4
/* 80221744 0021E6A4  98 83 00 00 */	stb r4, 0(r3)
/* 80221748 0021E6A8  38 63 00 01 */	addi r3, r3, 1
/* 8022174C 0021E6AC  38 A5 00 01 */	addi r5, r5, 1
/* 80221750 0021E6B0  42 00 FF E8 */	bdnz lbl_80221738
lbl_80221754:
/* 80221754 0021E6B4  38 60 00 01 */	li r3, 1
/* 80221758 0021E6B8  48 00 00 0C */	b lbl_80221764
lbl_8022175C:
/* 8022175C 0021E6BC  7C E3 EA 14 */	add r7, r3, r29
/* 80221760 0021E6C0  4B FF FE 84 */	b lbl_802215E4
lbl_80221764:
/* 80221764 0021E6C4  BA C1 00 20 */	lmw r22, 0x20(r1)
/* 80221768 0021E6C8  38 21 00 48 */	addi r1, r1, 0x48
/* 8022176C 0021E6CC  4E 80 00 20 */	blr 

.global DBGReadMailbox
DBGReadMailbox:
/* 80221770 0021E6D0  7C 08 02 A6 */	mflr r0
/* 80221774 0021E6D4  38 80 00 02 */	li r4, 2
/* 80221778 0021E6D8  90 01 00 04 */	stw r0, 4(r1)
/* 8022177C 0021E6DC  3C 00 60 00 */	lis r0, 0x6000
/* 80221780 0021E6E0  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 80221784 0021E6E4  BF 61 00 24 */	stmw r27, 0x24(r1)
/* 80221788 0021E6E8  3F C0 CC 00 */	lis r30, 0xCC006800@ha
/* 8022178C 0021E6EC  3B 63 00 00 */	addi r27, r3, 0
/* 80221790 0021E6F0  3B BE 68 00 */	addi r29, r30, 0xCC006800@l
/* 80221794 0021E6F4  38 61 00 18 */	addi r3, r1, 0x18
/* 80221798 0021E6F8  80 BE 68 28 */	lwz r5, 0x6828(r30)
/* 8022179C 0021E6FC  70 A5 04 05 */	andi. r5, r5, 0x405
/* 802217A0 0021E700  60 A5 00 C0 */	ori r5, r5, 0xc0
/* 802217A4 0021E704  94 BD 00 28 */	stwu r5, 0x28(r29)
/* 802217A8 0021E708  38 A0 00 01 */	li r5, 1
/* 802217AC 0021E70C  90 01 00 18 */	stw r0, 0x18(r1)
/* 802217B0 0021E710  4B FF FD 29 */	bl DBGEXIImm
/* 802217B4 0021E714  7C 60 00 34 */	cntlzw r0, r3
/* 802217B8 0021E718  54 1F D9 7E */	srwi r31, r0, 5
lbl_802217BC:
/* 802217BC 0021E71C  3B 9E 68 00 */	addi r28, r30, 0x6800
/* 802217C0 0021E720  84 1C 00 34 */	lwzu r0, 0x34(r28)
/* 802217C4 0021E724  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 802217C8 0021E728  40 82 FF F4 */	bne lbl_802217BC
/* 802217CC 0021E72C  38 7B 00 00 */	addi r3, r27, 0
/* 802217D0 0021E730  38 80 00 04 */	li r4, 4
/* 802217D4 0021E734  38 A0 00 00 */	li r5, 0
/* 802217D8 0021E738  4B FF FD 01 */	bl DBGEXIImm
/* 802217DC 0021E73C  7C 60 00 34 */	cntlzw r0, r3
/* 802217E0 0021E740  54 00 D9 7E */	srwi r0, r0, 5
/* 802217E4 0021E744  7F E3 03 78 */	or r3, r31, r0
lbl_802217E8:
/* 802217E8 0021E748  80 1C 00 00 */	lwz r0, 0(r28)
/* 802217EC 0021E74C  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 802217F0 0021E750  40 82 FF F8 */	bne lbl_802217E8
/* 802217F4 0021E754  80 9D 00 00 */	lwz r4, 0(r29)
/* 802217F8 0021E758  7C 60 00 34 */	cntlzw r0, r3
/* 802217FC 0021E75C  54 03 D9 7E */	srwi r3, r0, 5
/* 80221800 0021E760  70 80 04 05 */	andi. r0, r4, 0x405
/* 80221804 0021E764  90 1D 00 00 */	stw r0, 0(r29)
/* 80221808 0021E768  BB 61 00 24 */	lmw r27, 0x24(r1)
/* 8022180C 0021E76C  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 80221810 0021E770  38 21 00 38 */	addi r1, r1, 0x38
/* 80221814 0021E774  7C 08 03 A6 */	mtlr r0
/* 80221818 0021E778  4E 80 00 20 */	blr 

.global DBGRead
DBGRead:
/* 8022181C 0021E77C  7C 08 02 A6 */	mflr r0
/* 80221820 0021E780  90 01 00 04 */	stw r0, 4(r1)
/* 80221824 0021E784  54 60 41 EA */	rlwinm r0, r3, 8, 7, 0x15
/* 80221828 0021E788  64 00 20 00 */	oris r0, r0, 0x2000
/* 8022182C 0021E78C  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 80221830 0021E790  BF 41 00 28 */	stmw r26, 0x28(r1)
/* 80221834 0021E794  3F A0 CC 00 */	lis r29, 0xCC006800@ha
/* 80221838 0021E798  3B C5 00 00 */	addi r30, r5, 0
/* 8022183C 0021E79C  3B 44 00 00 */	addi r26, r4, 0
/* 80221840 0021E7A0  3B FD 68 00 */	addi r31, r29, 0xCC006800@l
/* 80221844 0021E7A4  38 61 00 24 */	addi r3, r1, 0x24
/* 80221848 0021E7A8  38 80 00 04 */	li r4, 4
/* 8022184C 0021E7AC  38 A0 00 01 */	li r5, 1
/* 80221850 0021E7B0  80 DD 68 28 */	lwz r6, 0x6828(r29)
/* 80221854 0021E7B4  70 C6 04 05 */	andi. r6, r6, 0x405
/* 80221858 0021E7B8  60 C6 00 C0 */	ori r6, r6, 0xc0
/* 8022185C 0021E7BC  94 DF 00 28 */	stwu r6, 0x28(r31)
/* 80221860 0021E7C0  90 01 00 24 */	stw r0, 0x24(r1)
/* 80221864 0021E7C4  4B FF FC 75 */	bl DBGEXIImm
/* 80221868 0021E7C8  7C 60 00 34 */	cntlzw r0, r3
/* 8022186C 0021E7CC  54 00 D9 7E */	srwi r0, r0, 5
/* 80221870 0021E7D0  7C 1B 03 78 */	mr r27, r0
lbl_80221874:
/* 80221874 0021E7D4  3B 9D 68 00 */	addi r28, r29, 0x6800
/* 80221878 0021E7D8  84 1C 00 34 */	lwzu r0, 0x34(r28)
/* 8022187C 0021E7DC  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 80221880 0021E7E0  40 82 FF F4 */	bne lbl_80221874
/* 80221884 0021E7E4  48 00 00 44 */	b lbl_802218C8
lbl_80221888:
/* 80221888 0021E7E8  38 61 00 20 */	addi r3, r1, 0x20
/* 8022188C 0021E7EC  38 80 00 04 */	li r4, 4
/* 80221890 0021E7F0  38 A0 00 00 */	li r5, 0
/* 80221894 0021E7F4  4B FF FC 45 */	bl DBGEXIImm
/* 80221898 0021E7F8  7C 60 00 34 */	cntlzw r0, r3
/* 8022189C 0021E7FC  54 00 D9 7E */	srwi r0, r0, 5
/* 802218A0 0021E800  7F 7B 03 78 */	or r27, r27, r0
lbl_802218A4:
/* 802218A4 0021E804  80 1C 00 00 */	lwz r0, 0(r28)
/* 802218A8 0021E808  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 802218AC 0021E80C  40 82 FF F8 */	bne lbl_802218A4
/* 802218B0 0021E810  80 01 00 20 */	lwz r0, 0x20(r1)
/* 802218B4 0021E814  37 DE FF FC */	addic. r30, r30, -4
/* 802218B8 0021E818  90 1A 00 00 */	stw r0, 0(r26)
/* 802218BC 0021E81C  3B 5A 00 04 */	addi r26, r26, 4
/* 802218C0 0021E820  40 80 00 08 */	bge lbl_802218C8
/* 802218C4 0021E824  3B C0 00 00 */	li r30, 0
lbl_802218C8:
/* 802218C8 0021E828  2C 1E 00 00 */	cmpwi r30, 0
/* 802218CC 0021E82C  40 82 FF BC */	bne lbl_80221888
/* 802218D0 0021E830  80 9F 00 00 */	lwz r4, 0(r31)
/* 802218D4 0021E834  7F 60 00 34 */	cntlzw r0, r27
/* 802218D8 0021E838  54 03 D9 7E */	srwi r3, r0, 5
/* 802218DC 0021E83C  70 80 04 05 */	andi. r0, r4, 0x405
/* 802218E0 0021E840  90 1F 00 00 */	stw r0, 0(r31)
/* 802218E4 0021E844  BB 41 00 28 */	lmw r26, 0x28(r1)
/* 802218E8 0021E848  80 01 00 44 */	lwz r0, 0x44(r1)
/* 802218EC 0021E84C  38 21 00 40 */	addi r1, r1, 0x40
/* 802218F0 0021E850  7C 08 03 A6 */	mtlr r0
/* 802218F4 0021E854  4E 80 00 20 */	blr 

.global DBGWrite
DBGWrite:
/* 802218F8 0021E858  7C 08 02 A6 */	mflr r0
/* 802218FC 0021E85C  90 01 00 04 */	stw r0, 4(r1)
/* 80221900 0021E860  54 60 41 EA */	rlwinm r0, r3, 8, 7, 0x15
/* 80221904 0021E864  64 00 A0 00 */	oris r0, r0, 0xa000
/* 80221908 0021E868  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 8022190C 0021E86C  BF 41 00 28 */	stmw r26, 0x28(r1)
/* 80221910 0021E870  3F A0 CC 00 */	lis r29, 0xCC006800@ha
/* 80221914 0021E874  3B C5 00 00 */	addi r30, r5, 0
/* 80221918 0021E878  3B 44 00 00 */	addi r26, r4, 0
/* 8022191C 0021E87C  3B FD 68 00 */	addi r31, r29, 0xCC006800@l
/* 80221920 0021E880  38 61 00 24 */	addi r3, r1, 0x24
/* 80221924 0021E884  38 80 00 04 */	li r4, 4
/* 80221928 0021E888  38 A0 00 01 */	li r5, 1
/* 8022192C 0021E88C  80 DD 68 28 */	lwz r6, 0x6828(r29)
/* 80221930 0021E890  70 C6 04 05 */	andi. r6, r6, 0x405
/* 80221934 0021E894  60 C6 00 C0 */	ori r6, r6, 0xc0
/* 80221938 0021E898  94 DF 00 28 */	stwu r6, 0x28(r31)
/* 8022193C 0021E89C  90 01 00 24 */	stw r0, 0x24(r1)
/* 80221940 0021E8A0  4B FF FB 99 */	bl DBGEXIImm
/* 80221944 0021E8A4  7C 60 00 34 */	cntlzw r0, r3
/* 80221948 0021E8A8  54 00 D9 7E */	srwi r0, r0, 5
/* 8022194C 0021E8AC  7C 1B 03 78 */	mr r27, r0
lbl_80221950:
/* 80221950 0021E8B0  3B 9D 68 00 */	addi r28, r29, 0x6800
/* 80221954 0021E8B4  84 1C 00 34 */	lwzu r0, 0x34(r28)
/* 80221958 0021E8B8  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8022195C 0021E8BC  40 82 FF F4 */	bne lbl_80221950
/* 80221960 0021E8C0  48 00 00 44 */	b lbl_802219A4
lbl_80221964:
/* 80221964 0021E8C4  80 1A 00 00 */	lwz r0, 0(r26)
/* 80221968 0021E8C8  38 61 00 20 */	addi r3, r1, 0x20
/* 8022196C 0021E8CC  38 80 00 04 */	li r4, 4
/* 80221970 0021E8D0  90 01 00 20 */	stw r0, 0x20(r1)
/* 80221974 0021E8D4  38 A0 00 01 */	li r5, 1
/* 80221978 0021E8D8  3B 5A 00 04 */	addi r26, r26, 4
/* 8022197C 0021E8DC  4B FF FB 5D */	bl DBGEXIImm
/* 80221980 0021E8E0  7C 60 00 34 */	cntlzw r0, r3
/* 80221984 0021E8E4  54 00 D9 7E */	srwi r0, r0, 5
/* 80221988 0021E8E8  7F 7B 03 78 */	or r27, r27, r0
lbl_8022198C:
/* 8022198C 0021E8EC  80 1C 00 00 */	lwz r0, 0(r28)
/* 80221990 0021E8F0  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 80221994 0021E8F4  40 82 FF F8 */	bne lbl_8022198C
/* 80221998 0021E8F8  37 DE FF FC */	addic. r30, r30, -4
/* 8022199C 0021E8FC  40 80 00 08 */	bge lbl_802219A4
/* 802219A0 0021E900  3B C0 00 00 */	li r30, 0
lbl_802219A4:
/* 802219A4 0021E904  2C 1E 00 00 */	cmpwi r30, 0
/* 802219A8 0021E908  40 82 FF BC */	bne lbl_80221964
/* 802219AC 0021E90C  80 9F 00 00 */	lwz r4, 0(r31)
/* 802219B0 0021E910  7F 60 00 34 */	cntlzw r0, r27
/* 802219B4 0021E914  54 03 D9 7E */	srwi r3, r0, 5
/* 802219B8 0021E918  70 80 04 05 */	andi. r0, r4, 0x405
/* 802219BC 0021E91C  90 1F 00 00 */	stw r0, 0(r31)
/* 802219C0 0021E920  BB 41 00 28 */	lmw r26, 0x28(r1)
/* 802219C4 0021E924  80 01 00 44 */	lwz r0, 0x44(r1)
/* 802219C8 0021E928  38 21 00 40 */	addi r1, r1, 0x40
/* 802219CC 0021E92C  7C 08 03 A6 */	mtlr r0
/* 802219D0 0021E930  4E 80 00 20 */	blr 

.global DBGReadStatus
DBGReadStatus:
/* 802219D4 0021E934  7C 08 02 A6 */	mflr r0
/* 802219D8 0021E938  38 80 00 02 */	li r4, 2
/* 802219DC 0021E93C  90 01 00 04 */	stw r0, 4(r1)
/* 802219E0 0021E940  3C 00 40 00 */	lis r0, 0x4000
/* 802219E4 0021E944  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 802219E8 0021E948  BF 61 00 24 */	stmw r27, 0x24(r1)
/* 802219EC 0021E94C  3F C0 CC 00 */	lis r30, 0xCC006800@ha
/* 802219F0 0021E950  3B 63 00 00 */	addi r27, r3, 0
/* 802219F4 0021E954  3B BE 68 00 */	addi r29, r30, 0xCC006800@l
/* 802219F8 0021E958  38 61 00 18 */	addi r3, r1, 0x18
/* 802219FC 0021E95C  80 BE 68 28 */	lwz r5, 0x6828(r30)
/* 80221A00 0021E960  70 A5 04 05 */	andi. r5, r5, 0x405
/* 80221A04 0021E964  60 A5 00 C0 */	ori r5, r5, 0xc0
/* 80221A08 0021E968  94 BD 00 28 */	stwu r5, 0x28(r29)
/* 80221A0C 0021E96C  38 A0 00 01 */	li r5, 1
/* 80221A10 0021E970  90 01 00 18 */	stw r0, 0x18(r1)
/* 80221A14 0021E974  4B FF FA C5 */	bl DBGEXIImm
/* 80221A18 0021E978  7C 60 00 34 */	cntlzw r0, r3
/* 80221A1C 0021E97C  54 1F D9 7E */	srwi r31, r0, 5
lbl_80221A20:
/* 80221A20 0021E980  3B 9E 68 00 */	addi r28, r30, 0x6800
/* 80221A24 0021E984  84 1C 00 34 */	lwzu r0, 0x34(r28)
/* 80221A28 0021E988  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 80221A2C 0021E98C  40 82 FF F4 */	bne lbl_80221A20
/* 80221A30 0021E990  38 7B 00 00 */	addi r3, r27, 0
/* 80221A34 0021E994  38 80 00 04 */	li r4, 4
/* 80221A38 0021E998  38 A0 00 00 */	li r5, 0
/* 80221A3C 0021E99C  4B FF FA 9D */	bl DBGEXIImm
/* 80221A40 0021E9A0  7C 60 00 34 */	cntlzw r0, r3
/* 80221A44 0021E9A4  54 00 D9 7E */	srwi r0, r0, 5
/* 80221A48 0021E9A8  7F E3 03 78 */	or r3, r31, r0
lbl_80221A4C:
/* 80221A4C 0021E9AC  80 1C 00 00 */	lwz r0, 0(r28)
/* 80221A50 0021E9B0  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 80221A54 0021E9B4  40 82 FF F8 */	bne lbl_80221A4C
/* 80221A58 0021E9B8  80 9D 00 00 */	lwz r4, 0(r29)
/* 80221A5C 0021E9BC  7C 60 00 34 */	cntlzw r0, r3
/* 80221A60 0021E9C0  54 03 D9 7E */	srwi r3, r0, 5
/* 80221A64 0021E9C4  70 80 04 05 */	andi. r0, r4, 0x405
/* 80221A68 0021E9C8  90 1D 00 00 */	stw r0, 0(r29)
/* 80221A6C 0021E9CC  BB 61 00 24 */	lmw r27, 0x24(r1)
/* 80221A70 0021E9D0  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 80221A74 0021E9D4  38 21 00 38 */	addi r1, r1, 0x38
/* 80221A78 0021E9D8  7C 08 03 A6 */	mtlr r0
/* 80221A7C 0021E9DC  4E 80 00 20 */	blr 

.global MWCallback
MWCallback:
/* 80221A80 0021E9E0  7C 08 02 A6 */	mflr r0
/* 80221A84 0021E9E4  90 01 00 04 */	stw r0, 4(r1)
/* 80221A88 0021E9E8  38 00 00 01 */	li r0, 1
/* 80221A8C 0021E9EC  94 21 FF F8 */	stwu r1, -8(r1)
/* 80221A90 0021E9F0  81 8D 34 B0 */	lwz r12, MTRCallback@sda21(r13)
/* 80221A94 0021E9F4  98 0D 34 C4 */	stb r0, EXIInputFlag@sda21(r13)
/* 80221A98 0021E9F8  28 0C 00 00 */	cmplwi r12, 0
/* 80221A9C 0021E9FC  41 82 00 10 */	beq lbl_80221AAC
/* 80221AA0 0021EA00  7D 88 03 A6 */	mtlr r12
/* 80221AA4 0021EA04  38 60 00 00 */	li r3, 0
/* 80221AA8 0021EA08  4E 80 00 21 */	blrl 
lbl_80221AAC:
/* 80221AAC 0021EA0C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80221AB0 0021EA10  38 21 00 08 */	addi r1, r1, 8
/* 80221AB4 0021EA14  7C 08 03 A6 */	mtlr r0
/* 80221AB8 0021EA18  4E 80 00 20 */	blr 

.global DBGHandler
DBGHandler:
/* 80221ABC 0021EA1C  7C 08 02 A6 */	mflr r0
/* 80221AC0 0021EA20  3C A0 CC 00 */	lis r5, 0xCC003000@ha
/* 80221AC4 0021EA24  90 01 00 04 */	stw r0, 4(r1)
/* 80221AC8 0021EA28  38 00 10 00 */	li r0, 0x1000
/* 80221ACC 0021EA2C  94 21 FF F8 */	stwu r1, -8(r1)
/* 80221AD0 0021EA30  81 8D 34 B4 */	lwz r12, DBGCallback@sda21(r13)
/* 80221AD4 0021EA34  90 05 30 00 */	stw r0, 0xCC003000@l(r5)
/* 80221AD8 0021EA38  28 0C 00 00 */	cmplwi r12, 0
/* 80221ADC 0021EA3C  41 82 00 10 */	beq lbl_80221AEC
/* 80221AE0 0021EA40  7D 88 03 A6 */	mtlr r12
/* 80221AE4 0021EA44  7C 63 07 34 */	extsh r3, r3
/* 80221AE8 0021EA48  4E 80 00 21 */	blrl 
lbl_80221AEC:
/* 80221AEC 0021EA4C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80221AF0 0021EA50  38 21 00 08 */	addi r1, r1, 8
/* 80221AF4 0021EA54  7C 08 03 A6 */	mtlr r0
/* 80221AF8 0021EA58  4E 80 00 20 */	blr 

.global DBInitComm
DBInitComm:
/* 80221AFC 0021EA5C  7C 08 02 A6 */	mflr r0
/* 80221B00 0021EA60  90 01 00 04 */	stw r0, 4(r1)
/* 80221B04 0021EA64  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80221B08 0021EA68  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80221B0C 0021EA6C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80221B10 0021EA70  3B C4 00 00 */	addi r30, r4, 0
/* 80221B14 0021EA74  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80221B18 0021EA78  3B A3 00 00 */	addi r29, r3, 0
/* 80221B1C 0021EA7C  4B FD 74 61 */	bl OSDisableInterrupts
/* 80221B20 0021EA80  38 0D 34 C4 */	addi r0, r13, EXIInputFlag@sda21
/* 80221B24 0021EA84  90 0D 34 C0 */	stw r0, pEXIInputFlag@sda21(r13)
/* 80221B28 0021EA88  3C 80 00 02 */	lis r4, 0x00018000@ha
/* 80221B2C 0021EA8C  3B E3 00 00 */	addi r31, r3, 0
/* 80221B30 0021EA90  80 0D 34 C0 */	lwz r0, pEXIInputFlag@sda21(r13)
/* 80221B34 0021EA94  38 64 80 00 */	addi r3, r4, 0x00018000@l
/* 80221B38 0021EA98  90 1D 00 00 */	stw r0, 0(r29)
/* 80221B3C 0021EA9C  93 CD 34 B0 */	stw r30, MTRCallback@sda21(r13)
/* 80221B40 0021EAA0  4B FD 77 DD */	bl __OSMaskInterrupts
/* 80221B44 0021EAA4  3C 60 CC 00 */	lis r3, 0xCC006828@ha
/* 80221B48 0021EAA8  38 00 00 00 */	li r0, 0
/* 80221B4C 0021EAAC  90 03 68 28 */	stw r0, 0xCC006828@l(r3)
/* 80221B50 0021EAB0  7F E3 FB 78 */	mr r3, r31
/* 80221B54 0021EAB4  4B FD 74 51 */	bl OSRestoreInterrupts
/* 80221B58 0021EAB8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80221B5C 0021EABC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80221B60 0021EAC0  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80221B64 0021EAC4  7C 08 03 A6 */	mtlr r0
/* 80221B68 0021EAC8  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80221B6C 0021EACC  38 21 00 20 */	addi r1, r1, 0x20
/* 80221B70 0021EAD0  4E 80 00 20 */	blr 

.global DBInitInterrupts
DBInitInterrupts:
/* 80221B74 0021EAD4  7C 08 02 A6 */	mflr r0
/* 80221B78 0021EAD8  3C 60 00 02 */	lis r3, 0x00018000@ha
/* 80221B7C 0021EADC  90 01 00 04 */	stw r0, 4(r1)
/* 80221B80 0021EAE0  38 63 80 00 */	addi r3, r3, 0x00018000@l
/* 80221B84 0021EAE4  94 21 FF F8 */	stwu r1, -8(r1)
/* 80221B88 0021EAE8  4B FD 77 95 */	bl __OSMaskInterrupts
/* 80221B8C 0021EAEC  38 60 00 40 */	li r3, 0x40
/* 80221B90 0021EAF0  4B FD 77 8D */	bl __OSMaskInterrupts
/* 80221B94 0021EAF4  3C 60 80 22 */	lis r3, MWCallback@ha
/* 80221B98 0021EAF8  38 03 1A 80 */	addi r0, r3, MWCallback@l
/* 80221B9C 0021EAFC  3C 60 80 22 */	lis r3, DBGHandler@ha
/* 80221BA0 0021EB00  90 0D 34 B4 */	stw r0, DBGCallback@sda21(r13)
/* 80221BA4 0021EB04  38 83 1A BC */	addi r4, r3, DBGHandler@l
/* 80221BA8 0021EB08  38 60 00 19 */	li r3, 0x19
/* 80221BAC 0021EB0C  4B FD 74 1D */	bl __OSSetInterruptHandler
/* 80221BB0 0021EB10  38 60 00 40 */	li r3, 0x40
/* 80221BB4 0021EB14  4B FD 77 F1 */	bl __OSUnmaskInterrupts
/* 80221BB8 0021EB18  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80221BBC 0021EB1C  38 21 00 08 */	addi r1, r1, 8
/* 80221BC0 0021EB20  7C 08 03 A6 */	mtlr r0
/* 80221BC4 0021EB24  4E 80 00 20 */	blr 

.global DBQueryData
DBQueryData:
/* 80221BC8 0021EB28  7C 08 02 A6 */	mflr r0
/* 80221BCC 0021EB2C  38 60 00 00 */	li r3, 0
/* 80221BD0 0021EB30  90 01 00 04 */	stw r0, 4(r1)
/* 80221BD4 0021EB34  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80221BD8 0021EB38  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80221BDC 0021EB3C  80 0D 34 BC */	lwz r0, RecvDataLeng@sda21(r13)
/* 80221BE0 0021EB40  98 6D 34 C4 */	stb r3, EXIInputFlag@sda21(r13)
/* 80221BE4 0021EB44  2C 00 00 00 */	cmpwi r0, 0
/* 80221BE8 0021EB48  40 82 00 5C */	bne lbl_80221C44
/* 80221BEC 0021EB4C  4B FD 73 91 */	bl OSDisableInterrupts
/* 80221BF0 0021EB50  3B E3 00 00 */	addi r31, r3, 0
/* 80221BF4 0021EB54  38 61 00 08 */	addi r3, r1, 8
/* 80221BF8 0021EB58  4B FF FD DD */	bl DBGReadStatus
/* 80221BFC 0021EB5C  80 01 00 08 */	lwz r0, 8(r1)
/* 80221C00 0021EB60  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 80221C04 0021EB64  41 82 00 40 */	beq lbl_80221C44
/* 80221C08 0021EB68  38 61 00 08 */	addi r3, r1, 8
/* 80221C0C 0021EB6C  4B FF FB 65 */	bl DBGReadMailbox
/* 80221C10 0021EB70  80 01 00 08 */	lwz r0, 8(r1)
/* 80221C14 0021EB74  54 00 00 FE */	clrlwi r0, r0, 3
/* 80221C18 0021EB78  90 01 00 08 */	stw r0, 8(r1)
/* 80221C1C 0021EB7C  80 81 00 08 */	lwz r4, 8(r1)
/* 80221C20 0021EB80  54 83 00 CE */	rlwinm r3, r4, 0, 3, 7
/* 80221C24 0021EB84  3C 03 E1 00 */	addis r0, r3, 0xe100
/* 80221C28 0021EB88  28 00 00 00 */	cmplwi r0, 0
/* 80221C2C 0021EB8C  40 82 00 18 */	bne lbl_80221C44
/* 80221C30 0021EB90  54 83 04 7E */	clrlwi r3, r4, 0x11
/* 80221C34 0021EB94  90 8D 34 B8 */	stw r4, SendMailData@sda21(r13)
/* 80221C38 0021EB98  38 00 00 01 */	li r0, 1
/* 80221C3C 0021EB9C  90 6D 34 BC */	stw r3, RecvDataLeng@sda21(r13)
/* 80221C40 0021EBA0  98 0D 34 C4 */	stb r0, EXIInputFlag@sda21(r13)
lbl_80221C44:
/* 80221C44 0021EBA4  7F E3 FB 78 */	mr r3, r31
/* 80221C48 0021EBA8  4B FD 73 5D */	bl OSRestoreInterrupts
/* 80221C4C 0021EBAC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80221C50 0021EBB0  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80221C54 0021EBB4  38 21 00 18 */	addi r1, r1, 0x18
/* 80221C58 0021EBB8  80 6D 34 BC */	lwz r3, RecvDataLeng@sda21(r13)
/* 80221C5C 0021EBBC  7C 08 03 A6 */	mtlr r0
/* 80221C60 0021EBC0  4E 80 00 20 */	blr 

.global DBRead
DBRead:
/* 80221C64 0021EBC4  7C 08 02 A6 */	mflr r0
/* 80221C68 0021EBC8  90 01 00 04 */	stw r0, 4(r1)
/* 80221C6C 0021EBCC  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80221C70 0021EBD0  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80221C74 0021EBD4  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80221C78 0021EBD8  3B C4 00 00 */	addi r30, r4, 0
/* 80221C7C 0021EBDC  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80221C80 0021EBE0  3B A3 00 00 */	addi r29, r3, 0
/* 80221C84 0021EBE4  4B FD 72 F9 */	bl OSDisableInterrupts
/* 80221C88 0021EBE8  80 0D 34 B8 */	lwz r0, SendMailData@sda21(r13)
/* 80221C8C 0021EBEC  3B E3 00 00 */	addi r31, r3, 0
/* 80221C90 0021EBF0  54 00 03 DF */	rlwinm. r0, r0, 0, 0xf, 0xf
/* 80221C94 0021EBF4  41 82 00 0C */	beq lbl_80221CA0
/* 80221C98 0021EBF8  38 60 10 00 */	li r3, 0x1000
/* 80221C9C 0021EBFC  48 00 00 08 */	b lbl_80221CA4
lbl_80221CA0:
/* 80221CA0 0021EC00  38 60 00 00 */	li r3, 0
lbl_80221CA4:
/* 80221CA4 0021EC04  3C 63 00 02 */	addis r3, r3, 2
/* 80221CA8 0021EC08  38 1E 00 03 */	addi r0, r30, 3
/* 80221CAC 0021EC0C  38 9D 00 00 */	addi r4, r29, 0
/* 80221CB0 0021EC10  54 05 00 3A */	rlwinm r5, r0, 0, 0, 0x1d
/* 80221CB4 0021EC14  38 63 E0 00 */	addi r3, r3, -8192
/* 80221CB8 0021EC18  4B FF FB 65 */	bl DBGRead
/* 80221CBC 0021EC1C  38 00 00 00 */	li r0, 0
/* 80221CC0 0021EC20  90 0D 34 BC */	stw r0, RecvDataLeng@sda21(r13)
/* 80221CC4 0021EC24  7F E3 FB 78 */	mr r3, r31
/* 80221CC8 0021EC28  98 0D 34 C4 */	stb r0, EXIInputFlag@sda21(r13)
/* 80221CCC 0021EC2C  4B FD 72 D9 */	bl OSRestoreInterrupts
/* 80221CD0 0021EC30  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80221CD4 0021EC34  38 60 00 00 */	li r3, 0
/* 80221CD8 0021EC38  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80221CDC 0021EC3C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80221CE0 0021EC40  7C 08 03 A6 */	mtlr r0
/* 80221CE4 0021EC44  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80221CE8 0021EC48  38 21 00 20 */	addi r1, r1, 0x20
/* 80221CEC 0021EC4C  4E 80 00 20 */	blr 

.global DBWrite
DBWrite:
/* 80221CF0 0021EC50  7C 08 02 A6 */	mflr r0
/* 80221CF4 0021EC54  90 01 00 04 */	stw r0, 4(r1)
/* 80221CF8 0021EC58  94 21 FF 88 */	stwu r1, -0x78(r1)
/* 80221CFC 0021EC5C  BF 01 00 58 */	stmw r24, 0x58(r1)
/* 80221D00 0021EC60  3B 43 00 00 */	addi r26, r3, 0
/* 80221D04 0021EC64  3B 64 00 00 */	addi r27, r4, 0
/* 80221D08 0021EC68  4B FD 72 75 */	bl OSDisableInterrupts
/* 80221D0C 0021EC6C  3B 83 00 00 */	addi r28, r3, 0
/* 80221D10 0021EC70  3F 20 CC 00 */	lis r25, 0xCC006828@ha
/* 80221D14 0021EC74  3F E0 40 00 */	lis r31, 0x4000
lbl_80221D18:
/* 80221D18 0021EC78  80 19 68 28 */	lwz r0, 0xCC006828@l(r25)
/* 80221D1C 0021EC7C  3B D9 68 00 */	addi r30, r25, 0x6800
/* 80221D20 0021EC80  38 61 00 50 */	addi r3, r1, 0x50
/* 80221D24 0021EC84  70 00 04 05 */	andi. r0, r0, 0x405
/* 80221D28 0021EC88  38 80 00 02 */	li r4, 2
/* 80221D2C 0021EC8C  38 A0 00 01 */	li r5, 1
/* 80221D30 0021EC90  60 00 00 C0 */	ori r0, r0, 0xc0
/* 80221D34 0021EC94  94 1E 00 28 */	stwu r0, 0x28(r30)
/* 80221D38 0021EC98  93 E1 00 50 */	stw r31, 0x50(r1)
/* 80221D3C 0021EC9C  4B FF F7 9D */	bl DBGEXIImm
/* 80221D40 0021ECA0  7C 60 00 34 */	cntlzw r0, r3
/* 80221D44 0021ECA4  54 18 D9 7E */	srwi r24, r0, 5
lbl_80221D48:
/* 80221D48 0021ECA8  3B B9 68 00 */	addi r29, r25, 0x6800
/* 80221D4C 0021ECAC  84 1D 00 34 */	lwzu r0, 0x34(r29)
/* 80221D50 0021ECB0  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 80221D54 0021ECB4  40 82 FF F4 */	bne lbl_80221D48
/* 80221D58 0021ECB8  38 61 00 54 */	addi r3, r1, 0x54
/* 80221D5C 0021ECBC  38 80 00 04 */	li r4, 4
/* 80221D60 0021ECC0  38 A0 00 00 */	li r5, 0
/* 80221D64 0021ECC4  4B FF F7 75 */	bl DBGEXIImm
lbl_80221D68:
/* 80221D68 0021ECC8  80 1D 00 00 */	lwz r0, 0(r29)
/* 80221D6C 0021ECCC  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 80221D70 0021ECD0  40 82 FF F8 */	bne lbl_80221D68
/* 80221D74 0021ECD4  80 1E 00 00 */	lwz r0, 0(r30)
/* 80221D78 0021ECD8  70 00 04 05 */	andi. r0, r0, 0x405
/* 80221D7C 0021ECDC  90 1E 00 00 */	stw r0, 0(r30)
/* 80221D80 0021ECE0  80 01 00 54 */	lwz r0, 0x54(r1)
/* 80221D84 0021ECE4  54 00 07 BD */	rlwinm. r0, r0, 0, 0x1e, 0x1e
/* 80221D88 0021ECE8  40 82 FF 90 */	bne lbl_80221D18
/* 80221D8C 0021ECEC  88 6D 2A F8 */	lbz r3, SendCount@sda21(r13)
/* 80221D90 0021ECF0  38 03 00 01 */	addi r0, r3, 1
/* 80221D94 0021ECF4  98 0D 2A F8 */	stb r0, SendCount@sda21(r13)
/* 80221D98 0021ECF8  88 0D 2A F8 */	lbz r0, SendCount@sda21(r13)
/* 80221D9C 0021ECFC  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 80221DA0 0021ED00  41 82 00 0C */	beq lbl_80221DAC
/* 80221DA4 0021ED04  38 60 10 00 */	li r3, 0x1000
/* 80221DA8 0021ED08  48 00 00 08 */	b lbl_80221DB0
lbl_80221DAC:
/* 80221DAC 0021ED0C  38 60 00 00 */	li r3, 0
lbl_80221DB0:
/* 80221DB0 0021ED10  38 1B 00 03 */	addi r0, r27, 3
/* 80221DB4 0021ED14  64 79 00 01 */	oris r25, r3, 1
/* 80221DB8 0021ED18  54 18 00 3A */	rlwinm r24, r0, 0, 0, 0x1d
/* 80221DBC 0021ED1C  63 39 C0 00 */	ori r25, r25, 0xc000
lbl_80221DC0:
/* 80221DC0 0021ED20  38 79 00 00 */	addi r3, r25, 0
/* 80221DC4 0021ED24  38 9A 00 00 */	addi r4, r26, 0
/* 80221DC8 0021ED28  38 B8 00 00 */	addi r5, r24, 0
/* 80221DCC 0021ED2C  4B FF FB 2D */	bl DBGWrite
/* 80221DD0 0021ED30  2C 03 00 00 */	cmpwi r3, 0
/* 80221DD4 0021ED34  41 82 FF EC */	beq lbl_80221DC0
/* 80221DD8 0021ED38  3F E0 40 00 */	lis r31, 0x4000
lbl_80221DDC:
/* 80221DDC 0021ED3C  80 1E 00 00 */	lwz r0, 0(r30)
/* 80221DE0 0021ED40  38 61 00 4C */	addi r3, r1, 0x4c
/* 80221DE4 0021ED44  38 80 00 02 */	li r4, 2
/* 80221DE8 0021ED48  70 00 04 05 */	andi. r0, r0, 0x405
/* 80221DEC 0021ED4C  38 A0 00 01 */	li r5, 1
/* 80221DF0 0021ED50  60 00 00 C0 */	ori r0, r0, 0xc0
/* 80221DF4 0021ED54  90 1E 00 00 */	stw r0, 0(r30)
/* 80221DF8 0021ED58  93 E1 00 4C */	stw r31, 0x4c(r1)
/* 80221DFC 0021ED5C  4B FF F6 DD */	bl DBGEXIImm
/* 80221E00 0021ED60  7C 60 00 34 */	cntlzw r0, r3
/* 80221E04 0021ED64  54 1A D9 7E */	srwi r26, r0, 5
lbl_80221E08:
/* 80221E08 0021ED68  80 1D 00 00 */	lwz r0, 0(r29)
/* 80221E0C 0021ED6C  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 80221E10 0021ED70  40 82 FF F8 */	bne lbl_80221E08
/* 80221E14 0021ED74  38 61 00 54 */	addi r3, r1, 0x54
/* 80221E18 0021ED78  38 80 00 04 */	li r4, 4
/* 80221E1C 0021ED7C  38 A0 00 00 */	li r5, 0
/* 80221E20 0021ED80  4B FF F6 B9 */	bl DBGEXIImm
lbl_80221E24:
/* 80221E24 0021ED84  80 1D 00 00 */	lwz r0, 0(r29)
/* 80221E28 0021ED88  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 80221E2C 0021ED8C  40 82 FF F8 */	bne lbl_80221E24
/* 80221E30 0021ED90  80 1E 00 00 */	lwz r0, 0(r30)
/* 80221E34 0021ED94  70 00 04 05 */	andi. r0, r0, 0x405
/* 80221E38 0021ED98  90 1E 00 00 */	stw r0, 0(r30)
/* 80221E3C 0021ED9C  80 01 00 54 */	lwz r0, 0x54(r1)
/* 80221E40 0021EDA0  54 00 07 BD */	rlwinm. r0, r0, 0, 0x1e, 0x1e
/* 80221E44 0021EDA4  40 82 FF 98 */	bne lbl_80221DDC
/* 80221E48 0021EDA8  88 0D 2A F8 */	lbz r0, SendCount@sda21(r13)
/* 80221E4C 0021EDAC  54 00 80 1E */	slwi r0, r0, 0x10
/* 80221E50 0021EDB0  64 00 1F 00 */	oris r0, r0, 0x1f00
/* 80221E54 0021EDB4  7C 00 DB 78 */	or r0, r0, r27
/* 80221E58 0021EDB8  54 00 00 FE */	clrlwi r0, r0, 3
/* 80221E5C 0021EDBC  64 18 C0 00 */	oris r24, r0, 0xc000
lbl_80221E60:
/* 80221E60 0021EDC0  80 1E 00 00 */	lwz r0, 0(r30)
/* 80221E64 0021EDC4  38 61 00 44 */	addi r3, r1, 0x44
/* 80221E68 0021EDC8  38 80 00 04 */	li r4, 4
/* 80221E6C 0021EDCC  70 00 04 05 */	andi. r0, r0, 0x405
/* 80221E70 0021EDD0  38 A0 00 01 */	li r5, 1
/* 80221E74 0021EDD4  60 00 00 C0 */	ori r0, r0, 0xc0
/* 80221E78 0021EDD8  90 1E 00 00 */	stw r0, 0(r30)
/* 80221E7C 0021EDDC  93 01 00 44 */	stw r24, 0x44(r1)
/* 80221E80 0021EDE0  4B FF F6 59 */	bl DBGEXIImm
/* 80221E84 0021EDE4  7C 60 00 34 */	cntlzw r0, r3
/* 80221E88 0021EDE8  54 03 D9 7E */	srwi r3, r0, 5
lbl_80221E8C:
/* 80221E8C 0021EDEC  80 1D 00 00 */	lwz r0, 0(r29)
/* 80221E90 0021EDF0  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 80221E94 0021EDF4  40 82 FF F8 */	bne lbl_80221E8C
/* 80221E98 0021EDF8  80 1E 00 00 */	lwz r0, 0(r30)
/* 80221E9C 0021EDFC  70 00 04 05 */	andi. r0, r0, 0x405
/* 80221EA0 0021EE00  2C 03 00 00 */	cmpwi r3, 0
/* 80221EA4 0021EE04  90 1E 00 00 */	stw r0, 0(r30)
/* 80221EA8 0021EE08  40 82 FF B8 */	bne lbl_80221E60
/* 80221EAC 0021EE0C  3F 60 40 00 */	lis r27, 0x4000
lbl_80221EB0:
/* 80221EB0 0021EE10  80 1E 00 00 */	lwz r0, 0(r30)
/* 80221EB4 0021EE14  38 61 00 3C */	addi r3, r1, 0x3c
/* 80221EB8 0021EE18  38 80 00 02 */	li r4, 2
/* 80221EBC 0021EE1C  70 00 04 05 */	andi. r0, r0, 0x405
/* 80221EC0 0021EE20  38 A0 00 01 */	li r5, 1
/* 80221EC4 0021EE24  60 00 00 C0 */	ori r0, r0, 0xc0
/* 80221EC8 0021EE28  90 1E 00 00 */	stw r0, 0(r30)
/* 80221ECC 0021EE2C  93 61 00 3C */	stw r27, 0x3c(r1)
/* 80221ED0 0021EE30  4B FF F6 09 */	bl DBGEXIImm
/* 80221ED4 0021EE34  7C 60 00 34 */	cntlzw r0, r3
/* 80221ED8 0021EE38  54 1A D9 7E */	srwi r26, r0, 5
lbl_80221EDC:
/* 80221EDC 0021EE3C  80 1D 00 00 */	lwz r0, 0(r29)
/* 80221EE0 0021EE40  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 80221EE4 0021EE44  40 82 FF F8 */	bne lbl_80221EDC
/* 80221EE8 0021EE48  38 61 00 54 */	addi r3, r1, 0x54
/* 80221EEC 0021EE4C  38 80 00 04 */	li r4, 4
/* 80221EF0 0021EE50  38 A0 00 00 */	li r5, 0
/* 80221EF4 0021EE54  4B FF F5 E5 */	bl DBGEXIImm
/* 80221EF8 0021EE58  7C 60 00 34 */	cntlzw r0, r3
/* 80221EFC 0021EE5C  54 00 D9 7E */	srwi r0, r0, 5
/* 80221F00 0021EE60  7F 43 03 78 */	or r3, r26, r0
lbl_80221F04:
/* 80221F04 0021EE64  80 1D 00 00 */	lwz r0, 0(r29)
/* 80221F08 0021EE68  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 80221F0C 0021EE6C  40 82 FF F8 */	bne lbl_80221F04
/* 80221F10 0021EE70  80 1E 00 00 */	lwz r0, 0(r30)
/* 80221F14 0021EE74  70 00 04 05 */	andi. r0, r0, 0x405
/* 80221F18 0021EE78  2C 03 00 00 */	cmpwi r3, 0
/* 80221F1C 0021EE7C  90 1E 00 00 */	stw r0, 0(r30)
/* 80221F20 0021EE80  40 82 FF 90 */	bne lbl_80221EB0
/* 80221F24 0021EE84  80 01 00 54 */	lwz r0, 0x54(r1)
/* 80221F28 0021EE88  54 00 07 BD */	rlwinm. r0, r0, 0, 0x1e, 0x1e
/* 80221F2C 0021EE8C  40 82 FF 84 */	bne lbl_80221EB0
/* 80221F30 0021EE90  7F 83 E3 78 */	mr r3, r28
/* 80221F34 0021EE94  4B FD 70 71 */	bl OSRestoreInterrupts
/* 80221F38 0021EE98  BB 01 00 58 */	lmw r24, 0x58(r1)
/* 80221F3C 0021EE9C  38 60 00 00 */	li r3, 0
/* 80221F40 0021EEA0  80 01 00 7C */	lwz r0, 0x7c(r1)
/* 80221F44 0021EEA4  38 21 00 78 */	addi r1, r1, 0x78
/* 80221F48 0021EEA8  7C 08 03 A6 */	mtlr r0
/* 80221F4C 0021EEAC  4E 80 00 20 */	blr 

.global DBOpen
DBOpen:
/* 80221F50 0021EEB0  4E 80 00 20 */	blr 

.global DBClose
DBClose:
/* 80221F54 0021EEB4  4E 80 00 20 */	blr 
