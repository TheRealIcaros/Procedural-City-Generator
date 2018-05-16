#include "../header/GenWindow.h"

GenWindow::GenWindow()
{
	this->perlinCalls = 0;
	this->mainRoads = 0;
	this->sizeX = 0;
	this->sizeY = 0;
	this->smallRoads = 0;
	this->seed = 0;
	this->genTime = 0;
	this->isDrawing = false;
	this->count = 0;

	this->tSizeX = 25;
	this->tSizeY = 25;
	this->pSizeX = 25;
	this->pSizeY = 25;

	this->octave = Array<float>(OCTAVENUMBER);
	this->amplitude = Array<float>(OCTAVENUMBER);
	this->octave.add(1.0);
	this->octave.add(2.0);
	this->octave.add(4.0);
	this->octave.add(8.0);
	this->octave.add(16.0);
	this->octave.add(32.0);
	this->octave.add(64.0);
	this->octave.add(128.0);

	this->amplitude.add(0.50f);
	this->amplitude.add(0.25f);
	this->amplitude.add(0.125f);
	this->amplitude.add(0.0625);
	this->amplitude.add(0.03125f);
	this->amplitude.add(0.015625f);
	this->amplitude.add(0.0078125f);
	this->amplitude.add(0.00390625f);
	this->redistribution = 1.0;
	this->borderPerc = 0.2f;
	this->minHeight[0] = 1;
	this->maxHeight[0] = 2;
	this->minHeight[1] = 3;
	this->maxHeight[1] = 6;
	this->minHeight[2] = 1;
	this->maxHeight[2] = 2;
	for (int i = 0; i < MAX_DISTRICTS; i++)
	{
		this->buildings[i] = 0;
		this->grass[i] = 0;
		this->density[i] = 100;
		this->blockSize[i] = 2;
	}
	this->minMainRoadDistance = 2;
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
		ImGui::Text("%d", buildings[0]);
		ImGui::Text("Skyscrapers");
		ImGui::Text("%d", buildings[1]);
		ImGui::Text("Factories");
		ImGui::Text("%d", buildings[2]);
		ImGui::Text("Total Buildings");
		ImGui::Text("%d", buildings[0] + buildings[1] + buildings[2]);
		ImGui::Text("D1 grass");
		ImGui::Text("%d", grass[0]);
		ImGui::Text("D2 grass");
		ImGui::Text("%d", grass[1]);
		ImGui::Text("D3 grass");
		ImGui::Text("%d", grass[2]);
		ImGui::Text("Total grass");
		ImGui::Text("%d", grass[0] + grass[1] + grass[2]);
		ImGui::Text("Integer Seed");
		ImGui::Text("%u", seed);
		ImGui::Text("Generation Time");
		ImGui::Text("%f s", genTime);
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
		ImGui::InputFloat("1", &octave[0]);
		ImGui::InputFloat("2", &octave[1]);
		ImGui::InputFloat("3", &octave[2]);
		ImGui::InputFloat("4", &octave[3]);
		ImGui::InputFloat("5", &octave[4]);
		ImGui::InputFloat("6", &octave[5]);
		ImGui::InputFloat("7", &octave[6]);
		ImGui::InputFloat("8", &octave[7]);
		ImGui::Text("Octaves Percentage");
		ImGui::InputFloat("1 ##Perc", &amplitude[0]);
		ImGui::InputFloat("2 ##Perc", &amplitude[1]);
		ImGui::InputFloat("3 ##Perc", &amplitude[2]);
		ImGui::InputFloat("4 ##Perc", &amplitude[3]);
		ImGui::InputFloat("5 ##Perc", &amplitude[4]);
		ImGui::InputFloat("6 ##Perc", &amplitude[5]);
		ImGui::InputFloat("7 ##Perc", &amplitude[6]);
		ImGui::InputFloat("8 ##Perc", &amplitude[7]);
		ImGui::Text("Redistribution");
		ImGui::InputFloat("##Redistribution", &redistribution);
		ImGui::Separator();
		ImGui::Text("Border Blend Percentage");
		ImGui::InputFloat("##District Perc", &borderPerc);
		ImGui::Separator();
		ImGui::Text("Main Road");
		ImGui::Spacing();
		ImGui::Text("Min Road Distance");
		ImGui::SliderInt("##Main Road Distance", &minMainRoadDistance, 1, 5);
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
		ImGui::SliderInt("##House.Block.Size", &blockSize[0], 1, 5);
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
		ImGui::SliderInt("##Skyscrapers.Block.Size", &blockSize[1], 1, 5);
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
		ImGui::SliderInt("##Factories.Block.Size", &blockSize[2], 1, 5);
		ImGui::Separator();
		ImGui::Spacing();
		ImGui::Checkbox("Random Generator", &random);
		ImGui::Checkbox("Random Building Generator", &randBuild);
		ImGui::Checkbox("Random District Generator", &randDistrict);
		ImGui::Checkbox("Performance Test", &performance);
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

void GenWindow::randomiser()
{
	float max = 8;
	float min = 1;
	std::sprintf(inputBuf, "%d", rand());
	int ampAmmount = rand() % ((int)max - (int)min + 1) + (int)min;

	max = tSizeX;
	pSizeX = rand() % ((int)max - (int)min + 1) + (int)min;
	pSizeY = pSizeX;

	
	min = 0;
	max = INT_MAX;
	for (int k = 0; k < ampAmmount; k++)
	{
		octave[k] = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
		amplitude[k] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	}

	for (int k = ampAmmount; k < 8; k++)
	{
		octave[k] = 0;
		amplitude[k] = 0;
	}

	min = 0;
	max = 10;
	redistribution = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));

	borderPerc = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

	min = 1;
	max = 5;
	minMainRoadDistance = rand() % ((int)max - (int)min + 1) + (int)min;

	for (int k = 0; k < 3; k++)
	{
		min = 1;
		max = 10;
		minHeight[k] = rand() % ((int)max - (int)min + 1) + (int)min;;
		maxHeight[k] = rand() % ((int)max - (int)min + 1) + (int)min;
		max = 100;
		density[k] = rand() % ((int)max - (int)min + 1) + (int)min;
		max = 5;
		blockSize[k] = rand() % ((int)max - (int)min + 1) + (int)min;
	}


}
