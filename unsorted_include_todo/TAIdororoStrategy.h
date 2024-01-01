#ifndef _TAIDOROROSTRATEGY_H
#define _TAIDOROROSTRATEGY_H

/**
 * .obj __vt__17TAIdororoStrategy, global
 * .4byte __RTTI__17TAIdororoStrategy
 * .4byte 0
 * .4byte start__17TAIdororoStrategyFR4Teki
 * .4byte act__17TAIdororoStrategyFR4Teki
 * .4byte eventPerformed__11YaiStrategyFR9TekiEvent
 * .4byte createEffect__17TAIdororoStrategyFR4Tekii
 * .4byte draw__17TAIdororoStrategyFR4TekiR8Graphics
 * .4byte drawDebugInfo__12TekiStrategyFR4TekiR8Graphics
 * .4byte interact__12TekiStrategyFR4TekiR18TekiInteractionKey
 * .4byte spawnCorpseParts__12TekiStrategyFR4Teki
*/

struct YaiStrategy {
	virtual void start(Teki &);                // _08
	virtual void act(Teki &);                  // _0C
	virtual void eventPerformed(TekiEvent &);  // _10
};

struct TekiStrategy {
	virtual void start(Teki &);                           // _08
	virtual void act(Teki &);                             // _0C
	virtual void _10() = 0;                               // _10
	virtual void createEffect(Teki &, int);               // _14
	virtual void draw(Teki &, Graphics &);                // _18
	virtual void drawDebugInfo(Teki &, Graphics &);       // _1C
	virtual void interact(Teki &, TekiInteractionKey &);  // _20
	virtual void spawnCorpseParts(Teki &);                // _24
};

/**
 * @brief TODO
 */
struct TAIdororoStrategy : public YaiStrategy, public TekiStrategy {
	virtual void start(Teki &);              // _08
	virtual void act(Teki &);                // _0C
	virtual void createEffect(Teki &, int);  // _14
	virtual void draw(Teki &, Graphics &);   // _18

};

#endif
