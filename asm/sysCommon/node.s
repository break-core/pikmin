.include "macros.inc"
.section .text, "ax"  # 0x80005560 - 0x80221F60
.fn add__8CoreNodeFP8CoreNode, global
/* 800405D8 0003D538  80 03 00 10 */	lwz r0, 0x10(r3)
/* 800405DC 0003D53C  28 00 00 00 */	cmplwi r0, 0
/* 800405E0 0003D540  7C 05 03 78 */	mr r5, r0
/* 800405E4 0003D544  41 82 00 20 */	beq .L_80040604
/* 800405E8 0003D548  48 00 00 08 */	b .L_800405F0
.L_800405EC:
/* 800405EC 0003D54C  7C 05 03 78 */	mr r5, r0
.L_800405F0:
/* 800405F0 0003D550  80 05 00 0C */	lwz r0, 0xc(r5)
/* 800405F4 0003D554  28 00 00 00 */	cmplwi r0, 0
/* 800405F8 0003D558  40 82 FF F4 */	bne .L_800405EC
/* 800405FC 0003D55C  90 85 00 0C */	stw r4, 0xc(r5)
/* 80040600 0003D560  48 00 00 08 */	b .L_80040608
.L_80040604:
/* 80040604 0003D564  90 83 00 10 */	stw r4, 0x10(r3)
.L_80040608:
/* 80040608 0003D568  90 64 00 08 */	stw r3, 8(r4)
/* 8004060C 0003D56C  4E 80 00 20 */	blr 
.endfn add__8CoreNodeFP8CoreNode

.fn del__8CoreNodeFv, global
/* 80040610 0003D570  80 83 00 08 */	lwz r4, 8(r3)
/* 80040614 0003D574  28 04 00 00 */	cmplwi r4, 0
/* 80040618 0003D578  4D 82 00 20 */	beqlr 
/* 8004061C 0003D57C  38 A4 00 10 */	addi r5, r4, 0x10
/* 80040620 0003D580  80 84 00 10 */	lwz r4, 0x10(r4)
/* 80040624 0003D584  38 C0 00 00 */	li r6, 0
/* 80040628 0003D588  48 00 00 4C */	b .L_80040674
.L_8004062C:
/* 8004062C 0003D58C  7C 04 18 40 */	cmplw r4, r3
/* 80040630 0003D590  40 82 00 3C */	bne .L_8004066C
/* 80040634 0003D594  28 06 00 00 */	cmplwi r6, 0
/* 80040638 0003D598  41 82 00 1C */	beq .L_80040654
/* 8004063C 0003D59C  80 84 00 0C */	lwz r4, 0xc(r4)
/* 80040640 0003D5A0  38 00 00 00 */	li r0, 0
/* 80040644 0003D5A4  90 86 00 0C */	stw r4, 0xc(r6)
/* 80040648 0003D5A8  90 03 00 0C */	stw r0, 0xc(r3)
/* 8004064C 0003D5AC  90 03 00 08 */	stw r0, 8(r3)
/* 80040650 0003D5B0  4E 80 00 20 */	blr 
.L_80040654:
/* 80040654 0003D5B4  80 84 00 0C */	lwz r4, 0xc(r4)
/* 80040658 0003D5B8  38 00 00 00 */	li r0, 0
/* 8004065C 0003D5BC  90 85 00 00 */	stw r4, 0(r5)
/* 80040660 0003D5C0  90 03 00 0C */	stw r0, 0xc(r3)
/* 80040664 0003D5C4  90 03 00 08 */	stw r0, 8(r3)
/* 80040668 0003D5C8  4E 80 00 20 */	blr 
.L_8004066C:
/* 8004066C 0003D5CC  7C 86 23 78 */	mr r6, r4
/* 80040670 0003D5D0  80 84 00 0C */	lwz r4, 0xc(r4)
.L_80040674:
/* 80040674 0003D5D4  28 04 00 00 */	cmplwi r4, 0
/* 80040678 0003D5D8  40 82 FF B4 */	bne .L_8004062C
/* 8004067C 0003D5DC  4E 80 00 20 */	blr 
.endfn del__8CoreNodeFv

.fn getChildCount__8CoreNodeFv, global
/* 80040680 0003D5E0  80 83 00 10 */	lwz r4, 0x10(r3)
/* 80040684 0003D5E4  38 60 00 00 */	li r3, 0
/* 80040688 0003D5E8  48 00 00 0C */	b .L_80040694
.L_8004068C:
/* 8004068C 0003D5EC  80 84 00 0C */	lwz r4, 0xc(r4)
/* 80040690 0003D5F0  38 63 00 01 */	addi r3, r3, 1
.L_80040694:
/* 80040694 0003D5F4  28 04 00 00 */	cmplwi r4, 0
/* 80040698 0003D5F8  40 82 FF F4 */	bne .L_8004068C
/* 8004069C 0003D5FC  4E 80 00 20 */	blr 
.endfn getChildCount__8CoreNodeFv

.fn load__8CoreNodeFPcPcUl, global
/* 800406A0 0003D600  7C 08 02 A6 */	mflr r0
/* 800406A4 0003D604  38 C5 00 00 */	addi r6, r5, 0
/* 800406A8 0003D608  90 01 00 04 */	stw r0, 4(r1)
/* 800406AC 0003D60C  38 A4 00 00 */	addi r5, r4, 0
/* 800406B0 0003D610  4C C6 31 82 */	crclr 6
/* 800406B4 0003D614  38 8D 86 68 */	addi r4, r13, lbl_803DD388@sda21
/* 800406B8 0003D618  94 21 FE E0 */	stwu r1, -0x120(r1)
/* 800406BC 0003D61C  93 E1 01 1C */	stw r31, 0x11c(r1)
/* 800406C0 0003D620  93 C1 01 18 */	stw r30, 0x118(r1)
/* 800406C4 0003D624  3B C3 00 00 */	addi r30, r3, 0
/* 800406C8 0003D628  38 61 00 18 */	addi r3, r1, 0x18
/* 800406CC 0003D62C  48 1D 5E CD */	bl sprintf
/* 800406D0 0003D630  80 6D 2D EC */	lwz r3, gsys@sda21(r13)
/* 800406D4 0003D634  38 81 00 18 */	addi r4, r1, 0x18
/* 800406D8 0003D638  38 A0 00 01 */	li r5, 1
/* 800406DC 0003D63C  81 83 01 A0 */	lwz r12, 0x1a0(r3)
/* 800406E0 0003D640  38 C0 00 01 */	li r6, 1
/* 800406E4 0003D644  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 800406E8 0003D648  7D 88 03 A6 */	mtlr r12
/* 800406EC 0003D64C  4E 80 00 21 */	blrl 
/* 800406F0 0003D650  7C 7F 1B 79 */	or. r31, r3, r3
/* 800406F4 0003D654  41 82 00 30 */	beq .L_80040724
/* 800406F8 0003D658  7F C3 F3 78 */	mr r3, r30
/* 800406FC 0003D65C  81 9E 00 00 */	lwz r12, 0(r30)
/* 80040700 0003D660  7F E4 FB 78 */	mr r4, r31
/* 80040704 0003D664  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 80040708 0003D668  7D 88 03 A6 */	mtlr r12
/* 8004070C 0003D66C  4E 80 00 21 */	blrl 
/* 80040710 0003D670  7F E3 FB 78 */	mr r3, r31
/* 80040714 0003D674  81 9F 00 04 */	lwz r12, 4(r31)
/* 80040718 0003D678  81 8C 00 4C */	lwz r12, 0x4c(r12)
/* 8004071C 0003D67C  7D 88 03 A6 */	mtlr r12
/* 80040720 0003D680  4E 80 00 21 */	blrl 
.L_80040724:
/* 80040724 0003D684  80 01 01 24 */	lwz r0, 0x124(r1)
/* 80040728 0003D688  83 E1 01 1C */	lwz r31, 0x11c(r1)
/* 8004072C 0003D68C  83 C1 01 18 */	lwz r30, 0x118(r1)
/* 80040730 0003D690  38 21 01 20 */	addi r1, r1, 0x120
/* 80040734 0003D694  7C 08 03 A6 */	mtlr r0
/* 80040738 0003D698  4E 80 00 20 */	blr 
.endfn load__8CoreNodeFPcPcUl

.fn init__4NodeFPc, global
/* 8004073C 0003D69C  38 C0 00 00 */	li r6, 0
/* 80040740 0003D6A0  90 C3 00 10 */	stw r6, 0x10(r3)
/* 80040744 0003D6A4  38 A0 00 03 */	li r5, 3
/* 80040748 0003D6A8  38 00 FF FF */	li r0, -1
/* 8004074C 0003D6AC  90 C3 00 0C */	stw r6, 0xc(r3)
/* 80040750 0003D6B0  90 C3 00 08 */	stw r6, 8(r3)
/* 80040754 0003D6B4  90 83 00 04 */	stw r4, 4(r3)
/* 80040758 0003D6B8  90 A3 00 18 */	stw r5, 0x18(r3)
/* 8004075C 0003D6BC  90 03 00 1C */	stw r0, 0x1c(r3)
/* 80040760 0003D6C0  4E 80 00 20 */	blr 
.endfn init__4NodeFPc

.fn update__4NodeFv, global
/* 80040764 0003D6C4  7C 08 02 A6 */	mflr r0
/* 80040768 0003D6C8  90 01 00 04 */	stw r0, 4(r1)
/* 8004076C 0003D6CC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80040770 0003D6D0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80040774 0003D6D4  83 E3 00 10 */	lwz r31, 0x10(r3)
/* 80040778 0003D6D8  48 00 00 3C */	b .L_800407B4
.L_8004077C:
/* 8004077C 0003D6DC  80 1F 00 18 */	lwz r0, 0x18(r31)
/* 80040780 0003D6E0  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 80040784 0003D6E4  41 82 00 2C */	beq .L_800407B0
/* 80040788 0003D6E8  7F E3 FB 78 */	mr r3, r31
/* 8004078C 0003D6EC  81 9F 00 00 */	lwz r12, 0(r31)
/* 80040790 0003D6F0  81 8C 00 1C */	lwz r12, 0x1c(r12)
/* 80040794 0003D6F4  7D 88 03 A6 */	mtlr r12
/* 80040798 0003D6F8  4E 80 00 21 */	blrl 
/* 8004079C 0003D6FC  7F E3 FB 78 */	mr r3, r31
/* 800407A0 0003D700  81 9F 00 00 */	lwz r12, 0(r31)
/* 800407A4 0003D704  81 8C 00 10 */	lwz r12, 0x10(r12)
/* 800407A8 0003D708  7D 88 03 A6 */	mtlr r12
/* 800407AC 0003D70C  4E 80 00 21 */	blrl 
.L_800407B0:
/* 800407B0 0003D710  83 FF 00 0C */	lwz r31, 0xc(r31)
.L_800407B4:
/* 800407B4 0003D714  28 1F 00 00 */	cmplwi r31, 0
/* 800407B8 0003D718  40 82 FF C4 */	bne .L_8004077C
/* 800407BC 0003D71C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800407C0 0003D720  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800407C4 0003D724  38 21 00 18 */	addi r1, r1, 0x18
/* 800407C8 0003D728  7C 08 03 A6 */	mtlr r0
/* 800407CC 0003D72C  4E 80 00 20 */	blr 
.endfn update__4NodeFv

.fn draw__4NodeFR8Graphics, global
/* 800407D0 0003D730  7C 08 02 A6 */	mflr r0
/* 800407D4 0003D734  90 01 00 04 */	stw r0, 4(r1)
/* 800407D8 0003D738  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800407DC 0003D73C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800407E0 0003D740  93 C1 00 10 */	stw r30, 0x10(r1)
/* 800407E4 0003D744  7C 9E 23 78 */	mr r30, r4
/* 800407E8 0003D748  83 E3 00 10 */	lwz r31, 0x10(r3)
/* 800407EC 0003D74C  48 00 00 20 */	b .L_8004080C
.L_800407F0:
/* 800407F0 0003D750  7F E3 FB 78 */	mr r3, r31
/* 800407F4 0003D754  81 9F 00 00 */	lwz r12, 0(r31)
/* 800407F8 0003D758  7F C4 F3 78 */	mr r4, r30
/* 800407FC 0003D75C  81 8C 00 14 */	lwz r12, 0x14(r12)
/* 80040800 0003D760  7D 88 03 A6 */	mtlr r12
/* 80040804 0003D764  4E 80 00 21 */	blrl 
/* 80040808 0003D768  83 FF 00 0C */	lwz r31, 0xc(r31)
.L_8004080C:
/* 8004080C 0003D76C  28 1F 00 00 */	cmplwi r31, 0
/* 80040810 0003D770  40 82 FF E0 */	bne .L_800407F0
/* 80040814 0003D774  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80040818 0003D778  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8004081C 0003D77C  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80040820 0003D780  38 21 00 18 */	addi r1, r1, 0x18
/* 80040824 0003D784  7C 08 03 A6 */	mtlr r0
/* 80040828 0003D788  4E 80 00 20 */	blr 
.endfn draw__4NodeFR8Graphics

.fn render__4NodeFR8Graphics, global
/* 8004082C 0003D78C  7C 08 02 A6 */	mflr r0
/* 80040830 0003D790  90 01 00 04 */	stw r0, 4(r1)
/* 80040834 0003D794  94 21 FF F8 */	stwu r1, -8(r1)
/* 80040838 0003D798  81 83 00 00 */	lwz r12, 0(r3)
/* 8004083C 0003D79C  81 8C 00 14 */	lwz r12, 0x14(r12)
/* 80040840 0003D7A0  7D 88 03 A6 */	mtlr r12
/* 80040844 0003D7A4  4E 80 00 21 */	blrl 
/* 80040848 0003D7A8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8004084C 0003D7AC  38 21 00 08 */	addi r1, r1, 8
/* 80040850 0003D7B0  7C 08 03 A6 */	mtlr r0
/* 80040854 0003D7B4  4E 80 00 20 */	blr 
.endfn render__4NodeFR8Graphics

.fn update__7SRTNodeFv, global
/* 80040858 0003D7B8  7C 08 02 A6 */	mflr r0
/* 8004085C 0003D7BC  90 01 00 04 */	stw r0, 4(r1)
/* 80040860 0003D7C0  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80040864 0003D7C4  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80040868 0003D7C8  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8004086C 0003D7CC  7C 7E 1B 78 */	mr r30, r3
/* 80040870 0003D7D0  83 E3 00 10 */	lwz r31, 0x10(r3)
/* 80040874 0003D7D4  48 00 00 40 */	b .L_800408B4
.L_80040878:
/* 80040878 0003D7D8  80 1F 00 18 */	lwz r0, 0x18(r31)
/* 8004087C 0003D7DC  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 80040880 0003D7E0  41 82 00 30 */	beq .L_800408B0
/* 80040884 0003D7E4  7F E3 FB 78 */	mr r3, r31
/* 80040888 0003D7E8  81 9F 00 00 */	lwz r12, 0(r31)
/* 8004088C 0003D7EC  38 9E 00 20 */	addi r4, r30, 0x20
/* 80040890 0003D7F0  81 8C 00 28 */	lwz r12, 0x28(r12)
/* 80040894 0003D7F4  7D 88 03 A6 */	mtlr r12
/* 80040898 0003D7F8  4E 80 00 21 */	blrl 
/* 8004089C 0003D7FC  7F E3 FB 78 */	mr r3, r31
/* 800408A0 0003D800  81 9F 00 00 */	lwz r12, 0(r31)
/* 800408A4 0003D804  81 8C 00 10 */	lwz r12, 0x10(r12)
/* 800408A8 0003D808  7D 88 03 A6 */	mtlr r12
/* 800408AC 0003D80C  4E 80 00 21 */	blrl 
.L_800408B0:
/* 800408B0 0003D810  83 FF 00 0C */	lwz r31, 0xc(r31)
.L_800408B4:
/* 800408B4 0003D814  28 1F 00 00 */	cmplwi r31, 0
/* 800408B8 0003D818  40 82 FF C0 */	bne .L_80040878
/* 800408BC 0003D81C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800408C0 0003D820  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800408C4 0003D824  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 800408C8 0003D828  38 21 00 18 */	addi r1, r1, 0x18
/* 800408CC 0003D82C  7C 08 03 A6 */	mtlr r0
/* 800408D0 0003D830  4E 80 00 20 */	blr 
.endfn update__7SRTNodeFv

.fn Del__7NodeMgrFP4Node, global
/* 800408D4 0003D834  38 00 00 01 */	li r0, 1
/* 800408D8 0003D838  28 04 00 00 */	cmplwi r4, 0
/* 800408DC 0003D83C  98 03 00 00 */	stb r0, 0(r3)
/* 800408E0 0003D840  4D 82 00 20 */	beqlr 
/* 800408E4 0003D844  80 64 00 08 */	lwz r3, 8(r4)
/* 800408E8 0003D848  28 03 00 00 */	cmplwi r3, 0
/* 800408EC 0003D84C  4D 82 00 20 */	beqlr 
/* 800408F0 0003D850  80 A3 00 10 */	lwz r5, 0x10(r3)
/* 800408F4 0003D854  38 60 00 00 */	li r3, 0
/* 800408F8 0003D858  48 00 00 34 */	b .L_8004092C
.L_800408FC:
/* 800408FC 0003D85C  7C 05 20 40 */	cmplw r5, r4
/* 80040900 0003D860  40 82 00 24 */	bne .L_80040924
/* 80040904 0003D864  28 03 00 00 */	cmplwi r3, 0
/* 80040908 0003D868  41 82 00 10 */	beq .L_80040918
/* 8004090C 0003D86C  80 05 00 0C */	lwz r0, 0xc(r5)
/* 80040910 0003D870  90 03 00 0C */	stw r0, 0xc(r3)
/* 80040914 0003D874  4E 80 00 20 */	blr 
.L_80040918:
/* 80040918 0003D878  80 05 00 0C */	lwz r0, 0xc(r5)
/* 8004091C 0003D87C  80 64 00 08 */	lwz r3, 8(r4)
/* 80040920 0003D880  90 03 00 10 */	stw r0, 0x10(r3)
.L_80040924:
/* 80040924 0003D884  7C A3 2B 78 */	mr r3, r5
/* 80040928 0003D888  80 A5 00 0C */	lwz r5, 0xc(r5)
.L_8004092C:
/* 8004092C 0003D88C  28 05 00 00 */	cmplwi r5, 0
/* 80040930 0003D890  40 82 FF CC */	bne .L_800408FC
/* 80040934 0003D894  4E 80 00 20 */	blr 
.endfn Del__7NodeMgrFP4Node

.fn __ct__7NodeMgrFv, global
/* 80040938 0003D898  3C 80 80 22 */	lis r4, __vt__5ANode@ha
/* 8004093C 0003D89C  38 04 73 8C */	addi r0, r4, __vt__5ANode@l
/* 80040940 0003D8A0  3C 80 80 22 */	lis r4, __vt__8CoreNode@ha
/* 80040944 0003D8A4  90 03 00 04 */	stw r0, 4(r3)
/* 80040948 0003D8A8  38 04 73 7C */	addi r0, r4, __vt__8CoreNode@l
/* 8004094C 0003D8AC  90 03 00 04 */	stw r0, 4(r3)
/* 80040950 0003D8B0  38 A0 00 00 */	li r5, 0
/* 80040954 0003D8B4  3C 80 80 23 */	lis r4, lbl_80228D8C@ha
/* 80040958 0003D8B8  90 A3 00 14 */	stw r5, 0x14(r3)
/* 8004095C 0003D8BC  38 04 8D 8C */	addi r0, r4, lbl_80228D8C@l
/* 80040960 0003D8C0  90 A3 00 10 */	stw r5, 0x10(r3)
/* 80040964 0003D8C4  90 A3 00 0C */	stw r5, 0xc(r3)
/* 80040968 0003D8C8  90 03 00 08 */	stw r0, 8(r3)
/* 8004096C 0003D8CC  98 A3 00 00 */	stb r5, 0(r3)
/* 80040970 0003D8D0  4E 80 00 20 */	blr 
.endfn __ct__7NodeMgrFv

.fn concat__7SRTNodeFv, weak
/* 80040974 0003D8D4  4E 80 00 20 */	blr 
.endfn concat__7SRTNodeFv

.fn concat__7SRTNodeFR8Matrix4f, weak
/* 80040978 0003D8D8  4E 80 00 20 */	blr 
.endfn concat__7SRTNodeFR8Matrix4f

.fn getModelMatrix__7SRTNodeFv, weak
/* 8004097C 0003D8DC  38 63 00 20 */	addi r3, r3, 0x20
/* 80040980 0003D8E0  4E 80 00 20 */	blr 
.endfn getModelMatrix__7SRTNodeFv

.section .data, "wa"  # 0x80222DC0 - 0x802E9640
.balign 8
.obj lbl_80228D80, local
	.asciz "node.cpp"
.endobj lbl_80228D80
.balign 4
.obj lbl_80228D8C, local
	.asciz "CoreNode"
.endobj lbl_80228D8C
.balign 4
.obj lbl_80228D98, local
	.4byte __RTTI__5ANode
	.4byte 0
	.4byte 0
.endobj lbl_80228D98
.obj lbl_80228DA4, local
	.4byte __RTTI__5ANode
	.4byte 0
	.4byte __RTTI__8CoreNode
	.4byte 0
	.4byte 0
.endobj lbl_80228DA4
.obj lbl_80228DB8, local
	.4byte __RTTI__5ANode
	.4byte 0
	.4byte __RTTI__8CoreNode
	.4byte 0
	.4byte __RTTI__4Node
	.4byte 0
	.4byte 0
.endobj lbl_80228DB8
.obj __vt__7SRTNode, global
	.4byte __RTTI__7SRTNode
	.4byte 0
	.4byte getAgeNodeType__5ANodeFv
	.4byte read__8CoreNodeFR18RandomAccessStream
	.4byte update__7SRTNodeFv
	.4byte draw__4NodeFR8Graphics
	.4byte render__4NodeFR8Graphics
	.4byte concat__7SRTNodeFv
	.4byte concat__4NodeFR3VQS
	.4byte concat__4NodeFR3SRT
	.4byte concat__7SRTNodeFR8Matrix4f
	.4byte getModelMatrix__7SRTNodeFv
.endobj __vt__7SRTNode
	.4byte 0
	.4byte 0
	.4byte 0
	.4byte 0
	.4byte 0
	.4byte 0
	.4byte 0
.obj __vt__4Node, global
	.4byte __RTTI__4Node
	.4byte 0
	.4byte getAgeNodeType__5ANodeFv
	.4byte read__8CoreNodeFR18RandomAccessStream
	.4byte update__4NodeFv
	.4byte draw__4NodeFR8Graphics
	.4byte render__4NodeFR8Graphics
	.4byte concat__4NodeFv
	.4byte concat__4NodeFR3VQS
	.4byte concat__4NodeFR3SRT
	.4byte concat__4NodeFR8Matrix4f
	.4byte getModelMatrix__4NodeFv
.endobj __vt__4Node

.section .sdata, "wa"  # 0x803DCD20 - 0x803E7820
.balign 8
.obj lbl_803DD380, local
	.asciz "Node"
.endobj lbl_803DD380
.balign 4
.obj lbl_803DD388, local
	.asciz "%s%s"
.endobj lbl_803DD388
.balign 4
.obj lbl_803DD390, local
	.asciz "SRTNode"
.endobj lbl_803DD390
.balign 4
.obj lbl_803DD398, local
	.asciz "ANode"
.endobj lbl_803DD398
.balign 4
.obj __RTTI__5ANode, local
	.4byte lbl_803DD398
	.4byte 0
.endobj __RTTI__5ANode
.obj __RTTI__8CoreNode, local
	.4byte lbl_80228D8C
	.4byte lbl_80228D98
.endobj __RTTI__8CoreNode
.obj __RTTI__4Node, local
	.4byte lbl_803DD380
	.4byte lbl_80228DA4
.endobj __RTTI__4Node
.obj __RTTI__7SRTNode, local
	.4byte lbl_803DD390
	.4byte lbl_80228DB8
.endobj __RTTI__7SRTNode

.section .sbss, "wa"
.balign 8
.obj nodeMgr, global
	.skip 4
.endobj nodeMgr
