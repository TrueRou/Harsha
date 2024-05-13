#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <thread>
#include <mutex>

class Slot {
	public:
		Slot(int type, float posX, float posY, float pixel);
		void Draw();
		void AttachType(int type);
		int GetType() const;

	private:
		int type;
		float posX;
		float posY;
		float pixel;
};

Slot::Slot(int type, float posX, float posY, float pixel) {
	this->type = type;
	this->posX = posX;
	this->posY = posY;
	this->pixel = pixel;
}

void Slot::Draw() {
	IMAGE image = NULL;
	wchar_t filePath[100];

	swprintf_s(filePath, L"Images\\%d.jpg", this->type);
	loadimage(&image, filePath, int(pixel), int(pixel), true);
	putimage(int(posX), int(posY), &image, SRCCOPY);
}

void Slot::AttachType(int type) {
	this->type = type;
}

int Slot::GetType() const {
	return this->type;
}

class MineSweeper {
	public:
		MineSweeper(int windowSize, int dimension);
		void CreateGame();

	private:
		Slot* slots;
		int dimension;
		int bombNum;
		int windowSize;
		int elementSize;
		bool ValidateBomb(int index);
		void StartEventLoop();
};

MineSweeper::MineSweeper(int windowSize, int dimension) {
	this->dimension = dimension;
	this->windowSize = windowSize;
	this->bombNum = 5;
	this->elementSize = windowSize / dimension;
	this->slots = (Slot*) malloc(sizeof(Slot) * dimension * dimension);
}

void MineSweeper::CreateGame() {
	initgraph(windowSize, windowSize);
	srand(time(0));
	// create slots for the minesweeper graph
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			Slot slot(0, i * elementSize, j * elementSize, elementSize);
			slots[i * dimension + j] = slot; // keep the reference of slots
		}
	}

	// add bombs to specific slots
	for (int i = 0; i < bombNum; i++) {
		int slotIndex = rand() % (dimension * dimension);
		slots[slotIndex].AttachType(-1);
	}

	// calculate bomb nums
	for (int i = 0; i < dimension * dimension; i++) {
		int surrounds = 0;
		if (slots[i].GetType() == -1) continue;
		if (ValidateBomb(i - 1)) surrounds += 1;
		if (ValidateBomb(i + 1)) surrounds += 1;
		if (ValidateBomb(i - dimension)) surrounds += 1;
		if (ValidateBomb(i - dimension - 1)) surrounds += 1;
		if (ValidateBomb(i - dimension + 1)) surrounds += 1;
		if (ValidateBomb(i + dimension)) surrounds += 1;
		if (ValidateBomb(i + dimension - 1)) surrounds += 1;
		if (ValidateBomb(i + dimension + 1)) surrounds += 1;
		slots[i].AttachType(surrounds);
	}

	// draw all the slots
	for (int i = 0; i < dimension * dimension; i++) {
		slots[i].Draw();
	}

	StartEventLoop();
}

bool MineSweeper::ValidateBomb(int index)
{
	if (index >= 0 && index < dimension * dimension) {
		return slots[index].GetType() == -1;
	}
	return false; // that index is not exist
}

void MineSweeper::StartEventLoop () {
	while (true) {
		int key = _getch();
	}
}

int main()
{
	MineSweeper minesweeper(640, 16);
	minesweeper.CreateGame();
}

