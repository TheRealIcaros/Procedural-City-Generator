#include "../header/GenWindow.h"

GenWindow::GenWindow()
{
	this->perlinCalls = 0;
	this->mainRoads = 0;
	this->sizeX = 0;
	this->sizeY = 0;
	this->smallRoads = 0;
	this->houses = 0;
	this->skyscrapers = 0;
	this->factories = 0;
	this->totalBuildings = 0;
	this->grassD1 = 0;
	this->grassD2 = 0;
	this->grassD3 = 0;
	this->grassTotal = 0;
	this->seed = 0;
	this->genTime = 0;
	this->isDrawing = false;
	this->count = 0;

	this->tSizeX = 25;
	this->tSizeY = 25;
	this->pSizeX = 15;
	this->pSizeY = 15;
	this->terrainOctave1 = 1.0;
	this->terrainOctave2 = 1.0;
	this->terrainOctave3 = 1.0;
	this->terrainOctave4 = 1.0;
	this->terrainOctave5 = 1.0;
	this->terrainOctave6 = 1.0;
	this->terrainOctave7 = 1.0;
	this->terrainOctave8 = 1.0;
	this->terrainOctavePerc1 = 0.50;
	this->terrainOctavePerc2 = 0.35;
	this->terrainOctavePerc3 = 0.15;
	this->terrainOctavePerc4 = 0.0;
	this->terrainOctavePerc5 = 0.0;
	this->terrainOctavePerc6 = 0.0;
	this->terrainOctavePerc7 = 0.0;
	this->terrainOctavePerc8 = 0.0;
	this->redistribution = 1.0;
	this->borderPerc = 0.2;
	this->houseMinHeight = 1;
	this->houseMaxHeight = 2;
	this->houseDensity = 100;
	this->houseBlockSize = 2;
	this->skyscraperMinHeight = 1;
	this->skyscraperMaxHeight = 2;
	this->skyscraperDensity = 100;
	this->skyscraperBlockSize = 2;
	this->factoriesMinHeight = 1;
	this->factoriesMaxHeight = 2;
	this->factoriesDensity = 100;
	this->factoriesBlockSize = 2;
	this->generate = false;
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
		ImGui::Text("%d", count);
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
		ImGui::Text("%d", seed);
		ImGui::Text("Generation Time");
		ImGui::Text("%d", genTime);
	}

	ImGui::End();

	ImGui::SetNextWindowSize(ImVec2(WIDTH / 4, HEIGHT), ImGuiCond_Always);
	ImGui::SetNextWindowPos({ (WIDTH / 4) * 3, 0 });

	begin = ImGui::Begin("##debugWin1", 0, { 0, 0 }, 0.6f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
	if (begin)
	{
		ImGui::InputText("Seed", inputBuf, 128, ImGuiInputTextFlags_CharsNoBlank);
		ImGui::Separator();
		ImGui::Text("Perlin");
		ImGui::Text("Size");
		ImGui::InputFloat("X ##Perlin", &pSizeX, 1, 100);
		ImGui::InputFloat("Y ##Perlin", &pSizeY, 1, 100);
		ImGui::Separator();
		ImGui::Text("Terrain");
		ImGui::Text("Size");
		ImGui::InputInt("X ##Terrain", &tSizeX, 1, 1000);
		ImGui::InputInt("Y ##Terrain", &tSizeY, 1, 1000);
		ImGui::Text("Octaves");
		ImGui::InputFloat("1", &terrainOctave1);
		ImGui::InputFloat("2", &terrainOctave2);
		ImGui::InputFloat("3", &terrainOctave3);
		ImGui::InputFloat("4", &terrainOctave4);
		ImGui::InputFloat("5", &terrainOctave5);
		ImGui::InputFloat("6", &terrainOctave6);
		ImGui::InputFloat("7", &terrainOctave7);
		ImGui::InputFloat("8", &terrainOctave8);
		ImGui::Text("Octaves Percentage");
		ImGui::InputFloat("1", &terrainOctavePerc1);
		ImGui::InputFloat("2", &terrainOctavePerc2);
		ImGui::InputFloat("3", &terrainOctavePerc3);
		ImGui::InputFloat("4", &terrainOctavePerc4);
		ImGui::InputFloat("5", &terrainOctavePerc5);
		ImGui::InputFloat("6", &terrainOctavePerc6);
		ImGui::InputFloat("7", &terrainOctavePerc7);
		ImGui::InputFloat("8", &terrainOctavePerc8);
		ImGui::Text("Redistribution");
		ImGui::InputFloat("##Redistribution", &redistribution);
		ImGui::Separator();
		ImGui::Text("Border Blend Percentage");
		ImGui::InputFloat("##District Perc", &borderPerc);
		ImGui::Separator();
		ImGui::Text("Houses");
		ImGui::Spacing();
		ImGui::Text("Min. Height");
		ImGui::SliderInt("##House.Min. Height", &houseMinHeight, 1, 10);
		ImGui::Text("Max. Height");
		ImGui::SliderInt("##House.Max. Height", &houseMaxHeight, 1, 10);
		ImGui::Text("Density");
		ImGui::SliderInt("##House.Density", &houseDensity, 1, 100);
		ImGui::Text("Block Size");
		ImGui::SliderInt("##House.Block.Size", &houseBlockSize, 1, 100);
		ImGui::Separator();
		ImGui::Text("Skyscrapers");
		ImGui::Spacing();
		ImGui::Text("Min. Height");
		ImGui::SliderInt("##Skyscrapers.Min. Height", &skyscraperMinHeight, 1, 10);
		ImGui::Text("Max. Height");
		ImGui::SliderInt("##Skyscrapers.Max. Height", &skyscraperMaxHeight, 1, 10);
		ImGui::Text("Density");
		ImGui::SliderInt("##Skyscrapers.Density", &skyscraperDensity, 1, 100);
		ImGui::Text("Block Size");
		ImGui::SliderInt("##Skyscrapers.Block.Size", &skyscraperBlockSize, 1, 100);
		ImGui::Separator();
		ImGui::Text("Factories");
		ImGui::Spacing();
		ImGui::Text("Min. Height");
		ImGui::SliderInt("##Factories.Min. Height", &factoriesMinHeight, 1, 10);
		ImGui::Text("Max. Height");
		ImGui::SliderInt("##Factories.Max. Height", &factoriesMaxHeight, 1, 10);
		ImGui::Text("Density");
		ImGui::SliderInt("##Factories.Density", &factoriesDensity, 1, 100);
		ImGui::Text("Block Size");
		ImGui::SliderInt("##Factories.Block.Size", &factoriesBlockSize, 1, 100);
		ImGui::Separator();
		ImGui::Spacing();
		if (ImGui::Button("Generate"))
		{
			generate = true;;
			count = 0;
			sizeX = tSizeX;
			sizeY = tSizeY;
		}

	}
	ImGui::End();
}
