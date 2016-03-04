#include "stdafx.h"
#include "TestApplication.h"

TestApplication::TestApplication(HINSTANCE hInstance, int nCmdShow, bool fullscreen, int maxLevel, int count):
	Application(hInstance, nCmdShow, fullscreen) {
	mMaxLevel = maxLevel;
	mCount = count;
	GAME_CONTENT_WIDTH = 1024;
	GAME_CONTENT_HEIGHT = 768;
}

int TestApplication::getMaxLevel() {
	return mMaxLevel; 
}

int TestApplication::getCount() {
	return mCount; 
}

void TestApplication::RegisterTypes() {
	Application::RegisterTypes();
	REGISTER_WIDGET_XML(TestWidget, "TestWidget");
}

void TestApplication::LoadResources() {
	Core::LuaExecuteStartupScript("start.lua");
}