#ifndef _INTERACTRELEASE_H
#define _INTERACTRELEASE_H

/**
 * .obj __vt__15InteractRelease, global
 * .4byte __RTTI__15InteractRelease
 * .4byte 0
 * .4byte actCommon__15InteractReleaseFP8Creature
 * .4byte actPiki__11InteractionFP4Piki
 * .4byte actTeki__11InteractionFP4Teki
 * .4byte actNavi__11InteractionFP4Navi
 * .4byte actBoss__11InteractionFP4Boss
 * .4byte actPellet__11InteractionFP6Pellet
 * .4byte actHinderRock__11InteractionFP10HinderRock
 * .4byte actBridge__11InteractionFP6Bridge
 * .4byte actItem__11InteractionFP12ItemCreature
*/

struct Interaction {
	virtual void actCommon(Creature *);        // _08
	virtual void actPiki(Piki *);              // _0C
	virtual void actTeki(Teki *);              // _10
	virtual void actNavi(Navi *);              // _14
	virtual void actBoss(Boss *);              // _18
	virtual void actPellet(Pellet *);          // _1C
	virtual void actHinderRock(HinderRock *);  // _20
	virtual void actBridge(Bridge *);          // _24
	virtual void actItem(ItemCreature *);      // _28
};

/**
 * @brief TODO
 */
struct InteractRelease : public Interaction {
	virtual void actCommon(Creature *);  // _08

};

#endif
