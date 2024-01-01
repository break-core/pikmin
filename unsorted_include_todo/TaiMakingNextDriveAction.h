#ifndef _TAIMAKINGNEXTDRIVEACTION_H
#define _TAIMAKINGNEXTDRIVEACTION_H

/**
 * .obj __vt__24TaiMakingNextDriveAction, global
 * .4byte __RTTI__24TaiMakingNextDriveAction
 * .4byte 0
 * .4byte start__9TaiActionFR4Teki
 * .4byte finish__9TaiActionFR4Teki
 * .4byte act__24TaiMakingNextDriveActionFR4Teki
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
struct TaiMakingNextDriveAction : public TaiAction {
	virtual void act(Teki &);  // _10

};

#endif
