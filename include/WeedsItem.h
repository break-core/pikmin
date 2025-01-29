#ifndef _WEEDSITEM_H
#define _WEEDSITEM_H

#include "types.h"
#include "ItemMgr.h"
#include "PikiAI.h"

/*
 * @brief TODO
 */
struct Grass {
	Grass();

	bool isAlive() { return mHealth != 0; }

	int attack()
	{
		if (mHealth != 0) {
			mHealth--;
			if (mHealth == 0) {
				return ACTOUT_Success;
			}
			return ACTOUT_Continue;
		}
		return ACTOUT_Fail;
	}

	// TODO: members
	Vector3f mPosition; // _00
	u8 _0C;             // _0C, unknown
	u8 _0D;             // _0D
	u8 mHealth;         // _0E
};

/*
 * @brief TODO
 */
struct Pebble {
	Pebble();

	bool isAlive() { return mHealth != 0; }

	int attack()
	{
		if (mHealth != 0) {
			mHealth--;
			if (mHealth == 0) {
				return ACTOUT_Success;
			}
			return ACTOUT_Continue;
		}
		return ACTOUT_Fail;
	}

	// TODO: members
	Vector3f mPosition; // _00
	u8 _0C;             // _0C, unknown
	u8 _0D;             // _0D
	u8 mHealth;         // _0E
};

/**
 * @brief TODO
 *
 * @note Size: 0x3E4.
 */
struct GrassGen : public ItemCreature {
	GrassGen(Shape*, CreatureProp*);

	virtual void startAI(int);                           // _34
	virtual f32 getSize();                               // _3C
	virtual bool isVisible() { return true; }            // _74
	virtual bool isAlive() { return mActiveGrass != 0; } // _88
	virtual bool needFlick(Creature*) { return false; }  // _94
	virtual void update();                               // _E0
	virtual void refresh(Graphics&);                     // _EC

	bool workable();
	void startWork();
	void finishWork();
	void resolve();
	void create(int, f32, int);
	void setSizeAndNum(f32, int);
	Grass* getRandomGrass();

	// _00      = VTBL
	// _00-_3C8 = ItemCreature
	int mWorkingPikis; // _3C8
	Grass* mGrass;     // _3CC
	u16 mActiveGrass;  // _3D0
	u16 _3D2;          // _3D2
	Vector3f _3D4;     // _3D4
	f32 mSize;         // _3E0
};

/**
 * @brief TODO
 *
 * @note Size: 0x3E8
 */
struct RockGen : public ItemCreature {
	RockGen(Shape*, CreatureProp*);

	virtual void startAI(int);                // _34
	virtual f32 getSize();                    // _3C
	virtual void doSave(RandomAccessStream&); // _50
	virtual void doLoad(RandomAccessStream&); // _54
	virtual bool isVisible() { return true; } // _74
	virtual bool isAlive() { return mActivePebbles != 0; }
	// _88
	virtual bool needFlick(Creature*) { return false; } // _94
	virtual void update();                              // _E0
	virtual void refresh(Graphics&);                    // _EC

	bool workable();
	void startWork();
	void finishWork();
	void resolve();
	void create(int, f32, int);
	void setSizeAndNum(f32, int);
	void killPebble();
	Pebble* getRandomPebble();

	// _00      = VTBL
	// _00-_3C8 = ItemCreature
	int mWorkingPikis;  // _3C8
	u8 _3CC;            // _3CC
	Pebble* mPebbles;   // _3D0
	u16 mActivePebbles; // _3D4
	u16 _3D6;           // _3D6
	Vector3f _3D8;      // _3D8
	f32 mSize;          // _3E4
};

/*
 * @brief TODO
 */
struct WeedsGen : public ItemCreature {
	WeedsGen(Shape*, CreatureProp*);

	virtual void startAI(int);       // _34
	virtual void update();           // _E0
	virtual void refresh(Graphics&); // _EC

	// _00      = VTBL
	// _00-_3C8 = ItemCreature
	int _3C8;           // _3C8
	Shape* _3CC;        // _3CC
	CreatureProp* _3D0; // _3D0
};

/*
 * @brief TODO
 */
struct Weed : public ItemCreature {
	Weed();

	virtual void startAI(int);                          // _34
	virtual bool isVisible();                           // _74
	virtual bool isAtari();                             // _84
	virtual bool isAlive();                             // _88
	virtual bool needFlick(Creature*) { return false; } // _94
	virtual void update();                              // _E0
	virtual void refresh(Graphics&);                    // _EC

	bool interactPullout(Creature*);

	// _00      = VTBL
	// _00-_3C8 = ItemCreature
	u16 _3C8;       // _3C8
	u16 _3CA;       // _3CA
	WeedsGen* mGen; // _3CC
};

#endif
