#include <graphics.h>
#include <conio.h>
#include <iostream>

class Slot {
	public:
		int type;
		Slot(int type, float posX, float posY, float pixel);
		void Draw(bool visible);
		void OnMouseClick();

	private:
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

void Slot::Draw(bool visible) {
	IMAGE image = NULL;
	wchar_t filePath[100];

	// if it is not visible, we only show walls to the user
	int target = visible ? this->type : 0;

	swprintf_s(filePath, L"Images\\%d.jpg", target);
	loadimage(&image, filePath, int(pixel), int(pixel), true);
	putimage(int(posX), int(posY), &image, SRCCOPY);
}

void Slot::OnMouseClick() {
	Draw(true);
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
		void DrawSlots(bool visible);
		void StartEventLoop();
		void OnSlotClicked(Slot slot, int x, int y);
};

MineSweeper::MineSweeper(int windowSize, int dimension) {
	this->dimension = dimension;
	this->windowSize = windowSize;
	this->bombNum = 16;
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
		slots[slotIndex].type = -1;
	}

	// calculate bomb nums
	for (int i = 0; i < dimension * dimension; i++) {
		int surrounds = 0;
		if (slots[i].type == -1) continue;
		if (ValidateBomb(i - 1)) surrounds += 1;
		if (ValidateBomb(i + 1)) surrounds += 1;
		if (ValidateBomb(i - dimension)) surrounds += 1;
		if (ValidateBomb(i - dimension - 1)) surrounds += 1;
		if (ValidateBomb(i - dimension + 1)) surrounds += 1;
		if (ValidateBomb(i + dimension)) surrounds += 1;
		if (ValidateBomb(i + dimension - 1)) surrounds += 1;
		if (ValidateBomb(i + dimension + 1)) surrounds += 1;
		slots[i].type = surrounds;
	}

	// draw all the slots with no visiblity
	DrawSlots(false);

	StartEventLoop();
}

bool MineSweeper::ValidateBomb(int index) {
	if (index >= 0 && index < dimension * dimension) {
		return slots[index].type == -1;
	}
	return false; // that index is not exist
}

void MineSweeper::DrawSlots(bool visible) {
	for (int i = 0; i < dimension * dimension; i++) {
		slots[i].Draw(visible);
	}
}

void MineSweeper::StartEventLoop() {
	while (true) {
		ExMessage msg = getmessage(EX_MOUSE | EX_KEY);
		if (msg.message == WM_LBUTTONDOWN) {
			int x = msg.x / elementSize;
			int y = msg.y / elementSize;
			OnSlotClicked(slots[x * dimension + y], y, x);
		}
		if (msg.message = WM_KEYDOWN && msg.vkcode == 0x56) {
			DrawSlots(true); // V Key: Show slots
		}
		if (msg.message = WM_KEYDOWN && msg.vkcode == 0x48) {
			DrawSlots(false); // H Key: Hide slots
		}
	}
}

void MineSweeper::OnSlotClicked(Slot slot, int x, int y) {
	slot.OnMouseClick();
	// TODO: extend related slots, and fire the bombs.
}

int main()
{
	MineSweeper minesweeper(640, 16);
	minesweeper.CreateGame();
}

