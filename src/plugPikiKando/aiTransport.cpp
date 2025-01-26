#include "PikiAI.h"
#include "Pellet.h"
#include "AIConstant.h"
#include "Stickers.h"
#include "MapCode.h"
#include "GoalItem.h"
#include "SoundMgr.h"
#include "zen/Math.h"
#include "DebugLog.h"

/*
 * --INFO--
 * Address:	........
 * Size:	00009C
 */
DEFINE_ERROR()

/*
 * --INFO--
 * Address:	........
 * Size:	0000F4
 */
DEFINE_PRINT("Transport")

/*
 * --INFO--
 * Address:	800AEC80
 * Size:	000290
 */
void ActTransport::turnOver()
{
	if (!isStickLeader()) {
		return;
	}

	Pellet* pel = mPellet.getPtr();
	Stickers stuckList(pel);
	Iterator iter(&stuckList);
	CI_LOOP(iter)
	{
		Creature* stuck = *iter;
		if (stuck->isPiki()) {
			Piki* piki           = static_cast<Piki*>(stuck);
			ActTransport* action = static_cast<ActTransport*>(piki->mActiveAction->getCurrAction());
			action->mState       = STATE_Wait;
			piki->endStickObject();
			piki->mPikiAnimMgr.finishMotion(action);
			iter.dec();
		}
	}

	Vector3f dir = mActor->mPosition - pel->mPosition;
	dir.normalise();
	dir.multiply(pel->getBottomRadius());
	Vector3f upNorm(0.0f, 400.0f * pel->getBottomRadius() / 20.0f, 0.0f);
	dir.CP(upNorm);
	pel->mAngularMomentum = pel->mAngularMomentum + dir;
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000A4
 */
void ActTransport::initWait()
{
	Pellet* pel = mPellet.getPtr();
	mState      = STATE_Wait;
	mActor->startLook(&pel->mPosition);
	mActor->startMotion(PaniMotionInfo(PIKIANIM_Wait), PaniMotionInfo(PIKIANIM_Wait));
	_A4 = 3.0f;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000070
 */
int ActTransport::exeWait()
{
	Pellet* pel = mPellet.getPtr();
	mActor->mTargetVelocity.set(0.0f, 0.0f, 0.0f);
	if (pel->getGroundFlag() == 0x55) {
		_40    = 0;
		mState = STATE_Unk0;
	}
	_A4 -= gsys->getFrameTime();
	if (_A4 < 0.0f) {
		_40    = 0;
		mState = STATE_Unk0;
	}

	return ACTOUT_Continue;
}

/*
 * --INFO--
 * Address:	800AEF10
 * Size:	000150
 */
bool ActTransport::isStickLeader()
{
	Pellet* pel = mPellet.getPtr();
	if (!pel) {
		return false;
	}

	Stickers stuckList(pel);
	Iterator iter(&stuckList);
	CI_LOOP(iter)
	{
		Creature* piki = *iter;
		if (piki->isPiki()) {
			return piki == mActor;
		}
	}
	return false;
}

/*
 * --INFO--
 * Address:	800AF060
 * Size:	000190
 */
f32 ActTransport::getCarriers()
{
	u32 badCompiler;
	Pellet* pel = mPellet.getPtr();
	if (pel) {
		Stickers stuckList(pel);
		u32 badCompiler2[3];
		Iterator iter(&stuckList);
		f32 carriers = 0.0f;
		CI_LOOP(iter)
		{
			Piki* piki = static_cast<Piki*>(*iter);
			if (piki->isPiki()) {
				carriers += 0.5f * piki->mHappa + 1.0f;
			}
		}
		return carriers;
	}
	return 0.0f;
}

/*
 * --INFO--
 * Address:	........
 * Size:	00001C
 */
int ActTransport::getNumStickers()
{
	Pellet* pel = mPellet.getPtr();
	if (pel) {
		return pel->_570;
	}
	return 0;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000140
 */
int ActTransport::calcNumStickers()
{
	Pellet* pel = mPellet.getPtr();
	if (pel) {
		Stickers stuckList(pel);
		Iterator iter(&stuckList);
		int count = 0;
		CI_LOOP(iter)
		{
			Creature* piki = *iter;
			if (piki->isPiki()) {
				count++;
			}
		}

		return count;
	}
	return 0;
}

/*
 * --INFO--
 * Address:	800AF1F0
 * Size:	0000F4
 */
ActTransport::ActTransport(Piki* piki)
    : Action(piki, true)
{
	setName("Transport");
	_A8 = -1;
}

/*
 * --INFO--
 * Address:	800AF2E4
 * Size:	000160
 */
Pellet* ActTransport::findPellet()
{
	Iterator iter(pelletMgr);
	f32 minDist           = 200.0f;
	Pellet* closestPellet = nullptr;
	CI_LOOP(iter)
	{
		Pellet* pellet = static_cast<Pellet*>(*iter);
		if (roughCull(pellet, mActor, minDist)) {
			continue;
		}
		if (pellet->isFree()) {
			f32 dist = qdist2(pellet, mActor);
			if (dist < minDist) {
				minDist       = dist;
				closestPellet = pellet;
			}
		}
	}

	return closestPellet;
}

/*
 * --INFO--
 * Address:	800AF444
 * Size:	000160
 */
void ActTransport::init(Creature* target)
{
	mActor->_408 = 1;
	if (!target) {
		target = findPellet();
	}

	if (target && target->mObjType == OBJTYPE_Pellet && target->isAlive()) {
		mPellet.set(static_cast<Pellet*>(target));
		if (mPellet.getPtr()->isUfoParts()) {
			mActor->_408 = 2;
		}
	} else {
		mPellet.reset();
	}

	_40    = 0;
	mState = STATE_Unk0;
	_A4    = 3.0f;
	_9C    = 0;
	_9D    = 0;
	mGoal  = nullptr;
	setSlotIndex();
	_B4 = 0;
	mActor->startMotion(PaniMotionInfo(PIKIANIM_Walk), PaniMotionInfo(PIKIANIM_Walk));
}

/*
 * --INFO--
 * Address:	800AF5A4
 * Size:	00004C
 */
void ActTransport::setSlotIndex()
{
	Pellet* pel = mPellet.getPtr();
	if (pel) {
		mSlotIndex = pel->getRandomFreeSlotIndex();
	} else {
		mSlotIndex = -1;
	}
}

/*
 * --INFO--
 * Address:	800AF5F0
 * Size:	000194
 */
void ActTransport::animationKeyUpdated(PaniAnimKeyEvent& event)
{
	switch (event.mEventType) {
	case KEY_Action0:
		_9D = 1;
		break;
	case KEY_LoopEnd:
		if (mState == STATE_Unk2) {
			Pellet* pel  = mPellet.getPtr();
			int numStick = getNumStickers();
			if (pel && numStick < pel->mConfig->mCarryMinPikis()) {
				_A0--;
				if (_A0 < 0) {
					mActor->mPikiAnimMgr.finishMotion(this);
				}
			}
		}
		break;
	case KEY_Finished:
		if (mState == STATE_Unk6) {
			_9C = 1;
			break;
		}
		if (mState == STATE_Unk2) {
			mActor->startMotion(PaniMotionInfo(PIKIANIM_PickLoop, this), PaniMotionInfo(PIKIANIM_PickLoop));
			_9D = 0;
			_A0 = int(randFloat(3.0f)) + 5;
		}
		break;
	}
}

/*
 * --INFO--
 * Address:	........
 * Size:	000064
 */
void ActTransport::initJump()
{
	mActor->mTargetVelocity.set(0.0f, 0.0f, 0.0f);
	mActor->mVelocity.set(0.0f, 0.0f, 0.0f);
	mActor->mVelocity.y = 0.5f * AIConstant::_instance->mConstants.mGravity();
	_3E                 = 0;
	mState              = STATE_Jump;
}

/*
 * --INFO--
 * Address:	800AF784
 * Size:	0004F0
 */
int ActTransport::execJump()
{
	Pellet* pel = mPellet.getPtr();
	if (mSlotIndex == -1 || !pel) {
		PRINT("JUMP FAILED * PEL IS FULL OR NO PEL\n");
		return ACTOUT_Fail;
	}

	if (!pel->isAlive()) {
		PRINT("JUMP FAILED * PEL IS NOT ALIVE\n");
		return ACTOUT_Fail;
	}

	Vector3f slotPos = pel->getSlotGlobalPos(mSlotIndex, 0.0f);
	Vector3f slotDir = slotPos - mActor->mPosition;
	f32 slotDistXZ   = speedy_sqrtf(slotDir.x * slotDir.x + slotDir.z * slotDir.z);
	f32 slotHeight   = slotDir.y;
	f32 dist         = slotDir.normalise() - pel->getCentreSize();

	if (slotDistXZ > 60.0f) {
		_40    = 0;
		mState = STATE_Unk0;
		return ACTOUT_Continue;
	}

	if (zen::Abs(slotHeight) <= 8.8f) {
		if (!pel->isSlotFree(mSlotIndex)) {
			int oldSlot = mSlotIndex;
			mSlotIndex  = pel->getNearestFreeSlotIndex(mActor->mPosition);
			if (oldSlot == mSlotIndex) {
				mActor->mEmotion = 1;
				return ACTOUT_Fail;
			}
			if (mSlotIndex == -1) {
				mActor->mEmotion = 1;
				return ACTOUT_Fail;
			}

			_40    = 0;
			mState = STATE_Unk0;
			_A4    = 3.0f;
			return ACTOUT_Continue;
		}

		mActor->mFaceDirection = roundAng(atan2f(slotDir.x, slotDir.z));
		mActor->mRotation.y    = mActor->mFaceDirection;
		mState                 = STATE_Unk2;

		mActor->startMotion(PaniMotionInfo(PIKIANIM_PickLoop, this), PaniMotionInfo(PIKIANIM_PickLoop));
		mActor->enableMotionBlend();
		PRINT("start try sound \n");
		pel->setTrySound(true);

		Vector3f pelNorm(0.0f, pel->getCylinderHeight(), 0.0f);
		_9D = 0;
		_A0 = int(randFloat(3.0f)) + 5;
		mActor->startStickObject(pel, nullptr, mSlotIndex, 0.0f);

		seSystem->playPikiSound(SEF_PIKI_HANG, mActor->mPosition);
		mActor->mTargetVelocity.set(0.0f, 0.0f, 0.0f);
		mActor->mVelocity.set(0.0f, 0.0f, 0.0f);

		int numStickers = calcNumStickers();
		int minWeight   = pel->mConfig->mCarryMinPikis();
		Vector3f carryInfoPos(pel->mPosition);
		carryInfoPos.y += 5.0f + pel->getCylinderHeight();

		pel->mLifeGauge.countOn(carryInfoPos, numStickers, minWeight);
		return ACTOUT_Continue;
	}

	if (mActor->mFloorTri) {
		_3E++;
		if (_3E > 6) {
			mActor->mVelocity.y = 0.5f * AIConstant::_instance->mConstants.mGravity();
			_3E                 = 0;
		}
	} else {
		_3E = 0;
	}

	return ACTOUT_Continue;
}

/*
 * --INFO--
 * Address:	800AFC74
 * Size:	000740
 */
bool ActTransport::gotoLiftPos()
{
	Pellet* pel = mPellet.getPtr();
	if (mSlotIndex == -1 || !pel) {
		return false;
	}
	if (!pel->isAlive()) {
		return false;
	}

	Vector3f slotPos = pel->getSlotGlobalPos(mSlotIndex, 0.0f);
	Vector3f slotDir = slotPos - mActor->mPosition;
	f32 slotDistXZ   = speedy_sqrtf(slotDir.x * slotDir.x + slotDir.z * slotDir.z);
	f32 slotHeight   = slotDir.y;
	f32 dist         = slotDir.normalise();
	f32 unused       = dist - pel->getCentreSize();

	if (slotDistXZ < 100.0f && ++_40 >= 60) {
		int oldSlot = mSlotIndex;
		mSlotIndex  = pel->getNearestFreeSlotIndex(mActor->mPosition);
		if (oldSlot == mSlotIndex) {
			mActor->mEmotion = 1;
			return false;
		}

		if (mSlotIndex == -1) {
			mActor->mEmotion = 1;
			return false;
		}

		_40    = 0;
		mState = STATE_Unk0;
		_A4    = 3.0f;
		return true;
	}

	if (slotDistXZ > 6.0f) {
		mActor->setSpeed(1.0f, slotDir);
		return true;
	}

	if (slotDistXZ < 6.0f && slotHeight >= -8.0f) {
		if (slotHeight >= 8.0f) {
			initJump();
			return true;
		}

		if (!pel->isSlotFree(mSlotIndex)) {
			mSlotIndex = pel->getNearestFreeSlotIndex(mActor->mPosition);
			if (mSlotIndex == -1) {
				mActor->mEmotion = 1;
				return false;
			}

			_40    = 0;
			mState = STATE_Unk0;
			_A4    = 3.0f;
			return true;
		}

		mActor->mFaceDirection = roundAng(atan2f(slotDir.x, slotDir.z));
		mActor->mRotation.y    = mActor->mFaceDirection;
		mState                 = STATE_Unk2;
		mActor->startMotion(PaniMotionInfo(PIKIANIM_PickLoop, this), PaniMotionInfo(PIKIANIM_PickLoop));
		mActor->enableMotionBlend();
		if (pel->isCreatureFlag(CF_IsPositionFixed)) {
			PRINT("start try sound \n");
			pel->setTrySound(true);
		} else {
			PRINT("*** OMIT try sound \n");
		}

		Vector3f pelNorm(0.0f, pel->getCylinderHeight(), 0.0f);
		_9D = 0;
		_A0 = int(randFloat(3.0f)) + 5;
		mActor->startStickObject(pel, nullptr, mSlotIndex, 0.0f);
		seSystem->playPikiSound(SEF_PIKI_HANG, mActor->mPosition);
		mActor->mTargetVelocity.set(0.0f, 0.0f, 0.0f);
		mActor->mVelocity.set(0.0f, 0.0f, 0.0f);

		int numStickers = calcNumStickers();
		int minWeight   = pel->mConfig->mCarryMinPikis();
		Vector3f carryInfoPos(pel->mPosition);
		carryInfoPos.y += 5.0f + pel->getCylinderHeight();
		pel->mLifeGauge.countOn(carryInfoPos, numStickers, minWeight);
		return true;
	}

	Vector3f centreDir = pel->getCentre() - mActor->mPosition;
	f32 centreDist     = centreDir.normalise();
	Vector3f orthoDir(slotDir);
	orthoDir.CP(centreDir);

	if (centreDist < dist) {
		Vector3f pikiMoveDir(-slotDir.z, 0.0f, slotDir.x);
		if (orthoDir.y > 0.0f) {
			pikiMoveDir.multiply(-1.0f);
		}

		mActor->setSpeed(0.2f, pikiMoveDir);
		_A4 -= gsys->getFrameTime();

		if (_A4 < 0.0f) {
			mSlotIndex = pel->getNearestFreeSlotIndex(mActor->mPosition);
			if (mSlotIndex == -1) {
				mActor->mEmotion = 1;
				return false;
			}

			_40    = 0;
			mState = STATE_Unk0;
			_A4    = 3.0f;
			return true;
		}
		return true;
	}

	mActor->setSpeed(0.2f, slotDir);
	return true;
}

/*
 * --INFO--
 * Address:	800B03B4
 * Size:	000664
 */
void ActTransport::doLift()
{
	Pellet* pel = mPellet.getPtr();
	Stickers stuckList(pel);
	int numStickers = getNumStickers();
	int count       = 0;
	Iterator iter(&stuckList);
	CI_LOOP(iter)
	{
		Creature* stuck = *iter;
		if (stuck->isPiki()) {
			Piki* piki = static_cast<Piki*>(stuck);
			if (piki->mMode == PikiMode::TransportMode) {
				ActTransport* action = static_cast<ActTransport*>(piki->mActiveAction->getCurrAction());
				if (action->_9D) {
					count++;
				}
			}
		}
	}

	if (_9D) {

		if (count < pel->mConfig->mCarryMinPikis()) {
			return;
		}

		if (SmartTurnOver && pel->getGroundFlag() != 0x55) {
			turnOver();
			return;
		}

		if (isStickLeader()) {
			decideGoal(pel);
			// this isn't in the DLL, but the asm is so dumb it has to be something like this
			// it also fixes the stack, so.
			bool landOnly       = !!doLandOnly();
			WayPoint* nearestWP = nullptr;
			WayPoint* wpA;
			WayPoint* wpB;
			bool fxCheck = false;
			if (pel->mWaterFxTimer) {
				fxCheck = true;
			}
			PRINT("** NEAREST EDGE AVOID OFF =================\n");
			routeMgr->findNearestEdgeAvoidOff(&wpA, &wpB, 'test', mActor->mPosition, landOnly, false, fxCheck);

			if (wpA && wpB) {
				PRINT("** FIND NEAREST EDGE %d and %d\n", wpA->mIndex, wpB->mIndex);
			}

			if (wpA && wpB) {
				Vector3f sepA = wpA->mPosition - mActor->mPosition;
				Vector3f sepB = wpB->mPosition - mActor->mPosition;
				if (sepA.length() > sepB.length()) {
					nearestWP = wpB;
				} else {
					nearestWP = wpA;
				}
			} else {
				PRINT("gakkari desu ...\n");
				nearestWP = routeMgr->findNearestWayPoint('test', mActor->mPosition, landOnly);
			}

			int idx       = nearestWP->mIndex;
			int goalWPIdx = mGoal->getRouteIndex();
			int maxNumWP  = routeMgr->getNumWayPoints('test') - 1;
			PRINT("PATHFINDING : %d ==> %d\n", idx, goalWPIdx);
			if (idx < 0 || idx > maxNumWP || goalWPIdx < 0 || goalWPIdx > maxNumWP) {
				ERROR("sorry");
			}
			PRINT("start find route\n");
			if (landOnly) {
				PathFinder::setMode(1);
			}

			int routePoints = mActor->findRoute(idx, goalWPIdx, false, false);
			mNumRoutePoints = routePoints;
			PRINT("numWayPoints = %d\n", routePoints);
			PRINT("done\n");
			if (routePoints == 0) {
				PRINT("SECOND TRY START !!!\n");
				routePoints     = mActor->findRoute(idx, goalWPIdx, true, false);
				mNumRoutePoints = routePoints;
				if (routePoints == 0) {
					if (landOnly) {
						PRINT("THIRD TRY START !!!\n");
						PathFinder::clearMode();
						routePoints     = mActor->findRoute(idx, goalWPIdx, true, false);
						mNumRoutePoints = routePoints;
					}

					if (routePoints == 0) {
						PRINT("end of abusan!");
						mState = STATE_Unk6;
						pel->mVelocity.set(0.0f, 0.0f, 0.0f);
						mActor->mVelocity.set(0.0f, 0.0f, 0.0f);
						mActor->mPikiAnimMgr.finishMotion(this);
						mActor->endStickObject();
						return;
					}
				}
			}
			if (landOnly) {
				PathFinder::clearMode();
			}
			_B4          = 1;
			_A8          = 0;
			mGoalWPIndex = goalWPIdx;
			pel->startPick();
			mActor->playEventSound(pel, SE_LIFT_MOVE);
			crInit();
		}

		mActor->startMotion(PaniMotionInfo(PIKIANIM_Pick), PaniMotionInfo(PIKIANIM_Pick));
		mActor->mPikiAnimMgr.getUpperAnimator().mAnimationCounter = 11.0f;
		mActor->mPikiAnimMgr.getLowerAnimator().mAnimationCounter = 11.0f;
		mActor->enableMotionBlend();
		mState = STATE_Unk3;
	} else {
		pel->getPickOffset();
	}
}

/*
 * --INFO--
 * Address:	800B0A18
 * Size:	000168
 */
bool ActTransport::useWaterRoute()
{
	Pellet* pel      = mPellet.getPtr();
	CollTriInfo* tri = pel->mFloorTri;
	if (tri && MapCode::getAttribute(tri) == ATTR_Water) {
		return true;
	}

	bool onlyBlueCarry = true;
	Stickers stuckList(pel);
	Iterator iter(&stuckList);
	CI_LOOP(iter)
	{
		Creature* stuck = *iter;
		if (stuck->isPiki()) {
			Piki* piki = static_cast<Piki*>(stuck);
			if (piki->mColor != Blue) {
				onlyBlueCarry = false;
				break;
			}
		}
	}

	return onlyBlueCarry;
}

/*
 * --INFO--
 * Address:	800B0B80
 * Size:	0008B4
 */
int ActTransport::exec()
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x170(r1)
	  stfd      f31, 0x168(r1)
	  stfd      f30, 0x160(r1)
	  stmw      r27, 0x14C(r1)
	  mr        r29, r3
	  lwz       r30, 0x18(r3)
	  cmplwi    r30, 0
	  beq-      .loc_0xE4
	  mr        r3, r30
	  lwz       r12, 0x0(r30)
	  lwz       r12, 0x74(r12)
	  mtlr      r12
	  blrl
	  rlwinm.   r0,r3,0,24,31
	  bne-      .loc_0xF8
	  lwz       r3, 0x55C(r30)
	  cmplwi    r3, 0
	  beq-      .loc_0x64
	  lwz       r0, 0x5C(r3)
	  subfic    r0, r0, 0x3
	  cntlzw    r0, r0
	  rlwinm    r0,r0,27,24,31
	  b         .loc_0x68

	.loc_0x64:
	  li        r0, 0

	.loc_0x68:
	  cmpwi     r0, 0
	  beq-      .loc_0xA8
	  mr        r3, r30
	  bl        -0x1B6BC
	  cmpwi     r3, 0x1
	  bne-      .loc_0x98
	  lwz       r3, 0xC(r29)
	  li        r0, 0x9
	  stb       r0, 0x400(r3)
	  lwz       r3, 0xC(r29)
	  stw       r30, 0x404(r3)
	  b         .loc_0xDC

	.loc_0x98:
	  lwz       r3, 0xC(r29)
	  li        r0, 0x1
	  stb       r0, 0x400(r3)
	  b         .loc_0xDC

	.loc_0xA8:
	  mr        r3, r30
	  bl        -0x1B6F4
	  cmpwi     r3, 0x1
	  bne-      .loc_0xD0
	  lwz       r3, 0xC(r29)
	  li        r0, 0x4
	  stb       r0, 0x400(r3)
	  lwz       r3, 0xC(r29)
	  stw       r30, 0x404(r3)
	  b         .loc_0xDC

	.loc_0xD0:
	  lwz       r3, 0xC(r29)
	  li        r0, 0x1
	  stb       r0, 0x400(r3)

	.loc_0xDC:
	  li        r3, 0x1
	  b         .loc_0x898

	.loc_0xE4:
	  lwz       r4, 0xC(r29)
	  li        r0, 0x7
	  li        r3, 0x1
	  stb       r0, 0x400(r4)
	  b         .loc_0x898

	.loc_0xF8:
	  lhz       r0, 0x1C(r29)
	  cmplwi    r0, 0x7
	  bgt-      .loc_0x894
	  lis       r3, 0x802B
	  addi      r3, r3, 0x5EDC
	  rlwinm    r0,r0,2,0,29
	  lwzx      r0, r3, r0
	  mtctr     r0
	  bctr
	  lwz       r3, 0xC(r29)
	  lwz       r4, 0x18(r29)
	  lfs       f0, -0x4DE0(r13)
	  stfsu     f0, 0xA4(r3)
	  lfs       f0, -0x4DDC(r13)
	  stfs      f0, 0x4(r3)
	  lfs       f0, -0x4DD8(r13)
	  stfs      f0, 0x8(r3)
	  lbz       r0, 0x439(r4)
	  cmplwi    r0, 0x55
	  bne-      .loc_0x154
	  li        r0, 0
	  sth       r0, 0x40(r29)
	  sth       r0, 0x1C(r29)

	.loc_0x154:
	  lwz       r3, 0x2DEC(r13)
	  lfs       f1, 0xA4(r29)
	  lfs       f0, 0x28C(r3)
	  fsubs     f0, f1, f0
	  stfs      f0, 0xA4(r29)
	  lfs       f1, 0xA4(r29)
	  lfs       f0, -0x7018(r2)
	  fcmpo     cr0, f1, f0
	  bge-      .loc_0x184
	  li        r0, 0
	  sth       r0, 0x40(r29)
	  sth       r0, 0x1C(r29)

	.loc_0x184:
	  li        r3, 0
	  b         .loc_0x898
	  mr        r3, r29
	  bl        -0x109C
	  rlwinm.   r0,r3,0,24,31
	  bne-      .loc_0x894
	  lwz       r0, 0x18(r29)
	  cmplwi    r0, 0
	  bne-      .loc_0x1B0
	  li        r3, 0x1
	  b         .loc_0x898

	.loc_0x1B0:
	  li        r3, 0x1
	  b         .loc_0x898
	  mr        r3, r29
	  bl        -0x15B8
	  b         .loc_0x898
	  mr        r3, r29
	  bl        -0x994
	  b         .loc_0x894
	  addi      r3, r1, 0x124
	  addi      r4, r30, 0
	  bl        -0x200D4
	  lwz       r3, 0x18(r29)
	  cmplwi    r3, 0
	  beq-      .loc_0x1F0
	  lhz       r31, 0x570(r3)
	  b         .loc_0x1F4

	.loc_0x1F0:
	  li        r31, 0

	.loc_0x1F4:
	  lwz       r3, 0x55C(r30)
	  lwz       r0, 0x7C(r3)
	  cmpw      r31, r0
	  bge-      .loc_0x26C
	  li        r0, 0x6
	  sth       r0, 0x1C(r29)
	  cmplwi    r29, 0
	  mr        r4, r29
	  lfs       f0, -0x4D70(r13)
	  stfs      f0, 0x70(r30)
	  lfs       f0, -0x4D6C(r13)
	  stfs      f0, 0x74(r30)
	  lfs       f0, -0x4D68(r13)
	  stfs      f0, 0x78(r30)
	  lwz       r3, 0xC(r29)
	  lfs       f0, -0x4D64(r13)
	  stfsu     f0, 0x70(r3)
	  lfs       f0, -0x4D60(r13)
	  stfs      f0, 0x4(r3)
	  lfs       f0, -0x4D5C(r13)
	  stfs      f0, 0x8(r3)
	  beq-      .loc_0x250
	  lwz       r4, 0x14(r29)

	.loc_0x250:
	  lwz       r3, 0xC(r29)
	  addi      r3, r3, 0x354
	  bl        0x6ECE8
	  lwz       r3, 0xC(r29)
	  bl        -0x20568
	  li        r3, 0
	  b         .loc_0x898

	.loc_0x26C:
	  xoris     r3, r31, 0x8000
	  lfd       f2, -0x6FE8(r2)
	  xoris     r0, r0, 0x8000
	  stw       r3, 0x144(r1)
	  lis       r3, 0x4330
	  lfs       f3, -0x6FB0(r2)
	  stw       r0, 0x13C(r1)
	  lwz       r4, 0xC(r29)
	  stw       r3, 0x140(r1)
	  stw       r3, 0x138(r1)
	  lfd       f1, 0x140(r1)
	  lfd       f0, 0x138(r1)
	  fsubs     f1, f1, f2
	  fsubs     f0, f0, f2
	  fdivs     f0, f1, f0
	  fmuls     f0, f3, f0
	  stfsu     f0, 0x70(r4)
	  lfs       f0, -0x4D58(r13)
	  stfs      f0, 0x4(r4)
	  lfs       f0, -0x4D54(r13)
	  stfs      f0, 0x8(r4)
	  lwz       r4, 0x18(r29)
	  cmplwi    r4, 0
	  bne-      .loc_0x2D4
	  li        r0, 0
	  b         .loc_0x3BC

	.loc_0x2D4:
	  addi      r3, r1, 0xAC
	  bl        -0x201D4
	  addi      r0, r1, 0xAC
	  stw       r0, 0xC0(r1)
	  li        r0, 0
	  addi      r3, r1, 0xBC
	  stw       r0, 0xC4(r1)
	  bl        -0x210B4
	  b         .loc_0x35C

	.loc_0x2F8:
	  lwz       r4, 0xBC(r1)
	  cmpwi     r4, -0x1
	  bne-      .loc_0x320
	  lwz       r3, 0xC0(r1)
	  li        r4, 0
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  b         .loc_0x334

	.loc_0x320:
	  lwz       r3, 0xC0(r1)
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl

	.loc_0x334:
	  lwz       r0, 0x6C(r3)
	  cmpwi     r0, 0
	  bne-      .loc_0x354
	  lwz       r0, 0xC(r29)
	  sub       r0, r0, r3
	  cntlzw    r0, r0
	  rlwinm    r0,r0,27,5,31
	  b         .loc_0x3BC

	.loc_0x354:
	  addi      r3, r1, 0xBC
	  bl        -0x21240

	.loc_0x35C:
	  lwz       r3, 0xC0(r1)
	  lwz       r4, 0xBC(r1)
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0x384
	  li        r0, 0x1
	  b         .loc_0x3B0

	.loc_0x384:
	  lwz       r3, 0xC0(r1)
	  lwz       r4, 0xBC(r1)
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  cmplwi    r3, 0
	  bne-      .loc_0x3AC
	  li        r0, 0x1
	  b         .loc_0x3B0

	.loc_0x3AC:
	  li        r0, 0

	.loc_0x3B0:
	  rlwinm.   r0,r0,0,24,31
	  beq+      .loc_0x2F8
	  li        r0, 0

	.loc_0x3BC:
	  rlwinm.   r0,r0,0,24,31
	  beq-      .loc_0x750
	  lwz       r0, 0xA8(r29)
	  cmpwi     r0, -0x1
	  beq-      .loc_0x750
	  lwz       r4, 0xB0(r29)
	  cmplwi    r4, 0
	  bne-      .loc_0x3E4
	  li        r3, 0x1
	  b         .loc_0x898

	.loc_0x3E4:
	  beq-      .loc_0x3EC
	  cmplwi    r30, 0

	.loc_0x3EC:
	  lwz       r12, 0x0(r4)
	  addi      r28, r30, 0x94
	  addi      r3, r1, 0xDC
	  lwz       r12, 0x15C(r12)
	  mtlr      r12
	  blrl
	  lfs       f1, 0xDC(r1)
	  lfs       f0, 0x0(r28)
	  lfs       f3, 0xE0(r1)
	  lfs       f2, 0x4(r28)
	  fsubs     f0, f1, f0
	  lfs       f1, 0x8(r28)
	  lfs       f4, 0xE4(r1)
	  fsubs     f2, f3, f2
	  stfs      f0, 0x118(r1)
	  fsubs     f0, f4, f1
	  stfs      f2, 0x11C(r1)
	  stfs      f0, 0x120(r1)
	  lfs       f0, 0x118(r1)
	  lfs       f1, 0x120(r1)
	  fmuls     f2, f0, f0
	  lfs       f0, -0x7018(r2)
	  fmuls     f1, f1, f1
	  fadds     f31, f2, f1
	  fcmpo     cr0, f31, f0
	  ble-      .loc_0x468
	  fsqrte    f0, f31
	  fmul      f0, f31, f0
	  frsp      f0, f0
	  stfs      f0, 0xA8(r1)
	  lfs       f31, 0xA8(r1)

	.loc_0x468:
	  lfs       f1, 0x118(r1)
	  lfs       f0, 0x11C(r1)
	  fmuls     f1, f1, f1
	  lfs       f2, 0x120(r1)
	  fmuls     f0, f0, f0
	  fmuls     f2, f2, f2
	  fadds     f0, f1, f0
	  fadds     f1, f2, f0
	  bl        -0xA33C8
	  lfs       f0, -0x7018(r2)
	  fcmpu     cr0, f0, f1
	  beq-      .loc_0x4BC
	  lfs       f0, 0x118(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x118(r1)
	  lfs       f0, 0x11C(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x11C(r1)
	  lfs       f0, 0x120(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x120(r1)

	.loc_0x4BC:
	  lfs       f0, -0x7018(r2)
	  fcmpu     cr0, f0, f1
	  bne-      .loc_0x4E0
	  lfs       f1, -0x4D50(r13)
	  lfs       f0, -0x4D4C(r13)
	  stfs      f1, 0x118(r1)
	  stfs      f0, 0x11C(r1)
	  lfs       f0, -0x4D48(r13)
	  stfs      f0, 0x120(r1)

	.loc_0x4E0:
	  li        r0, 0x1
	  stb       r0, 0xB4(r29)
	  lfs       f0, -0x6FAC(r2)
	  fcmpo     cr0, f31, f0
	  bge-      .loc_0x680
	  li        r0, 0x6
	  sth       r0, 0x1C(r29)
	  cmplwi    r29, 0
	  mr        r4, r29
	  lfs       f0, -0x4D44(r13)
	  stfs      f0, 0x70(r30)
	  lfs       f0, -0x4D40(r13)
	  stfs      f0, 0x74(r30)
	  lfs       f0, -0x4D3C(r13)
	  stfs      f0, 0x78(r30)
	  beq-      .loc_0x524
	  lwz       r4, 0x14(r29)

	.loc_0x524:
	  lwz       r3, 0xC(r29)
	  addi      r3, r3, 0x354
	  bl        0x6EA14
	  lwz       r3, 0xC(r29)
	  bl        -0x2083C
	  lwz       r3, 0xC(r29)
	  addi      r4, r30, 0
	  li        r5, 0xB9
	  bl        -0x26AD8
	  lwz       r0, 0x6C(r30)
	  cmpwi     r0, 0x34
	  bne-      .loc_0x894
	  lis       r3, 0x802B
	  lfs       f1, -0x6FD0(r2)
	  addi      r4, r3, 0x5ECC
	  addi      r28, r1, 0x124
	  addi      r3, r1, 0xFC
	  bl        0x65304
	  mr        r3, r28
	  lwz       r12, 0x0(r28)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  mr        r29, r3
	  b         .loc_0x60C

	.loc_0x588:
	  cmpwi     r29, -0x1
	  bne-      .loc_0x5AC
	  mr        r3, r28
	  lwz       r12, 0x0(r28)
	  li        r4, 0
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  b         .loc_0x5C4

	.loc_0x5AC:
	  mr        r3, r28
	  lwz       r12, 0x0(r28)
	  mr        r4, r29
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl

	.loc_0x5C4:
	  cmplwi    r3, 0
	  beq-      .loc_0x5E8
	  lwz       r0, 0x6C(r3)
	  cmpwi     r0, 0
	  bne-      .loc_0x5E8
	  bl        -0x208E0
	  cmpwi     r29, 0
	  blt-      .loc_0x5E8
	  subi      r29, r29, 0x1

	.loc_0x5E8:
	  addi      r3, r1, 0xFC
	  bl        0x6528C
	  mr        r3, r28
	  lwz       r12, 0x0(r28)
	  mr        r4, r29
	  lwz       r12, 0x10(r12)
	  mtlr      r12
	  blrl
	  mr        r29, r3

	.loc_0x60C:
	  mr        r3, r28
	  lwz       r12, 0x0(r28)
	  mr        r4, r29
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0x634
	  li        r0, 0x1
	  b         .loc_0x660

	.loc_0x634:
	  mr        r3, r28
	  lwz       r12, 0x0(r28)
	  mr        r4, r29
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  cmplwi    r3, 0
	  bne-      .loc_0x65C
	  li        r0, 0x1
	  b         .loc_0x660

	.loc_0x65C:
	  li        r0, 0

	.loc_0x660:
	  rlwinm.   r0,r0,0,24,31
	  beq+      .loc_0x588
	  addi      r28, r30, 0
	  addi      r3, r28, 0
	  bl        -0x1B7A4
	  mr        r3, r28
	  bl        -0x1B72C
	  b         .loc_0x894

	.loc_0x680:
	  lwz       r3, 0xC(r29)
	  lwz       r0, 0x504(r3)
	  cmplwi    r0, 0
	  lwz       r5, 0x3068(r13)
	  mr        r3, r29
	  lwz       r4, 0x18(r29)
	  lwz       r5, 0x68(r5)
	  lwz       r6, 0x55C(r4)
	  lfs       f2, -0x6FA8(r2)
	  lfs       f1, 0x78(r5)
	  lfs       f0, -0x6FF0(r2)
	  fmuls     f31, f2, f1
	  lwz       r28, 0x7C(r6)
	  lwz       r27, 0x8C(r6)
	  fmuls     f30, f0, f31
	  bl        -0x21DC
	  xoris     r0, r28, 0x8000
	  lfs       f2, -0x6FF4(r2)
	  stw       r0, 0x13C(r1)
	  lis       r3, 0x4330
	  xoris     r0, r27, 0x8000
	  lfd       f4, -0x6FE8(r2)
	  stw       r3, 0x138(r1)
	  lfs       f0, -0x7018(r2)
	  fadds     f5, f2, f1
	  stw       r0, 0x144(r1)
	  fsubs     f1, f31, f30
	  lfd       f2, 0x138(r1)
	  stw       r3, 0x140(r1)
	  fsubs     f3, f2, f4
	  mr        r3, r30
	  lfd       f2, 0x140(r1)
	  addi      r5, r1, 0x118
	  stfs      f0, 0x11C(r1)
	  fsubs     f3, f5, f3
	  lfs       f0, 0x118(r1)
	  fsubs     f2, f2, f4
	  rlwinm    r6,r31,0,16,31
	  fdivs     f2, f3, f2
	  fmuls     f1, f2, f1
	  fadds     f1, f30, f1
	  fmuls     f0, f0, f1
	  stfs      f0, 0x118(r1)
	  lfs       f0, 0x11C(r1)
	  fmuls     f0, f0, f1
	  stfs      f0, 0x11C(r1)
	  lfs       f0, 0x120(r1)
	  fmuls     f0, f0, f1
	  stfs      f0, 0x120(r1)
	  lwz       r4, 0xC(r29)
	  bl        -0x1B68C
	  b         .loc_0x894

	.loc_0x750:
	  lwz       r3, 0xC(r29)
	  lwz       r0, 0x184(r3)
	  cmplwi    r0, 0
	  bne-      .loc_0x894
	  li        r0, 0x6
	  sth       r0, 0x1C(r29)
	  cmplwi    r29, 0
	  mr        r4, r29
	  lfs       f0, -0x4D38(r13)
	  stfs      f0, 0x70(r30)
	  lfs       f0, -0x4D34(r13)
	  stfs      f0, 0x74(r30)
	  lfs       f0, -0x4D30(r13)
	  stfs      f0, 0x78(r30)
	  lwz       r3, 0xC(r29)
	  lfs       f0, -0x4D2C(r13)
	  stfsu     f0, 0x70(r3)
	  lfs       f0, -0x4D28(r13)
	  stfs      f0, 0x4(r3)
	  lfs       f0, -0x4D24(r13)
	  stfs      f0, 0x8(r3)
	  beq-      .loc_0x7AC
	  lwz       r4, 0x14(r29)

	.loc_0x7AC:
	  lwz       r3, 0xC(r29)
	  addi      r3, r3, 0x354
	  bl        0x6E78C
	  lwz       r3, 0xC(r29)
	  bl        -0x20AC4
	  b         .loc_0x894
	  mr        r3, r29
	  bl        0x2A98
	  b         .loc_0x898
	  mr        r3, r29
	  bl        .loc_0x8B4
	  b         .loc_0x898
	  lbz       r0, 0x9C(r29)
	  cmplwi    r0, 0
	  beq-      .loc_0x894
	  lwz       r3, 0x18(r29)
	  lwz       r4, 0x55C(r3)
	  cmplwi    r4, 0
	  beq-      .loc_0x80C
	  lwz       r0, 0x5C(r4)
	  subfic    r0, r0, 0x3
	  cntlzw    r0, r0
	  rlwinm    r0,r0,27,24,31
	  b         .loc_0x810

	.loc_0x80C:
	  li        r0, 0

	.loc_0x810:
	  cmpwi     r0, 0
	  beq-      .loc_0x850
	  bl        -0x1BE60
	  cmpwi     r3, 0x1
	  bne-      .loc_0x840
	  lwz       r3, 0xC(r29)
	  li        r0, 0x9
	  stb       r0, 0x400(r3)
	  lwz       r0, 0x18(r29)
	  lwz       r3, 0xC(r29)
	  stw       r0, 0x404(r3)
	  b         .loc_0x88C

	.loc_0x840:
	  lwz       r3, 0xC(r29)
	  li        r0, 0x1
	  stb       r0, 0x400(r3)
	  b         .loc_0x88C

	.loc_0x850:
	  bl        -0x1BE98
	  cmpwi     r3, 0x1
	  bne-      .loc_0x880
	  lwz       r3, 0xC(r29)
	  li        r0, 0x4
	  stb       r0, 0x400(r3)
	  lwz       r3, 0xC(r29)
	  stb       r0, 0x400(r3)
	  lwz       r0, 0x18(r29)
	  lwz       r3, 0xC(r29)
	  stw       r0, 0x404(r3)
	  b         .loc_0x88C

	.loc_0x880:
	  lwz       r3, 0xC(r29)
	  li        r0, 0x1
	  stb       r0, 0x400(r3)

	.loc_0x88C:
	  li        r3, 0x2
	  b         .loc_0x898

	.loc_0x894:
	  li        r3, 0

	.loc_0x898:
	  lmw       r27, 0x14C(r1)
	  lwz       r0, 0x174(r1)
	  lfd       f31, 0x168(r1)
	  lfd       f30, 0x160(r1)
	  addi      r1, r1, 0x170
	  mtlr      r0
	  blr

	.loc_0x8B4:
	*/
}

/*
 * --INFO--
 * Address:	800B1434
 * Size:	0008A8
 */
int ActTransport::moveGuruGuru()
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x1C0(r1)
	  stfd      f31, 0x1B8(r1)
	  stfd      f30, 0x1B0(r1)
	  stfd      f29, 0x1A8(r1)
	  stfd      f28, 0x1A0(r1)
	  stmw      r25, 0x184(r1)
	  mr        r31, r3
	  lwz       r30, 0x18(r3)
	  addi      r3, r1, 0x160
	  addi      r4, r30, 0
	  bl        -0x207E0
	  lwz       r3, 0x18(r31)
	  cmplwi    r3, 0
	  beq-      .loc_0x48
	  lhz       r29, 0x570(r3)
	  b         .loc_0x4C

	.loc_0x48:
	  li        r29, 0

	.loc_0x4C:
	  lwz       r3, 0x55C(r30)
	  lwz       r28, 0x7C(r3)
	  cmpw      r29, r28
	  bge-      .loc_0xC4
	  li        r0, 0x6
	  sth       r0, 0x1C(r31)
	  cmplwi    r31, 0
	  addi      r4, r31, 0
	  lfs       f0, -0x4D20(r13)
	  stfs      f0, 0x70(r30)
	  lfs       f0, -0x4D1C(r13)
	  stfs      f0, 0x74(r30)
	  lfs       f0, -0x4D18(r13)
	  stfs      f0, 0x78(r30)
	  lwz       r3, 0xC(r31)
	  lfs       f0, -0x4D14(r13)
	  stfsu     f0, 0x70(r3)
	  lfs       f0, -0x4D10(r13)
	  stfs      f0, 0x4(r3)
	  lfs       f0, -0x4D0C(r13)
	  stfs      f0, 0x8(r3)
	  beq-      .loc_0xA8
	  lwz       r4, 0x14(r31)

	.loc_0xA8:
	  lwz       r3, 0xC(r31)
	  addi      r3, r3, 0x354
	  bl        0x6E5DC
	  lwz       r3, 0xC(r31)
	  bl        -0x20C74
	  li        r3, 0
	  b         .loc_0x884

	.loc_0xC4:
	  xoris     r3, r29, 0x8000
	  lfd       f2, -0x6FE8(r2)
	  xoris     r0, r28, 0x8000
	  stw       r3, 0x17C(r1)
	  lis       r3, 0x4330
	  lfs       f3, -0x6FB0(r2)
	  stw       r0, 0x174(r1)
	  lwz       r4, 0xC(r31)
	  stw       r3, 0x178(r1)
	  stw       r3, 0x170(r1)
	  lfd       f1, 0x178(r1)
	  lfd       f0, 0x170(r1)
	  fsubs     f1, f1, f2
	  fsubs     f0, f0, f2
	  fdivs     f0, f1, f0
	  fmuls     f0, f3, f0
	  stfsu     f0, 0x70(r4)
	  lfs       f0, -0x4D08(r13)
	  stfs      f0, 0x4(r4)
	  lfs       f0, -0x4D04(r13)
	  stfs      f0, 0x8(r4)
	  lwz       r4, 0x18(r31)
	  cmplwi    r4, 0
	  bne-      .loc_0x12C
	  li        r0, 0
	  b         .loc_0x214

	.loc_0x12C:
	  addi      r3, r1, 0xD4
	  bl        -0x208E0
	  addi      r0, r1, 0xD4
	  stw       r0, 0xE8(r1)
	  li        r0, 0
	  addi      r3, r1, 0xE4
	  stw       r0, 0xEC(r1)
	  bl        -0x217C0
	  b         .loc_0x1B4

	.loc_0x150:
	  lwz       r4, 0xE4(r1)
	  cmpwi     r4, -0x1
	  bne-      .loc_0x178
	  lwz       r3, 0xE8(r1)
	  li        r4, 0
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  b         .loc_0x18C

	.loc_0x178:
	  lwz       r3, 0xE8(r1)
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl

	.loc_0x18C:
	  lwz       r0, 0x6C(r3)
	  cmpwi     r0, 0
	  bne-      .loc_0x1AC
	  lwz       r0, 0xC(r31)
	  sub       r0, r0, r3
	  cntlzw    r0, r0
	  rlwinm    r0,r0,27,5,31
	  b         .loc_0x214

	.loc_0x1AC:
	  addi      r3, r1, 0xE4
	  bl        -0x2194C

	.loc_0x1B4:
	  lwz       r3, 0xE8(r1)
	  lwz       r4, 0xE4(r1)
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0x1DC
	  li        r0, 0x1
	  b         .loc_0x208

	.loc_0x1DC:
	  lwz       r3, 0xE8(r1)
	  lwz       r4, 0xE4(r1)
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  cmplwi    r3, 0
	  bne-      .loc_0x204
	  li        r0, 0x1
	  b         .loc_0x208

	.loc_0x204:
	  li        r0, 0

	.loc_0x208:
	  rlwinm.   r0,r0,0,24,31
	  beq+      .loc_0x150
	  li        r0, 0

	.loc_0x214:
	  rlwinm.   r0,r0,0,24,31
	  beq-      .loc_0x700
	  lwz       r0, 0xA8(r31)
	  cmpwi     r0, -0x1
	  beq-      .loc_0x700
	  lwz       r4, 0xC(r31)
	  lis       r6, 0x7465
	  rlwinm    r0,r0,3,0,28
	  lwz       r3, 0x302C(r13)
	  lwz       r5, 0x2CC(r4)
	  addi      r4, r6, 0x7374
	  lwzx      r5, r5, r0
	  bl        -0x10000
	  lbz       r0, 0x38(r3)
	  mr        r26, r3
	  addi      r27, r26, 0
	  cmplwi    r0, 0
	  beq-      .loc_0x290
	  lbz       r0, 0x40(r26)
	  rlwinm.   r0,r0,0,30,30
	  bne-      .loc_0x290
	  lwz       r4, 0xA8(r31)
	  addi      r3, r31, 0
	  addi      r4, r4, 0x1
	  bl        0xCDC
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0x290
	  li        r0, 0x3
	  sth       r0, 0x1C(r31)
	  li        r3, 0
	  b         .loc_0x884

	.loc_0x290:
	  lwz       r0, 0xA8(r31)
	  li        r25, 0
	  cmpwi     r0, 0x1
	  blt-      .loc_0x2CC
	  lwz       r4, 0xC(r31)
	  lis       r6, 0x7465
	  rlwinm    r0,r0,3,0,28
	  lwz       r3, 0x302C(r13)
	  lwz       r5, 0x2CC(r4)
	  addi      r4, r6, 0x7374
	  add       r5, r5, r0
	  lwz       r5, -0x8(r5)
	  bl        -0x1007C
	  mr        r26, r3
	  b         .loc_0x2D0

	.loc_0x2CC:
	  li        r25, 0x1

	.loc_0x2D0:
	  lfs       f1, 0x0(r27)
	  lfs       f0, 0x0(r26)
	  lfs       f3, 0x4(r27)
	  lfs       f2, 0x4(r26)
	  fsubs     f0, f1, f0
	  lfs       f4, 0x8(r27)
	  lfs       f1, 0x8(r26)
	  fsubs     f2, f3, f2
	  stfs      f0, 0x154(r1)
	  fsubs     f0, f4, f1
	  stfs      f2, 0x158(r1)
	  stfs      f0, 0x15C(r1)
	  lfs       f1, 0x154(r1)
	  lfs       f0, 0x158(r1)
	  lfs       f2, 0x15C(r1)
	  fmuls     f1, f1, f1
	  fmuls     f0, f0, f0
	  fmuls     f2, f2, f2
	  fadds     f0, f1, f0
	  fadds     f1, f2, f0
	  bl        -0xA3B14
	  lfs       f0, -0x7018(r2)
	  fcmpu     cr0, f0, f1
	  beq-      .loc_0x354
	  lfs       f0, 0x154(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x154(r1)
	  lfs       f0, 0x158(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x158(r1)
	  lfs       f0, 0x15C(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x15C(r1)

	.loc_0x354:
	  lfs       f2, -0x6FA4(r2)
	  lfs       f0, -0x7018(r2)
	  fsubs     f4, f1, f2
	  fcmpo     cr0, f4, f0
	  bge-      .loc_0x36C
	  fmr       f4, f0

	.loc_0x36C:
	  rlwinm.   r0,r25,0,24,31
	  beq-      .loc_0x394
	  lwz       r3, 0x90(r31)
	  lwz       r0, 0x94(r31)
	  lfs       f29, -0x6FAC(r2)
	  stw       r3, 0x154(r1)
	  stw       r0, 0x158(r1)
	  lwz       r0, 0x98(r31)
	  stw       r0, 0x15C(r1)
	  b         .loc_0x3D4

	.loc_0x394:
	  lfs       f0, 0x154(r1)
	  lfs       f3, 0x15C(r1)
	  fmuls     f0, f0, f4
	  lfs       f1, 0x0(r26)
	  lfs       f2, 0x158(r1)
	  fmuls     f3, f3, f4
	  fadds     f0, f1, f0
	  fmuls     f1, f2, f4
	  stfs      f0, 0x154(r1)
	  lfs       f0, 0x4(r26)
	  fadds     f0, f0, f1
	  stfs      f0, 0x158(r1)
	  lfs       f0, 0x8(r26)
	  fadds     f0, f0, f3
	  stfs      f0, 0x15C(r1)
	  lfs       f29, -0x6FAC(r2)

	.loc_0x3D4:
	  lwz       r3, 0x2DEC(r13)
	  lfs       f1, -0x6FA0(r2)
	  lfs       f0, 0x28C(r3)
	  lfs       f2, 0xA4(r31)
	  fmuls     f0, f1, f0
	  fadds     f0, f2, f0
	  stfs      f0, 0xA4(r31)
	  lfs       f1, 0xA4(r31)
	  lfs       f0, -0x6F9C(r2)
	  fcmpo     cr0, f1, f0
	  ble-      .loc_0x480
	  fsubs     f0, f1, f0
	  lis       r3, 0x803A
	  subi      r27, r3, 0x2848
	  stfs      f0, 0xA4(r31)
	  lwz       r3, 0x1DC(r27)
	  lbz       r0, 0x124(r3)
	  cmplwi    r0, 0
	  bne-      .loc_0x480
	  lwz       r3, 0x2F6C(r13)
	  li        r4, 0x1C
	  addi      r3, r3, 0x54
	  bl        -0x2F39C
	  rlwinm.   r0,r3,0,24,31
	  bne-      .loc_0x480
	  lwz       r3, 0x2F6C(r13)
	  li        r4, 0x1C
	  addi      r3, r3, 0x54
	  bl        -0x2F128
	  lwz       r0, 0xC8(r30)
	  rlwinm.   r0,r0,0,12,12
	  bne-      .loc_0x474
	  lwz       r3, 0x1E8(r27)
	  li        r4, 0
	  li        r5, 0x17
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  b         .loc_0x480

	.loc_0x474:
	  addi      r3, r30, 0
	  li        r4, 0x17
	  bl        0x5B5BC

	.loc_0x480:
	  lfs       f31, 0x158(r1)
	  lfs       f2, 0x98(r30)
	  lfs       f1, 0x154(r1)
	  lfs       f0, 0x94(r30)
	  fsubs     f2, f31, f2
	  lfs       f30, 0x15C(r1)
	  fsubs     f4, f1, f0
	  lfs       f0, 0x9C(r30)
	  fmuls     f1, f2, f2
	  fsubs     f3, f30, f0
	  lfs       f0, -0x7018(r2)
	  fmuls     f2, f4, f4
	  fmuls     f3, f3, f3
	  fadds     f1, f2, f1
	  fadds     f4, f3, f1
	  fcmpo     cr0, f4, f0
	  ble-      .loc_0x51C
	  fsqrte    f1, f4
	  lfd       f3, -0x7008(r2)
	  lfd       f2, -0x7000(r2)
	  fmul      f0, f1, f1
	  fmul      f1, f3, f1
	  fmul      f0, f4, f0
	  fsub      f0, f2, f0
	  fmul      f1, f1, f0
	  fmul      f0, f1, f1
	  fmul      f1, f3, f1
	  fmul      f0, f4, f0
	  fsub      f0, f2, f0
	  fmul      f1, f1, f0
	  fmul      f0, f1, f1
	  fmul      f1, f3, f1
	  fmul      f0, f4, f0
	  fsub      f0, f2, f0
	  fmul      f0, f1, f0
	  fmul      f0, f4, f0
	  frsp      f0, f0
	  stfs      f0, 0x74(r1)
	  lfs       f4, 0x74(r1)

	.loc_0x51C:
	  lfs       f0, -0x6F98(r2)
	  fcmpo     cr0, f4, f0
	  ble-      .loc_0x538
	  mr        r3, r31
	  bl        -0x15AC
	  li        r3, 0
	  b         .loc_0x884

	.loc_0x538:
	  lfs       f1, 0xA4(r31)
	  bl        0x16A1E4
	  fmr       f28, f1
	  lfs       f1, 0xA4(r31)
	  bl        0x16A36C
	  stfs      f1, 0x134(r1)
	  mr        r4, r30
	  lfs       f0, -0x4D00(r13)
	  addi      r3, r1, 0xFC
	  stfs      f0, 0x138(r1)
	  stfs      f28, 0x13C(r1)
	  lfs       f0, 0x134(r1)
	  fmuls     f0, f0, f29
	  stfs      f0, 0x134(r1)
	  lfs       f0, 0x138(r1)
	  fmuls     f0, f0, f29
	  stfs      f0, 0x138(r1)
	  lfs       f0, 0x13C(r1)
	  fmuls     f0, f0, f29
	  stfs      f0, 0x13C(r1)
	  lfs       f1, 0x134(r1)
	  lfs       f0, 0x154(r1)
	  fadds     f0, f1, f0
	  stfs      f0, 0x134(r1)
	  lfs       f0, 0x138(r1)
	  fadds     f0, f0, f31
	  stfs      f0, 0x138(r1)
	  lfs       f0, 0x13C(r1)
	  fadds     f0, f0, f30
	  stfs      f0, 0x13C(r1)
	  lwz       r12, 0x0(r30)
	  lwz       r12, 0x58(r12)
	  mtlr      r12
	  blrl
	  lfs       f1, 0x134(r1)
	  lfs       f0, 0xFC(r1)
	  lfs       f3, 0x138(r1)
	  lfs       f2, 0x100(r1)
	  fsubs     f0, f1, f0
	  lfs       f4, 0x13C(r1)
	  lfs       f1, 0x104(r1)
	  fsubs     f2, f3, f2
	  stfs      f0, 0x134(r1)
	  fsubs     f0, f4, f1
	  stfs      f2, 0x138(r1)
	  stfs      f0, 0x13C(r1)
	  lfs       f1, 0x134(r1)
	  lfs       f0, 0x138(r1)
	  lfs       f2, 0x13C(r1)
	  fmuls     f1, f1, f1
	  fmuls     f0, f0, f0
	  fmuls     f2, f2, f2
	  fadds     f0, f1, f0
	  fadds     f1, f2, f0
	  bl        -0xA3E04
	  lfs       f0, -0x7018(r2)
	  fcmpu     cr0, f0, f1
	  beq-      .loc_0x644
	  lfs       f0, 0x134(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x134(r1)
	  lfs       f0, 0x138(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x138(r1)
	  lfs       f0, 0x13C(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x13C(r1)

	.loc_0x644:
	  lwz       r4, 0x3068(r13)
	  mr        r3, r31
	  lfs       f2, -0x6FA8(r2)
	  lwz       r4, 0x68(r4)
	  lfs       f0, -0x6FF0(r2)
	  lfs       f1, 0x78(r4)
	  fmuls     f28, f2, f1
	  fmuls     f29, f0, f28
	  bl        -0x2A38
	  lwz       r3, 0x55C(r30)
	  xoris     r0, r28, 0x8000
	  lfs       f0, -0x6FF4(r2)
	  lis       r4, 0x4330
	  stw       r0, 0x174(r1)
	  lwz       r0, 0x8C(r3)
	  fadds     f6, f0, f1
	  stw       r4, 0x170(r1)
	  fsubs     f2, f28, f29
	  xoris     r0, r0, 0x8000
	  stw       r0, 0x17C(r1)
	  lfd       f5, -0x6FE8(r2)
	  mr        r3, r30
	  lfd       f0, 0x170(r1)
	  addi      r5, r1, 0x134
	  stw       r4, 0x178(r1)
	  fsubs     f4, f0, f5
	  lfs       f1, -0x6FF0(r2)
	  lfd       f3, 0x178(r1)
	  rlwinm    r6,r29,0,16,31
	  lfs       f0, 0x134(r1)
	  fsubs     f4, f6, f4
	  fsubs     f3, f3, f5
	  fdivs     f3, f4, f3
	  fmuls     f2, f3, f2
	  fadds     f2, f29, f2
	  fmuls     f2, f2, f1
	  fmuls     f0, f0, f2
	  stfs      f0, 0x134(r1)
	  lfs       f0, 0x138(r1)
	  fmuls     f0, f0, f2
	  stfs      f0, 0x138(r1)
	  lfs       f0, 0x13C(r1)
	  fmuls     f0, f0, f2
	  stfs      f0, 0x13C(r1)
	  lwz       r4, 0xC(r31)
	  bl        -0x1BEF0
	  b         .loc_0x880

	.loc_0x700:
	  lwz       r4, 0x18(r31)
	  cmplwi    r4, 0
	  bne-      .loc_0x714
	  li        r0, 0
	  b         .loc_0x7FC

	.loc_0x714:
	  addi      r3, r1, 0x8C
	  bl        -0x20EC8
	  addi      r0, r1, 0x8C
	  stw       r0, 0xA0(r1)
	  li        r0, 0
	  addi      r3, r1, 0x9C
	  stw       r0, 0xA4(r1)
	  bl        -0x21DA8
	  b         .loc_0x79C

	.loc_0x738:
	  lwz       r4, 0x9C(r1)
	  cmpwi     r4, -0x1
	  bne-      .loc_0x760
	  lwz       r3, 0xA0(r1)
	  li        r4, 0
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  b         .loc_0x774

	.loc_0x760:
	  lwz       r3, 0xA0(r1)
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl

	.loc_0x774:
	  lwz       r0, 0x6C(r3)
	  cmpwi     r0, 0
	  bne-      .loc_0x794
	  lwz       r0, 0xC(r31)
	  sub       r0, r0, r3
	  cntlzw    r0, r0
	  rlwinm    r0,r0,27,5,31
	  b         .loc_0x7FC

	.loc_0x794:
	  addi      r3, r1, 0x9C
	  bl        -0x21F34

	.loc_0x79C:
	  lwz       r3, 0xA0(r1)
	  lwz       r4, 0x9C(r1)
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0x7C4
	  li        r0, 0x1
	  b         .loc_0x7F0

	.loc_0x7C4:
	  lwz       r3, 0xA0(r1)
	  lwz       r4, 0x9C(r1)
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  cmplwi    r3, 0
	  bne-      .loc_0x7EC
	  li        r0, 0x1
	  b         .loc_0x7F0

	.loc_0x7EC:
	  li        r0, 0

	.loc_0x7F0:
	  rlwinm.   r0,r0,0,24,31
	  beq+      .loc_0x738
	  li        r0, 0

	.loc_0x7FC:
	  rlwinm.   r0,r0,0,24,31
	  beq-      .loc_0x810
	  lwz       r0, 0xA8(r31)
	  cmpwi     r0, -0x1
	  beq-      .loc_0x820

	.loc_0x810:
	  lwz       r3, 0xC(r31)
	  lwz       r0, 0x184(r3)
	  cmplwi    r0, 0
	  bne-      .loc_0x880

	.loc_0x820:
	  li        r0, 0x6
	  sth       r0, 0x1C(r31)
	  cmplwi    r31, 0
	  addi      r4, r31, 0
	  lfs       f0, -0x4CFC(r13)
	  stfs      f0, 0x70(r30)
	  lfs       f0, -0x4CF8(r13)
	  stfs      f0, 0x74(r30)
	  lfs       f0, -0x4CF4(r13)
	  stfs      f0, 0x78(r30)
	  lwz       r3, 0xC(r31)
	  lfs       f0, -0x4CF0(r13)
	  stfsu     f0, 0x70(r3)
	  lfs       f0, -0x4CEC(r13)
	  stfs      f0, 0x4(r3)
	  lfs       f0, -0x4CE8(r13)
	  stfs      f0, 0x8(r3)
	  beq-      .loc_0x86C
	  lwz       r4, 0x14(r31)

	.loc_0x86C:
	  lwz       r3, 0xC(r31)
	  addi      r3, r3, 0x354
	  bl        0x6DE18
	  lwz       r3, 0xC(r31)
	  bl        -0x21438

	.loc_0x880:
	  li        r3, 0

	.loc_0x884:
	  lmw       r25, 0x184(r1)
	  lwz       r0, 0x1C4(r1)
	  lfd       f31, 0x1B8(r1)
	  lfd       f30, 0x1B0(r1)
	  lfd       f29, 0x1A8(r1)
	  lfd       f28, 0x1A0(r1)
	  addi      r1, r1, 0x1C0
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	800B1CDC
 * Size:	000318
 */
void ActTransport::decideGoal(Creature*)
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0xB8(r1)
	  stmw      r26, 0xA0(r1)
	  mr        r26, r3
	  lwz       r3, 0x18(r3)
	  lwz       r3, 0x55C(r3)
	  lwz       r0, 0x5C(r3)
	  cmpwi     r0, 0x3
	  bne-      .loc_0x44
	  lwz       r3, 0x30AC(r13)
	  bl        0x40F30
	  stw       r3, 0xB0(r26)
	  lwz       r0, 0xB0(r26)
	  lwz       r3, 0x18(r26)
	  stw       r0, 0x458(r3)
	  b         .loc_0x304

	.loc_0x44:
	  lis       r3, 0x803A
	  subi      r3, r3, 0x24E0
	  lwz       r3, 0x230(r3)
	  li        r0, 0
	  addi      r28, r1, 0x6C
	  stw       r0, 0x6C(r1)
	  subfic    r3, r3, 0x1
	  cntlzw    r3, r3
	  stw       r0, 0x70(r1)
	  rlwinm    r31,r3,27,5,31
	  addi      r3, r1, 0x50
	  stw       r0, 0x74(r1)
	  li        r27, 0
	  bl        -0x210D0
	  addi      r30, r1, 0x50
	  addi      r3, r30, 0
	  lwz       r12, 0x0(r30)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  addi      r29, r3, 0
	  rlwinm    r31,r31,0,24,31
	  b         .loc_0x184

	.loc_0xA0:
	  cmpwi     r29, -0x1
	  bne-      .loc_0xC4
	  mr        r3, r30
	  lwz       r12, 0x0(r30)
	  li        r4, 0
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  b         .loc_0xDC

	.loc_0xC4:
	  mr        r3, r30
	  lwz       r12, 0x0(r30)
	  mr        r4, r29
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl

	.loc_0xDC:
	  lwz       r0, 0x6C(r3)
	  cmpwi     r0, 0
	  bne-      .loc_0x168
	  cmpwi     r29, -0x1
	  bne-      .loc_0x10C
	  mr        r3, r30
	  lwz       r12, 0x0(r30)
	  li        r4, 0
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  b         .loc_0x124

	.loc_0x10C:
	  mr        r3, r30
	  lwz       r12, 0x0(r30)
	  mr        r4, r29
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl

	.loc_0x124:
	  cmplwi    r31, 0
	  bne-      .loc_0x144
	  lhz       r0, 0x510(r3)
	  rlwinm    r4,r0,2,0,29
	  lwzx      r3, r28, r4
	  addi      r0, r3, 0x1
	  stwx      r0, r28, r4
	  b         .loc_0x168

	.loc_0x144:
	  lhz       r0, 0x510(r3)
	  cmpwi     r0, 0x2
	  bne-      .loc_0x158
	  lwz       r3, 0x504(r3)
	  lwz       r0, 0x92C(r3)

	.loc_0x158:
	  rlwinm    r4,r0,2,0,29
	  lwzx      r3, r28, r4
	  addi      r0, r3, 0x1
	  stwx      r0, r28, r4

	.loc_0x168:
	  mr        r3, r30
	  lwz       r12, 0x0(r30)
	  mr        r4, r29
	  lwz       r12, 0x10(r12)
	  mtlr      r12
	  blrl
	  mr        r29, r3

	.loc_0x184:
	  mr        r3, r30
	  lwz       r12, 0x0(r30)
	  mr        r4, r29
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0x1AC
	  li        r0, 0x1
	  b         .loc_0x1D8

	.loc_0x1AC:
	  mr        r3, r30
	  lwz       r12, 0x0(r30)
	  mr        r4, r29
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  cmplwi    r3, 0
	  bne-      .loc_0x1D4
	  li        r0, 0x1
	  b         .loc_0x1D8

	.loc_0x1D4:
	  li        r0, 0

	.loc_0x1D8:
	  rlwinm.   r0,r0,0,24,31
	  beq+      .loc_0xA0
	  lwz       r0, 0x6C(r1)
	  li        r6, -0x1
	  cmpw      r0, r6
	  ble-      .loc_0x1F4
	  mr        r6, r0

	.loc_0x1F4:
	  addi      r3, r28, 0x4
	  lwz       r0, 0x4(r28)
	  cmpw      r0, r6
	  ble-      .loc_0x208
	  mr        r6, r0

	.loc_0x208:
	  lwz       r0, 0x4(r3)
	  cmpw      r0, r6
	  ble-      .loc_0x218
	  mr        r6, r0

	.loc_0x218:
	  lwz       r0, 0x6C(r1)
	  addi      r3, r1, 0x60
	  li        r5, 0
	  cmpw      r6, r0
	  bne-      .loc_0x23C
	  li        r0, 0
	  rlwinm    r0,r0,2,0,29
	  stwx      r5, r3, r0
	  li        r27, 0x1

	.loc_0x23C:
	  addi      r4, r28, 0x4
	  lwz       r0, 0x4(r28)
	  li        r5, 0x1
	  cmpw      r6, r0
	  bne-      .loc_0x25C
	  rlwinm    r0,r27,2,0,29
	  stwx      r5, r3, r0
	  addi      r27, r27, 0x1

	.loc_0x25C:
	  lwz       r0, 0x4(r4)
	  li        r5, 0x2
	  cmpw      r6, r0
	  bne-      .loc_0x278
	  rlwinm    r0,r27,2,0,29
	  stwx      r5, r3, r0
	  addi      r27, r27, 0x1

	.loc_0x278:
	  bl        0x16611C
	  xoris     r0, r3, 0x8000
	  lfd       f3, -0x6FE8(r2)
	  stw       r0, 0x9C(r1)
	  lis       r3, 0x4330
	  xoris     r0, r27, 0x8000
	  lfs       f0, -0x6FDC(r2)
	  stw       r3, 0x98(r1)
	  lfs       f1, -0x6FF4(r2)
	  lfd       f2, 0x98(r1)
	  stw       r0, 0x94(r1)
	  fsubs     f2, f2, f3
	  stw       r3, 0x90(r1)
	  fdivs     f2, f2, f0
	  lfd       f0, 0x90(r1)
	  fmuls     f1, f1, f2
	  fsubs     f0, f0, f3
	  fmuls     f0, f0, f1
	  fctiwz    f0, f0
	  stfd      f0, 0x80(r1)
	  lwz       r0, 0x84(r1)
	  stfd      f0, 0x88(r1)
	  cmpw      r0, r27
	  lwz       r0, 0x8C(r1)
	  blt-      .loc_0x2E0
	  li        r0, 0

	.loc_0x2E0:
	  rlwinm    r0,r0,2,0,29
	  lwz       r3, 0x30AC(r13)
	  addi      r4, r1, 0x60
	  lwzx      r4, r4, r0
	  bl        0x409EC
	  stw       r3, 0xB0(r26)
	  lwz       r0, 0xB0(r26)
	  lwz       r3, 0x18(r26)
	  stw       r0, 0x458(r3)

	.loc_0x304:
	  lmw       r26, 0xA0(r1)
	  lwz       r0, 0xBC(r1)
	  addi      r1, r1, 0xB8
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	800B1FF4
 * Size:	0001B8
 */
void ActTransport::cleanup()
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x68(r1)
	  stmw      r27, 0x54(r1)
	  mr        r31, r3
	  lwz       r3, 0xC(r3)
	  bl        -0x21794
	  lwz       r29, 0x18(r31)
	  cmplwi    r29, 0
	  addi      r28, r29, 0
	  beq-      .loc_0x18C
	  mr        r4, r29
	  beq-      .loc_0x10C
	  addi      r3, r1, 0x20
	  bl        -0x213A8
	  addi      r0, r1, 0x20
	  stw       r0, 0x34(r1)
	  li        r30, 0
	  addi      r3, r1, 0x30
	  stw       r30, 0x38(r1)
	  bl        -0x22288
	  b         .loc_0xAC

	.loc_0x58:
	  lwz       r4, 0x30(r1)
	  cmpwi     r4, -0x1
	  bne-      .loc_0x80
	  lwz       r3, 0x34(r1)
	  li        r4, 0
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  b         .loc_0x94

	.loc_0x80:
	  lwz       r3, 0x34(r1)
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl

	.loc_0x94:
	  lwz       r0, 0x6C(r3)
	  cmpwi     r0, 0
	  bne-      .loc_0xA4
	  addi      r30, r30, 0x1

	.loc_0xA4:
	  addi      r3, r1, 0x30
	  bl        -0x22404

	.loc_0xAC:
	  lwz       r3, 0x34(r1)
	  lwz       r4, 0x30(r1)
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0xD4
	  li        r0, 0x1
	  b         .loc_0x100

	.loc_0xD4:
	  lwz       r3, 0x34(r1)
	  lwz       r4, 0x30(r1)
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  cmplwi    r3, 0
	  bne-      .loc_0xFC
	  li        r0, 0x1
	  b         .loc_0x100

	.loc_0xFC:
	  li        r0, 0

	.loc_0x100:
	  rlwinm.   r0,r0,0,24,31
	  beq+      .loc_0x58
	  b         .loc_0x110

	.loc_0x10C:
	  li        r30, 0

	.loc_0x110:
	  lwz       r3, 0x55C(r29)
	  cmpwi     r30, 0
	  lwz       r27, 0x7C(r3)
	  ble-      .loc_0x178
	  lfs       f0, 0x94(r29)
	  mr        r3, r28
	  stfs      f0, 0x40(r1)
	  lfs       f0, 0x98(r29)
	  stfs      f0, 0x44(r1)
	  lfs       f0, 0x9C(r29)
	  stfs      f0, 0x48(r1)
	  lwz       r12, 0x0(r28)
	  lwz       r12, 0x44(r12)
	  mtlr      r12
	  blrl
	  lfs       f2, -0x6FD0(r2)
	  mr        r5, r30
	  lfs       f0, 0x44(r1)
	  mr        r6, r27
	  fadds     f1, f2, f1
	  addi      r3, r28, 0x1E0
	  addi      r4, r1, 0x40
	  fadds     f0, f0, f1
	  stfs      f0, 0x44(r1)
	  bl        -0x551F8
	  b         .loc_0x18C

	.loc_0x178:
	  addi      r3, r28, 0x1E0
	  bl        -0x550BC
	  addi      r3, r28, 0
	  li        r4, 0
	  bl        -0x1CB50

	.loc_0x18C:
	  lwz       r3, 0x18(r31)
	  cmplwi    r3, 0
	  beq-      .loc_0x1A4
	  bl        0x321E0
	  li        r0, 0
	  stw       r0, 0x18(r31)

	.loc_0x1A4:
	  lmw       r27, 0x54(r1)
	  lwz       r0, 0x6C(r1)
	  addi      r1, r1, 0x68
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	800B21AC
 * Size:	0001D8
 */
Vector3f ActTransport::crGetPoint(int)
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x88(r1)
	  stfd      f31, 0x80(r1)
	  stw       r31, 0x7C(r1)
	  addi      r31, r5, 0
	  stw       r30, 0x78(r1)
	  mr        r30, r4
	  stw       r29, 0x74(r1)
	  addi      r29, r3, 0
	  lwz       r0, 0xB0(r4)
	  cmplwi    r0, 0
	  bne-      .loc_0x40
	  lwz       r4, 0x18(r30)
	  mr        r3, r30
	  bl        -0x50C

	.loc_0x40:
	  cmpwi     r31, 0
	  bge-      .loc_0x64
	  lfs       f0, 0x7C(r30)
	  stfs      f0, 0x0(r29)
	  lfs       f0, 0x80(r30)
	  stfs      f0, 0x4(r29)
	  lfs       f0, 0x84(r30)
	  stfs      f0, 0x8(r29)
	  b         .loc_0x1B8

	.loc_0x64:
	  lhz       r0, 0x3C(r30)
	  cmpw      r31, r0
	  blt-      .loc_0x8C
	  lwz       r4, 0xB0(r30)
	  mr        r3, r29
	  lwz       r12, 0x0(r4)
	  lwz       r12, 0x15C(r12)
	  mtlr      r12
	  blrl
	  b         .loc_0x1B8

	.loc_0x8C:
	  lwz       r4, 0xC(r30)
	  lis       r6, 0x7465
	  rlwinm    r0,r31,3,0,28
	  lwz       r3, 0x302C(r13)
	  lwz       r5, 0x2CC(r4)
	  addi      r4, r6, 0x7374
	  lwzx      r5, r5, r0
	  bl        -0x10BDC
	  mr.       r31, r3
	  lwz       r4, 0xB0(r30)
	  addi      r3, r1, 0x48
	  lwz       r12, 0x0(r4)
	  lwz       r12, 0x15C(r12)
	  mtlr      r12
	  blrl
	  lfs       f3, 0x4(r31)
	  lfs       f2, 0x4C(r1)
	  lfs       f1, 0x0(r31)
	  lfs       f0, 0x48(r1)
	  fsubs     f3, f3, f2
	  lfs       f2, 0x8(r31)
	  fsubs     f4, f1, f0
	  lfs       f0, 0x50(r1)
	  fmuls     f1, f3, f3
	  fsubs     f3, f2, f0
	  lfs       f0, -0x7018(r2)
	  fmuls     f2, f4, f4
	  fmuls     f3, f3, f3
	  fadds     f1, f2, f1
	  fadds     f31, f3, f1
	  fcmpo     cr0, f31, f0
	  ble-      .loc_0x164
	  fsqrte    f1, f31
	  lfd       f3, -0x7008(r2)
	  lfd       f2, -0x7000(r2)
	  fmul      f0, f1, f1
	  fmul      f1, f3, f1
	  fmul      f0, f31, f0
	  fsub      f0, f2, f0
	  fmul      f1, f1, f0
	  fmul      f0, f1, f1
	  fmul      f1, f3, f1
	  fmul      f0, f31, f0
	  fsub      f0, f2, f0
	  fmul      f1, f1, f0
	  fmul      f0, f1, f1
	  fmul      f1, f3, f1
	  fmul      f0, f31, f0
	  fsub      f0, f2, f0
	  fmul      f0, f1, f0
	  fmul      f0, f31, f0
	  frsp      f0, f0
	  stfs      f0, 0x44(r1)
	  lfs       f31, 0x44(r1)

	.loc_0x164:
	  lwz       r3, 0xB0(r30)
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x160(r12)
	  mtlr      r12
	  blrl
	  fcmpo     cr0, f31, f1
	  cror      2, 0, 0x2
	  bne-      .loc_0x1A0
	  lwz       r4, 0xB0(r30)
	  mr        r3, r29
	  lwz       r12, 0x0(r4)
	  lwz       r12, 0x15C(r12)
	  mtlr      r12
	  blrl
	  b         .loc_0x1B8

	.loc_0x1A0:
	  lfs       f0, 0x0(r31)
	  stfs      f0, 0x0(r29)
	  lfs       f0, 0x4(r31)
	  stfs      f0, 0x4(r29)
	  lfs       f0, 0x8(r31)
	  stfs      f0, 0x8(r29)

	.loc_0x1B8:
	  lwz       r0, 0x8C(r1)
	  lfd       f31, 0x80(r1)
	  lwz       r31, 0x7C(r1)
	  lwz       r30, 0x78(r1)
	  lwz       r29, 0x74(r1)
	  addi      r1, r1, 0x88
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	800B2384
 * Size:	00008C
 */
bool ActTransport::crPointOpen(int)
{
	/*
	.loc_0x0:
	  mflr      r0
	  cmpwi     r4, 0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x18(r1)
	  stw       r31, 0x14(r1)
	  addi      r31, r3, 0
	  blt-      .loc_0x28
	  lhz       r0, 0x3C(r31)
	  cmpw      r4, r0
	  blt-      .loc_0x30

	.loc_0x28:
	  li        r3, 0x1
	  b         .loc_0x78

	.loc_0x30:
	  lwz       r5, 0xC(r31)
	  lis       r6, 0x7465
	  rlwinm    r0,r4,3,0,28
	  lwz       r3, 0x302C(r13)
	  lwz       r5, 0x2CC(r5)
	  addi      r4, r6, 0x7374
	  lwzx      r5, r5, r0
	  bl        -0x10D58
	  cmplwi    r3, 0
	  lbz       r0, 0x38(r3)
	  li        r4, 0
	  cmplwi    r0, 0
	  beq-      .loc_0x74
	  lbz       r0, 0x40(r3)
	  rlwinm.   r0,r0,0,30,30
	  bne-      .loc_0x74
	  li        r4, 0x1

	.loc_0x74:
	  mr        r3, r4

	.loc_0x78:
	  lwz       r0, 0x1C(r1)
	  lwz       r31, 0x14(r1)
	  addi      r1, r1, 0x18
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	........
 * Size:	000078
 */
f32 ActTransport::crGetRadius(int)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	800B2410
 * Size:	000514
 */
void ActTransport::crInit()
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  li        r0, -0x1
	  stwu      r1, -0x1E8(r1)
	  stfd      f31, 0x1E0(r1)
	  stfd      f30, 0x1D8(r1)
	  stfd      f29, 0x1D0(r1)
	  stfd      f28, 0x1C8(r1)
	  stfd      f27, 0x1C0(r1)
	  stfd      f26, 0x1B8(r1)
	  stfd      f25, 0x1B0(r1)
	  stmw      r27, 0x19C(r1)
	  mr        r30, r3
	  addi      r4, r30, 0
	  lwz       r31, 0x18(r3)
	  stw       r0, 0x44(r3)
	  addi      r3, r1, 0x100
	  lwz       r5, 0x94(r31)
	  lwz       r0, 0x98(r31)
	  stw       r5, 0x7C(r30)
	  stw       r0, 0x80(r30)
	  lwz       r0, 0x9C(r31)
	  stw       r0, 0x84(r30)
	  lwz       r5, 0x44(r30)
	  addi      r5, r5, 0x1
	  bl        -0x2C8
	  lwz       r5, 0x44(r30)
	  mr        r4, r30
	  lfs       f30, 0x100(r1)
	  addi      r3, r1, 0xF4
	  lfs       f31, 0x104(r1)
	  lfs       f28, 0x108(r1)
	  addi      r5, r5, 0x2
	  bl        -0x2E8
	  lwz       r3, 0x44(r30)
	  lfs       f27, 0xF4(r1)
	  addic.    r5, r3, 0x2
	  lfs       f26, 0xF8(r1)
	  lfs       f25, 0xFC(r1)
	  lwz       r3, 0x18(r30)
	  bge-      .loc_0xBC
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x5C(r12)
	  mtlr      r12
	  blrl
	  fmr       f29, f1
	  b         .loc_0xF4

	.loc_0xBC:
	  lhz       r0, 0x3C(r30)
	  cmpw      r5, r0
	  blt-      .loc_0xD0
	  lfs       f29, -0x6FB0(r2)
	  b         .loc_0xF4

	.loc_0xD0:
	  lwz       r4, 0xC(r30)
	  lis       r6, 0x7465
	  rlwinm    r0,r5,3,0,28
	  lwz       r3, 0x302C(r13)
	  lwz       r5, 0x2CC(r4)
	  addi      r4, r6, 0x7374
	  lwzx      r5, r5, r0
	  bl        -0x10E84
	  lfs       f29, 0xC(r3)

	.loc_0xF4:
	  lwz       r4, 0x44(r30)
	  lwz       r3, 0x18(r30)
	  addic.    r5, r4, 0x1
	  bge-      .loc_0x118
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x5C(r12)
	  mtlr      r12
	  blrl
	  b         .loc_0x150

	.loc_0x118:
	  lhz       r0, 0x3C(r30)
	  cmpw      r5, r0
	  blt-      .loc_0x12C
	  lfs       f1, -0x6FB0(r2)
	  b         .loc_0x150

	.loc_0x12C:
	  lwz       r4, 0xC(r30)
	  lis       r6, 0x7465
	  rlwinm    r0,r5,3,0,28
	  lwz       r3, 0x302C(r13)
	  lwz       r5, 0x2CC(r4)
	  addi      r4, r6, 0x7374
	  lwzx      r5, r5, r0
	  bl        -0x10EE0
	  lfs       f1, 0xC(r3)

	.loc_0x150:
	  stfs      f30, 0x15C(r1)
	  addi      r3, r1, 0x15C
	  lfs       f2, -0x7018(r2)
	  addi      r4, r1, 0x13C
	  stfs      f31, 0x160(r1)
	  addi      r5, r1, 0x14C
	  stfs      f28, 0x164(r1)
	  addi      r6, r1, 0x158
	  stfs      f27, 0x168(r1)
	  stfs      f26, 0x16C(r1)
	  stfs      f25, 0x170(r1)
	  stfs      f2, 0x154(r1)
	  stfs      f1, 0x174(r1)
	  stfs      f2, 0x150(r1)
	  stfs      f29, 0x178(r1)
	  stfs      f2, 0x14C(r1)
	  lfs       f0, 0x94(r31)
	  stfs      f0, 0x13C(r1)
	  lfs       f0, 0x98(r31)
	  stfs      f0, 0x140(r1)
	  lfs       f0, 0x9C(r31)
	  stfs      f0, 0x144(r1)
	  stfs      f2, 0x148(r1)
	  bl        -0x2B230
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0x2D4
	  lwz       r3, 0x44(r30)
	  addic.    r3, r3, 0x2
	  blt-      .loc_0x1D0
	  lhz       r0, 0x3C(r30)
	  cmpw      r3, r0
	  blt-      .loc_0x1D8

	.loc_0x1D0:
	  li        r4, 0x1
	  b         .loc_0x21C

	.loc_0x1D8:
	  lwz       r4, 0xC(r30)
	  lis       r6, 0x7465
	  rlwinm    r0,r3,3,0,28
	  lwz       r3, 0x302C(r13)
	  lwz       r5, 0x2CC(r4)
	  addi      r4, r6, 0x7374
	  lwzx      r5, r5, r0
	  bl        -0x10F8C
	  cmplwi    r3, 0
	  lbz       r0, 0x38(r3)
	  li        r4, 0
	  cmplwi    r0, 0
	  beq-      .loc_0x21C
	  lbz       r0, 0x40(r3)
	  rlwinm.   r0,r0,0,30,30
	  bne-      .loc_0x21C
	  li        r4, 0x1

	.loc_0x21C:
	  rlwinm.   r0,r4,0,24,31
	  beq-      .loc_0x2D4
	  li        r28, 0
	  stw       r28, 0x44(r30)
	  addi      r4, r30, 0
	  addi      r3, r1, 0xE8
	  li        r5, -0x1
	  bl        -0x49C
	  lwz       r6, 0xE8(r1)
	  mr        r4, r30
	  lwz       r0, 0xEC(r1)
	  addi      r3, r1, 0xDC
	  li        r5, -0x1
	  stw       r6, 0x4C(r30)
	  stw       r0, 0x50(r30)
	  lwz       r0, 0xF0(r1)
	  stw       r0, 0x54(r30)
	  bl        -0x4C4
	  lwz       r6, 0xDC(r1)
	  mr        r4, r30
	  lwz       r0, 0xE0(r1)
	  addi      r3, r1, 0xD0
	  li        r5, 0x1
	  stw       r6, 0x58(r30)
	  stw       r0, 0x5C(r30)
	  lwz       r0, 0xE4(r1)
	  stw       r0, 0x60(r30)
	  bl        -0x4EC
	  lwz       r6, 0xD0(r1)
	  mr        r4, r30
	  lwz       r0, 0xD4(r1)
	  addi      r3, r1, 0xC4
	  li        r5, 0x2
	  stw       r6, 0x64(r30)
	  stw       r0, 0x68(r30)
	  lwz       r0, 0xD8(r1)
	  stw       r0, 0x6C(r30)
	  bl        -0x514
	  lwz       r3, 0xC4(r1)
	  lwz       r0, 0xC8(r1)
	  stw       r3, 0x70(r30)
	  stw       r0, 0x74(r30)
	  lwz       r0, 0xCC(r1)
	  stw       r0, 0x78(r30)
	  stb       r28, 0x88(r30)
	  b         .loc_0x4CC

	.loc_0x2D4:
	  mr        r3, r30
	  bl        -0x1CD0
	  lwz       r5, 0xC(r30)
	  lis       r28, 0x7465
	  lwz       r3, 0x302C(r13)
	  addi      r4, r28, 0x7374
	  lwz       r5, 0x2CC(r5)
	  li        r27, 0
	  lwz       r5, 0x0(r5)
	  bl        -0x11090
	  lhz       r0, 0x3C(r30)
	  addi      r29, r3, 0
	  cmplwi    r0, 0x2
	  blt-      .loc_0x328
	  lwz       r5, 0xC(r30)
	  addi      r4, r28, 0x7374
	  lwz       r3, 0x302C(r13)
	  lwz       r5, 0x2CC(r5)
	  lwz       r5, 0x8(r5)
	  bl        -0x110B8
	  mr        r27, r3

	.loc_0x328:
	  cmplwi    r29, 0
	  beq-      .loc_0x4BC
	  cmplwi    r27, 0
	  beq-      .loc_0x4BC
	  lfs       f0, -0x7018(r2)
	  stfs      f0, 0x134(r1)
	  stfs      f0, 0x130(r1)
	  stfs      f0, 0x12C(r1)
	  lfs       f3, 0x0(r27)
	  lfs       f2, 0x0(r29)
	  lfs       f1, 0x4(r27)
	  lfs       f0, 0x4(r29)
	  fsubs     f31, f3, f2
	  lfs       f2, 0x8(r27)
	  fsubs     f30, f1, f0
	  lfs       f0, 0x8(r29)
	  fmuls     f1, f31, f31
	  fsubs     f29, f2, f0
	  fmuls     f0, f30, f30
	  fmuls     f2, f29, f29
	  fadds     f0, f1, f0
	  fadds     f1, f2, f0
	  bl        -0xA4B50
	  lfs       f0, -0x7018(r2)
	  fcmpu     cr0, f0, f1
	  beq-      .loc_0x39C
	  fdivs     f31, f31, f1
	  fdivs     f30, f30, f1
	  fdivs     f29, f29, f1

	.loc_0x39C:
	  lfs       f3, 0x94(r31)
	  lfs       f2, 0x0(r29)
	  lfs       f0, -0x7018(r2)
	  fsubs     f2, f3, f2
	  stfs      f2, 0x84(r1)
	  lfs       f3, 0x98(r31)
	  lfs       f2, 0x4(r29)
	  lfs       f4, 0x84(r1)
	  fsubs     f2, f3, f2
	  lfs       f6, 0x9C(r31)
	  lfs       f5, 0x8(r29)
	  fmuls     f3, f31, f4
	  fsubs     f4, f6, f5
	  fmuls     f2, f30, f2
	  fmuls     f4, f29, f4
	  fadds     f2, f3, f2
	  fadds     f2, f4, f2
	  fdivs     f2, f2, f1
	  fcmpo     cr0, f2, f0
	  bge-      .loc_0x408
	  lwz       r3, 0x0(r29)
	  lwz       r0, 0x4(r29)
	  stw       r3, 0x12C(r1)
	  stw       r0, 0x130(r1)
	  lwz       r0, 0x8(r29)
	  stw       r0, 0x134(r1)
	  b         .loc_0x490

	.loc_0x408:
	  lfs       f0, -0x6FF4(r2)
	  fcmpo     cr0, f2, f0
	  ble-      .loc_0x430
	  lwz       r3, 0x0(r27)
	  lwz       r0, 0x4(r27)
	  stw       r3, 0x12C(r1)
	  stw       r0, 0x130(r1)
	  lwz       r0, 0x8(r27)
	  stw       r0, 0x134(r1)
	  b         .loc_0x490

	.loc_0x430:
	  fmuls     f0, f2, f1
	  addi      r6, r1, 0x64
	  addi      r5, r1, 0x60
	  addi      r4, r1, 0x5C
	  fmuls     f2, f29, f0
	  fmuls     f1, f30, f0
	  addi      r3, r1, 0xA0
	  fmuls     f0, f31, f0
	  stfs      f2, 0x64(r1)
	  stfs      f1, 0x60(r1)
	  stfs      f0, 0x5C(r1)
	  bl        -0x7B750
	  lfs       f2, 0xA0(r1)
	  lfs       f0, 0x0(r29)
	  lfs       f1, 0xA4(r1)
	  fadds     f0, f2, f0
	  stfs      f0, 0x12C(r1)
	  lfs       f0, 0x4(r29)
	  fadds     f0, f1, f0
	  stfs      f0, 0x130(r1)
	  lfs       f1, 0xA8(r1)
	  lfs       f0, 0x8(r29)
	  fadds     f0, f1, f0
	  stfs      f0, 0x134(r1)

	.loc_0x490:
	  mr        r3, r30
	  bl        .loc_0x514
	  lwz       r4, 0x12C(r1)
	  li        r0, 0x1
	  lwz       r3, 0x130(r1)
	  stw       r4, 0x64(r30)
	  stw       r3, 0x68(r30)
	  lwz       r3, 0x134(r1)
	  stw       r3, 0x6C(r30)
	  stb       r0, 0x88(r30)
	  b         .loc_0x4CC

	.loc_0x4BC:
	  mr        r3, r30
	  bl        .loc_0x514
	  li        r0, 0x2
	  stb       r0, 0x88(r30)

	.loc_0x4CC:
	  mr        r3, r30
	  bl        0xC4
	  lfs       f1, -0x6F94(r2)
	  addi      r3, r30, 0x20
	  lfs       f2, -0x6FAC(r2)
	  bl        0x1AF24
	  lmw       r27, 0x19C(r1)
	  lwz       r0, 0x1EC(r1)
	  lfd       f31, 0x1E0(r1)
	  lfd       f30, 0x1D8(r1)
	  lfd       f29, 0x1D0(r1)
	  lfd       f28, 0x1C8(r1)
	  lfd       f27, 0x1C0(r1)
	  lfd       f26, 0x1B8(r1)
	  lfd       f25, 0x1B0(r1)
	  addi      r1, r1, 0x1E8
	  mtlr      r0
	  blr

	.loc_0x514:
	*/
}

/*
 * --INFO--
 * Address:	800B2924
 * Size:	000080
 */
void ActTransport::crMakeRefs()
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x28(r1)
	  stw       r31, 0x24(r1)
	  stw       r30, 0x20(r1)
	  li        r30, 0
	  stw       r29, 0x1C(r1)
	  addi      r29, r3, 0
	  addi      r31, r29, 0

	.loc_0x24:
	  lwz       r0, 0x44(r29)
	  subi      r5, r30, 0x1
	  addi      r4, r29, 0
	  addi      r3, r1, 0xC
	  add       r5, r0, r5
	  bl        -0x7B0
	  lwz       r3, 0xC(r1)
	  addi      r30, r30, 0x1
	  lwz       r0, 0x10(r1)
	  cmpwi     r30, 0x4
	  stw       r3, 0x4C(r31)
	  stw       r0, 0x50(r31)
	  lwz       r0, 0x14(r1)
	  stw       r0, 0x54(r31)
	  addi      r31, r31, 0xC
	  blt+      .loc_0x24
	  lwz       r0, 0x2C(r1)
	  lwz       r31, 0x24(r1)
	  lwz       r30, 0x20(r1)
	  lwz       r29, 0x1C(r1)
	  addi      r1, r1, 0x28
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	800B29A4
 * Size:	00032C
 */
void ActTransport::findObstacle()
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  li        r0, 0
	  stwu      r1, -0x188(r1)
	  stfd      f31, 0x180(r1)
	  stfd      f30, 0x178(r1)
	  stfd      f29, 0x170(r1)
	  stfd      f28, 0x168(r1)
	  stfd      f27, 0x160(r1)
	  stfd      f26, 0x158(r1)
	  stfd      f25, 0x150(r1)
	  stmw      r24, 0x130(r1)
	  addi      r26, r3, 0
	  stw       r0, 0x48(r3)
	  lfs       f25, 0x58(r3)
	  lfs       f1, 0x64(r3)
	  lfs       f26, 0x5C(r3)
	  lfs       f0, 0x68(r3)
	  fsubs     f30, f1, f25
	  lfs       f27, 0x60(r3)
	  fsubs     f29, f0, f26
	  lfs       f0, 0x6C(r3)
	  fmuls     f1, f30, f30
	  fsubs     f28, f0, f27
	  fmuls     f0, f29, f29
	  fmuls     f2, f28, f28
	  fadds     f0, f1, f0
	  fadds     f1, f2, f0
	  bl        -0xA4DD4
	  fmr       f31, f1
	  lfs       f0, -0x7018(r2)
	  fcmpu     cr0, f0, f31
	  beq-      .loc_0x90
	  fdivs     f30, f30, f31
	  fdivs     f29, f29, f31
	  fdivs     f28, f28, f31

	.loc_0x90:
	  lwz       r28, 0x3160(r13)
	  mr        r3, r28
	  lwz       r12, 0x0(r28)
	  lwz       r12, 0xC(r12)
	  mtlr      r12
	  blrl
	  addi      r27, r3, 0
	  addi      r31, r1, 0x5C
	  addi      r30, r1, 0x58
	  addi      r29, r1, 0x54
	  lis       r25, 0x7465
	  b         .loc_0x2A0

	.loc_0xC0:
	  cmpwi     r27, -0x1
	  bne-      .loc_0xE8
	  mr        r3, r28
	  lwz       r12, 0x0(r28)
	  li        r4, 0
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  mr        r24, r3
	  b         .loc_0x104

	.loc_0xE8:
	  mr        r3, r28
	  lwz       r12, 0x0(r28)
	  mr        r4, r27
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  mr        r24, r3

	.loc_0x104:
	  lwz       r12, 0x0(r24)
	  mr        r3, r24
	  lwz       r12, 0x88(r12)
	  mtlr      r12
	  blrl
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0x284
	  mr        r3, r24
	  lwz       r12, 0x0(r24)
	  lwz       r12, 0x7C(r12)
	  mtlr      r12
	  blrl
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0x284
	  lfs       f0, 0x94(r24)
	  addi      r4, r29, 0
	  addi      r5, r30, 0
	  fsubs     f0, f0, f25
	  addi      r6, r31, 0
	  addi      r3, r1, 0xC0
	  stfs      f0, 0xAC(r1)
	  lfs       f0, 0x98(r24)
	  lfs       f2, 0x9C(r24)
	  fsubs     f0, f0, f26
	  lfs       f1, 0xAC(r1)
	  fsubs     f2, f2, f27
	  fmuls     f1, f30, f1
	  fmuls     f0, f29, f0
	  fmuls     f2, f28, f2
	  fadds     f0, f1, f0
	  fadds     f0, f2, f0
	  fdivs     f0, f0, f31
	  fmuls     f0, f0, f31
	  fmuls     f2, f28, f0
	  fmuls     f1, f29, f0
	  fmuls     f0, f30, f0
	  stfs      f2, 0x5C(r1)
	  stfs      f1, 0x58(r1)
	  stfs      f0, 0x54(r1)
	  bl        -0x7BA28
	  lfs       f0, 0xC0(r1)
	  lfs       f1, 0xC4(r1)
	  fadds     f4, f0, f25
	  lfs       f2, 0x94(r24)
	  lfs       f0, 0xC8(r1)
	  fadds     f3, f1, f26
	  lfs       f1, 0x98(r24)
	  fsubs     f5, f4, f2
	  lfs       f2, 0x9C(r24)
	  fsubs     f4, f3, f1
	  fadds     f3, f0, f27
	  fmuls     f1, f5, f5
	  fmuls     f0, f4, f4
	  fsubs     f2, f3, f2
	  fadds     f0, f1, f0
	  fmuls     f1, f2, f2
	  fadds     f1, f1, f0
	  bl        -0xA4F4C
	  lwz       r4, 0x44(r26)
	  lwz       r3, 0x18(r26)
	  cmpwi     r4, 0
	  bge-      .loc_0x210
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x5C(r12)
	  mtlr      r12
	  blrl
	  b         .loc_0x238

	.loc_0x210:
	  lhz       r0, 0x3C(r26)
	  cmpw      r4, r0
	  bge-      .loc_0x238
	  lwz       r5, 0xC(r26)
	  rlwinm    r0,r4,3,0,28
	  lwz       r3, 0x302C(r13)
	  addi      r4, r25, 0x7374
	  lwz       r5, 0x2CC(r5)
	  lwzx      r5, r5, r0
	  bl        -0x11560

	.loc_0x238:
	  lwz       r4, 0x44(r26)
	  lwz       r3, 0x18(r26)
	  addic.    r4, r4, 0x1
	  bge-      .loc_0x25C
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x5C(r12)
	  mtlr      r12
	  blrl
	  b         .loc_0x284

	.loc_0x25C:
	  lhz       r0, 0x3C(r26)
	  cmpw      r4, r0
	  bge-      .loc_0x284
	  lwz       r5, 0xC(r26)
	  rlwinm    r0,r4,3,0,28
	  lwz       r3, 0x302C(r13)
	  addi      r4, r25, 0x7374
	  lwz       r5, 0x2CC(r5)
	  lwzx      r5, r5, r0
	  bl        -0x115AC

	.loc_0x284:
	  mr        r3, r28
	  lwz       r12, 0x0(r28)
	  mr        r4, r27
	  lwz       r12, 0x10(r12)
	  mtlr      r12
	  blrl
	  mr        r27, r3

	.loc_0x2A0:
	  mr        r3, r28
	  lwz       r12, 0x0(r28)
	  mr        r4, r27
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0x2C8
	  li        r0, 0x1
	  b         .loc_0x2F4

	.loc_0x2C8:
	  mr        r3, r28
	  lwz       r12, 0x0(r28)
	  mr        r4, r27
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  cmplwi    r3, 0
	  bne-      .loc_0x2F0
	  li        r0, 0x1
	  b         .loc_0x2F4

	.loc_0x2F0:
	  li        r0, 0

	.loc_0x2F4:
	  rlwinm.   r0,r0,0,24,31
	  beq+      .loc_0xC0
	  lmw       r24, 0x130(r1)
	  lwz       r0, 0x18C(r1)
	  lfd       f31, 0x180(r1)
	  lfd       f30, 0x178(r1)
	  lfd       f29, 0x170(r1)
	  lfd       f28, 0x168(r1)
	  lfd       f27, 0x160(r1)
	  lfd       f26, 0x158(r1)
	  lfd       f25, 0x150(r1)
	  addi      r1, r1, 0x188
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	800B2CD0
 * Size:	00094C
 */
bool ActTransport::crMove()
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x278(r1)
	  stfd      f31, 0x270(r1)
	  stfd      f30, 0x268(r1)
	  stfd      f29, 0x260(r1)
	  stfd      f28, 0x258(r1)
	  stfd      f27, 0x250(r1)
	  stfd      f26, 0x248(r1)
	  stfd      f25, 0x240(r1)
	  stw       r31, 0x23C(r1)
	  stw       r30, 0x238(r1)
	  mr        r30, r3
	  mr        r4, r30
	  stw       r29, 0x234(r1)
	  lwz       r31, 0x18(r3)
	  lwz       r5, 0x44(r3)
	  addi      r3, r1, 0x1DC
	  bl        -0xB6C
	  lwz       r0, 0x44(r30)
	  lfs       f31, 0x1DC(r1)
	  cmpwi     r0, -0x1
	  lfs       f30, 0x1E0(r1)
	  lfs       f29, 0x1E4(r1)
	  lfs       f25, 0x64(r30)
	  lfs       f26, 0x68(r30)
	  lfs       f27, 0x6C(r30)
	  bne-      .loc_0xD0
	  lhz       r0, 0x3C(r30)
	  li        r5, 0x1
	  cmpwi     r0, 0x1
	  bgt-      .loc_0x84
	  b         .loc_0xC8

	.loc_0x84:
	  lwz       r4, 0xC(r30)
	  lis       r6, 0x7465
	  rlwinm    r0,r5,3,0,28
	  lwz       r3, 0x302C(r13)
	  lwz       r5, 0x2CC(r4)
	  addi      r4, r6, 0x7374
	  lwzx      r5, r5, r0
	  bl        -0x116F8
	  cmplwi    r3, 0
	  lbz       r0, 0x38(r3)
	  li        r5, 0
	  cmplwi    r0, 0
	  beq-      .loc_0xC8
	  lbz       r0, 0x40(r3)
	  rlwinm.   r0,r0,0,30,30
	  bne-      .loc_0xC8
	  li        r5, 0x1

	.loc_0xC8:
	  rlwinm.   r0,r5,0,24,31
	  beq-      .loc_0x144

	.loc_0xD0:
	  lwz       r3, 0x44(r30)
	  cmpwi     r3, -0x1
	  beq-      .loc_0x1A0
	  addic.    r3, r3, 0x1
	  blt-      .loc_0xF0
	  lhz       r0, 0x3C(r30)
	  cmpw      r3, r0
	  blt-      .loc_0xF8

	.loc_0xF0:
	  li        r4, 0x1
	  b         .loc_0x13C

	.loc_0xF8:
	  lwz       r4, 0xC(r30)
	  lis       r6, 0x7465
	  rlwinm    r0,r3,3,0,28
	  lwz       r3, 0x302C(r13)
	  lwz       r5, 0x2CC(r4)
	  addi      r4, r6, 0x7374
	  lwzx      r5, r5, r0
	  bl        -0x1176C
	  cmplwi    r3, 0
	  lbz       r0, 0x38(r3)
	  li        r4, 0
	  cmplwi    r0, 0
	  beq-      .loc_0x13C
	  lbz       r0, 0x40(r3)
	  rlwinm.   r0,r0,0,30,30
	  bne-      .loc_0x13C
	  li        r4, 0x1

	.loc_0x13C:
	  rlwinm.   r0,r4,0,24,31
	  bne-      .loc_0x1A0

	.loc_0x144:
	  lwz       r5, 0xC(r30)
	  lis       r3, 0x7465
	  lwz       r0, 0x44(r30)
	  addi      r4, r3, 0x7374
	  lwz       r5, 0x2CC(r5)
	  rlwinm    r0,r0,3,0,28
	  lwz       r3, 0x302C(r13)
	  add       r5, r5, r0
	  lwz       r5, 0x8(r5)
	  bl        -0x117C0
	  cmplwi    r3, 0
	  li        r0, 0x4
	  sth       r0, 0x1C(r30)
	  li        r3, 0x1
	  lwz       r4, 0x94(r31)
	  lwz       r0, 0x98(r31)
	  stw       r4, 0x90(r30)
	  stw       r0, 0x94(r30)
	  lwz       r0, 0x9C(r31)
	  stw       r0, 0x98(r30)
	  lfs       f0, -0x7018(r2)
	  stfs      f0, 0xA4(r30)
	  b         .loc_0x914

	.loc_0x1A0:
	  fmr       f1, f25
	  lfs       f3, 0x94(r31)
	  fmr       f2, f27
	  lfs       f4, 0x9C(r31)
	  bl        -0x7A858
	  lfs       f0, -0x6FC8(r2)
	  fcmpo     cr0, f1, f0
	  bge-      .loc_0x348
	  lhz       r3, 0x3C(r30)
	  lwz       r4, 0x44(r30)
	  subi      r0, r3, 0x2
	  cmpw      r4, r0
	  blt-      .loc_0x260
	  li        r0, 0x5
	  sth       r0, 0x1C(r30)
	  addi      r3, r1, 0x1C4
	  addi      r4, r30, 0x4C
	  lfs       f1, -0x6FF4(r2)
	  bl        0x5FC74
	  lwz       r3, 0x1C4(r1)
	  lwz       r0, 0x1C8(r1)
	  stw       r3, 0x30(r30)
	  stw       r0, 0x34(r30)
	  lwz       r0, 0x1CC(r1)
	  stw       r0, 0x38(r30)
	  lfs       f1, 0x30(r30)
	  lfs       f0, 0x34(r30)
	  lfs       f2, 0x38(r30)
	  fmuls     f1, f1, f1
	  fmuls     f0, f0, f0
	  fmuls     f2, f2, f2
	  fadds     f0, f1, f0
	  fadds     f1, f2, f0
	  bl        -0xA52B4
	  lfs       f0, -0x7018(r2)
	  fcmpu     cr0, f0, f1
	  beq-      .loc_0x258
	  lfs       f0, 0x30(r30)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x30(r30)
	  lfs       f0, 0x34(r30)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x34(r30)
	  lfs       f0, 0x38(r30)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x38(r30)

	.loc_0x258:
	  li        r3, 0x1
	  b         .loc_0x914

	.loc_0x260:
	  addi      r0, r4, 0x1
	  stw       r0, 0x44(r30)
	  addi      r29, r30, 0
	  li        r31, 0
	  lwz       r3, 0xA8(r30)
	  addi      r0, r3, 0x1
	  stw       r0, 0xA8(r30)

	.loc_0x27C:
	  lwz       r0, 0x44(r30)
	  subi      r5, r31, 0x1
	  addi      r4, r30, 0
	  addi      r3, r1, 0x13C
	  add       r5, r0, r5
	  bl        -0xDB4
	  lwz       r3, 0x13C(r1)
	  addi      r31, r31, 0x1
	  lwz       r0, 0x140(r1)
	  cmpwi     r31, 0x4
	  stw       r3, 0x4C(r29)
	  stw       r0, 0x50(r29)
	  lwz       r0, 0x144(r1)
	  stw       r0, 0x54(r29)
	  addi      r29, r29, 0xC
	  blt+      .loc_0x27C
	  mr        r3, r30
	  bl        -0x5EC
	  lfs       f1, -0x7018(r2)
	  addi      r3, r1, 0x1B8
	  addi      r4, r30, 0x4C
	  bl        0x5FB8C
	  lwz       r3, 0x1B8(r1)
	  lwz       r0, 0x1BC(r1)
	  stw       r3, 0x30(r30)
	  stw       r0, 0x34(r30)
	  lwz       r0, 0x1C0(r1)
	  stw       r0, 0x38(r30)
	  lfs       f1, 0x30(r30)
	  lfs       f0, 0x34(r30)
	  lfs       f2, 0x38(r30)
	  fmuls     f1, f1, f1
	  fmuls     f0, f0, f0
	  fmuls     f2, f2, f2
	  fadds     f0, f1, f0
	  fadds     f1, f2, f0
	  bl        -0xA539C
	  lfs       f0, -0x7018(r2)
	  fcmpu     cr0, f0, f1
	  beq-      .loc_0x340
	  lfs       f0, 0x30(r30)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x30(r30)
	  lfs       f0, 0x34(r30)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x34(r30)
	  lfs       f0, 0x38(r30)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x38(r30)

	.loc_0x340:
	  li        r3, 0x1
	  b         .loc_0x914

	.loc_0x348:
	  fsubs     f2, f25, f31
	  fsubs     f1, f26, f30
	  fsubs     f0, f27, f29
	  stfs      f2, 0x1FC(r1)
	  stfs      f1, 0x200(r1)
	  stfs      f0, 0x204(r1)
	  lfs       f1, 0x1FC(r1)
	  lfs       f0, 0x200(r1)
	  fmuls     f1, f1, f1
	  lfs       f2, 0x204(r1)
	  fmuls     f0, f0, f0
	  fmuls     f2, f2, f2
	  fadds     f0, f1, f0
	  fadds     f1, f2, f0
	  bl        -0xA5410
	  lfs       f0, -0x7018(r2)
	  fcmpu     cr0, f0, f1
	  beq-      .loc_0x3B4
	  lfs       f0, 0x1FC(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x1FC(r1)
	  lfs       f0, 0x200(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x200(r1)
	  lfs       f0, 0x204(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x204(r1)

	.loc_0x3B4:
	  lfs       f0, -0x7018(r2)
	  fcmpo     cr0, f1, f0
	  ble-      .loc_0x408
	  lfs       f0, 0x94(r31)
	  lfs       f4, 0x1FC(r1)
	  fsubs     f0, f0, f31
	  stfs      f0, 0x124(r1)
	  lfs       f0, 0x98(r31)
	  lfs       f5, 0x9C(r31)
	  fsubs     f0, f0, f30
	  lfs       f3, 0x124(r1)
	  lfs       f2, 0x200(r1)
	  fsubs     f5, f5, f29
	  lfs       f6, 0x204(r1)
	  fmuls     f3, f4, f3
	  fmuls     f0, f2, f0
	  fmuls     f2, f6, f5
	  fadds     f0, f3, f0
	  fadds     f0, f2, f0
	  fdivs     f27, f0, f1
	  b         .loc_0x40C

	.loc_0x408:
	  lfs       f27, -0x6FF4(r2)

	.loc_0x40C:
	  lfs       f0, -0x7018(r2)
	  fcmpo     cr0, f27, f0
	  bge-      .loc_0x41C
	  fmr       f27, f0

	.loc_0x41C:
	  lfs       f0, -0x6FF4(r2)
	  fcmpo     cr0, f27, f0
	  ble-      .loc_0x42C
	  fmr       f27, f0

	.loc_0x42C:
	  fmuls     f2, f27, f1
	  lfs       f28, 0x204(r1)
	  lfs       f0, 0x1FC(r1)
	  addi      r6, r1, 0x98
	  addi      r5, r1, 0x94
	  fmuls     f1, f28, f2
	  addi      r4, r1, 0x90
	  fmuls     f0, f0, f2
	  addi      r3, r1, 0x194
	  stfs      f1, 0x98(r1)
	  lfs       f1, 0x200(r1)
	  fmuls     f1, f1, f2
	  stfs      f0, 0x90(r1)
	  stfs      f1, 0x94(r1)
	  bl        -0x7C018
	  lfs       f1, 0x194(r1)
	  lfs       f0, 0x19C(r1)
	  fadds     f3, f1, f31
	  lfs       f2, 0x94(r31)
	  lfs       f30, -0x7018(r2)
	  fadds     f1, f0, f29
	  lfs       f0, 0x9C(r31)
	  fsubs     f31, f3, f2
	  fsubs     f29, f1, f0
	  fmuls     f0, f30, f30
	  fmuls     f1, f31, f31
	  fmuls     f2, f29, f29
	  fadds     f0, f1, f0
	  fadds     f1, f2, f0
	  bl        -0xA5530
	  fmr       f25, f1
	  lfs       f0, -0x7018(r2)
	  fcmpu     cr0, f0, f25
	  beq-      .loc_0x4C0
	  fdivs     f31, f31, f25
	  fdivs     f30, f30, f25
	  fdivs     f29, f29, f25

	.loc_0x4C0:
	  lwz       r5, 0x44(r30)
	  lwz       r3, 0x18(r30)
	  cmpwi     r5, 0
	  bge-      .loc_0x4E8
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x5C(r12)
	  mtlr      r12
	  blrl
	  fmr       f26, f1
	  b         .loc_0x520

	.loc_0x4E8:
	  lhz       r0, 0x3C(r30)
	  cmpw      r5, r0
	  blt-      .loc_0x4FC
	  lfs       f26, -0x6FB0(r2)
	  b         .loc_0x520

	.loc_0x4FC:
	  lwz       r4, 0xC(r30)
	  lis       r6, 0x7465
	  rlwinm    r0,r5,3,0,28
	  lwz       r3, 0x302C(r13)
	  lwz       r5, 0x2CC(r4)
	  addi      r4, r6, 0x7374
	  lwzx      r5, r5, r0
	  bl        -0x11B70
	  lfs       f26, 0xC(r3)

	.loc_0x520:
	  lwz       r4, 0x44(r30)
	  lwz       r3, 0x18(r30)
	  addic.    r5, r4, 0x1
	  bge-      .loc_0x544
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x5C(r12)
	  mtlr      r12
	  blrl
	  b         .loc_0x57C

	.loc_0x544:
	  lhz       r0, 0x3C(r30)
	  cmpw      r5, r0
	  blt-      .loc_0x558
	  lfs       f1, -0x6FB0(r2)
	  b         .loc_0x57C

	.loc_0x558:
	  lwz       r4, 0xC(r30)
	  lis       r6, 0x7465
	  rlwinm    r0,r5,3,0,28
	  lwz       r3, 0x302C(r13)
	  lwz       r5, 0x2CC(r4)
	  addi      r4, r6, 0x7374
	  lwzx      r5, r5, r0
	  bl        -0x11BCC
	  lfs       f1, 0xC(r3)

	.loc_0x57C:
	  lfs       f2, -0x6FF4(r2)
	  fmuls     f1, f27, f1
	  fabs      f3, f25
	  lfs       f0, -0x6F90(r2)
	  fsubs     f2, f2, f27
	  fmuls     f2, f2, f26
	  fadds     f1, f2, f1
	  fdivs     f1, f3, f1
	  fcmpo     cr0, f1, f0
	  fmr       f26, f1
	  bge-      .loc_0x5AC
	  lfs       f26, -0x7018(r2)

	.loc_0x5AC:
	  lfs       f0, -0x6F8C(r2)
	  fcmpo     cr0, f26, f0
	  ble-      .loc_0x5D8
	  fabs      f1, f25
	  lfs       f0, -0x6F88(r2)
	  fcmpo     cr0, f1, f0
	  ble-      .loc_0x5D8
	  mr        r3, r30
	  bl        -0x2EE8
	  li        r3, 0x1
	  b         .loc_0x914

	.loc_0x5D8:
	  lfs       f0, -0x6FF4(r2)
	  fcmpo     cr0, f26, f0
	  ble-      .loc_0x5EC
	  fmr       f26, f0
	  b         .loc_0x5FC

	.loc_0x5EC:
	  lfs       f0, -0x7018(r2)
	  fcmpo     cr0, f26, f0
	  bge-      .loc_0x5FC
	  fmr       f26, f0

	.loc_0x5FC:
	  lfs       f0, -0x6FF4(r2)
	  fcmpo     cr0, f27, f0
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x798
	  lhz       r3, 0x3C(r30)
	  lwz       r4, 0x44(r30)
	  subi      r0, r3, 0x2
	  cmpw      r4, r0
	  blt-      .loc_0x6AC
	  li        r0, 0x5
	  fmr       f1, f27
	  sth       r0, 0x1C(r30)
	  addi      r3, r1, 0x188
	  addi      r4, r30, 0x4C
	  bl        0x5F828
	  lwz       r3, 0x188(r1)
	  lwz       r0, 0x18C(r1)
	  stw       r3, 0x30(r30)
	  stw       r0, 0x34(r30)
	  lwz       r0, 0x190(r1)
	  stw       r0, 0x38(r30)
	  lfs       f1, 0x30(r30)
	  lfs       f0, 0x34(r30)
	  lfs       f2, 0x38(r30)
	  fmuls     f1, f1, f1
	  fmuls     f0, f0, f0
	  fmuls     f2, f2, f2
	  fadds     f0, f1, f0
	  fadds     f1, f2, f0
	  bl        -0xA5700
	  lfs       f0, -0x7018(r2)
	  fcmpu     cr0, f0, f1
	  beq-      .loc_0x6A4
	  lfs       f0, 0x30(r30)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x30(r30)
	  lfs       f0, 0x34(r30)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x34(r30)
	  lfs       f0, 0x38(r30)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x38(r30)

	.loc_0x6A4:
	  li        r3, 0x1
	  b         .loc_0x914

	.loc_0x6AC:
	  addi      r0, r4, 0x1
	  stw       r0, 0x44(r30)
	  addi      r29, r30, 0
	  li        r31, 0
	  lwz       r3, 0xA8(r30)
	  addi      r0, r3, 0x1
	  stw       r0, 0xA8(r30)
	  lfs       f25, -0x7018(r2)

	.loc_0x6CC:
	  lwz       r0, 0x44(r30)
	  subi      r5, r31, 0x1
	  addi      r4, r30, 0
	  addi      r3, r1, 0xF4
	  add       r5, r0, r5
	  bl        -0x1204
	  lwz       r3, 0xF4(r1)
	  addi      r31, r31, 0x1
	  lwz       r0, 0xF8(r1)
	  cmpwi     r31, 0x4
	  stw       r3, 0x4C(r29)
	  stw       r0, 0x50(r29)
	  lwz       r0, 0xFC(r1)
	  stw       r0, 0x54(r29)
	  addi      r29, r29, 0xC
	  blt+      .loc_0x6CC
	  mr        r3, r30
	  bl        -0xA3C
	  fmr       f1, f25
	  addi      r3, r1, 0x17C
	  addi      r4, r30, 0x4C
	  bl        0x5F73C
	  lwz       r3, 0x17C(r1)
	  lwz       r0, 0x180(r1)
	  stw       r3, 0x30(r30)
	  stw       r0, 0x34(r30)
	  lwz       r0, 0x184(r1)
	  stw       r0, 0x38(r30)
	  lfs       f1, 0x30(r30)
	  lfs       f0, 0x34(r30)
	  lfs       f2, 0x38(r30)
	  fmuls     f1, f1, f1
	  fmuls     f0, f0, f0
	  fmuls     f2, f2, f2
	  fadds     f0, f1, f0
	  fadds     f1, f2, f0
	  bl        -0xA57EC
	  lfs       f0, -0x7018(r2)
	  fcmpu     cr0, f0, f1
	  beq-      .loc_0x790
	  lfs       f0, 0x30(r30)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x30(r30)
	  lfs       f0, 0x34(r30)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x34(r30)
	  lfs       f0, 0x38(r30)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x38(r30)

	.loc_0x790:
	  li        r3, 0x1
	  b         .loc_0x914

	.loc_0x798:
	  fmr       f1, f27
	  addi      r3, r1, 0x170
	  addi      r4, r30, 0x4C
	  bl        0x5F6B8
	  lwz       r3, 0x170(r1)
	  lwz       r0, 0x174(r1)
	  stw       r3, 0x30(r30)
	  stw       r0, 0x34(r30)
	  lwz       r0, 0x178(r1)
	  stw       r0, 0x38(r30)
	  lfs       f1, 0x30(r30)
	  lfs       f0, 0x34(r30)
	  lfs       f2, 0x38(r30)
	  fmuls     f1, f1, f1
	  fmuls     f0, f0, f0
	  fmuls     f2, f2, f2
	  fadds     f0, f1, f0
	  fadds     f1, f2, f0
	  bl        -0xA5870
	  lfs       f0, -0x7018(r2)
	  fcmpu     cr0, f0, f1
	  beq-      .loc_0x814
	  lfs       f0, 0x30(r30)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x30(r30)
	  lfs       f0, 0x34(r30)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x34(r30)
	  lfs       f0, 0x38(r30)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x38(r30)

	.loc_0x814:
	  fmuls     f2, f31, f26
	  lfs       f0, -0x6FF4(r2)
	  fmuls     f1, f30, f26
	  fsubs     f5, f0, f26
	  stfs      f2, 0xA0(r1)
	  fmuls     f0, f29, f26
	  lfs       f2, 0x30(r30)
	  lfs       f4, 0x38(r30)
	  fmuls     f2, f2, f5
	  lfs       f3, 0x34(r30)
	  fmuls     f4, f4, f5
	  fmuls     f3, f3, f5
	  stfs      f2, 0x9C(r1)
	  lfs       f2, 0x9C(r1)
	  stfs      f2, 0x158(r1)
	  stfs      f3, 0x15C(r1)
	  stfs      f4, 0x160(r1)
	  lfs       f3, 0x158(r1)
	  lfs       f2, 0xA0(r1)
	  fadds     f2, f3, f2
	  stfs      f2, 0xE0(r1)
	  lfs       f2, 0xE0(r1)
	  stfs      f2, 0x164(r1)
	  lfs       f2, 0x15C(r1)
	  fadds     f1, f2, f1
	  stfs      f1, 0x168(r1)
	  lfs       f1, 0x160(r1)
	  fadds     f0, f1, f0
	  stfs      f0, 0x16C(r1)
	  lwz       r4, 0x164(r1)
	  lwz       r0, 0x168(r1)
	  stw       r4, 0x30(r30)
	  stw       r0, 0x34(r30)
	  lwz       r0, 0x16C(r1)
	  stw       r0, 0x38(r30)
	  lfs       f0, 0x38(r30)
	  lfs       f3, 0x30(r30)
	  lfs       f2, 0x1FC(r1)
	  fmuls     f1, f0, f28
	  lfs       f0, -0x7018(r2)
	  fmuls     f2, f3, f2
	  fadds     f1, f2, f1
	  fcmpo     cr0, f1, f0
	  cror      2, 0, 0x2
	  bne-      .loc_0x8E0
	  lwz       r4, 0x1FC(r1)
	  lwz       r0, 0x200(r1)
	  stw       r4, 0x30(r30)
	  stw       r0, 0x34(r30)
	  lwz       r0, 0x204(r1)
	  stw       r0, 0x38(r30)

	.loc_0x8E0:
	  lis       r4, 0x803A
	  subi      r4, r4, 0x2848
	  lwz       r4, 0x1DC(r4)
	  lbz       r0, 0x124(r4)
	  cmplwi    r0, 0
	  bne-      .loc_0x914
	  addi      r3, r30, 0x20
	  addi      r4, r31, 0x94
	  addi      r5, r31, 0x464
	  bl        0x1A258
	  rlwinm.   r0,r3,0,24,31
	  bne-      .loc_0x914
	  li        r3, 0

	.loc_0x914:
	  lwz       r0, 0x27C(r1)
	  lfd       f31, 0x270(r1)
	  lfd       f30, 0x268(r1)
	  lfd       f29, 0x260(r1)
	  lfd       f28, 0x258(r1)
	  lfd       f27, 0x250(r1)
	  lfd       f26, 0x248(r1)
	  lfd       f25, 0x240(r1)
	  lwz       r31, 0x23C(r1)
	  lwz       r30, 0x238(r1)
	  lwz       r29, 0x234(r1)
	  addi      r1, r1, 0x278
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	800B361C
 * Size:	0007C4
 */
void ActTransport::draw(Graphics&)
{
	/*
	.loc_0x0:
	  mflr      r0
	  lis       r5, 0x802B
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x438(r1)
	  stfd      f31, 0x430(r1)
	  stfd      f30, 0x428(r1)
	  stfd      f29, 0x420(r1)
	  stfd      f28, 0x418(r1)
	  stfd      f27, 0x410(r1)
	  stfd      f26, 0x408(r1)
	  stw       r31, 0x404(r1)
	  addi      r31, r4, 0
	  stw       r30, 0x400(r1)
	  addi      r30, r3, 0
	  stw       r29, 0x3FC(r1)
	  addi      r29, r5, 0x5EB0
	  stw       r28, 0x3F8(r1)
	  lbz       r0, 0x2FA8(r13)
	  cmplwi    r0, 0
	  beq-      .loc_0x78C
	  lwz       r4, 0x18(r30)
	  cmplwi    r4, 0
	  bne-      .loc_0x64
	  li        r0, 0
	  b         .loc_0x14C

	.loc_0x64:
	  addi      r3, r1, 0xA0
	  bl        -0x22A00
	  addi      r0, r1, 0xA0
	  stw       r0, 0xB4(r1)
	  li        r0, 0
	  addi      r3, r1, 0xB0
	  stw       r0, 0xB8(r1)
	  bl        -0x238E0
	  b         .loc_0xEC

	.loc_0x88:
	  lwz       r4, 0xB0(r1)
	  cmpwi     r4, -0x1
	  bne-      .loc_0xB0
	  lwz       r3, 0xB4(r1)
	  li        r4, 0
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  b         .loc_0xC4

	.loc_0xB0:
	  lwz       r3, 0xB4(r1)
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl

	.loc_0xC4:
	  lwz       r0, 0x6C(r3)
	  cmpwi     r0, 0
	  bne-      .loc_0xE4
	  lwz       r0, 0xC(r30)
	  sub       r0, r0, r3
	  cntlzw    r0, r0
	  rlwinm    r0,r0,27,5,31
	  b         .loc_0x14C

	.loc_0xE4:
	  addi      r3, r1, 0xB0
	  bl        -0x23A6C

	.loc_0xEC:
	  lwz       r3, 0xB4(r1)
	  lwz       r4, 0xB0(r1)
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0x114
	  li        r0, 0x1
	  b         .loc_0x140

	.loc_0x114:
	  lwz       r3, 0xB4(r1)
	  lwz       r4, 0xB0(r1)
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  cmplwi    r3, 0
	  bne-      .loc_0x13C
	  li        r0, 0x1
	  b         .loc_0x140

	.loc_0x13C:
	  li        r0, 0

	.loc_0x140:
	  rlwinm.   r0,r0,0,24,31
	  beq+      .loc_0x88
	  li        r0, 0

	.loc_0x14C:
	  rlwinm.   r0,r0,0,24,31
	  beq-      .loc_0x78C
	  lis       r3, 0x8022
	  crclr     6, 0x6
	  addi      r7, r3, 0x24B0
	  lwz       r4, 0x0(r7)
	  lis       r3, 0x8022
	  lwz       r0, 0x4(r7)
	  addi      r6, r3, 0x24CC
	  addi      r3, r1, 0x1C0
	  stw       r4, 0x3D8(r1)
	  subi      r4, r13, 0x4C9C
	  stw       r0, 0x3DC(r1)
	  lwz       r5, 0x8(r7)
	  lwz       r0, 0xC(r7)
	  stw       r5, 0x3E0(r1)
	  stw       r0, 0x3E4(r1)
	  lwz       r5, 0x10(r7)
	  lwz       r0, 0x14(r7)
	  stw       r5, 0x3E8(r1)
	  stw       r0, 0x3EC(r1)
	  lwz       r0, 0x18(r7)
	  stw       r0, 0x3F0(r1)
	  lwz       r5, 0x0(r6)
	  lwz       r0, 0x4(r6)
	  stw       r5, 0x3CC(r1)
	  stw       r0, 0x3D0(r1)
	  lwz       r0, 0x8(r6)
	  stw       r0, 0x3D4(r1)
	  lwz       r5, 0xC(r30)
	  lfsu      f0, 0x94(r5)
	  stfs      f0, 0x3C0(r1)
	  lfs       f0, 0x4(r5)
	  stfs      f0, 0x3C4(r1)
	  lfs       f0, 0x8(r5)
	  stfs      f0, 0x3C8(r1)
	  bl        0x162DA0
	  lhz       r3, 0x1C(r30)
	  cmplwi    r3, 0x3
	  bne-      .loc_0x558
	  lwz       r28, 0x18(r30)
	  mr        r4, r30
	  lwz       r5, 0x44(r30)
	  addi      r3, r1, 0x100
	  bl        -0x166C
	  lwz       r5, 0x44(r30)
	  mr        r4, r30
	  lfs       f31, 0x100(r1)
	  addi      r3, r1, 0xF4
	  lfs       f30, 0x104(r1)
	  lfs       f29, 0x108(r1)
	  addi      r5, r5, 0x1
	  bl        -0x168C
	  lfs       f1, 0xF4(r1)
	  lfs       f0, 0xF8(r1)
	  fsubs     f1, f1, f31
	  lfs       f2, 0xFC(r1)
	  fsubs     f0, f0, f30
	  stfs      f1, 0x198(r1)
	  fsubs     f1, f2, f29
	  stfs      f0, 0x19C(r1)
	  stfs      f1, 0x1A0(r1)
	  lfs       f1, 0x198(r1)
	  lfs       f0, 0x19C(r1)
	  fmuls     f1, f1, f1
	  lfs       f2, 0x1A0(r1)
	  fmuls     f0, f0, f0
	  fmuls     f2, f2, f2
	  fadds     f0, f1, f0
	  fadds     f1, f2, f0
	  bl        -0xA5C40
	  lfs       f0, -0x7018(r2)
	  fcmpu     cr0, f0, f1
	  beq-      .loc_0x298
	  lfs       f0, 0x198(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x198(r1)
	  lfs       f0, 0x19C(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x19C(r1)
	  lfs       f0, 0x1A0(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x1A0(r1)

	.loc_0x298:
	  lfs       f0, 0x94(r28)
	  lfs       f5, 0x198(r1)
	  fsubs     f2, f0, f31
	  lfs       f0, -0x7018(r2)
	  stfs      f2, 0x8C(r1)
	  lfs       f2, 0x98(r28)
	  lfs       f4, 0x9C(r28)
	  fsubs     f2, f2, f30
	  lfs       f3, 0x8C(r1)
	  lfs       f27, 0x19C(r1)
	  fsubs     f4, f4, f29
	  lfs       f28, 0x1A0(r1)
	  fmuls     f3, f5, f3
	  fmuls     f2, f27, f2
	  fmuls     f4, f28, f4
	  fadds     f2, f3, f2
	  fadds     f2, f4, f2
	  fdivs     f2, f2, f1
	  fcmpo     cr0, f2, f0
	  fmr       f26, f2
	  bge-      .loc_0x2F0
	  fmr       f26, f0

	.loc_0x2F0:
	  lfs       f0, -0x6FF4(r2)
	  fcmpo     cr0, f26, f0
	  ble-      .loc_0x300
	  fmr       f26, f0

	.loc_0x300:
	  fmuls     f0, f26, f1
	  addi      r6, r1, 0x54
	  addi      r5, r1, 0x50
	  addi      r4, r1, 0x4C
	  fmuls     f2, f28, f0
	  fmuls     f1, f27, f0
	  addi      r3, r1, 0xD0
	  fmuls     f0, f5, f0
	  stfs      f2, 0x54(r1)
	  stfs      f1, 0x50(r1)
	  stfs      f0, 0x4C(r1)
	  bl        -0x7C82C
	  lfs       f0, 0xD0(r1)
	  lfs       f1, 0xD4(r1)
	  fadds     f4, f0, f31
	  lfs       f2, 0x94(r28)
	  lfs       f0, 0xD8(r1)
	  fadds     f3, f1, f30
	  lfs       f1, 0x98(r28)
	  fsubs     f5, f4, f2
	  lfs       f2, 0x9C(r28)
	  fsubs     f4, f3, f1
	  fadds     f3, f0, f29
	  fmuls     f1, f5, f5
	  fmuls     f0, f4, f4
	  fsubs     f2, f3, f2
	  fadds     f0, f1, f0
	  fmuls     f1, f2, f2
	  fadds     f1, f1, f0
	  bl        -0xA5D50
	  lwz       r5, 0x44(r30)
	  fmr       f29, f1
	  lwz       r3, 0x18(r30)
	  cmpwi     r5, 0
	  bge-      .loc_0x3A4
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x5C(r12)
	  mtlr      r12
	  blrl
	  fmr       f30, f1
	  b         .loc_0x3DC

	.loc_0x3A4:
	  lhz       r0, 0x3C(r30)
	  cmpw      r5, r0
	  blt-      .loc_0x3B8
	  lfs       f30, -0x6FB0(r2)
	  b         .loc_0x3DC

	.loc_0x3B8:
	  lwz       r4, 0xC(r30)
	  lis       r6, 0x7465
	  rlwinm    r0,r5,3,0,28
	  lwz       r3, 0x302C(r13)
	  lwz       r5, 0x2CC(r4)
	  addi      r4, r6, 0x7374
	  lwzx      r5, r5, r0
	  bl        -0x12378
	  lfs       f30, 0xC(r3)

	.loc_0x3DC:
	  lwz       r4, 0x44(r30)
	  lwz       r3, 0x18(r30)
	  addic.    r5, r4, 0x1
	  bge-      .loc_0x400
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x5C(r12)
	  mtlr      r12
	  blrl
	  b         .loc_0x438

	.loc_0x400:
	  lhz       r0, 0x3C(r30)
	  cmpw      r5, r0
	  blt-      .loc_0x414
	  lfs       f1, -0x6FB0(r2)
	  b         .loc_0x438

	.loc_0x414:
	  lwz       r4, 0xC(r30)
	  lis       r6, 0x7465
	  rlwinm    r0,r5,3,0,28
	  lwz       r3, 0x302C(r13)
	  lwz       r5, 0x2CC(r4)
	  addi      r4, r6, 0x7374
	  lwzx      r5, r5, r0
	  bl        -0x123D4
	  lfs       f1, 0xC(r3)

	.loc_0x438:
	  lfs       f3, -0x6FF4(r2)
	  fmuls     f2, f26, f1
	  lfs       f0, -0x7018(r2)
	  fmr       f1, f26
	  fsubs     f3, f3, f26
	  stfs      f0, 0x184(r1)
	  addi      r3, r1, 0x17C
	  fmuls     f3, f3, f30
	  stfs      f0, 0x180(r1)
	  addi      r4, r30, 0x4C
	  stfs      f0, 0x17C(r1)
	  fadds     f30, f3, f2
	  bl        0x5F0A8
	  lfs       f0, 0x180(r1)
	  lfs       f3, 0x17C(r1)
	  lfs       f2, 0x198(r1)
	  fmuls     f1, f0, f27
	  lfs       f4, 0x184(r1)
	  fmuls     f2, f3, f2
	  lfs       f0, -0x7018(r2)
	  fmuls     f3, f4, f28
	  fadds     f1, f2, f1
	  fadds     f1, f3, f1
	  fcmpo     cr0, f1, f0
	  cror      2, 0, 0x2
	  bne-      .loc_0x4B8
	  lwz       r0, 0x198(r1)
	  lwz       r3, 0x19C(r1)
	  stw       r0, 0x17C(r1)
	  lwz       r0, 0x1A0(r1)
	  stw       r3, 0x180(r1)
	  stw       r0, 0x184(r1)

	.loc_0x4B8:
	  lfs       f0, 0x3C0(r1)
	  mr        r3, r31
	  addi      r4, r1, 0x170
	  stfs      f0, 0x170(r1)
	  addi      r5, r1, 0x17C
	  lfs       f0, 0x3C4(r1)
	  stfs      f0, 0x174(r1)
	  lfs       f1, 0x3C8(r1)
	  lfs       f0, -0x6F84(r2)
	  stfs      f1, 0x178(r1)
	  lfs       f1, 0x174(r1)
	  fadds     f0, f1, f0
	  stfs      f0, 0x174(r1)
	  lfs       f1, -0x7010(r2)
	  bl        0x62EA4
	  addi      r3, r31, 0
	  addi      r5, r30, 0x4C
	  li        r4, 0x10
	  bl        0x63100
	  lhz       r0, 0x1C(r30)
	  fmr       f1, f26
	  addi      r3, r1, 0x3D8
	  lwz       r6, 0x44(r30)
	  rlwinm    r0,r0,2,0,29
	  lwzx      r5, r3, r0
	  addi      r3, r1, 0x2C0
	  crset     6, 0x6
	  addi      r4, r29, 0x4C
	  bl        0x162A54
	  lbz       r0, 0x88(r30)
	  fmr       f1, f29
	  fmr       f2, f30
	  addi      r3, r1, 0x3CC
	  rlwinm    r0,r0,2,0,29
	  lwzx      r5, r3, r0
	  addi      r3, r1, 0x1C0
	  addi      r4, r29, 0x58
	  crset     6, 0x6
	  bl        0x162A2C
	  b         .loc_0x588

	.loc_0x558:
	  lbz       r0, 0x88(r30)
	  rlwinm    r5,r3,2,0,29
	  addi      r4, r1, 0x3D8
	  lwz       r6, 0x44(r30)
	  rlwinm    r0,r0,2,0,29
	  addi      r3, r1, 0x3CC
	  lwzx      r5, r4, r5
	  lwzx      r7, r3, r0
	  addi      r3, r1, 0x2C0
	  addi      r4, r29, 0x68
	  crclr     6, 0x6
	  bl        0x1629F8

	.loc_0x588:
	  lwz       r12, 0x3B4(r31)
	  lis       r4, 0x803A
	  mr        r3, r31
	  lwz       r12, 0x74(r12)
	  subi      r4, r4, 0x77C0
	  li        r5, 0
	  mtlr      r12
	  blrl
	  li        r0, 0xFF
	  stb       r0, 0xCC(r1)
	  addi      r4, r1, 0xCC
	  addi      r3, r31, 0
	  stb       r0, 0xCD(r1)
	  li        r5, 0x1
	  stb       r0, 0xCE(r1)
	  stb       r0, 0xCF(r1)
	  lwz       r12, 0x3B4(r31)
	  lwz       r12, 0xA8(r12)
	  mtlr      r12
	  blrl
	  lfs       f1, 0x3C4(r1)
	  addi      r3, r1, 0x164
	  lfs       f0, -0x6F80(r2)
	  fadds     f0, f1, f0
	  stfs      f0, 0x3C4(r1)
	  lfs       f0, 0x3C0(r1)
	  stfs      f0, 0x164(r1)
	  lfs       f0, 0x3C4(r1)
	  stfs      f0, 0x168(r1)
	  lfs       f0, 0x3C8(r1)
	  stfs      f0, 0x16C(r1)
	  lwz       r4, 0x2E4(r31)
	  addi      r4, r4, 0x1E0
	  bl        -0x7C4DC
	  lwz       r3, 0x2DEC(r13)
	  addi      r4, r1, 0x2C0
	  lwz       r3, 0x10(r3)
	  bl        -0x8BB04
	  lwz       r12, 0x3B4(r31)
	  neg       r0, r3
	  lwz       r4, 0x2DEC(r13)
	  srawi     r6, r0, 0x1
	  lwz       r12, 0xF0(r12)
	  lwz       r4, 0x10(r4)
	  addi      r3, r31, 0
	  mtlr      r12
	  addze     r6, r6
	  addi      r5, r1, 0x164
	  crclr     6, 0x6
	  addi      r8, r1, 0x2C0
	  li        r7, 0
	  blrl
	  lwz       r0, 0x3C0(r1)
	  addi      r3, r1, 0x164
	  lwz       r4, 0x3C4(r1)
	  stw       r0, 0x164(r1)
	  lwz       r0, 0x3C8(r1)
	  stw       r4, 0x168(r1)
	  lfs       f0, -0x6F7C(r2)
	  stw       r0, 0x16C(r1)
	  lfs       f1, 0x168(r1)
	  fadds     f0, f1, f0
	  stfs      f0, 0x168(r1)
	  lwz       r4, 0x2E4(r31)
	  addi      r4, r4, 0x1E0
	  bl        -0x7C55C
	  lwz       r3, 0x2DEC(r13)
	  addi      r4, r1, 0x1C0
	  lwz       r3, 0x10(r3)
	  bl        -0x8BB84
	  lwz       r12, 0x3B4(r31)
	  neg       r0, r3
	  lwz       r4, 0x2DEC(r13)
	  srawi     r6, r0, 0x1
	  lwz       r12, 0xF0(r12)
	  lwz       r4, 0x10(r4)
	  addi      r3, r31, 0
	  mtlr      r12
	  addze     r6, r6
	  addi      r5, r1, 0x164
	  crclr     6, 0x6
	  addi      r8, r1, 0x1C0
	  li        r7, 0
	  blrl
	  lhz       r0, 0x1C(r30)
	  cmplwi    r0, 0x3
	  bne-      .loc_0x740
	  li        r29, 0
	  addi      r28, r30, 0

	.loc_0x6EC:
	  lfs       f0, 0x4C(r28)
	  addi      r5, r29, 0
	  addi      r3, r1, 0x118
	  crclr     6, 0x6
	  stfs      f0, 0x158(r1)
	  subi      r4, r13, 0x4C98
	  lfs       f0, 0x50(r28)
	  stfs      f0, 0x15C(r1)
	  lfs       f0, 0x54(r28)
	  stfs      f0, 0x160(r1)
	  bl        0x162868
	  lfs       f1, -0x6FB0(r2)
	  addi      r3, r31, 0
	  addi      r4, r1, 0x158
	  addi      r5, r1, 0x118
	  bl        0x62848
	  addi      r29, r29, 0x1
	  cmpwi     r29, 0x4
	  addi      r28, r28, 0xC
	  blt+      .loc_0x6EC
	  b         .loc_0x78C

	.loc_0x740:
	  cmplwi    r0, 0x5
	  bne-      .loc_0x78C
	  lwz       r4, 0xB0(r30)
	  addi      r3, r1, 0xC0
	  lwz       r12, 0x0(r4)
	  lwz       r12, 0x15C(r12)
	  mtlr      r12
	  blrl
	  lfs       f0, 0xC0(r1)
	  mr        r3, r31
	  lfs       f1, 0xC4(r1)
	  addi      r4, r1, 0x10C
	  stfs      f0, 0x10C(r1)
	  lfs       f0, 0xC8(r1)
	  subi      r5, r13, 0x4CC0
	  stfs      f1, 0x110(r1)
	  lfs       f1, -0x6FB0(r2)
	  stfs      f0, 0x114(r1)
	  bl        0x627E8

	.loc_0x78C:
	  lwz       r0, 0x43C(r1)
	  lfd       f31, 0x430(r1)
	  lfd       f30, 0x428(r1)
	  lfd       f29, 0x420(r1)
	  lfd       f28, 0x418(r1)
	  lfd       f27, 0x410(r1)
	  lfd       f26, 0x408(r1)
	  lwz       r31, 0x404(r1)
	  lwz       r30, 0x400(r1)
	  lwz       r29, 0x3FC(r1)
	  lwz       r28, 0x3F8(r1)
	  addi      r1, r1, 0x438
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	800B3DE0
 * Size:	0006FC
 */
int ActTransport::moveToWayPoint()
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x168(r1)
	  stfd      f31, 0x160(r1)
	  stfd      f30, 0x158(r1)
	  stfd      f29, 0x150(r1)
	  stmw      r27, 0x13C(r1)
	  mr        r31, r3
	  lwz       r29, 0x18(r3)
	  cmplwi    r29, 0
	  addi      r27, r29, 0
	  beq-      .loc_0x38
	  lhz       r30, 0x570(r29)
	  b         .loc_0x3C

	.loc_0x38:
	  li        r30, 0

	.loc_0x3C:
	  lwz       r3, 0x55C(r29)
	  lwz       r28, 0x7C(r3)
	  cmpw      r30, r28
	  bge-      .loc_0xB4
	  li        r0, 0x6
	  sth       r0, 0x1C(r31)
	  cmplwi    r31, 0
	  addi      r4, r31, 0
	  lfs       f0, -0x4C94(r13)
	  stfs      f0, 0x70(r29)
	  lfs       f0, -0x4C90(r13)
	  stfs      f0, 0x74(r29)
	  lfs       f0, -0x4C8C(r13)
	  stfs      f0, 0x78(r29)
	  lwz       r3, 0xC(r31)
	  lfs       f0, -0x4C88(r13)
	  stfsu     f0, 0x70(r3)
	  lfs       f0, -0x4C84(r13)
	  stfs      f0, 0x4(r3)
	  lfs       f0, -0x4C80(r13)
	  stfs      f0, 0x8(r3)
	  beq-      .loc_0x98
	  lwz       r4, 0x14(r31)

	.loc_0x98:
	  lwz       r3, 0xC(r31)
	  addi      r3, r3, 0x354
	  bl        0x6BC40
	  lwz       r3, 0xC(r31)
	  bl        -0x23610
	  li        r3, 0
	  b         .loc_0x6DC

	.loc_0xB4:
	  cmplwi    r29, 0
	  bne-      .loc_0xC4
	  li        r0, 0
	  b         .loc_0x1B0

	.loc_0xC4:
	  addi      r3, r1, 0xA0
	  addi      r4, r29, 0
	  bl        -0x23228
	  addi      r0, r1, 0xA0
	  stw       r0, 0xB4(r1)
	  li        r0, 0
	  addi      r3, r1, 0xB0
	  stw       r0, 0xB8(r1)
	  bl        -0x24108
	  b         .loc_0x150

	.loc_0xEC:
	  lwz       r4, 0xB0(r1)
	  cmpwi     r4, -0x1
	  bne-      .loc_0x114
	  lwz       r3, 0xB4(r1)
	  li        r4, 0
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  b         .loc_0x128

	.loc_0x114:
	  lwz       r3, 0xB4(r1)
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl

	.loc_0x128:
	  lwz       r0, 0x6C(r3)
	  cmpwi     r0, 0
	  bne-      .loc_0x148
	  lwz       r0, 0xC(r31)
	  sub       r0, r0, r3
	  cntlzw    r0, r0
	  rlwinm    r0,r0,27,5,31
	  b         .loc_0x1B0

	.loc_0x148:
	  addi      r3, r1, 0xB0
	  bl        -0x24294

	.loc_0x150:
	  lwz       r3, 0xB4(r1)
	  lwz       r4, 0xB0(r1)
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0x178
	  li        r0, 0x1
	  b         .loc_0x1A4

	.loc_0x178:
	  lwz       r3, 0xB4(r1)
	  lwz       r4, 0xB0(r1)
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  cmplwi    r3, 0
	  bne-      .loc_0x1A0
	  li        r0, 0x1
	  b         .loc_0x1A4

	.loc_0x1A0:
	  li        r0, 0

	.loc_0x1A4:
	  rlwinm.   r0,r0,0,24,31
	  beq+      .loc_0xEC
	  li        r0, 0

	.loc_0x1B0:
	  rlwinm.   r0,r0,0,24,31
	  beq-      .loc_0x558
	  lwz       r3, 0xA8(r31)
	  cmpwi     r3, -0x1
	  beq-      .loc_0x558
	  lbz       r0, 0xB4(r31)
	  cmplwi    r0, 0
	  bne-      .loc_0x238
	  li        r0, 0x6
	  sth       r0, 0x1C(r31)
	  cmplwi    r31, 0
	  addi      r4, r31, 0
	  lfs       f0, -0x4C7C(r13)
	  stfs      f0, 0x70(r29)
	  lfs       f0, -0x4C78(r13)
	  stfs      f0, 0x74(r29)
	  lfs       f0, -0x4C74(r13)
	  stfs      f0, 0x78(r29)
	  lwz       r3, 0xC(r31)
	  lfs       f0, -0x4C70(r13)
	  stfsu     f0, 0x70(r3)
	  lfs       f0, -0x4C6C(r13)
	  stfs      f0, 0x4(r3)
	  lfs       f0, -0x4C68(r13)
	  stfs      f0, 0x8(r3)
	  beq-      .loc_0x21C
	  lwz       r4, 0x14(r31)

	.loc_0x21C:
	  lwz       r3, 0xC(r31)
	  addi      r3, r3, 0x354
	  bl        0x6BABC
	  lwz       r3, 0xC(r31)
	  bl        -0x23794
	  li        r3, 0
	  b         .loc_0x6DC

	.loc_0x238:
	  lwz       r4, 0xC(r31)
	  lis       r6, 0x7465
	  rlwinm    r0,r3,3,0,28
	  lwz       r3, 0x302C(r13)
	  lwz       r5, 0x2CC(r4)
	  addi      r4, r6, 0x7374
	  lwzx      r5, r5, r0
	  bl        -0x129BC
	  lbz       r0, 0x38(r3)
	  cmplwi    r0, 0
	  beq-      .loc_0x270
	  lbz       r0, 0x40(r3)
	  rlwinm.   r0,r0,0,30,30
	  beq-      .loc_0x3D0

	.loc_0x270:
	  lwz       r5, 0xA8(r31)
	  addi      r4, r31, 0
	  addi      r3, r1, 0xE0
	  bl        -0x1EB0
	  lwz       r5, 0xA8(r31)
	  mr        r4, r31
	  lfs       f31, 0xE0(r1)
	  addi      r3, r1, 0xD4
	  lfs       f30, 0xE4(r1)
	  lfs       f29, 0xE8(r1)
	  addi      r5, r5, 0x1
	  bl        -0x1ED0
	  lfs       f1, 0xD4(r1)
	  lfs       f0, 0xD8(r1)
	  fsubs     f1, f1, f31
	  lfs       f2, 0xDC(r1)
	  fsubs     f0, f0, f30
	  stfs      f1, 0x100(r1)
	  fsubs     f1, f2, f29
	  stfs      f0, 0x104(r1)
	  stfs      f1, 0x108(r1)
	  lfs       f1, 0x100(r1)
	  lfs       f0, 0x104(r1)
	  fmuls     f1, f1, f1
	  lfs       f2, 0x108(r1)
	  fmuls     f0, f0, f0
	  fmuls     f2, f2, f2
	  fadds     f0, f1, f0
	  fadds     f1, f2, f0
	  bl        -0xA6484
	  lfs       f0, -0x7018(r2)
	  fcmpu     cr0, f0, f1
	  beq-      .loc_0x318
	  lfs       f0, 0x100(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x100(r1)
	  lfs       f0, 0x104(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x104(r1)
	  lfs       f0, 0x108(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x108(r1)

	.loc_0x318:
	  lfs       f4, -0x7018(r2)
	  stfs      f4, 0xF8(r1)
	  stfs      f4, 0xF4(r1)
	  stfs      f4, 0xF0(r1)
	  lwz       r0, 0x100(r1)
	  lwz       r3, 0x104(r1)
	  stw       r0, 0xF0(r1)
	  lwz       r0, 0x108(r1)
	  stw       r3, 0xF4(r1)
	  lfs       f0, 0x100(r1)
	  stw       r0, 0xF8(r1)
	  fmuls     f1, f0, f31
	  lfs       f0, 0x104(r1)
	  lfs       f2, 0x108(r1)
	  fmuls     f0, f0, f30
	  fmuls     f2, f2, f29
	  fadds     f0, f1, f0
	  fadds     f0, f2, f0
	  stfs      f0, 0xFC(r1)
	  lfs       f3, 0xF0(r1)
	  lfs       f2, 0x94(r29)
	  lfs       f1, 0xF4(r1)
	  lfs       f0, 0x98(r29)
	  fmuls     f2, f3, f2
	  lfs       f3, 0xF8(r1)
	  fmuls     f0, f1, f0
	  lfs       f1, 0x9C(r29)
	  lfs       f5, 0xFC(r1)
	  fmuls     f1, f3, f1
	  fadds     f0, f2, f0
	  fadds     f0, f1, f0
	  fsubs     f0, f0, f5
	  fcmpo     cr0, f0, f4
	  cror      2, 0, 0x2
	  bne-      .loc_0x3D0
	  lwz       r5, 0x94(r29)
	  li        r0, 0x4
	  lwz       r4, 0x98(r29)
	  li        r3, 0
	  stw       r5, 0x90(r31)
	  stw       r4, 0x94(r31)
	  lwz       r4, 0x9C(r29)
	  stw       r4, 0x98(r31)
	  sth       r0, 0x1C(r31)
	  stfs      f4, 0xA4(r31)
	  b         .loc_0x6DC

	.loc_0x3D0:
	  mr        r3, r31
	  bl        -0x14E4
	  rlwinm.   r0,r3,0,24,31
	  bne-      .loc_0x448
	  li        r0, 0x6
	  sth       r0, 0x1C(r31)
	  cmplwi    r31, 0
	  addi      r4, r31, 0
	  lfs       f0, -0x4C64(r13)
	  stfs      f0, 0x70(r29)
	  lfs       f0, -0x4C60(r13)
	  stfs      f0, 0x74(r29)
	  lfs       f0, -0x4C5C(r13)
	  stfs      f0, 0x78(r29)
	  lwz       r3, 0xC(r31)
	  lfs       f0, -0x4C58(r13)
	  stfsu     f0, 0x70(r3)
	  lfs       f0, -0x4C54(r13)
	  stfs      f0, 0x4(r3)
	  lfs       f0, -0x4C50(r13)
	  stfs      f0, 0x8(r3)
	  beq-      .loc_0x42C
	  lwz       r4, 0x14(r31)

	.loc_0x42C:
	  lwz       r3, 0xC(r31)
	  addi      r3, r3, 0x354
	  bl        0x6B8AC
	  lwz       r3, 0xC(r31)
	  bl        -0x239A4
	  li        r3, 0
	  b         .loc_0x6DC

	.loc_0x448:
	  lwz       r4, 0x3068(r13)
	  mr        r3, r31
	  lfs       f2, -0x6FA8(r2)
	  lwz       r4, 0x68(r4)
	  lfs       f0, -0x6FF0(r2)
	  lfs       f1, 0x78(r4)
	  fmuls     f30, f2, f1
	  fmuls     f29, f0, f30
	  bl        -0x51E8
	  lwz       r3, 0x55C(r29)
	  xoris     r0, r28, 0x8000
	  lfs       f0, -0x6FF4(r2)
	  lis       r4, 0x4330
	  stw       r0, 0x134(r1)
	  lwz       r0, 0x8C(r3)
	  fadds     f5, f0, f1
	  stw       r4, 0x130(r1)
	  fsubs     f1, f30, f29
	  xoris     r0, r0, 0x8000
	  stw       r0, 0x12C(r1)
	  lfd       f4, -0x6FE8(r2)
	  lfd       f0, 0x130(r1)
	  stw       r4, 0x128(r1)
	  fsubs     f3, f0, f4
	  lfs       f0, -0x7018(r2)
	  lfd       f2, 0x128(r1)
	  stfs      f0, 0x34(r31)
	  fsubs     f3, f5, f3
	  fsubs     f0, f2, f4
	  lfs       f4, 0x30(r31)
	  lfs       f2, 0x34(r31)
	  lfs       f5, 0x38(r31)
	  fdivs     f0, f3, f0
	  fmuls     f3, f0, f1
	  fmuls     f1, f4, f4
	  fmuls     f0, f2, f2
	  fmuls     f2, f5, f5
	  fadds     f29, f29, f3
	  fadds     f0, f1, f0
	  fadds     f1, f2, f0
	  bl        -0xA6688
	  lfs       f0, -0x7018(r2)
	  fcmpu     cr0, f0, f1
	  beq-      .loc_0x51C
	  lfs       f0, 0x30(r31)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x30(r31)
	  lfs       f0, 0x34(r31)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x34(r31)
	  lfs       f0, 0x38(r31)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x38(r31)

	.loc_0x51C:
	  lfs       f0, 0x30(r31)
	  addi      r3, r27, 0
	  addi      r5, r31, 0x30
	  fmuls     f0, f0, f29
	  rlwinm    r6,r30,0,16,31
	  stfs      f0, 0x30(r31)
	  lfs       f0, 0x34(r31)
	  fmuls     f0, f0, f29
	  stfs      f0, 0x34(r31)
	  lfs       f0, 0x38(r31)
	  fmuls     f0, f0, f29
	  stfs      f0, 0x38(r31)
	  lwz       r4, 0xC(r31)
	  bl        -0x1E6F4
	  b         .loc_0x6D8

	.loc_0x558:
	  lwz       r4, 0x18(r31)
	  cmplwi    r4, 0
	  bne-      .loc_0x56C
	  li        r0, 0
	  b         .loc_0x654

	.loc_0x56C:
	  addi      r3, r1, 0x70
	  bl        -0x236CC
	  addi      r0, r1, 0x70
	  stw       r0, 0x84(r1)
	  li        r0, 0
	  addi      r3, r1, 0x80
	  stw       r0, 0x88(r1)
	  bl        -0x245AC
	  b         .loc_0x5F4

	.loc_0x590:
	  lwz       r4, 0x80(r1)
	  cmpwi     r4, -0x1
	  bne-      .loc_0x5B8
	  lwz       r3, 0x84(r1)
	  li        r4, 0
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  b         .loc_0x5CC

	.loc_0x5B8:
	  lwz       r3, 0x84(r1)
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl

	.loc_0x5CC:
	  lwz       r0, 0x6C(r3)
	  cmpwi     r0, 0
	  bne-      .loc_0x5EC
	  lwz       r0, 0xC(r31)
	  sub       r0, r0, r3
	  cntlzw    r0, r0
	  rlwinm    r0,r0,27,5,31
	  b         .loc_0x654

	.loc_0x5EC:
	  addi      r3, r1, 0x80
	  bl        -0x24738

	.loc_0x5F4:
	  lwz       r3, 0x84(r1)
	  lwz       r4, 0x80(r1)
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0x61C
	  li        r0, 0x1
	  b         .loc_0x648

	.loc_0x61C:
	  lwz       r3, 0x84(r1)
	  lwz       r4, 0x80(r1)
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  cmplwi    r3, 0
	  bne-      .loc_0x644
	  li        r0, 0x1
	  b         .loc_0x648

	.loc_0x644:
	  li        r0, 0

	.loc_0x648:
	  rlwinm.   r0,r0,0,24,31
	  beq+      .loc_0x590
	  li        r0, 0

	.loc_0x654:
	  rlwinm.   r0,r0,0,24,31
	  beq-      .loc_0x668
	  lwz       r0, 0xA8(r31)
	  cmpwi     r0, -0x1
	  beq-      .loc_0x678

	.loc_0x668:
	  lwz       r3, 0xC(r31)
	  lwz       r0, 0x184(r3)
	  cmplwi    r0, 0
	  bne-      .loc_0x6D8

	.loc_0x678:
	  li        r0, 0x6
	  sth       r0, 0x1C(r31)
	  cmplwi    r31, 0
	  addi      r4, r31, 0
	  lfs       f0, -0x4C4C(r13)
	  stfs      f0, 0x70(r29)
	  lfs       f0, -0x4C48(r13)
	  stfs      f0, 0x74(r29)
	  lfs       f0, -0x4C44(r13)
	  stfs      f0, 0x78(r29)
	  lwz       r3, 0xC(r31)
	  lfs       f0, -0x4C40(r13)
	  stfsu     f0, 0x70(r3)
	  lfs       f0, -0x4C3C(r13)
	  stfs      f0, 0x4(r3)
	  lfs       f0, -0x4C38(r13)
	  stfs      f0, 0x8(r3)
	  beq-      .loc_0x6C4
	  lwz       r4, 0x14(r31)

	.loc_0x6C4:
	  lwz       r3, 0xC(r31)
	  addi      r3, r3, 0x354
	  bl        0x6B614
	  lwz       r3, 0xC(r31)
	  bl        -0x23C3C

	.loc_0x6D8:
	  li        r3, 0

	.loc_0x6DC:
	  lmw       r27, 0x13C(r1)
	  lwz       r0, 0x16C(r1)
	  lfd       f31, 0x160(r1)
	  lfd       f30, 0x158(r1)
	  lfd       f29, 0x150(r1)
	  addi      r1, r1, 0x168
	  mtlr      r0
	  blr
	*/
}
