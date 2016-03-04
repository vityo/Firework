#include "stdafx.h"
#include "TestWidget.h"
#include "TestApplication.h"

TestWidget::TestWidget(const std::string& name, rapidxml::xml_node<>* elem)
	: Widget(name) {
}

TestWidget::~TestWidget() {
	for (std::vector<NFirework::Firework*>::iterator it = fireworks.begin(); it != fireworks.end(); it++)
		SAFE_DELETE(*it);

	fireworks.clear();
}

void TestWidget::Draw() {
	for (int i = 0; i < fireworks.size(); i++)
		if (fireworks[i] && fireworks[i]->getEffectsContainer())
			fireworks[i]->getEffectsContainer()->Draw();
}

void TestWidget::Update(float dt) {
	for (int i = 0; i < fireworks.size(); i++) {
		if (fireworks[i]->isEnd()) {
			delete fireworks[i];
			fireworks.erase(fireworks.begin() + i);
			i--;
		}
		else {
			fireworks[i]->update(dt);
		}
	}
}

bool TestWidget::MouseDown(const IPoint &mouse_pos) {
	if (Core::mainInput.GetMouseLeftButton())
		fireworks.push_back(new NFirework::Firework(
			IPoint(math::random(Core::appInstance->GAME_CONTENT_WIDTH), 0),
			mouse_pos, NFirework::cfAttenuation, NFirework::cfFreeFallAccelerationHeightSize *
			Core::appInstance->GAME_CONTENT_HEIGHT, NFirework::cfFlyPeriod,
			dynamic_cast<TestApplication*>(Core::appInstance)->getMaxLevel() - 1,
			dynamic_cast<TestApplication*>(Core::appInstance)->getCount()));

	return false;
}
