#include "Nucleus.h"
#include "Collision.h"
#include "Graphics.h"
#include "Shape.h"
#include "sysNew.h"
#include "Dolphin/os.h"

/*
 * --INFO--
 * Address:	........
 * Size:	00009C
 */
static void _Error(char* fmt, ...)
{
	OSPanic(__FILE__, __LINE__, fmt);
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000F0
 */
static void _Print(char*, ...)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	8017A1AC
 * Size:	000090
 */
NucleusProp::NucleusProp()
{
	mCreatureProps.mFriction.mValue      = 1.0f;
	mCreatureProps.mFaceDirAdjust.mValue = 0.0f;
	mCreatureProps.mAcceleration.mValue  = 1.0f;
}

/*
 * --INFO--
 * Address:	8017A23C
 * Size:	000084
 */
Nucleus::Nucleus(CreatureProp* props)
    : Boss(props)
{
	mCollInfo  = new CollInfo(3);
	mNucleusAI = new NucleusAi(this);
}

/*
 * --INFO--
 * Address:	8017A2C0
 * Size:	000008
 */
f32 Nucleus::getiMass() { return 0.01f; }

/*
 * --INFO--
 * Address:	8017A2C8
 * Size:	000060
 */
void Nucleus::init(Vector3f&)
{
	mCollisionRadius = 20.0f;
	mScale.set(0.0f, 0.0f, 0.0f);
	_2B8 = 0;
	_2BE = 1;
	_2E0 = 30.0f;
	mNucleusAI->initAI(this);
}

/*
 * --INFO--
 * Address:	8017A328
 * Size:	000034
 */
void Nucleus::doKill()
{
	_2B8 = 0;
	_2B9 = 0;
	bossMgr->kill(this);
}

/*
 * --INFO--
 * Address:	8017A35C
 * Size:	000004
 */
void Nucleus::exitCourse() { }

/*
 * --INFO--
 * Address:	8017A360
 * Size:	000020
 */
void Nucleus::update() { Creature::update(); }

/*
 * --INFO--
 * Address:	8017A380
 * Size:	000098
 */
void Nucleus::refresh(Graphics& gfx)
{
	mTransformMatrix.makeSRT(mScale, mRotation, mPosition);
	Matrix4f mtx;
	gfx.mCamera->mLookAtMtx.multiplyTo(mTransformMatrix, mtx);
	mAnimator.updateContext();
	mShapeObject->mShape->updateAnim(gfx, mtx, nullptr);
	mCollInfo->updateInfo(gfx, false);
}

/*
 * --INFO--
 * Address:	8017A418
 * Size:	00006C
 */
void Nucleus::drawShape(Graphics& gfx)
{
	gfx.useMatrix(Matrix4f::ident, 0);
	mShapeObject->mShape->drawshape(gfx, *gfx.mCamera, nullptr);
}

/*
 * --INFO--
 * Address:	8017A484
 * Size:	000024
 */
void Nucleus::doAI() { mNucleusAI->update(); }

/*
 * --INFO--
 * Address:	8017A4A8
 * Size:	000044
 */
void Nucleus::doAnimation()
{
	if (mShapeObject) {
		mAnimator.animate(getMotionSpeed());
	}
}
