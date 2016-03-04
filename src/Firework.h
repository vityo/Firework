#pragma once
#include <vector>

namespace NFirework {
	#define TIME_TO_END								5
	#define STR_FIREWORK							"firework"
	#define STR_BOOM								"boom"
	#define STR_BOOM0								"boom0"
	#define	ANGLE									360
	#define SAFE_DELETE(p)							if(p) {delete p; p = NULL;}

	const float cfFreeFallAccelerationHeightSize = 0.2f;
	const float cfAttenuation = 0.3f;
	const float cfFlyPeriod = 2.0f;

	class Firework {
		IPoint						mStart;
		IPoint						mControl;
		IPoint						mEnd;
		float						mPeriod;
		float						mTime;
		float						mDeathTime;
		std::vector<Firework*>		mChilds;
		int							mLevelIndex;
		ParticleEffect*				mEffect;
		ParticleEffect*				mBoom;
		int							mMaxLevelIndex;
		int							mCount;
		EffectsContainer*			mEffectsContainer;
		float						mFreeFallAcceleration;
		float						mAttenuation;
		void move(float dt);

	public:
		Firework(IPoint start, IPoint end, float attenuation = 1.0f, float freeFallAcceleration = 0.0f,
			float period = 0.0f, int maxLevelIndex = 0, int count = 1, float time = 0.0f,
			int levelIndex = 0, EffectsContainer* effectsContainer = NULL);
		~Firework();

		void setMaxLevel(int value);
		void setCount(int value);
		void setFreeFallAcceleration(float value);
		EffectsContainer* getEffectsContainer();
		bool isEnd();
		void update(float dt);
	};
}
