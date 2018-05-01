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

	this->terrainOctave = Array<float>(OCTAVENUMBER);
	this->terrainOctavePerc = Array<float>(OCTAVENUMBER);
	for (int i = 0; i < OCTAVENUMBER; i++)
	{
		this->terrainOctave.add(1.0);
	}
	this->terrainOctavePerc.add(0.50);
	this->terrainOctavePerc.add(0.35);
	this->terrainOctavePerc.add(0.15);
	this->terrainOctavePerc.add(0.0);
	this->terrainOctavePerc.add(0.0);
	this->terrainOctavePerc.add(0.0);
	this->terrainOctavePerc.add(0.0);
	this->terrainOctavePerc.add(0.0);
	this->redistribution = 1.0;
	this->borderPerc = 0.2;
	this->minHeight = Array<int>(MAX_DISTRICTS);
	this->maxHeight = Array<int>(MAX_DISTRICTS);
	this->density = Array<int>(MAX_DISTRICTS);
	this->blockSize = Array<int>(MAX_DISTRICTS);
	for (int j = 0; j < MAX_DISTRICTS; j++)
	{
		this->minHeight.add(1);
		this->maxHeight.add(2);
		this->density.add(100);
		this->blockSize.add(2);
	}
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
		ImGui::InputFloat("1", &terrainOctave[0]);
		ImGui::InputFloat("2", &terrainOctave[1]);
		ImGui::InputFloat("3", &terrainOctave[2]);
		ImGui::InputFloat("4", &terrainOctave[3]);
		ImGui::InputFloat("5", &terrainOctave[4]);
		ImGui::InputFloat("6", &terrainOctave[5]);
		ImGui::InputFloat("7", &terrainOctave[6]);
		ImGui::InputFloat("8", &terrainOctave[7]);
		ImGui::Text("Octaves Percentage");
		ImGui::InputFloat("1 ##Perc", &terrainOctavePerc[0]);
		ImGui::InputFloat("2 ##Perc", &terrainOctavePerc[1]);
		ImGui::InputFloat("3 ##Perc", &terrainOctavePerc[2]);
		ImGui::InputFloat("4 ##Perc", &terrainOctavePerc[3]);
		ImGui::InputFloat("5 ##Perc", &terrainOctavePerc[4]);
		ImGui::InputFloat("6 ##Perc", &terrainOctavePerc[5]);
		ImGui::InputFloat("7 ##Perc", &terrainOctavePerc[6]);
		ImGui::InputFloat("8 ##Perc", &terrainOctavePerc[7]);
		ImGui::Text("Redistribution");
		ImGui::InputFloat("##Redistribution", &redistribution);
		ImGui::Separator();
		ImGui::Text("Border Blend Percentage");
		ImGui::InputFloat("##District Perc", &borderPerc);
		ImGui::Separator();
		ImGui::Text("Houses");
		ImGui::Spacing();
		ImGui::Text("Min. Height");
		ImGui::SliderInt("##House.Min. Height", &minHeight[0], 1, 10);
		ImGui::Text("Max. Height");
		ImGui::SliderInt("##House.Max. Height", &maxHeight[0], 1, 10);
		ImGui::Text("Density");
		ImGui::SliderInt("##House.Density", &density[0], 1, 100);
		ImGui::Text("Block Size");
		ImGui::SliderInt("##House.Block.Size", &blockSize[0], 1, 100);
		ImGui::Separator();
		ImGui::Text("Skyscrapers");
		ImGui::Spacing();
		ImGui::Text("Min. Height");
		ImGui::SliderInt("##Skyscrapers.Min. Height", &minHeight[1], 1, 10);
		ImGui::Text("Max. Height");
		ImGui::SliderInt("##Skyscrapers.Max. Height", &maxHeight[1], 1, 10);
		ImGui::Text("Density");
		ImGui::SliderInt("##Skyscrapers.Density", &density[1], 1, 100);
		ImGui::Text("Block Size");
		ImGui::SliderInt("##Skyscrapers.Block.Size", &blockSize[1], 1, 100);
		ImGui::Separator();
		ImGui::Text("Factories");
		ImGui::Spacing();
		ImGui::Text("Min. Height");
		ImGui::SliderInt("##Factories.Min. Height", &minHeight[2], 1, 10);
		ImGui::Text("Max. Height");
		ImGui::SliderInt("##Factories.Max. Height", &maxHeight[2], 1, 10);
		ImGui::Text("Density");
		ImGui::SliderInt("##Factories.Density", &density[2], 1, 100);
		ImGui::Text("Block Size");
		ImGui::SliderInt("##Factories.Block.Size", &blockSize[2], 1, 100);
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
