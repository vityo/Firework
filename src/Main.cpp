#include "stdafx.h"
#include "TestApplication.h"

#define MYSETTINGS_REG_KEY		"Software\\Playrix Entertainment\\Firework"
#define MYWINDOW_CLASS_NAME		"MYFIREWORK_CLASS"
#define MYAPPLICATION_NAME		"Firework"
#define STR_FILE_INPUT			"input.txt"
#define STR_FOLDER_DATA			"data"
#define STR_INPUT_LEVEL			"Level"
#define STR_INPUT_COUNT			"Count"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{	
	IO::FileStream fs(STR_FILE_INPUT);
	IO::TextReader reader(&fs);
	std::string str, name, value;
	int level(0), count(0);
	Core::fileSystem.MountDirectory(STR_FOLDER_DATA);
	str = reader.ReadLine();

	if (utils::ReadNvp(str, name, value) && name == STR_INPUT_LEVEL)
		level = utils::lexical_cast<int>(value);

	str = reader.ReadLine();

	if (utils::ReadNvp(str, name, value) && name == STR_INPUT_COUNT)
		count = utils::lexical_cast<int>(value);
	
	TestApplication app(hInstance, nCmdShow, false, level, count);
	app.SETTINGS_REG_KEY = MYSETTINGS_REG_KEY;
	app.APPLICATION_NAME = MYAPPLICATION_NAME;
	app.WINDOW_CLASS_NAME = MYWINDOW_CLASS_NAME;
	app.Init(true);
	app.Start();
	app.ShutDown();
	
	return 0;
}
