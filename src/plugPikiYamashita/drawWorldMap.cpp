#include "zen/DrawWorldMap.h"
#include "zen/EffectMgr2D.h"
#include "zen/DrawCommon.h"
#include "P2D/Pane.h"
#include "P2D/TextBox.h"
#include "nlib/Math.h"
#include "DebugLog.h"
#include "sysNew.h"

#define MAX_PARTS_PRACTICE  (2)
#define MAX_PARTS_FOREST    (8)
#define MAX_PARTS_CAVE      (9)
#define MAX_PARTS_YAKUSHIMA (10)
#define MAX_PARTS_LAST      (1)

namespace {
zen::EffectMgr2D* WMeffMgr;

// idk what's going on with these. mapNoScr2Game has to spit out WorldMapName values, which have to equal StageID values
u8 mapNoScr2Game[5] = { WM_Yakushima, WM_Forest, WM_Practice, WM_Cave, WM_Last };
u8 mapNoGame2Scr[5] = { WMSCR_Practice, WMSCR_Forest, WMSCR_Cave, WMSCR_Yakushima, WMSCR_Last };
} // namespace

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
DEFINE_PRINT("drawWorldMap")

namespace zen {
/**
 * @brief TODO
 *
 * @note Size: 0x28.
 */
struct WorldMapWipe {
	WorldMapWipe() { mWipePane = nullptr; }

	// weak
	void init(P2DScreen* wipeScreen, u32 tag)
	{
		P2DPane* pane = wipeScreen->search(tag, true);
		if (pane->getTypeID() == PANETYPE_Picture) {
			mWipePane = (P2DPicture*)pane;
			_00.set(mWipePane->getPosH() + (mWipePane->getWidth() >> 1), mWipePane->getPosV() + (mWipePane->getHeight() >> 1), 0.0f);
			move(mWipePane->getPosH(), mWipePane->getPosV());

		} else {
			// these are load bearing, take these out and this inlines :')
			PRINT("not picture pane.\n");
			ERROR("not picture pane.\n");
		}
	}

	void move(int x, int y)
	{
		x -= (mWipePane->getWidth() >> 1);
		y -= (mWipePane->getHeight() >> 1);

		_0C.set(mWipePane->getPosH(), mWipePane->getPosV(), 0.0f);
		_18.set(x, y, 0.0f);
	}

	void set(int x, int y)
	{
		x -= (mWipePane->getWidth() >> 1);
		y -= (mWipePane->getHeight() >> 1);
		mWipePane->move(x, y);
		_0C.set(x, y, 0.0f);
		_18.set(x, y, 0.0f);
	}

	void moveDefaultPos() { move(zen::RoundOff(_00.x), zen::RoundOff(_00.y)); }
	void update(f32 t, u8 alpha)
	{
		f32 tComp = 1.0f - t;
		mWipePane->move(zen::RoundOff(_0C.x * tComp + _18.x * t), zen::RoundOff(_0C.y * tComp + _18.y * t));
		mWipePane->setAlpha(alpha);
	}

	void setDefault() { set(zen::RoundOff(_00.x), zen::RoundOff(_00.y)); }

	Vector3f _00;          // _00
	Vector3f _0C;          // _0C
	Vector3f _18;          // _18
	P2DPicture* mWipePane; // _24
};

/**
 * @brief TODO
 *
 * @note Size: 0xB0.
 */
struct WorldMapWipeMgr {
	WorldMapWipeMgr()
	{
		_04       = 0.0f;
		_08       = 1.0f;
		mIsActive = false;
	}

	void init(P2DScreen* wipeScreen)
	{
		mWipes[0].init(wipeScreen, 'wp00');
		mWipes[1].init(wipeScreen, 'wp01');
		mWipes[2].init(wipeScreen, 'wp02');
		mWipes[3].init(wipeScreen, 'wp03');
		init();
	}

	void init()
	{
		_04       = 0.0f;
		_08       = 0.8f;
		mIsActive = false;
	}

	void set(int x, int y)
	{
		for (int i = 0; i < 4; i++) {
			mWipes[i].set(x, y);
		}
		_00 = 0;
	}

	void open(f32 p1)
	{
		_04 = 0.0f;
		_08 = p1;
		for (int i = 0; i < 4; i++) {
			mWipes[i].moveDefaultPos();
		}
		_00       = 2;
		mIsActive = true;
	}

	bool isActive() { return mIsActive; }

	bool update()
	{
		int i;
		f32 blendFactor;
		u8 alpha;

		mIsActive = false;
		switch (int state = _00) {
		case 0:
			break;
		case 1:
		case 2:
			_04 += gsys->getFrameTime();
			if (_04 > _08) {
				_04   = _08;
				state = 0;
			}
			if (_00 == 2) {
				blendFactor = (1.0f - NMathF::cos(_04 / _08 * PI)) * 0.5f;
				alpha       = zen::RoundOff(255.0f * (1.0f - blendFactor));
			} else {
				blendFactor = NMathF::sin(_04 / _08 * HALF_PI);
				alpha       = zen::RoundOff(255.0f * blendFactor);
			}

			for (i = 0; i < 4; i++) {
				mWipes[i].update(blendFactor, alpha);
			}

			_00       = state;
			mIsActive = true;
			break;
		}

		return mIsActive;
	}

	void close(f32 p1, int p2, int p3)
	{
		_04 = 0.0f;
		_08 = p1;
		for (int i = 0; i < 4; i++) {
			mWipes[i].move(p2, p3);
		}
		_00       = 1;
		mIsActive = true;
	}

	void setDefault()
	{
		for (int i = 0; i < 4; i++) {
			mWipes[i].setDefault();
		}
		_00 = 0;
	}

	int _00;                // _00
	f32 _04;                // _04
	f32 _08;                // _08
	WorldMapWipe mWipes[4]; // _0C
	bool mIsActive;         // _AC
};

/**
 * @brief TODO
 *
 * @note Size: 0x3C.
 */
struct WorldMapCursorOnyon {
	WorldMapCursorOnyon()
	{
		mOnyonIcon = nullptr;
		_04.set(0.0f, 0.0f, 0.0f);
		_1C.set(0.0f, 0.0f, 0.0f);
		_34 = zen::Rand(scaleFrameMax);
		mBottomPos.set(0.0f, bottomLengthDefault, 0.0f);
	}

	// weak:
	void init()
	{
		if (mOnyonIcon) {
			mOnyonIcon->setOffset(mOnyonIcon->getWidth() >> 1, mOnyonIcon->getHeight() >> 2);
		} else {
			PRINT("Illegal init WorldMapCursorOnyon Class.\n");
			ERROR("Illegal initialize.");
		}

		_34 = zen::Rand(scaleFrameMax);

		_04.set(0.0f, 0.0f, 0.0f);
		_1C.set(0.0f, 0.0f, 0.0f);
		mBottomPos.set(0.0f, bottomLengthDefault, 0.0f);

		_38 = WMeffMgr->create(EFF2D_MapOnyonSparkle, Vector3f(0.0f, 0.0f, 0.0f), nullptr, nullptr);
	}
	void update(Vector3f& scale)
	{
		Vector3f vec1 = _10 - _04;
		f32 time      = 60.0f * gsys->getFrameTime();
		f32 len1      = vec1.length();
		if (len1 > 0.000001f) {
			f32 factor = len1 / 300.0f * 10.0f;
			vec1.div(len1);
			if (factor > 15.0f) {
				factor = 15.0f;
			}

			_1C.set(Vector3f(vec1 * factor * time));
			_04.add(_1C);
		}

		mOnyonIcon->move(_04.x, _04.y);
		updateBottomPos();
		_34 += gsys->getFrameTime();
		if (_34 > scaleFrameMax) {
			_34 -= scaleFrameMax;
		}
		f32 angle = _34 / scaleFrameMax;
		mOnyonIcon->setScale(
		    Vector3f(0.9f * scale.x + 0.1f * NMathF::sin(TAU * angle), 0.9f * scale.y - 0.1f * NMathF::sin(TAU * angle), 1.0f));
		if (_38) {
			Vector3f vec2;
			vec2.set(mOnyonIcon->getPosH() + (mOnyonIcon->getWidth() >> 1), mOnyonIcon->getPosV(), 0.0f);
			vec2.y = 480.0f - vec2.y;
			_38->setEmitPos(vec2);
		}
	}

	// DLL:
	void init(P2DScreen* iconScreen, u32 tag, bool hideIcon)
	{
		P2DPane* icon = iconScreen->search(tag, true);
		if (icon->getTypeID() == PANETYPE_Picture) {
			mOnyonIcon = (P2DPicture*)icon;
			if (hideIcon) {
				mOnyonIcon->hide();
			}
		}

		init();
	}
	void show()
	{
		mOnyonIcon->show();
		if (_38) {
			_38->startGen();
		}
	}
	void hide()
	{
		mOnyonIcon->hide();
		if (_38) {
			_38->stopGen();
		}
	}
	void move(f32 x, f32 y) { _10.set(x, y, 0.0f); }
	void set(f32 x, f32 y, f32 scale)
	{
		_04.set(x, y, 0.0f);
		_10.set(x, y, 0.0f);
		mBottomPos.set(x, y + bottomLengthDefault, 0.0f);
		mOnyonIcon->move(_04.x, _04.y);
		mOnyonIcon->setScale(Vector3f(scale, scale, 1.0f));
	}

	void updateBottomPos()
	{
		Vector3f vec1;
		Vector3f vec2;
		vec2.set(mBottomPos.x, mBottomPos.y + 3.0f * gsys->getFrameTime() * 60.0f, mBottomPos.z);
		vec1.set(vec2 - _04);

		f32 len1 = vec1.length();
		if (len1 < 0.000001f) {
			vec1.set(mBottomPos - _04);
			len1 = vec1.length();

			if (len1 < 0.000001f) {
				vec1.set(0.0f, bottomLengthDefault, 0.0f);
				len1 = bottomLengthDefault;
			}
		}

		if (len1 < bottomLengthMin) {
			vec1.multiply(bottomLengthMin / len1);
		} else if (len1 > bottomLengthMax) {
			vec1.multiply(bottomLengthMax / len1);
		}

		vec2.set(_04 + vec1);
		mOnyonIcon->rotateZ(NMathF::atan2(vec1.y, vec1.x) - HALF_PI);
		vec1.normalize();

		vec1.multiply((bottomLengthDefault - len1) * gsys->getFrameTime() * 10.0f);
		mBottomPos.set(vec2);
	}

	static f32 scaleFrameMax;
	static f32 bottomLengthMin;
	static f32 bottomLengthMax;
	static f32 bottomLengthDefault;

	P2DPicture* mOnyonIcon; // _00
	Vector3f _04;           // _04
	Vector3f _10;           // _10
	Vector3f _1C;           // _1C
	Vector3f mBottomPos;    // _28
	f32 _34;                // _34
	particleGenerator* _38; // _38
};

/**
 * @brief TODO
 *
 * @note Size: 0x12C.
 */
struct WorldMapCursorMgr {

	/**
	 * @brief TODO
	 */
	enum ufoStatusFlag {
		UFO_Unk0 = 0,
		UFO_Unk1 = 1,
		UFO_Unk2 = 2,
	};

	WorldMapCursorMgr()
	{
		mRocketIcon = nullptr;
		for (int i = 0; i < 2; i++) {
			_110[i] = 0;
		}

		initParams();
	}

	// weak functions:
	void initParams()
	{
		setLandingFlag(false);
		_35 = 0;
		_38.set(0.0f, 0.0f, 0.0f);
		_00 = 0.0f;
		_0C.set(0.0f, 0.0f, 0.0f);
		_24.set(0.0f, 0.0f, 0.0f);
		mRocketPos.set(0.0f, 0.0f, 0.0f);
		_30 = 0.0f;
		mBlueOnyonPos.set(0.0f, 0.0f, 0.0f);
		mOnyonVelocity.set(0.0f, 0.0f, 0.0f);
		setUfoStatus(UFO_Unk0);
		_128 = 1.0f;
	}

	void setLandingFlag(bool doSet)
	{
		if (doSet) {
			_34 = 1;
			SeSystem::playSysSe(SYSSE_SELECT_DECIDE);

			if (_110[0]) {
				_110[0]->setFreqFrm(4.0f * _118);
			}
			if (_110[1]) {
				_110[1]->setFreqFrm(5.0f * _11C);
			}
		} else {
			_34 = 0;
			if (_110[0]) {
				_110[0]->setFreqFrm(_118);
			}
			if (_110[1]) {
				_110[1]->setFreqFrm(_11C);
			}
		}
	}
	void init()
	{
		int i;
		if (mRocketIcon) {
			mRocketPos.set(mRocketIcon->getPosH(), mRocketIcon->getPosV(), 0.0f);
			mRocketIcon->setOffset(mRocketIcon->getWidth() >> 1, mRocketIcon->getHeight() >> 1);
			mRocketIcon->setScale(1.0f);
		} else {
			PRINT("Illegal initilize.\n");
			ERROR("Illegal initilize.\n");
		}

		initParams();
		mCursorOnyons[Blue].init();
		mCursorOnyons[Red].init();
		mCursorOnyons[Yellow].init();

		for (i = 0; i < 2; i++) {
			if (_110[i]) {
				_110[0]->forceFinish(); // oops
			}
		}

		_110[0] = WMeffMgr->create(EFF2D_MapRocketFire, Vector3f(0.0f, 0.0f, 0.0f), nullptr, nullptr);
		_110[0]->invisible();
		_118 = _110[0]->getFreqFrm();
		_120 = _110[0]->getInitVel();

		_110[1] = WMeffMgr->create(EFF2D_MapRocketSmoke, Vector3f(0.0f, 0.0f, 0.0f), nullptr, nullptr);
		_110[1]->invisible();
		_11C = _110[1]->getFreqFrm();
		_124 = _110[0]->getInitVel(); // maybe typo?

		if (playerState) {
			for (i = 0; i < PikiColorCount; i++) {
				if (playerState->displayPikiCount(i)) {
					mCursorOnyons[i].show();
				} else {
					mCursorOnyons[i].hide();
				}
			}
		} else {
			mCursorOnyons[Blue].show();
			mCursorOnyons[Red].show();
			mCursorOnyons[Yellow].show();
		}
	}
	void moveOnyon()
	{
		Vector3f onyonPos[PikiColorCount];
		updateOnyonPos(&onyonPos[Blue], &onyonPos[Red], &onyonPos[Yellow]);
		mCursorOnyons[Blue].move(onyonPos[Blue].x, onyonPos[Blue].y);
		mCursorOnyons[Red].move(onyonPos[Red].x, onyonPos[Red].y);
		mCursorOnyons[Yellow].move(onyonPos[Yellow].x, onyonPos[Yellow].y);
	}
	void updateOnyonPos(Vector3f* bluePos, Vector3f* redPos, Vector3f* yellowPos)
	{
		Vector3f orbitCenter;
		Vector3f newBlueTargetPos;
		Vector3f orbitVec;

		f32 time        = 60.0f * gsys->getFrameTime();
		f32 rocketScale = mRocketIcon->getScale().x;
		orbitCenter.set(mRocketPos.x + ONYON_OFFSET_X, mRocketPos.y + ONYON_OFFSET_Y, mRocketPos.z + ONYON_OFFSET_Z);

		mBlueOnyonPos.add(Vector3f(mOnyonVelocity * time));
		orbitVec.set(mBlueOnyonPos - orbitCenter);
		f32 norm = orbitVec.length();
		if (norm < 0.000001f) {
			orbitVec.set(0.0f, 0.0f, 0.0f);
		} else {
			orbitVec.multiply(ONYON_POS_RADIUS * rocketScale / norm);
		}

		newBlueTargetPos.set(orbitCenter + orbitVec);
		mOnyonVelocity.add(Vector3f(newBlueTargetPos - mBlueOnyonPos));
		mBlueOnyonPos.set(newBlueTargetPos);

		// set blue onyon position (just calculated, reference for others)
		bluePos->set(mBlueOnyonPos.x, mBlueOnyonPos.y, 0.0f);

		// calculate red onyon position (120 degrees rotated from blue)
		f32 cosR = cosf(TORADIANS(120));
		f32 sinR = sinf(TORADIANS(120));
		redPos->set(orbitVec.x * cosR + orbitCenter.x - orbitVec.y * sinR, orbitVec.x * sinR + orbitCenter.y + orbitVec.y * cosR, 0.0f);

		// calculate yellow onyon position (240 degrees rotated from blue)
		f32 cosY = cosf(TORADIANS(240));
		f32 sinY = sinf(TORADIANS(240));
		yellowPos->set(orbitVec.x * cosY + orbitCenter.x - orbitVec.y * sinY, orbitVec.x * sinY + orbitCenter.y + orbitVec.y * cosY, 0.0f);
	}
	void stayUfo()
	{
		Vector3f vec1;
		f32 sec = 60.0f * gsys->getFrameTime();
		vec1.set(_0C.x - mRocketPos.x, _0C.y - mRocketPos.y, 0.0f);
		vec1.multiply(0.8f * gsys->getFrameTime());
		_24.add(vec1);
		_24.multiply(0.92f);
		f32 len = _24.length();
		if (len < 0.000001f) {
			_24.set(0.0f, 0.5f, 0.0f);
		} else {
			if (len > 1.0f) {
				_24.multiply(1.0f / len);
			}
			if (len < 0.5f) {
				_24.multiply(0.5f / len);
			}
		}

		mRocketPos.add(_24);

		mRocketIcon->move(zen::RoundOff(mRocketPos.x), zen::RoundOff(mRocketPos.y));
		_30 += calcAddAngle(mRocketIcon->getRotate(), 0.0f, 0.017453292f, sec);
		_30 *= 0.9999f;
		if (_30 > (5.0f * PI / 180.0f)) {
			_30 = (5.0f * PI / 180.0f);
		}
		if (_30 < -(5.0f * PI / 180.0f)) {
			_30 = -(5.0f * PI / 180.0f);
		}

		rotateUfo(zen::correctRad(_30 + mRocketIcon->getRotate()));

		STACK_PAD_VAR(1);
	}

	bool moveUfo()
	{
		bool res = false;
		Vector3f vec1;
		f32 d;
		f32 sec   = 60.0f * gsys->getFrameTime();
		f32 scale = mRocketIcon->getScale().x;
		f32 a     = 1.0f;

		vec1.set(_0C.x - mRocketPos.x, _0C.y - mRocketPos.y, 0.0f);
		f32 len1 = vec1.length();
		f32 b    = mRocketIcon->getRotate() - HALF_PI;
		b        = zen::correctRad(b);
		f32 c    = NMathF::atan2(vec1.y, vec1.x);
		d        = len1 / 300.0f * 15.0f;
		f32 e;
		if (_34) {
			_00 += gsys->getFrameTime();
			if (len1 < 10.0f) {
				a = 0.0f;
				if (scale == 0.0f) {
					res = true;
				}
			} else {
				a = len1 / 300.0f;
				if (a > 1.0f) {
					a = 1.0f;
				}
			}

			d *= 1.5f;
			e = 20.0f * _00;
			if (e > 180.0f) {
				e = 0.0f;
			}
		} else {
			if (len1 < 20.0f && scale == 1.0f) {
				res = true;
			}
			e = 10.0f;
		}

		b += calcAddAngle(b, c, e * PI / 180.0f, sec);

		rotateUfo(zen::correctRad(b + HALF_PI));

		if (d > 15.0f) {
			d = 15.0f;
		}

		_24.set(d * NMathF::cos(b) * sec, d * NMathF::sin(b) * sec, 0.0f);
		mRocketPos.add(_24);

		// don't let the rocket go more than 100 out of screen bounds (640 x 480)
		if (mRocketPos.x < (0.0f - 100.0f)) {
			mRocketPos.x = (0.0f - 100.0f);
		}
		if (mRocketPos.x > (640.0f + 100.0f)) {
			mRocketPos.x = (640.0f + 100.0f);
		}

		if (mRocketPos.y < (0.0f - 100.0f)) {
			mRocketPos.y = (0.0f - 100.0f);
		}
		if (mRocketPos.y > (480.0f + 100.0f)) {
			mRocketPos.y = (480.0f + 100.0f);
		}

		mRocketIcon->move(zen::RoundOff(mRocketPos.x), zen::RoundOff(mRocketPos.y));

		if (zen::Abs(scale - a) < 0.02f) {
			scale = a;
		} else if (scale < a) {
			scale += 0.02f * sec;
		} else {
			scale -= 0.02f * sec;
		}

		mRocketIcon->setScale(scale);

		STACK_PAD_VAR(2);
		return res;
	}
	void forceMove()
	{
		if (_35) {
			setUfoStatus(UFO_Unk1);
			_00 = 0.0f;
			_0C.set(_38);
			_35 = false;
			setLandingFlag(true);
		} else {
			PRINT("can't forceMove.\n");
			ERROR("can't forceMove.");
		}
	}
	void effect()
	{
		f32 angle = mRocketIcon->getRotate() - HALF_PI;
		Vector3f vec1;
		vec1.set(mRocketIcon->getPosH() + (mRocketIcon->getWidth() >> 1), mRocketIcon->getPosV() + (mRocketIcon->getHeight() >> 1), 0.0f);
		vec1.add(Vector3f(NMathF::cos(angle) * (-f32(mRocketIcon->getWidth() >> 1) * mRocketIcon->getScale().x),
		                  NMathF::sin(angle) * (-f32(mRocketIcon->getHeight() >> 1) * mRocketIcon->getScale().y), 0.0f));
		vec1.y = 480.0f - vec1.y;

		if (_110[0]) {
			_110[0]->visible();
			_110[0]->setEmitPos(vec1);
			_110[0]->setEmitDir(Vector3f(-NMathF::cos(angle), NMathF::sin(angle), 0.0f));
			_110[0]->setScaleSize(mRocketIcon->getScale().x * 0.5f);
			_110[0]->setInitVel(_120 * mRocketIcon->getScale().x * mRocketIcon->getScale().x);
			if (mUfoStatus == UFO_Unk0) {
				_110[0]->setFreqFrm(_118);
			} else {
				_110[0]->setFreqFrm(2.0f * _118);
			}
		}

		if (_110[1]) {
			_110[1]->visible();
			_110[1]->setEmitPos(vec1);
			_110[1]->setEmitDir(Vector3f(-NMathF::cos(angle), NMathF::sin(angle), 0.0f));
			_110[1]->setScaleSize(mRocketIcon->getScale().x * 0.7f);
			_110[1]->setInitVel(_124 * mRocketIcon->getScale().x * mRocketIcon->getScale().x);
			if (mUfoStatus == UFO_Unk0) {
				_110[1]->setFreqFrm(_11C * 0.25f);
			} else {
				_110[1]->setFreqFrm(_11C);
			}
		}
	}

	// DLL:
	void setUfoStatus(ufoStatusFlag status)
	{
		mUfoStatus = status;
		switch (mUfoStatus) {
		case UFO_Unk0:
			_30 = 0.0f;
			break;
		case UFO_Unk1:
			break;
		}
	}

	void init(P2DScreen* iconScreen)
	{
		P2DPane* rocket = iconScreen->search('ri', true);
		if (rocket->getTypeID() == PANETYPE_Picture) {
			mRocketIcon = (P2DPicture*)rocket;
		}

		mCursorOnyons[Blue].init(iconScreen, 'ci_b', false);
		mCursorOnyons[Red].init(iconScreen, 'ci_r', false);
		mCursorOnyons[Yellow].init(iconScreen, 'ci_y', false);
		init();
	}
	void updateOnyons()
	{
		moveOnyon();
		for (int i = 0; i < PikiColorCount; i++) {
			mCursorOnyons[i].update(mRocketIcon->getScale());
		}
	}
	void update()
	{
		switch (mUfoStatus) {
		case UFO_Unk0:
			stayUfo();
			break;

		case UFO_Unk1:
			if (moveUfo()) {
				if (_35) {
					forceMove();
				} else if (_34) {
					setUfoStatus(UFO_Unk2);
				} else {
					setUfoStatus(UFO_Unk0);
				}
			}
			break;
		case UFO_Unk2:
			break;
		}

		updateOnyons();
		effect();
	}

	ufoStatusFlag getStatusFlag() { return mUfoStatus; }

	bool isLanding() { return _34; }
	bool isMoveOK() { return !_35 && !_34; }

	f32 calcAddAngle(f32 p1, f32 p2, f32 p3, f32 p4)
	{
		f32 diff = p2 - p1;
		if (zen::Abs(diff) > p3) {
			f32 x = p3;
			if (zen::Abs(diff) < PI) {
				if (diff < 0.0f) {
					x *= -1.0f;
				}
			} else if (diff > 0.0f) {
				x *= -1.0f;
			}

			return x * p4;
		}

		return diff;
	}

	void rotateUfo(f32 angle) { mRocketIcon->rotateZ(mRocketIcon->getWidth() >> 1, mRocketIcon->getHeight() >> 1, angle); }

	void set(int x, int y, f32 scale)
	{
		mRocketPos.set(x, y, 0.0f);
		_0C.set(x, y, 0.0f);
		mRocketIcon->move(x, y);
		mRocketIcon->setScale(Vector3f(scale, scale, 1.0f));
		setOnyonPos(scale);
	}
	void setOnyonPos(f32 scale)
	{
		Vector3f onyonPos[PikiColorCount];
		updateOnyonPos(&onyonPos[Blue], &onyonPos[Red], &onyonPos[Yellow]);
		mCursorOnyons[Blue].set(onyonPos[Blue].x, onyonPos[Blue].y, scale);
		mCursorOnyons[Red].set(onyonPos[Red].x, onyonPos[Red].y, scale);
		mCursorOnyons[Yellow].set(onyonPos[Yellow].x, onyonPos[Yellow].y, scale);
	}
	void move(int x, int y, bool p3)
	{
		bool check = false;
		if (_35) {
			return;
		}

		if (p3) {
			switch (mUfoStatus) {
			case UFO_Unk0:
				_00   = 0.0f;
				check = true;
				setLandingFlag(true);
				break;
			case UFO_Unk1:
				if (!_34) {
					_35 = true;
					_38.set(x, y, 0.0f);
				}
				break;
			}
		} else if (!_34) {
			check = true;
		}

		if (check) {
			if (!_34 && !_35) {
				SeSystem::playSysSe(SYSSE_SELECT_MOVE);
			}
			setUfoStatus(UFO_Unk1);
			_0C.set(x, y, 0.0f);
		}
	}

	void moveCancel(int x, int y)
	{
		if (_35 || _34) {
			_35 = false;
			setLandingFlag(false);
			setUfoStatus(UFO_Unk1);
			_0C.set(x, y, 0.0f);
			SeSystem::playSysSe(SYSSE_CANCEL);
		}
	}

	// DLL inlines to do:

	static const f32 ONYON_POS_RADIUS;
	static const f32 ONYON_OFFSET_X;
	static const f32 ONYON_OFFSET_Y;
	static const f32 ONYON_OFFSET_Z;

	f32 _00;                                           // _00
	ufoStatusFlag mUfoStatus;                          // _04
	P2DPicture* mRocketIcon;                           // _08
	Vector3f _0C;                                      // _0C
	Vector3f mRocketPos;                               // _18
	Vector3f _24;                                      // _24
	f32 _30;                                           // _30
	bool _34;                                          // _34
	bool _35;                                          // _35
	Vector3f _38;                                      // _38
	WorldMapCursorOnyon mCursorOnyons[PikiColorCount]; // _44, indexed by PikiColor
	Vector3f mBlueOnyonPos;                            // _F8
	Vector3f mOnyonVelocity;                           // _104
	zen::particleGenerator* _110[2];                   // _110
	f32 _118;                                          // _118
	f32 _11C;                                          // _11C
	f32 _120;                                          // _120
	f32 _124;                                          // _124
	f32 _128;                                          // _128
};

/**
 * @brief TODO
 */
struct WorldMapPartsInfoMgr {
	WorldMapPartsInfoMgr()
	{
		mMaxPartCount   = 0;
		mFadedStarIcons = nullptr;
	}

	void setDisplayParts(int max, int curr)
	{
		for (int i = 0; i < mMaxPartCount; i++) {
			if (i < max) {
				if (i < curr) {
					mGlowingStarIcons[i]->show();
					mFadedStarIcons[i]->hide();
				} else {
					mGlowingStarIcons[i]->hide();
					mFadedStarIcons[i]->show();
				}
			} else {
				mGlowingStarIcons[i]->hide();
				mFadedStarIcons[i]->hide();
			}
		}
	}
	void setActiveMapNo(WorldMapName id)
	{
		int curr, max;
		if (id == WM_NULL) {
			max = curr = 0;
		} else if (playerState) {
			switch (id) {
			case WM_Practice:
				max  = MAX_PARTS_PRACTICE;
				curr = playerState->getPartsGetCount(WM_Practice);
				break;
			case WM_Forest:
				max  = MAX_PARTS_FOREST;
				curr = playerState->getPartsGetCount(WM_Forest);
				break;
			case WM_Cave:
				max  = MAX_PARTS_CAVE;
				curr = playerState->getPartsGetCount(WM_Cave);
				break;
			case WM_Yakushima:
				max  = MAX_PARTS_YAKUSHIMA;
				curr = playerState->getPartsGetCount(WM_Yakushima);
				break;
			case WM_Last:
				max  = MAX_PARTS_LAST;
				curr = playerState->getPartsGetCount(WM_Last);
				break;
			default:
				max  = 0;
				curr = 0;
				break;
			}
		} else {
			switch (id) {
			case WM_Practice:
				max  = MAX_PARTS_PRACTICE;
				curr = 1;
				break;
			case WM_Forest:
				max  = MAX_PARTS_FOREST;
				curr = 2;
				break;
			case WM_Cave:
				max  = MAX_PARTS_CAVE;
				curr = 3;
				break;
			case WM_Yakushima:
				max  = MAX_PARTS_YAKUSHIMA;
				curr = 4;
				break;
			case WM_Last:
				max  = MAX_PARTS_LAST;
				curr = 0;
				break;
			default:
				max  = 0;
				curr = 0;
				break;
			}
		}

		setDisplayParts(max, curr);
	}

	// DLL:
	void init(P2DScreen* dataScreen)
	{
		char partStr[8];
		int partCount = 0;
		sprintf(partStr, "pa%02d", 0);
		while (dataScreen->search(P2DPaneLibrary::makeTag(partStr), false)) {
			sprintf(partStr, "pa%02d", ++partCount);
		}

		mMaxPartCount     = partCount;
		mFadedStarIcons   = new P2DPicture*[mMaxPartCount];
		mGlowingStarIcons = new P2DPicture*[mMaxPartCount];

		for (int i = 0; i < mMaxPartCount; i++) {
			sprintf(partStr, "pn%02d", i);
			P2DPane* pane = dataScreen->search(P2DPaneLibrary::makeTag(partStr), true);
			if (pane->getTypeID() == PANETYPE_Picture) {
				mFadedStarIcons[i] = (P2DPicture*)pane;
				mFadedStarIcons[i]->show();
				pane = P2DPaneLibrary::getParentPane(mFadedStarIcons[i]);
				P2DPaneLibrary::changeParent(mFadedStarIcons[i], pane);
			} else {
				PRINT("not picture pane.\n");
				ERROR("not picture pane.\n");
			}

			sprintf(partStr, "pa%02d", i);
			pane = dataScreen->search(P2DPaneLibrary::makeTag(partStr), true);
			if (pane->getTypeID() == PANETYPE_Picture) {
				mGlowingStarIcons[i] = (P2DPicture*)pane;
				mGlowingStarIcons[i]->show();
				pane = P2DPaneLibrary::getParentPane(mGlowingStarIcons[i]);
				P2DPaneLibrary::changeParent(mGlowingStarIcons[i], pane);
			} else {
				PRINT("not picture pane.\n");
				ERROR("not picture pane.\n");
			}
		}

		init();
	}
	void init() { }
	void update() { }

	void close() { setActiveMapNo(WM_NULL); }

	int mMaxPartCount;              // _00
	P2DPicture** mFadedStarIcons;   // _04
	P2DPicture** mGlowingStarIcons; // _08
};

/**
 * @brief TODO
 *
 * @note Size: 0x88.
 */
struct WorldMapConfirmMgr {
	/**
	 * @brief TODO
	 */
	enum statusFlag {
		STATUS_Unk0 = 0,
		STATUS_Unk1 = 1,
		STATUS_Unk2 = 2,
		STATUS_Unk3 = 3,
	};

	/**
	 * @brief TODO
	 */
	enum selectFlag {
		SELECT_Unk0 = 0,
		SELECT_Unk1 = 1,
		SELECT_COUNT, // 2
	};

	WorldMapConfirmMgr()
	{
		mConfirmScreen = new DrawScreen("screen/blo/w_ok.blo", nullptr, true, true);

		P2DScreen* confScreen = mConfirmScreen->getScreenPtr();
		confScreen->setOffset(mConfirmScreen->getScreenPtr()->getWidth() >> 1, mConfirmScreen->getScreenPtr()->getHeight() >> 1);
		P2DPane* parent = confScreen->search('pall', true);
		P2DPane* pane   = confScreen->search('se_c', true);
		if (pane->getTypeID() == PANETYPE_TextBox) {
			static_cast<P2DTextBox*>(pane)->getFontColor(mCharColor, mGradColor);
		} else {
			ERROR("tag<se_c> pane is not text box.\n");
		}

		mMenuItems = new DrawMenuItem[SELECT_COUNT];

		for (int i = 0; i < SELECT_COUNT; i++) {
			char str[8];
			sprintf(str, "he%02d", i);
			pane = confScreen->search(P2DPaneLibrary::makeTag(str), true);
			P2DPaneLibrary::changeParent(pane, parent);
			mMenuItems[i].setTextPane(pane, nullptr);

			sprintf(str, "i%02dl", i);
			pane = confScreen->search(P2DPaneLibrary::makeTag(str), true);
			if (mMenuItems[i].setIconLPane(pane, parent)) {
				ERROR("pane [%s] is not picture.\n", str);
			}

			sprintf(str, "i%02dr", i);
			pane = confScreen->search(P2DPaneLibrary::makeTag(str), true);
			if (mMenuItems[i].setIconRPane(pane, parent)) {
				ERROR("pane [%s] is not picture.\n", str);
			}
		}

		mLeftSpecCursor.init(confScreen, parent, 'z**l', 10.0f, 100.0f);
		mRightSpecCursor.init(confScreen, parent, 'z**r', 50.0f, 100.0f);
		init();
	}

	void init(statusFlag status)
	{
		mStatus = status;
		mConfirmScreen->getScreenPtr()->move(640, 0);
		mConfirmScreen->getScreenPtr()->setScale(1.0f);
		mConfirmScreen->getScreenPtr()->show();
		_70               = 0.0f;
		mCurrentSelection = SELECT_Unk0;
		mLeftSpecCursor.initPos(mMenuItems[mCurrentSelection].getIconLPosH(), mMenuItems[mCurrentSelection].getIconLPosV());
		mRightSpecCursor.initPos(mMenuItems[mCurrentSelection].getIconRPosH(), mMenuItems[mCurrentSelection].getIconRPosV());

		for (int i = 0; i < SELECT_COUNT; i++) {
			mMenuItems[i].init(i == mCurrentSelection, mCharColor, mGradColor);
		}
	}

	bool modeOperation(Controller* controller)
	{
		DrawMenuItem* currItem;
		bool res     = false;
		int startSel = mCurrentSelection;
		mCurrentSelection += controller->keyClick(KBBTN_MSTICK_DOWN) - controller->keyClick(KBBTN_MSTICK_UP);
		if (mCurrentSelection < 0) {
			mCurrentSelection = SELECT_Unk1;
		}
		if (mCurrentSelection > 1) {
			mCurrentSelection = SELECT_Unk0;
		}

		currItem = &mMenuItems[mCurrentSelection];
		for (int i = 0; i < 2; i++) {
			mMenuItems[i].update(i == mCurrentSelection, mCharColor, mGradColor);
		}
		if (startSel != mCurrentSelection) {
			SeSystem::playSysSe(SYSSE_MOVE1);
			mLeftSpecCursor.move(currItem->getIconLPosH(), currItem->getIconLPosV(), 0.5f);
			mRightSpecCursor.move(currItem->getIconRPosH(), currItem->getIconRPosV(), 0.5f);
		}

		if (controller->keyClick(KBBTN_START | KBBTN_A)) {
			SeSystem::playSysSe(SYSSE_DECIDE1);
			res = true;
		}

		if (controller->keyClick(KBBTN_B)) {
			SeSystem::playSysSe(SYSSE_CANCEL);
			mCurrentSelection = SELECT_Unk1;
			res               = true;
		}
		return res;
	}

	// DLL:
	void init() { init(STATUS_Unk0); }

	void draw(Graphics&) { mConfirmScreen->draw(); }

	bool update(Controller* controller)
	{
		switch (mStatus) {
		case STATUS_Unk1:
			_70 += gsys->getFrameTime();
			f32 a;
			if (_70 > 0.25f) {
				_70     = 0.0f;
				a       = 1.0f;
				mStatus = STATUS_Unk2;
			} else {
				a = NMathF::sin(_70 / 0.25f * HALF_PI);
			}

			f32 angle1 = HALF_PI * a;
			_7C.x      = 100.0f * NMathF::cos(angle1);
			_7C.y      = 0.0f;
			_7C.z      = 100.0f * NMathF::sin(angle1) - 100.0f;

			mConfirmScreen->getScreenPtr()->move(zen::RoundOff(_7C.x), zen::RoundOff(_7C.y));
			mConfirmScreen->getScreenPtr()->moveZ(_7C.z);
			mConfirmScreen->getScreenPtr()->rotate(P2DROTATE_Unk1, TAU - (angle1 - HALF_PI));
			break;
		case STATUS_Unk2:
			if (modeOperation(controller)) {
				mStatus = STATUS_Unk3;
				_70     = 0.0f;
			}
			break;
		case STATUS_Unk3:
			_70 += gsys->getFrameTime();
			f32 b;
			if (_70 > 0.25f) {
				_70     = 0.0f;
				b       = 1.0f;
				mStatus = STATUS_Unk0;
				mConfirmScreen->getScreenPtr()->hide();
			} else {
				b = 1.0f - NMathF::cos(_70 / 0.25f * HALF_PI);
			}
			if (mCurrentSelection == SELECT_Unk0) {
				mConfirmScreen->getScreenPtr()->move(0, zen::RoundOff(b * -480.0f));
			} else {
				f32 angle2 = HALF_PI * b + HALF_PI;
				_7C.x      = 100.0f * NMathF::cos(angle2);
				_7C.y      = 0.0f;
				_7C.z      = 100.0f * NMathF::sin(angle2) - 100.0f;

				mConfirmScreen->getScreenPtr()->move(zen::RoundOff(_7C.x), zen::RoundOff(_7C.y));
				mConfirmScreen->getScreenPtr()->moveZ(_7C.z);
				mConfirmScreen->getScreenPtr()->rotate(P2DROTATE_Unk1, TAU - (angle2 - HALF_PI));
			}
			break;
		}

		mConfirmScreen->update();
		mLeftSpecCursor.update();
		mRightSpecCursor.update();
		return mStatus == STATUS_Unk0;
	}
	selectFlag getSelectFlag() { return (selectFlag)mCurrentSelection; }

	void start() { init(STATUS_Unk1); }

	DrawScreen* mConfirmScreen;         // _00
	SpectrumCursorMgr mLeftSpecCursor;  // _04
	SpectrumCursorMgr mRightSpecCursor; // _34
	DrawMenuItem* mMenuItems;           // _64
	Colour mCharColor;                  // _68
	Colour mGradColor;                  // _6C
	f32 _70;                            // _70
	statusFlag mStatus;                 // _74
	int mCurrentSelection;              // _78, see selectFlag enum
	Vector3f _7C;                       // _7C
};

/**
 * @brief TODO
 *
 * @note Size: 0x138.
 */
struct WorldMapCoursePointMgr {
	WorldMapCoursePointMgr()
	{
		mSelectedPoint = 0;
		mEventFlag     = 0;
		_00            = 0;
	}

	bool modeAppear()
	{
		bool res                   = false;
		WorldMapCoursePoint* point = mCoursePoints;
		for (int i = 0; i < 5; i++) {
			point->update(point == mSelectedPoint);
			if (point->getEventFlag() & 0x1) {
				res = true;
			}
			point++;
		}
		return res;
	}
	bool modeOperation(Controller* controller, bool p2)
	{
		WorldMapCoursePoint* point = mCoursePoints;
		for (int i = 0; i < 5; i++) {
			point->update(point == mSelectedPoint);
			point++;
			STACK_PAD_VAR(1);
		}
		if (controller) {
			if (p2) {
				keyOperation(controller, KBBTN_MSTICK_UP, WorldMapCoursePoint::LINK_Up);
				keyOperation(controller, KBBTN_MSTICK_DOWN, WorldMapCoursePoint::LINK_Down);
				keyOperation(controller, KBBTN_MSTICK_LEFT, WorldMapCoursePoint::LINK_Left);
				keyOperation(controller, KBBTN_MSTICK_RIGHT, WorldMapCoursePoint::LINK_Right);

				if (controller->keyClick(KBBTN_START | KBBTN_A)) {
					SeSystem::playSysSe(SYSSE_DECIDE1);
					mEventFlag |= 0x10;
				}
			} else if (controller->keyClick(KBBTN_B)) {
				SeSystem::playSysSe(SYSSE_CANCEL);
				mEventFlag |= 0x20;
			}
		}
		return false;
	}

	// DLL:
	void setSelectCourse(WorldMapName gameStageID)
	{
		mSelectedPoint = &mCoursePoints[mapNoGame2Scr[gameStageID]];
		mSelectedPoint->select();
	}

	void init(P2DScreen* pointScreen, P2DScreen* lineScreen, WorldMapName startStageID)
	{
		WorldMapCoursePoint* point;
		mEventFlag = 0;
		if (playerState) {
			point = &mCoursePoints[0];
			point->setPane(pointScreen, 'x_1', 'x_1s', 'po01', lineScreen, 'sli1');
			point->setLink(&mCoursePoints[4], &mCoursePoints[1], nullptr, &mCoursePoints[3]);
			if (playerState->courseOpen(STAGE_Yakushima)) {
				point = &mCoursePoints[1];
				point->setPane(pointScreen, 'x_2', 'x_2s', 'po02', lineScreen, 'sli2');
				point->setLink(&mCoursePoints[0], nullptr, nullptr, &mCoursePoints[2]);
			} else {
				point = &mCoursePoints[1];
				point->setPane(pointScreen, 'x_2', 'x_2s', 'po02', lineScreen, 'sli2');
				point->setLink(&mCoursePoints[3], nullptr, nullptr, &mCoursePoints[2]);
			}

			point = &mCoursePoints[2];
			point->setPane(pointScreen, 'x_3', 'x_3s', 'po03', lineScreen, 'sli3');
			point->setLink(&mCoursePoints[3], nullptr, &mCoursePoints[1], nullptr);
			if (playerState->courseOpen(STAGE_Yakushima)) {
				point = &mCoursePoints[3];
				point->setPane(pointScreen, 'x_4', 'x_4s', 'po04', lineScreen, 'sli4');
				point->setLink(&mCoursePoints[4], &mCoursePoints[2], &mCoursePoints[0], nullptr);
			} else {
				point = &mCoursePoints[3];
				point->setPane(pointScreen, 'x_4', 'x_4s', 'po04', lineScreen, 'sli4');
				point->setLink(&mCoursePoints[4], &mCoursePoints[2], &mCoursePoints[1], nullptr);
			}

			point = &mCoursePoints[4];
			point->setPane(pointScreen, 'x_5', 'x_5s', 'po05', lineScreen, 'sli5');
			point->setLink(nullptr, &mCoursePoints[3], &mCoursePoints[0], nullptr);

		} else {
			point = &mCoursePoints[0];
			point->setPane(pointScreen, 'x_1', 'x_1s', 'po01', lineScreen, 'sli1');
			point->setLink(&mCoursePoints[4], &mCoursePoints[1], nullptr, &mCoursePoints[3]);

			point = &mCoursePoints[1];
			point->setPane(pointScreen, 'x_2', 'x_2s', 'po02', lineScreen, 'sli2');
			point->setLink(&mCoursePoints[0], nullptr, nullptr, &mCoursePoints[2]);

			point = &mCoursePoints[2];
			point->setPane(pointScreen, 'x_3', 'x_3s', 'po03', lineScreen, 'sli3');
			point->setLink(&mCoursePoints[3], nullptr, &mCoursePoints[1], nullptr);

			point = &mCoursePoints[3];
			point->setPane(pointScreen, 'x_4', 'x_4s', 'po04', lineScreen, 'sli4');
			point->setLink(&mCoursePoints[4], &mCoursePoints[2], &mCoursePoints[0], nullptr);

			point = &mCoursePoints[4];
			point->setPane(pointScreen, 'x_5', 'x_5s', 'po05', lineScreen, 'sli5');
			point->setLink(nullptr, &mCoursePoints[3], &mCoursePoints[0], nullptr);
		}

		for (int i = WM_START; i < WM_COUNT; i++) {
			WorldMapName gameStageID = (WorldMapName)mapNoScr2Game[i];
			char onyStr[8];
			sprintf(onyStr, "ony%d", i + 1);
			char chaStr[8];
			sprintf(chaStr, "cha%d", i + 1);

			mCoursePoints[i].setCursorPoint(pointScreen, P2DPaneLibrary::makeTag(onyStr), P2DPaneLibrary::makeTag(chaStr));
			mCoursePoints[i].setNumber(gameStageID);
			mCoursePoints[i].nonSelect();
			mCoursePoints[i].openCourse();
			if (playerState && !playerState->courseOpen(gameStageID)) {
				mCoursePoints[i].closeCourse();
			}
		}

		setSelectCourse(startStageID);
	}

	// might be appear
	void start(WorldMapName id)
	{
		_00 = 0;
		for (int i = 0; i < WM_COUNT; i++) {
			mCoursePoints[i].nonSelect();
		}
		setSelectCourse(id);
	}

	void getLandPos(int* x, int* y)
	{
		P2DPane* landPane = mSelectedPoint->getLandPane();
		*x                = landPane->getPosH();
		*y                = landPane->getPosV();
	}
	void getStayPos(int* x, int* y)
	{
		P2DPane* landPane = mSelectedPoint->getStayPane();
		*x                = landPane->getPosH();
		*y                = landPane->getPosV();
	}

	void appear(WorldMapName id)
	{
		_00 = 1;
		for (int i = 0; i < WM_COUNT; i++) {
			if (mSelectedPoint != &mCoursePoints[i]) {
				mCoursePoints[i].nonSelect();
			} else {
				mCoursePoints[i].select();
			}
		}

		mCoursePoints[mapNoGame2Scr[id]].appear();
	}

	WorldMapName getSelectCourseNumber()
	{
		WorldMapName id = WM_NULL;
		if (mSelectedPoint) {
			id = mSelectedPoint->getNumber();
		}
		return id;
	}

	bool update(Controller* controller, bool p2)
	{
		bool res   = false;
		mEventFlag = 0;
		switch (_00) {
		case 0:
			res = modeOperation(controller, p2);
			break;
		case 1:
			res = modeAppear();
			if (res == true) {
				_00        = 0;
				mEventFlag = 0x40;
			}
			break;
		default:
			PRINT("unknown mode %d \n", _00);
			ERROR("unknown mode %d \n", _00);
			break;
		}
		return res;
	}

	u32 getEventFlag() { return mEventFlag; }

	void createCourseInEffect() { mSelectedPoint->createCourseInEffect(); }

	// DLL inlines to do:
	void keyOperation(Controller* controller, u32 button, WorldMapCoursePoint::linkFlag linkID)
	{
		if (controller->keyClick(button)) {
			WorldMapCoursePoint* linkPoint = mSelectedPoint->getLinkCoursePointPtr(linkID);
			if (linkPoint && linkPoint->getOpenSw()) {
				SeSystem::playSysSe(SYSSE_MOVE1);
				mSelectedPoint->nonSelect();
				mSelectedPoint = linkPoint;
				mSelectedPoint->select();
				mEventFlag |= 0x1;
			}
		}
	}

	int _00;                              // _00
	WorldMapCoursePoint* mSelectedPoint;  // _04
	WorldMapCoursePoint mCoursePoints[5]; // _08
	u32 mEventFlag;                       // _134
};

/**
 * @brief TODO
 */
struct WorldMapMapImageMgr {
	WorldMapMapImageMgr()
	{
		_04 = 2;
		_08 = -1;
		_00 = 0.0f;
		_20 = 0;
		for (int i = 0; i < 5; i++) {
			mMapImagePanes[i] = nullptr;
		}
	}

	// weak:
	void init()
	{
		_04 = 0;
		for (int i = 0; i < 5; i++) {
			if (mMapImagePanes[i]) {
				mMapImagePanes[i]->hide();
				mMapImagePanes[i]->setOffset(mMapImagePanes[i]->getWidth() >> 1, mMapImagePanes[i]->getHeight() >> 1);
			}
		}

		_08 = 0;

		closeMapImage();
	}
	void modeOpen()
	{
		_00 += gsys->getFrameTime();
		f32 a;
		if (_00 > 0.25f) {
			a   = 1.0f;
			_00 = 0.0f;
			if (_20) {
				_04 = 1;
				_20 = 0;
			} else {
				_04 = 0;
			}
		} else {
			a = _00 / 0.25f;
		}
		f32 xScale = a / 0.5f;
		if (xScale > 1.0f) {
			xScale = 1.0f;
		}
		f32 yScale = (a - 0.5f) / 0.5f;
		if (yScale < 0.05f) {
			yScale = 0.05f;
		}
		if (yScale > 1.0f) {
			yScale = 1.0f;
		}
		mMapImagePanes[_08]->setScale(xScale, yScale, 1.0f);
		mMapImagePanes[_08]->show();
	}
	void modeClose()
	{
		_00 += gsys->getFrameTime();
		if (_00 > 0.25f) {
			_00 = 0.25f;
			mMapImagePanes[_08]->hide();
		} else {
			f32 a      = 1.0f - _00 / 0.25f;
			f32 xScale = a / 0.5f;
			if (xScale > 1.0f) {
				xScale = 1.0f;
			}

			f32 yScale = (a - 0.5f) / 0.5f;
			if (yScale < 0.05f) {
				yScale = 0.05f;
			}
			if (yScale > 1.0f) {
				yScale = 1.0f;
			}
			mMapImagePanes[_08]->setScale(xScale, yScale, 1.0f);
			mMapImagePanes[_08]->show();
		}
	}

	// DLL:
	void init(P2DScreen* moniScreen)
	{
		P2DPane* pane1 = moniScreen->search('mi_1', true);
		if (pane1->getTypeID() == PANETYPE_Picture) {
			mMapImagePanes[0] = (P2DPicture*)pane1;
		}
		P2DPane* pane2 = moniScreen->search('mi_2', true);
		if (pane2->getTypeID() == PANETYPE_Picture) {
			mMapImagePanes[1] = (P2DPicture*)pane2;
		}
		P2DPane* pane3 = moniScreen->search('mi_3', true);
		if (pane3->getTypeID() == PANETYPE_Picture) {
			mMapImagePanes[2] = (P2DPicture*)pane3;
		}
		P2DPane* pane4 = moniScreen->search('mi_4', true);
		if (pane4->getTypeID() == PANETYPE_Picture) {
			mMapImagePanes[3] = (P2DPicture*)pane4;
		}
		P2DPane* pane5 = moniScreen->search('mi_5', true);
		if (pane5->getTypeID() == PANETYPE_Picture) {
			mMapImagePanes[4] = (P2DPicture*)pane5;
		}

		init();
	}

	void closeMapImage()
	{
		switch (_04) {
		case 0:
			_00 = 0.0f;
			_04 = 1;
			break;
		case 2:
			_20 = 1;
			break;
		}
	}

	void update()
	{
		switch (_04) {
		case 0:
			if (_08 != -1) {
				mMapImagePanes[_08]->show();
				mMapImagePanes[_08]->setScale(1.0f);
			}
			break;
		case 1:
			modeClose();
			break;
		case 2:
			modeOpen();
			break;
		}
	}
	void openMapImage(WorldMapName id)
	{
		if (_04 == 1) {
			_00 = 0.0f;
			_08 = id;
			_04 = 2;
			PRINT("openMapImage %d \n", id);
		}
	}

	f32 _00;                       // _00
	int _04;                       // _04
	int _08;                       // _08
	P2DPicture* mMapImagePanes[5]; // _0C
	u8 _20;                        // _20
};

} // namespace zen

const int zen::WorldMapTitleMgr::OBJ_NUM = 5;

// probably need to move these around later for ordering
f32 zen::WorldMapCursorOnyon::bottomLengthMin     = 10.0f;
f32 zen::WorldMapCursorOnyon::bottomLengthDefault = 15.0f;
f32 zen::WorldMapCursorOnyon::bottomLengthMax     = 20.0f;
f32 zen::WorldMapCursorOnyon::scaleFrameMax       = 0.8f;

const f32 zen::WorldMapCursorMgr::ONYON_POS_RADIUS = 60.0f;
const f32 zen::WorldMapCursorMgr::ONYON_OFFSET_X   = 0.0f;
const f32 zen::WorldMapCursorMgr::ONYON_OFFSET_Y   = 20.0f;
const f32 zen::WorldMapCursorMgr::ONYON_OFFSET_Z   = 0.0f;

const int WorldMapCoursePoint::EVENT_NONE          = 0;
const int WorldMapCoursePoint::EVENT_APPEAR_FINISH = 1;

/*
 * --INFO--
 * Address:	........
 * Size:	000040
 */
zen::DrawWorldMap::~DrawWorldMap()
{
}

/*
 * --INFO--
 * Address:	801DB14C
 * Size:	00246C
 */
zen::DrawWorldMap::DrawWorldMap()
{
	// SET UP EFFECTS MGR
	mEffectMgr2D = new EffectMgr2D(96, 500, 650);
	WMeffMgr     = mEffectMgr2D;

	// SET UP SCREENS
	mWipeScreen  = new DrawScreen("screen/blo/w_wipe.blo", nullptr, true, true);
	mIconScreen  = new DrawScreen("screen/blo/w_icon.blo", nullptr, true, true);
	mTitleScreen = new DrawScreen("screen/blo/w_title.blo", nullptr, true, true);
	mMoniScreen  = new DrawScreen("screen/blo/w_moni.blo", nullptr, true, true);
	mData1Screen = new DrawScreen("screen/blo/w_data1.blo", nullptr, true, true);
	mData2Screen = new DrawScreen("screen/blo/w_data2.blo", nullptr, true, true);
	mPointScreen = new DrawScreen("screen/blo/w_point.blo", nullptr, true, true);
	mLineScreen  = new DrawScreen("screen/blo/w_line.blo", nullptr, true, true);
	mBackScreen  = new DrawScreen("screen/blo/w_back.blo", nullptr, true, true);

	_0C = 0.0f;
	_04 = -1;
	_08 = -1;

	// SET UP COURSE POINTS
	mCoursePointMgr = new WorldMapCoursePointMgr();
	mCoursePointMgr->init(mPointScreen->getScreenPtr(), mLineScreen->getScreenPtr(), WM_START);

	// SET UP WIPES
	mWipeMgr = new WorldMapWipeMgr();
	mWipeMgr->init(mWipeScreen->getScreenPtr());

	// SET UP MAP IMAGES
	mMapImageMgr = new WorldMapMapImageMgr();
	mMapImageMgr->init(mMoniScreen->getScreenPtr());

	// SET UP COUNTERS
	if (playerState) {
		mTotalPartsNum           = playerState->getTotalParts();
		mCurrentPartsNum         = playerState->getCurrParts();
		mTotalPikiCounts[Blue]   = playerState->getTotalPikiCount(Blue);
		mTotalPikiCounts[Red]    = playerState->getTotalPikiCount(Red);
		mTotalPikiCounts[Yellow] = playerState->getTotalPikiCount(Yellow);

	} else {
		PRINT("WARNING! playerState ptr is NULL.\n");
		mTotalPartsNum           = 30;
		mCurrentPartsNum         = 29;
		mTotalPikiCounts[Blue]   = 999;
		mTotalPikiCounts[Red]    = 999;
		mTotalPikiCounts[Yellow] = 999;
	}

	P2DPane* dateCentrePane = mData1Screen->getScreenPtr()->search('dc_c', true);
	P2DPane* dateLeftPane   = mData1Screen->getScreenPtr()->search('dc_l', true);
	P2DPane* dateRightPane  = mData1Screen->getScreenPtr()->search('dc_r', true);

	dateCentrePane->setCallBack(new DrawWorldMapDateCallBack(dateCentrePane, dateLeftPane, dateRightPane));

	// CURRENT PARTS
	P2DPane* currPartsLeftPane = mData1Screen->getScreenPtr()->search('ro_l', true);
	currPartsLeftPane->setCallBack(new NumberPicCallBack<int>(currPartsLeftPane, &mCurrentPartsNum, 10, false));

	P2DPane* currPartsRightPane = mData1Screen->getScreenPtr()->search('ro_r', true);
	currPartsRightPane->setCallBack(new NumberPicCallBack<int>(currPartsRightPane, &mCurrentPartsNum, 1, false));

	// TOTAL PARTS
	P2DPane* totalPartsLeftPane = mData1Screen->getScreenPtr()->search('rt_l', true);
	totalPartsLeftPane->setCallBack(new NumberPicCallBack<int>(totalPartsLeftPane, &mTotalPartsNum, 10, false));

	P2DPane* totalPartsRightPane = mData1Screen->getScreenPtr()->search('rt_r', true);
	totalPartsRightPane->setCallBack(new NumberPicCallBack<int>(totalPartsRightPane, &mTotalPartsNum, 1, false));

	// BLUE PIKIS
	P2DPane* bluePikiLeftPane = mData1Screen->getScreenPtr()->search('bp_l', true);
	bluePikiLeftPane->setCallBack(new NumberPicCallBack<int>(bluePikiLeftPane, &mTotalPikiCounts[Blue], 100, false));

	P2DPane* bluePikiCentrePane = mData1Screen->getScreenPtr()->search('bp_c', true);
	bluePikiCentrePane->setCallBack(new NumberPicCallBack<int>(bluePikiCentrePane, &mTotalPikiCounts[Blue], 10, false));

	P2DPane* bluePikiRightPane = mData1Screen->getScreenPtr()->search('bp_r', true);
	bluePikiRightPane->setCallBack(new NumberPicCallBack<int>(bluePikiRightPane, &mTotalPikiCounts[Blue], 1, false));

	// RED PIKIS
	P2DPane* redPikiLeftPane = mData1Screen->getScreenPtr()->search('rp_l', true);
	redPikiLeftPane->setCallBack(new NumberPicCallBack<int>(redPikiLeftPane, &mTotalPikiCounts[Red], 100, false));

	P2DPane* redPikiCentrePane = mData1Screen->getScreenPtr()->search('rp_c', true);
	redPikiCentrePane->setCallBack(new NumberPicCallBack<int>(redPikiCentrePane, &mTotalPikiCounts[Red], 10, false));

	P2DPane* redPikiRightPane = mData1Screen->getScreenPtr()->search('rp_r', true);
	redPikiRightPane->setCallBack(new NumberPicCallBack<int>(redPikiRightPane, &mTotalPikiCounts[Red], 1, false));

	// YELLOW PIKIS
	P2DPane* yellowPikiLeftPane = mData1Screen->getScreenPtr()->search('yp_l', true);
	yellowPikiLeftPane->setCallBack(new NumberPicCallBack<int>(yellowPikiLeftPane, &mTotalPikiCounts[Yellow], 100, false));

	P2DPane* yellowPikiCentrePane = mData1Screen->getScreenPtr()->search('yp_c', true);
	yellowPikiCentrePane->setCallBack(new NumberPicCallBack<int>(yellowPikiCentrePane, &mTotalPikiCounts[Yellow], 10, false));

	P2DPane* yellowPikiRightPane = mData1Screen->getScreenPtr()->search('yp_r', true);
	yellowPikiRightPane->setCallBack(new NumberPicCallBack<int>(yellowPikiRightPane, &mTotalPikiCounts[Yellow], 1, false));

	mCursorMgr = new WorldMapCursorMgr();
	mCursorMgr->init(mIconScreen->getScreenPtr());

	mTitleMgr = new WorldMapTitleMgr();
	mTitleMgr->init(mTitleScreen->getScreenPtr());

	mPartsInfoMgr = new WorldMapPartsInfoMgr();
	mPartsInfoMgr->init(mData2Screen->getScreenPtr());

	mConfirmMgr = new WorldMapConfirmMgr();

	mShootingStarMgr = new WorldMapShootingStarMgr();
}

/*
 * --INFO--
 * Address:	801DE714
 * Size:	000C14
 */
bool zen::DrawWorldMap::update(Controller* controller)
{
	bool res = false;
	if (_04 != -1) {
		if (_04 == 3) {
			DrawWMPause::returnStatusFlag pauseState = mPause.update(controller);
			if (pauseState != DrawWMPause::RETURN_Unk0) {
				if (pauseState == DrawWMPause::RETURN_Unk2) {
					_04 = -1;
					res = true;
					_08 = 6;
				} else {
					_04 = 2;
				}
			}
		} else if (_04 == 6) {
			if (mSelectDiary.update(controller) == ogDrawSelectDiary::Inactive) {
				_04 = 7;
				mWipeMgr->set(320, 240);
				mWipeMgr->open(0.5f);
				SeSystem::playSysSe(YMENU_SELECT2);
			}
		} else {
			switch (_04) {
			case 5:
				if (!mWipeMgr->isActive()) {
					_04 = 6;
					mSelectDiary.start();
				}
				mCursorMgr->update();
				updateScreens();
				break;
			case 7:
				if (!mWipeMgr->isActive()) {
					_04 = 2;
				}
				mCursorMgr->update();
				updateScreens();
				break;
			case 0:
				if (modeStart(controller)) {
					if (mStartMode) {
						_04 = 1;
					} else {
						_04 = 2;
					}
				}
				break;
			case 1:
				if (modeAppear(controller)) {
					_04 = 2;
				}
				break;
			case 4:
				if (modeConfirm(controller)) {
					_04 = 2;
				}
				break;
			case 2:
				if (controller->keyClick(KBBTN_START)) {
					mPause.start();
					_04 = 3;
				} else if (controller->keyClick(KBBTN_Y)) {
					if (mCursorMgr->isMoveOK()) {
						mWipeMgr->setDefault();
						mWipeMgr->close(0.5f, 320, 240);
						_04 = 5;
						SeSystem::playSysSe(YMENU_SELECT2);
					}
				} else if (modeOperation(controller)) {
					_04 = 8;
				}
				break;
			case 8:
				if (modeEnd(controller)) {
					_04 = -1;
					res = true;
				}
				break;
			}

			if (mCursorMgr->getStatusFlag() == WorldMapCursorMgr::UFO_Unk0 || mCursorMgr->isLanding()) {
				openMapInfo();
			}

			mEffectMgr2D->update();
			mMapImageMgr->update();
			mWipeMgr->update();
			mTitleMgr->update();
			mPartsInfoMgr->update();
		}
	}

	return res;
}

/*
 * --INFO--
 * Address:	801E0D38
 * Size:	000134
 */
void zen::DrawWorldMap::draw(Graphics& gfx)
{
	if (_04 != 6) {
		mBackScreen->draw();
		mLineScreen->draw();
		mPointScreen->draw();
		mData1Screen->draw();
		mData2Screen->draw();
		mMoniScreen->draw();
		mIconScreen->draw();
		mTitleScreen->draw();
		mEffectMgr2D->draw(gfx);
		mConfirmMgr->draw(gfx);
		mWipeScreen->draw();
	} else {
		mSelectDiary.draw(gfx);
	}

	mPause.draw(gfx);
}

/*
 * --INFO--
 * Address:	........
 * Size:	000AA4
 */
void zen::DrawWorldMap::setCoursePoint(zen::DrawWorldMap::startPlaceFlag placeFlag)
{
	switch (placeFlag) {
	case PLACE_Unk0:
		mCoursePointMgr->start(WM_Practice);
		break;
	case PLACE_Unk1:
		mCoursePointMgr->start(WM_Forest);
		break;
	case PLACE_Unk2:
		mCoursePointMgr->start(WM_Cave);
		break;
	case PLACE_Unk3:
		mCoursePointMgr->start(WM_Yakushima);
		break;
	case PLACE_Unk4:
		mCoursePointMgr->start(WM_Last);
		break;
	default:
		PRINT("unknown place no : %d \n", placeFlag);
		mCoursePointMgr->start(WM_Practice);
		break;
	}
}

/*
 * --INFO--
 * Address:	801E0E6C
 * Size:	001B78
 */
void zen::DrawWorldMap::start(zen::DrawWorldMap::startModeFlag modeFlag, zen::DrawWorldMap::startPlaceFlag placeFlag)
{
	mStartMode = modeFlag;
	_04        = 0;
	_0C        = 0.0f;
	mEffectMgr2D->killAll(true);
	_08 = 5;

	P2DPaneLibrary::makeResident(mWipeScreen->getScreenPtr());
	P2DPaneLibrary::makeResident(mMoniScreen->getScreenPtr());
	P2DPaneLibrary::makeResident(mIconScreen->getScreenPtr());
	P2DPaneLibrary::makeResident(mTitleScreen->getScreenPtr());
	P2DPaneLibrary::makeResident(mData1Screen->getScreenPtr());
	P2DPaneLibrary::makeResident(mData2Screen->getScreenPtr());
	P2DPaneLibrary::makeResident(mPointScreen->getScreenPtr());
	P2DPaneLibrary::makeResident(mLineScreen->getScreenPtr());
	P2DPaneLibrary::makeResident(mBackScreen->getScreenPtr());

	mCursorMgr->init();
	setCoursePoint(placeFlag);

	int x;
	int y;
	mCoursePointMgr->getLandPos(&x, &y);
	mCursorMgr->set(x, y, 0.0f);

	mCoursePointMgr->getStayPos(&x, &y);
	mCursorMgr->move(x, y, false);

	if (mStartMode != START_Unk0) {
		switch (mStartMode) {
		case START_Unk1:
			mCoursePointMgr->appear(WM_Forest);
			break;
		case START_Unk2:
			mCoursePointMgr->appear(WM_Cave);
			break;
		case START_Unk3:
			mCoursePointMgr->appear(WM_Yakushima);
			break;
		case START_Unk4:
			mCoursePointMgr->appear(WM_Last);
			mShootingStarMgr->rapidFire();
			break;
		default:
			PRINT("unknown startMode %d \n", mStartMode);
			ERROR("unknown startMode %d \n", mStartMode);
			break;
		}
	}

	mMapImageMgr->init();

	if (playerState) {
		P2DPane* blueCount = mData1Screen->getScreenPtr()->search('p_bc', true);
		if (!playerState->displayPikiCount(Blue)) {
			blueCount->hide();
		}
		P2DPane* redCount = mData1Screen->getScreenPtr()->search('p_rc', true);
		if (!playerState->displayPikiCount(Red)) {
			redCount->hide();
		}
		P2DPane* yellowCount = mData1Screen->getScreenPtr()->search('p_yc', true);
		if (!playerState->displayPikiCount(Yellow)) {
			yellowCount->hide();
		}
	}

	mTitleMgr->init();
	mPartsInfoMgr->init();
	mPartsInfoMgr->setActiveMapNo(mCoursePointMgr->getSelectCourseNumber());
	mWipeMgr->init();
	mWipeMgr->set(320, 240);
	mWipeMgr->open(1.0f);
}

/*
 * --INFO--
 * Address:	801E2E0C
 * Size:	00047C
 */
bool zen::DrawWorldMap::modeStart(Controller* controller)
{
	bool res = false;
	f32 c    = _0C += gsys->getFrameTime();
	f32 b    = 1.0f;
	if (c > b) {
		_0C = b;
	}
	f32 a             = _0C / b;
	P2DScreen* screen = mPointScreen->getScreenPtr();
	screen->move(zen::RoundOff(-2.0f * screen->getWidth() * (1.0f - NMathF::sin(HALF_PI * a))), screen->getPosV());

	screen = mLineScreen->getScreenPtr();
	screen->move(zen::RoundOff(-2.0f * screen->getWidth() * (1.0f - NMathF::sin(HALF_PI * a))), screen->getPosV());

	screen = mTitleScreen->getScreenPtr();
	screen->move(zen::RoundOff(-2.0f * screen->getWidth() * (1.0f - NMathF::sin(HALF_PI * a))),
	             zen::RoundOff(-2.0f * screen->getHeight() * (1.0f - NMathF::sin(HALF_PI * a))));

	screen = mMoniScreen->getScreenPtr();
	screen->move(zen::RoundOff(-2.0f * screen->getWidth() * (1.0f - NMathF::sin(HALF_PI * a))), screen->getPosV());

	f32 scale = (1.0f - NMathF::sin(HALF_PI * a)) * 10.0f + 1.0f;
	screen    = mData1Screen->getScreenPtr();
	screen->setOffset(screen->getWidth() >> 1, screen->getHeight() >> 1);
	screen->setScale(scale);

	screen = mData2Screen->getScreenPtr();
	screen->move(zen::RoundOff(2.0f * screen->getWidth() * (1.0f - NMathF::sin(HALF_PI * a))), screen->getPosV());

	mConfirmMgr->init();

	if (a == 1.0f) {
		res = true;
	}

	updateScreens();
	STACK_PAD_VAR(1);
	return res;
}

/*
 * --INFO--
 * Address:	801E3288
 * Size:	002744
 */
bool zen::DrawWorldMap::modeAppear(Controller* controller)
{
	bool res = false;
	mCoursePointMgr->update(controller, false);
	if (mCoursePointMgr->getEventFlag() & 0x40) {
		if (mCoursePointMgr->getSelectCourseNumber() != mStartMode) {
			closeMapInfo();
		}

		switch (mStartMode) {
		case START_Unk1:
			setCoursePoint(PLACE_Unk1);
			break;
		case START_Unk2:
			setCoursePoint(PLACE_Unk2);
			break;
		case START_Unk3:
			setCoursePoint(PLACE_Unk3);
			break;
		case START_Unk4:
			setCoursePoint(PLACE_Unk4);
			break;
		default:
			PRINT("Illegal startMode. %d \n", mStartMode);
		}

		int x, y;
		mCoursePointMgr->getStayPos(&x, &y);
		mCursorMgr->move(x, y, false);
		res = true;
	}

	mCursorMgr->update();
	updateScreens();
	return res;
}

/*
 * --INFO--
 * Address:	801E6184
 * Size:	000868
 */
bool zen::DrawWorldMap::modeOperation(Controller* controller)
{
	bool res = false;
	mShootingStarMgr->update();
	mCoursePointMgr->update(controller, mCursorMgr->isMoveOK());
	u32 eventFlag = mCoursePointMgr->getEventFlag();
	int x, y;
	if (eventFlag & 0x1) {
		mCoursePointMgr->getStayPos(&x, &y);
		mCursorMgr->move(x, y, false);
		closeMapInfo();
	}

	if (eventFlag & 0x10) {
		mConfirmMgr->start();
		_04 = 4;
	}
	if (eventFlag & 0x20) {
		mCoursePointMgr->getStayPos(&x, &y);
		mCursorMgr->moveCancel(x, y);
	}

	if (mCursorMgr->getStatusFlag() == WorldMapCursorMgr::UFO_Unk2) {
		_08 = mCoursePointMgr->getSelectCourseNumber();
		mEffectMgr2D->killAll(false);
		mCoursePointMgr->createCourseInEffect();
		mWipeMgr->setDefault();
		mWipeMgr->close(0.5f, 320, 240);
		res = true;
	}

	mCursorMgr->update();
	updateScreens();
	return res;
}

/*
 * --INFO--
 * Address:	801E69EC
 * Size:	000614
 */
bool zen::DrawWorldMap::modeConfirm(Controller* controller)
{
	bool res = mConfirmMgr->update(controller);
	if (res && mConfirmMgr->getSelectFlag() == WorldMapConfirmMgr::SELECT_Unk0) {
		int x, y;
		mCoursePointMgr->getLandPos(&x, &y);
		mCursorMgr->move(x, y, true);
	}

	mCursorMgr->update();
	updateScreens();

	STACK_PAD_VAR(2);
	return res;
}

/*
 * --INFO--
 * Address:	801E71C8
 * Size:	000154
 */
bool zen::DrawWorldMap::modeEnd(Controller*)
{
	bool res = false;
	if (!mWipeMgr->isActive()) {
		mEffectMgr2D->killAll(true);
		res = true;
	}
	mCursorMgr->update();
	updateScreens();
	return res;
}

/*
 * --INFO--
 * Address:	801E731C
 * Size:	0000DC
 */
void zen::DrawWorldMap::updateScreens()
{
	mWipeScreen->update();
	mMoniScreen->update();
	mIconScreen->update();
	mTitleScreen->update();
	mData1Screen->update();
	mData2Screen->update();
	mPointScreen->update();
	mLineScreen->update();
	mBackScreen->update();
}

/*
 * --INFO--
 * Address:	801E73F8
 * Size:	000124
 */
void zen::DrawWorldMap::closeMapInfo()
{
	mMapImageMgr->closeMapImage();
	mTitleMgr->exitTitle();
	mPartsInfoMgr->close();
}

/*
 * --INFO--
 * Address:	801E7728
 * Size:	000220
 */
void zen::DrawWorldMap::openMapInfo()
{
	WorldMapName course = mCoursePointMgr->getSelectCourseNumber();
	mMapImageMgr->openMapImage(course);
	mTitleMgr->setTitle(course);
	mPartsInfoMgr->setActiveMapNo(course);
}
