#include "TekiStrategy.h"
#include "teki.h"
#include "sysNew.h"

static char file[] = __FILE__;
static char name[] = "tekistrategy";

/*
 * --INFO--
 * Address:	........
 * Size:	00009C
 */
static void _Error(char*, ...)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000F4
 */
static void _Print(char*, ...)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	8014D1A4
 * Size:	000010
 */
TekiStrategy::TekiStrategy() { }

/*
 * --INFO--
 * Address:	8014D1B4
 * Size:	000004
 */
void TekiStrategy::start(Teki&) { }

/*
 * --INFO--
 * Address:	8014D1B8
 * Size:	000004
 */
void TekiStrategy::act(Teki&) { }

/*
 * --INFO--
 * Address:	8014D1BC
 * Size:	000004
 */
void TekiStrategy::eventPerformed(TekiEvent&) { }

/*
 * --INFO--
 * Address:	8014D1C0
 * Size:	000004
 */
void TekiStrategy::createEffect(Teki&, int) { }

/*
 * --INFO--
 * Address:	8014D1C4
 * Size:	000034
 */
void TekiStrategy::draw(Teki& teki, Graphics& gfx) { teki.drawDefault(gfx); }

/*
 * --INFO--
 * Address:	8014D1F8
 * Size:	000034
 */
void TekiStrategy::drawDebugInfo(Teki& teki, Graphics& gfx) { teki.drawTekiDebugInfoDefault(gfx); }

/*
 * --INFO--
 * Address:	8014D22C
 * Size:	000034
 */
void TekiStrategy::interact(Teki& teki, TekiInteractionKey& key) { teki.interactDefault(key); }

/*
 * --INFO--
 * Address:	8014D260
 * Size:	000004
 */
void TekiStrategy::spawnCorpseParts(Teki&) { }

/*
 * --INFO--
 * Address:	8014D264
 * Size:	00006C
 */
TekiStrategyTable::TekiStrategyTable(int count)
{
	mCount = count;
	_04    = new u32[mCount];
	for (int i = 0; i < mCount; i++) {
		_04[i] = 0;
	}
}
