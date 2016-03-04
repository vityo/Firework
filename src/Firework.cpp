#include "stdafx.h"
#include "Firework.h"

using namespace NFirework;

Firework::Firework(IPoint start, IPoint end, float attenuation, float freeFallAcceleration,
	float period, int maxLevelIndex, int count, float time, int levelIndex,
	EffectsContainer* effectsContainer) :
	mStart(start), mEnd(end), mAttenuation(attenuation),
	mFreeFallAcceleration(freeFallAcceleration), mPeriod(period),
	mTime(time), mLevelIndex(levelIndex), mMaxLevelIndex(maxLevelIndex),
	mCount(count), mBoom(NULL), mDeathTime(0.0f) {
	if (effectsContainer)
		mEffectsContainer = effectsContainer;
	else
		mEffectsContainer = new EffectsContainer();

	mControl = IPoint(mStart.x + (mEnd.x - mStart.x)*0.5f,
		mStart.y + (mEnd.y - mStart.y)*0.5f + mFreeFallAcceleration*mPeriod);
	mEffect = mEffectsContainer->AddEffect(STR_FIREWORK);
	mEffect->posX = mStart.x;
	mEffect->posY = mStart.y;
	mEffect->Reset();
}

Firework::~Firework() {
	if (!mLevelIndex)
		SAFE_DELETE(mEffectsContainer);

	for (std::vector<Firework*>::iterator it = mChilds.begin(); it != mChilds.end(); it++)
		SAFE_DELETE(*it);

	mChilds.clear();
}

void Firework::setMaxLevel(int value) {
	mMaxLevelIndex = value;
}

void Firework::setCount(int value) {
	mCount = value;
}

void Firework::setFreeFallAcceleration(float value) {
	mFreeFallAcceleration = value;
}

EffectsContainer* Firework::getEffectsContainer() {
	return mEffectsContainer;
}

bool Firework::isEnd() {
	//не нашел в ParticleEffect время полной анимации партиклэффекта, а его isEnd() в определенный момент 
	//начинал указывать на недоступную память, поэтому так:
	bool bIsEnd = mDeathTime >= TIME_TO_END;

	if (bIsEnd)
	for (std::vector<Firework*>::iterator it = mChilds.begin(); it != mChilds.end(); it++)
		bIsEnd = bIsEnd && (*it)->isEnd();

	return bIsEnd;
}

void Firework::move(float dt) {
	if (mTime < mPeriod) {
		if (mEffect) {
			FPoint position = math::simpleBezier(mStart, mEnd, mControl,
				math::ease(mTime / mPeriod, 0.0f, 1.0f));
			mEffect->posX = position.x;
			mEffect->posY = position.y;
		}

		mTime += dt;

		if (mTime >= mPeriod && mEffect) {
			if (mLevelIndex)
				mBoom = mEffectsContainer->AddEffect(STR_BOOM);
			else
				mBoom = mEffectsContainer->AddEffect(STR_BOOM0);

			mBoom->posX = mEnd.x;
			mBoom->posY = mEnd.y;
			mBoom->SetScale(1.0f / (float)(mLevelIndex + 1));
			mBoom->Reset();
			mEffect->Finish();
			mEffect = NULL;
			mTime = mPeriod;

			for (int i = 0; i < mCount && mLevelIndex < mMaxLevelIndex; i++) {
				float angle = math::random(ANGLE);
				float attenuate = mAttenuation *
					(1.0f - (mLevelIndex + 1) * mAttenuation + math::random((mLevelIndex + 1) * mAttenuation));
				float length = math::Vector3((float)(mEnd.x - mStart.x),
					(float)(mEnd.y - mStart.y), 0.0f).Length() * attenuate;
				mChilds.push_back(new Firework(mEnd,
					IPoint(mEnd.x + math::cos(angle) * length, mEnd.y + math::sin(angle) * length),
					mAttenuation, mFreeFallAcceleration, mPeriod * attenuate, mMaxLevelIndex,
					mCount, 0.0f, mLevelIndex + 1, mEffectsContainer));
			}
		}
	}
	else
		mDeathTime += dt;

	for (std::vector<Firework*>::iterator it = mChilds.begin(); it != mChilds.end(); it++)
		(*it)->move(dt);
}

void Firework::update(float dt) {
	mEffectsContainer->Update(dt);
	move(dt);
}