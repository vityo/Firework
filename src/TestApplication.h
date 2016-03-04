#pragma once
#include "TestWidget.h"

class TestApplication : public Core::Application {
	int mMaxLevel;
	int mCount;

public:
	TestApplication(HINSTANCE hInstance, int nCmdShow, bool fullscreen, int maxLevel, int count);
	int getMaxLevel();
	int getCount();
	void RegisterTypes();
	void LoadResources();
};