//Класс для реализации удобного, гибкого и очень простого управления цветами

#include "ncurses.h"

//Макрос для инициализации цветовой системы

#define ccolor color = new ColorController

int number = 1; //Переменная для того, что бы можно было использовать
//множество цветов одновременно присваивая парам ее номер

class ColorController {
public:
	int chars; //Переменная для хранения нынешнего цвета символов
	int backs; //Переменная для хранения нынешнего цвета фона символов
	ColorController(int chcolor, int bgcolor) { //Констурктор, который инициализирует пару
		if(number >= 60) //Ограничение для того, что бы не выйти за пределы возможного кол-ва пар
			number = 1; //Возвращает к своему первоначальному значению
		number++; //Прибавляет номер, для каждого нового объекта
		chars = chcolor; //Запоминает нынешний цвет символов переданный через аргументы
		backs = bgcolor; //Запоминает нынешний цвет фона символов переданный через аргументы
		init_pair(number, chars, backs); //Инициализирует пару цветов
		attron(COLOR_PAIR(number)); //Включает аттрибут пары
	}
}*color; //Заранее выделенный указатель для динамического выделения объектов в любом месте кода
