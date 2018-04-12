#include "GenWindow.h"

GenWindow::GenWindow()
{
}

GenWindow::~GenWindow()
{
}

GenWindow * GenWindow::getInstance()
{
	static GenWindow instance;
	return &instance;
}

void GenWindow::releaseInstance()
{
}

void GenWindow::draw()
{
	if (!this->isDrawing)
	{ 
		return;
	}

	ImGui::SetNextWindowSize(ImVec2(WIDTH, HEIGHT / 2), ImGuiCond_Always);
	ImGui::SetNextWindowPos({ 0 ,0 });

	bool begin = ImGui::Begin("##debugWin", 0, { 0, 0 }, 0.6f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

	if (begin)
	{
	}

	ImGui::End();
}
