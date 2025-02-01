#include "PikiAI.h"
#include "PikiMgr.h"
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
 * Size:	0000F0
 */
DEFINE_PRINT(nullptr)

/*
 * --INFO--
 * Address:	800BB534
 * Size:	000084
 */
ActGuard::ActGuard(Piki* piki)
    : Action(piki, true)
{
	mTarget.clear();
	mLeft.clear();
	mRight.clear();
	_49 = 0;
	_3C = 30.0f;
}

/*
 * --INFO--
 * Address:	800BB5B8
 * Size:	0000C4
 */
void ActGuard::init(Creature*)
{
	mTarget.clear();
	mLeft.clear();
	mRight.clear();
	Piki* friendPiki = findFriend();
	if (friendPiki) {
		mTarget.set(friendPiki);
	}

	mTimer     = 6.0f;
	mIsWaiting = 0;
	_49        = 1;
	mPiki->startMotion(PaniMotionInfo(PIKIANIM_Wait), PaniMotionInfo(PIKIANIM_Wait));
}

/*
 * --INFO--
 * Address:	800BB67C
 * Size:	00011C
 */
void ActGuard::cleanup()
{
	mTarget.reset();
	if (!mRight.isNull()) {
		static_cast<ActGuard*>(static_cast<Piki*>(mRight.getPtr())->mActiveAction->getCurrAction())->mLeft.reset();
		mRight.reset();
	}

	if (!mLeft.isNull()) {
		static_cast<ActGuard*>(static_cast<Piki*>(mLeft.getPtr())->mActiveAction->getCurrAction())->mRight.reset();
		mLeft.reset();
	}

	_49 = 0;

	// this isn't elaborated on in the DLL either.
	rand();
	u32 badCompiler[4];
}

/*
 * --INFO--
 * Address:	800BB798
 * Size:	00000C
 */
void ActGuard::dump()
{
	if (mTarget.isNull()) {
		PRINT(" target is null (%x)\n", mTarget.getPtr());
	} else {
		PRINT(" xx target = %x(%.1f,%.1f) timer = %.1f\n", mTarget.getPtr(), mTarget.getPtr()->mPosition.x, mTarget.getPtr()->mPosition.z,
		      mTimer);
	}

	PRINT(" wait = %s landPos=(%.1f,%.1f)\n", mIsWaiting ? "true" : "false", mLandPosition.x, mLandPosition.z);
	PRINT(" currPos(%.1f,%.1f)\n", mPiki->mPosition.x, mPiki->mPosition.z);
}

/*
 * --INFO--
 * Address:	800BB7A4
 * Size:	00071C
 */
int ActGuard::exec()
{
	mPiki->mTargetVelocity.set(0.0f, 0.0f, 0.0f);
	if (mTarget.isNull()) {
		mTimer -= gsys->getFrameTime();
		if (mTimer < 0.0f) {
			return ACTOUT_Fail;
		}

		init(nullptr);
		return ACTOUT_Continue;
	}

	if (mIsWaiting) {
		Creature* sidePiki = mLeft.getPtr();
		if (sidePiki) {
			Vector3f dir     = sidePiki->mPosition - mPiki->mPosition;
			f32 angle        = atan2f(dir.x, dir.z);
			f32 dist         = dir.length();
			dir              = dir * (1.0f / dist);
			Vector3f offset  = (dist - _3C) * dir * gsys->getFrameTime() * 13.0f;
			mPiki->mVelocity = mPiki->mVelocity + offset - mPiki->mVelocity * gsys->getFrameTime() * 0.1f;

			if (angDist(angle, sidePiki->mFaceDirection) > 0.0f) {
				mPiki->mFaceDirection += angDist(roundAng(angle - HALF_PI), mPiki->mFaceDirection) * gsys->getFrameTime() / 0.5f;
			} else {
				mPiki->mFaceDirection += angDist(roundAng(angle + HALF_PI), mPiki->mFaceDirection) * gsys->getFrameTime() / 0.5f;
			}
		}

		sidePiki = mRight.getPtr();
		if (sidePiki) {
			Vector3f dir     = sidePiki->mPosition - mPiki->mPosition;
			f32 dist         = dir.length();
			dir              = dir * (1.0f / dist);
			Vector3f offset  = (dist - _3C) * dir * gsys->getFrameTime() * 13.0f;
			mPiki->mVelocity = mPiki->mVelocity + offset - mPiki->mVelocity * gsys->getFrameTime() * 0.1f;
		}

		return ACTOUT_Continue;
	}

	if (!mLeft.isNull() || !mRight.isNull()) {
		PRINT("############ left is %x right is %x but wait is false\n", mLeft.getPtr(), mRight.getPtr());
	}

	setGoal();

	bool doSet = false;
	if (_44 == 1) {
		doSet = setRight();
	} else {
		doSet = setLeft();
	}

	if (doSet) {
		mIsWaiting = true;
		_3C        = 30.0f;
		if (_44 == 1) {
			_44 = 0;
		} else {
			_44 = 1;
		}
		Piki* friendPiki = findFriend(_44);
		if (friendPiki) {
			mTarget.set(friendPiki);
			if (_44 == 1) {
				setRight();
			} else {
				setLeft();
			}
		}
	} else {
		mTarget.reset();
	}

	mPiki->mTargetVelocity.set(0.0f, 0.0f, 0.0f);
	return ACTOUT_Continue;
}

/*
 * --INFO--
 * Address:	800BBEC0
 * Size:	0001F4
 */
Piki* ActGuard::findFriend()
{
	Iterator iter(pikiMgr);
	Piki* friendPiki = nullptr;
	f32 minDist      = 70.0f;

	CI_LOOP(iter)
	{
		Piki* piki = static_cast<Piki*>(*iter);
		if (piki != mPiki && piki->isVisible() && piki->mMode == PikiMode::GuardMode
		    && static_cast<ActGuard*>(piki->mActiveAction->getCurrAction())->_49) {
			f32 dist = qdist2(piki, mPiki);
			if (dist < minDist && (!getLeft(piki) || !getRight(piki))) {
				friendPiki = piki;
				minDist    = dist;
			}
		}
	}

	if (friendPiki) {
		Vector3f dir = mPiki->mPosition - friendPiki->mPosition;
		_2C          = atan2f(dir.x, dir.z);
	}

	return friendPiki;
}

/*
 * --INFO--
 * Address:	800BC0B4
 * Size:	0000FC
 */
int ActGuard::checkLoop(Piki* piki)
{
	Piki* currPiki = piki;
	int count      = -1;
	while (getLeft(currPiki) && getLeft(currPiki) != piki) {
		Piki* next = getLeft(currPiki);
		if (next == mPiki) {
			return count;
		}

		currPiki = next;
		count++;
	}

	count = -1;
	while (getRight(currPiki) && getRight(currPiki) != piki) {
		Piki* next = getRight(currPiki);
		if (next == mPiki) {
			return count;
		}

		currPiki = next;
		count++;
	}
	return -1;
}

/*
 * --INFO--
 * Address:	800BC1B0
 * Size:	000258
 */
Piki* ActGuard::findFriend(int idx)
{
	Iterator iter(pikiMgr);
	Piki* friendPiki = nullptr;
	f32 minDist      = 90.0f;
	CI_LOOP(iter)
	{
		Piki* piki = static_cast<Piki*>(*iter);
		if (piki != mTarget.getPtr() && piki != mPiki && piki->isVisible() && piki->mMode == PikiMode::GuardMode
		    && static_cast<ActGuard*>(piki->mActiveAction->getCurrAction())->_49) {
			f32 dist = qdist2(piki, mPiki);
			if (getLeft(piki) && idx == 0) {
				continue;
			}

			if (getRight(piki) && idx == 1) {
				continue;
			}

			int loopIdx = checkLoop(piki);
			if (loopIdx != -1 && loopIdx < 3) {
				continue;
			}
			if (dist < minDist && (!getLeft(piki) || !getRight(piki))) {
				friendPiki = piki;
				minDist    = dist;
			}
		}
	}

	if (friendPiki) {
		Vector3f dir = mPiki->mPosition - friendPiki->mPosition;
		_2C          = atan2f(dir.x, dir.z);
	}

	return friendPiki;
}

/*
 * --INFO--
 * Address:	800BC408
 * Size:	0001F8
 */
void ActGuard::setGoal()
{
	Piki* target = static_cast<Piki*>(mTarget.getPtr());
	if (getLeft(target) && !getRight(target)) {
		_44 = 1;
	} else if (!getLeft(target) && getRight(target)) {
		_44 = 0;
	} else if (!getLeft(target) && !getRight(target)) {
		if (unitRandFloat() > 0.5f) {
			_44 = 1;
		} else {
			_44 = 0;
		}
	} else {
		mTarget.reset();
		return;
	}

	Vector3f targetPos(target->mPosition);
	f32 rad = 2.5f * target->getSize();

	f32 angle = (_44 == 1) ? _2C : PI - _2C;

	targetPos = targetPos + Vector3f(rad * sinf(angle), 0.0f, rad * cosf(angle));
	_20       = targetPos;
}

/*
 * --INFO--
 * Address:	800BC600
 * Size:	000088
 */
Piki* ActGuard::getLeft(Piki* piki)
{
	Piki* left = nullptr;
	if (piki->isVisible() && piki->mMode == PikiMode::GuardMode) {
		left = static_cast<Piki*>(static_cast<ActGuard*>(piki->mActiveAction->getCurrAction())->mLeft.getPtr());
	}

	return left;
}

/*
 * --INFO--
 * Address:	800BC688
 * Size:	000088
 */
Piki* ActGuard::getRight(Piki* piki)
{
	Piki* right = nullptr;
	if (piki->isVisible() && piki->mMode == PikiMode::GuardMode) {
		right = static_cast<Piki*>(static_cast<ActGuard*>(piki->mActiveAction->getCurrAction())->mRight.getPtr());
	}

	return right;
}

/*
 * --INFO--
 * Address:	800BC710
 * Size:	0001C4
 */
bool ActGuard::setLeft()
{
	Piki* target = static_cast<Piki*>(mTarget.getPtr());
	if (target->isVisible() && target->mMode == PikiMode::GuardMode) {
		if (getLeft(target)) {
			PRINT("CANNOT HAPPEN !!!! left hand duplicates %x->%x\n", mPiki, target);
		}

		static_cast<ActGuard*>(target->mActiveAction->getCurrAction())->mLeft.set(mPiki);
		static_cast<ActGuard*>(target->mActiveAction->getCurrAction())->mLandPosition.set(target->mPosition);
		static_cast<ActGuard*>(target->mActiveAction->getCurrAction())->mIsWaiting = true;
		mRight.set(target);
		return true;
	}

	return false;
}

/*
 * --INFO--
 * Address:	800BC8D4
 * Size:	0001C4
 */
bool ActGuard::setRight()
{
	Piki* target = static_cast<Piki*>(mTarget.getPtr());
	if (target->isVisible() && target->mMode == PikiMode::GuardMode) {
		if (getRight(target)) {
			PRINT("CANNOT HAPPEN !!!! right hand duplicates %x->%x\n", mPiki, target);
		}

		static_cast<ActGuard*>(target->mActiveAction->getCurrAction())->mRight.set(mPiki);
		static_cast<ActGuard*>(target->mActiveAction->getCurrAction())->mLandPosition.set(target->mPosition);
		static_cast<ActGuard*>(target->mActiveAction->getCurrAction())->mIsWaiting = true;
		mLeft.set(target);
		return true;
	}

	return false;
}
