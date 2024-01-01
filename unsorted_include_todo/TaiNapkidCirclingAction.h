#ifndef _TAINAPKIDCIRCLINGACTION_H
#define _TAINAPKIDCIRCLINGACTION_H

/**
 * .obj __vt__23TaiNapkidCirclingAction, global
 * .4byte __RTTI__23TaiNapkidCirclingAction
 * .4byte 0
 * .4byte start__23TaiNapkidCirclingActionFR4Teki
 * .4byte finish__23TaiNapkidCirclingActionFR4Teki
 * .4byte act__23TaiNapkidCirclingActionFR4Teki
 * .4byte actByEvent__9TaiActionFR9TekiEvent
 * .4byte hasNextState__9TaiActionFv
*/

struct TaiAction {
	virtual void start(Teki &);            // _08
	virtual void finish(Teki &);           // _0C
	virtual void act(Teki &);              // _10
	virtual void actByEvent(TekiEvent &);  // _14
	virtual void hasNextState();           // _18
};

/**
 * @brief TODO
 */
struct TaiNapkidCirclingAction : public TaiAction {
	virtual void start(Teki &);  // _08
	virtual void finish(Teki &); // _0C
	virtual void act(Teki &);    // _10

};

#endif
