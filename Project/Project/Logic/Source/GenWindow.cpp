#include "../header/GenWindow.h"

GenWindow::GenWindow()
{
	value = Values::getInstance();
	this->perlinCalls = 0;
	this->mainRoads = 0;
	this->smallRoads = 0;
	this->houses = 0;
	this->skyscrapers = 0;
	this->factories = 0;
	this->totalBuildings = 0;
	this->grassD1 = 0;
	this->grassD2 = 0;
	this->grassD3 = 0;
	this->grassTotal = 0;
	this->intSeed = 0;
	this->genTime = 0;
	this->isDrawing = false;
}

GenWindow::~GenWindow()
{
}

void GenWindow::draw()
{
	if (!this->isDrawing)
	{ 
		return;
	}

	ImGui::SetNextWindowSize(ImVec2(WIDTH / 4, HEIGHT), ImGuiCond_Always);
	ImGui::SetNextWindowPos({ 0, 0 });

	bool begin = ImGui::Begin("##debugWin", 0, { 0, 0 }, 0.6f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
	if (begin)
	{
		ImGui::Text("Statistics");
		ImGui::Separator();
		ImGui::Text("Perlin calls");
		ImGui::Text("%d", value->getCount());
		ImGui::Text("Map Size");
		ImGui::Text("X %d", sizeX);
		ImGui::Text("Y %d", sizeY);
		ImGui::Text("Main roads");
		ImGui::Text("%d", mainRoads);
		ImGui::Text("Small roads");
		ImGui::Text("%d", smallRoads);
		ImGui::Text("Houses");
		ImGui::Text("%d", houses);
		ImGui::Text("Skyscrapers");
		ImGui::Text("%d", skyscrapers);
		ImGui::Text("Factories");
		ImGui::Text("%d", factories);
		ImGui::Text("Total Buildings");
		ImGui::Text("%d", totalBuildings);
		ImGui::Text("D1 grass");
		ImGui::Text("%d", grassD1);
		ImGui::Text("D2 grass");
		ImGui::Text("%d", grassD2);
		ImGui::Text("D3 grass");
		ImGui::Text("%d", grassD3);
		ImGui::Text("Total grass");
		ImGui::Text("%d", grassTotal);
		ImGui::Text("Integer Seed");
		ImGui::Text("%d", value->getSeed());
		ImGui::Text("Generation Time");
		ImGui::Text("%d", genTime);
	}

	ImGui::End();

	ImGui::SetNextWindowSize(ImVec2(WIDTH / 4, HEIGHT), ImGuiCond_Always);
	ImGui::SetNextWindowPos({ (WIDTH / 4) * 3, 0 });

	begin = ImGui::Begin("##debugWin1", 0, { 0, 0 }, 0.6f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
	if (begin)
	{
		ImGui::InputText("Seed", value->getInputBufPTR(), 128, ImGuiInputTextFlags_CharsNoBlank);
		ImGui::Separator();
		ImGui::Text("Terrain");
		ImGui::Text("Size");
		ImGui::InputInt("X", value->getTSizeXPTR(), 1, 100);
		ImGui::InputInt("Y", value->getTSizeYPTR(), 1, 100);
		ImGui::Text("Octaves");
		ImGui::InputFloat("1", value->getTerrainOctavePTR1());
		ImGui::InputFloat("2", value->getTerrainOctavePTR2());
		ImGui::InputFloat("3", value->getTerrainOctavePTR3());
		ImGui::Text("Octaves Percentage");
		ImGui::InputFloat("1 ", value->getTerrainOctavePercPTR1());
		ImGui::InputFloat("2 ", value->getTerrainOctavePercPTR2());
		ImGui::InputFloat("3 ", value->getTerrainOctavePercPTR3());
		ImGui::Text("Redistribution");
		ImGui::InputFloat("##Redistribution", value->getRedistributionPTR());
		ImGui::Separator();
		ImGui::Text("Houses");
		ImGui::Spacing();
		ImGui::Text("Min. Height");
		ImGui::SliderInt("##House.Min. Height", value->getHouseMinHeightPTR(), 1, 10);
		ImGui::Text("Max. Height");
		ImGui::SliderInt("##House.Max. Height", value->getHouseMaxHeightPTR(), 1, 10);
		ImGui::Text("Density");
		ImGui::SliderInt("##House.Density", value->getHouseDensityPTR(), 1, 100);
		ImGui::Text("Block Size");
		ImGui::SliderInt("##House.Block.Size", value->getHouseBlockSizePTR(), 1, 100);
		ImGui::Separator();
		ImGui::Text("Skyscrapers");
		ImGui::Spacing();
		ImGui::Text("Min. Height");
		ImGui::SliderInt("##Skyscrapers.Min. Height", value->getSkyscraperMinHeightPTR(), 1, 10);
		ImGui::Text("Max. Height");
		ImGui::SliderInt("##Skyscrapers.Max. Height", value->getSkyscraperMaxHeightPTR(), 1, 10);
		ImGui::Text("Density");
		ImGui::SliderInt("##Skyscrapers.Density", value->getSkyscraperDensityPTR(), 1, 100);
		ImGui::Text("Block Size");
		ImGui::SliderInt("##Skyscrapers.Block.Size", value->getSkyscraperBlockSizePTR(), 1, 100);
		ImGui::Separator();
		ImGui::Text("Factories");
		ImGui::Spacing();
		ImGui::Text("Min. Height");
		ImGui::SliderInt("##Factories.Min. Height", value->getFactoriesMinHeightPTR(), 1, 10);
		ImGui::Text("Max. Height");
		ImGui::SliderInt("##Factories.Max. Height", value->getFactoriesMaxHeightPTR(), 1, 10);
		ImGui::Text("Density");
		ImGui::SliderInt("##Factories.Density", value->getFactoriesDensityPTR(), 1, 100);
		ImGui::Text("Block Size");
		ImGui::SliderInt("##Factories.Block.Size", value->getFactoriesBlockSizePTR(), 1, 100);
		ImGui::Separator();
		ImGui::Spacing();
		if (ImGui::Button("Generate"))
		{
			value->setGenerate(true);
			sizeX = value->getTSizeX();
			sizeY = value->getTSizeY();
		}

	}
	ImGui::End();
}
