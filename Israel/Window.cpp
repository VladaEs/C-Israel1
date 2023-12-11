#include <iostream>
#include "Window.h"
#include "fun_console.h"

ASD::Window::Window() {
	x = y = 0;
	width = GetCols();
	height = GetRows();
	int color;
	int bgCOlor;
	MaxLen = 70;
	startPosY;
	page = 1;


}

void ASD::Window::SetColor(int c) {
	color = c;
}
ASD::Window::~Window() {

}
void ASD::Window::SetStartPos(int posX, int posY) {
	this->startPosX = posX;
	this->startPosY = posY;
}
const char* ASD::Window::StartPos(const char *s) {
	this->SetPos(this->startPosX, this->startPosY++);
	this->Paint(this->color, this->bgColor);
	std::cout << this->FillGap(s);
	return 0;
}
void ASD::Window::SetBgColor(int c) {
	bgColor = c;
}

void ASD::Window::Move(int _x, int _y) {
	if (_x + width <= GetCols()) {
		x = _x;
	}
	else {
		width -= (_x - x);
		x = _x;
	}

	if (_y + height <= GetRows()) {
		y = _y;
	}
	else {
		height -= (_y - y);
		y = _y;
	}
}

void ASD::Window::SetWidth(int w) {
	if (w >= 3 && x + w <= GetCols()) {
		width = w;
	}
}

void ASD::Window::SetHeight(int h) {
	if (h >= 3 && y + h <= GetRows()) {
		height = h;
	}
}
void ASD::Window::Clear() {
	this->Paint(White, Black);
	cls();


}
int ASD::Window::GetMaxLen() {
	return MaxLen;
}
void ASD::Window::Paint(int col, int bgCol) {
	this->color = col;
	this->bgColor = bgCol;
	::SetColor(this->color, this->bgColor);
}
size_t ASD::Window::my_strlen(const char *s) {
	const char* cur = s;
	for (; *cur; ++cur);
	return (cur - s);
}
char* ASD::Window::FillGap(const char *s) {
	int strLen = this->my_strlen(s);
	int rest = (this->GetMaxLen() - strLen) - 2;
	char *Space = new char[rest + 1];

	for (int i = 0; i < strLen; i++) {
		std::cout << s[i];
	}
	for (int i = 0; i < rest; i++) {
		Space[i] = ' ';
	}
	Space[rest] = '\0';
	return Space;
}
void ASD::Window::Show() {


	for (int i = 0; i < height; i++) {
		GotoXY(x, y + i);
		for (int j = 0; j < width; j++) {
			std::cout << " ";
		}
	}
	GotoXY(x, y);
}
void ASD::Window::SetPos(int _x, int _y) {
	GotoXY(_x, _y);
}
ASD::Window& ASD::Window::SetPage() {
	if (page == 1) {
		this->page = 2;
		return *this;
	}
	else{
		this->page = 1;
		return *this;
	}
}
int ASD::Window::GetPage() {
	return this->page;
}
void ASD::Window::DrawMenu(bool loged) {
	if (page == 1) {

	
	this->SetStartPos(15, 8);
	//this->Clear();
	this->SetBgColor(Red);
	this->SetColor(White);
	StartPos("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
	StartPos("                 I. Основное меню");
	StartPos("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
	
	this->SetBgColor(White);
	this->SetColor(Black);

	StartPos("[1]- Создать учетную запись");
	this->SetBgColor(Green);
	this->SetColor(Black);
	StartPos("[2]- Войти в уже существующую запись");
	StartPos("[3]- Выход из программы");
	if (loged == true) {
		StartPos("[4]- Следующая страница");
	}
	this->SetBgColor(Cyan);
	this->SetColor(Black);
	this->SetStartPos(15, 21);
	StartPos("Введіть пункт меню: ");
	SetPos(35, 21);

	}
	if (page == 2 ) {
		this->SetStartPos(15, 8);
		//this->Clear();
		this->SetBgColor(Red);
		this->SetColor(White);
		StartPos("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
		StartPos("                 II. Создание публикаций");
		StartPos("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");

		this->SetBgColor(White);
		this->SetColor(Black);

		StartPos("[1]- Разместить новую недвиждимость");
		this->SetBgColor(Green);
		this->SetColor(Black);
		StartPos("[2]- Удалить 1 запись ");
		StartPos("[3]- Отобразить все обьявления");
		StartPos("[4]- Посмотреть все мои обьявления");
		StartPos("[5]- Фильтр обьявлений");
		this->SetBgColor(Magenta);
		this->SetColor(White);
		StartPos("[6]- Выйти в главное меню и выйти из учетной записи");
		this->SetBgColor(Cyan);
		this->SetColor(Black);
		this->SetStartPos(15, 21);
		StartPos("Введіть пункт меню: ");
		SetPos(35, 21);

	}
}