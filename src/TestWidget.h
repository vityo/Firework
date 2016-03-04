#pragma once
#include <vector>
#include "Firework.h"

class TestWidget : public GUI::Widget {
public:
	TestWidget(const std::string& name, rapidxml::xml_node<>* elem);
	~TestWidget();

	void Draw();
	void Update(float dt);
	bool MouseDown(const IPoint& mouse_pos);

private:	
	std::vector<NFirework::Firework*>	fireworks;
};
