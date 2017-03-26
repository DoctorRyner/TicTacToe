#include <cstdlib>
#include <ctime>
#include <cstring>
#include "ncurses.h"
#include "Window.cpp"
#include "ColorController.cpp"
#include "Graphics.cpp"
#include "ttt.cpp"
#include "Figures.cpp"

void draw(int); //Объявления метода для вырисовывания фигур

int MainMenu(); //Объявления метода для главного меню

void ttt::full() { //Метод для построения игрового поля
	int amount = 9; //Кол во кубов для игры
	for(int i=0; i<c.n; i++) //Цикл для обнуления фигур
		f[i].zero(); //Метод для обнуления фигуры
	int xedge = 11; //Переменные для определения местоположения перемещенных фигур
	int yedge = 8; 
	ccolor(0, 0); //Установка цвета, как черный
	for(int i=0; i<amount; i++) //Цикл для создания формы кубов
		f[i].cube(7, 3); //Создание формы фигуры
	for(int j=0; j<amount; j++) {  //Цикл для перемещения фигур на свои позиции
		f[j].moving(4 * xedge, 0);
		f[j].moving(0, 4 * (yedge / 2));
		if(j==2 || j==5) {
			xedge -= 2;
			yedge = 10;
		}
		yedge -= 2;
	}
	f[9].cube(c.x, 6); //Создание формы фигуры
	f[10].cube(c.x, 3); //Создание формы фигуры
	f[10].moving(0, c.y-3); //Перемещение фигуры
	f[11].cube(8, 1); //Создание формы фигуры
	f[11].moving(f[11].xmax / 2, 0); //Перемещение фигуры
}

void ttt::PvE() {
	full();
	f[11].add_text("(X) PLAYER VS (O) ai", 0, 1, 26, 0);
	draw(6);
	keypad(stdscr, true);
	bool ex = false;
	bool one = true;
	bool fs = true;
	int ai;
	int a = 0;
	int b = 8;
	int select = 8;
	int step;
	halfdelay(1);
	if(fs && toe.level) {
		f[4].add_text("O", 7, 0, 3, 1);
		f[4].by = 2;
		f[11].add_text("(O) PLAYER VS (O) ai", 0, 1, 25, 0);
		f[4].selected = true;
		draw(6);
		fs = false;
	}
	while(!ex) {
		int ch = getch();
		move(f[select].ymin + 1, f[select].xmin + 3);
		while(1) {
			if(winner)
				break;
			f1 = 0;
			f2 = 3;
			f3 = 6;
			for(int i=0; i<3; i++) {
				if(f[f1].by == 1 && f[f2].by == 1 && f[f3].by == 1) {
					winner = 1;
					if(winner)
						break;
					
				}
				if(f[f1].by == 2 && f[f2].by == 2 && f[f3].by == 2) {
					winner = 2;
					if(winner)
						break;
				}
				f1++;f2++;f3++;
			}
			//Вертикальные линии
			if(winner)
				break;
			f1 = -3;
			f2 = -2;
			f3 = -1;
			for(int i=0; i<3; i++) {
				f1 += 3; f2 += 3; f3 += 3;
				if(f[f1].by == 1 && f[f2].by == 1 && f[f3].by == 1) {
					winner = 1;
					break;
				}
				if(f[f1].by == 2 && f[f2].by == 2 && f[f3].by == 2) {
					winner = 2;
					break;
				}
			}
			//Диагональные линии
			if(winner)
				break;
			f1 = 0;
			f2 = 4;
			f3 = 8;
			if(f[f1].by == 1 && f[f2].by == 1 && f[f3].by == 1) {
				winner = 1;
			}
			if(f[f1].by == 2 && f[f2].by == 2 && f[f3].by == 2) {
				winner = 2;
			}
			if(winner)
				break;
			f1 = 2;
			f2 = 4;
			f3 = 6;
			if(f[f1].by == 1 && f[f2].by == 1 && f[f3].by == 1) {
				winner = 1;
				break;
			}
			if(f[f1].by == 2 && f[f2].by == 2 && f[f3].by == 2) {
				winner = 2;
				break;
			}
			break;
		}
		if(winner) {
			if(winner == 1) {
				f[f1].add_text("X", 1, 0, 3, 1);
				f[f2].add_text("X", 1, 0, 3, 1);
				f[f3].add_text("X", 1, 0, 3, 1);
				f[11].add_text("PLAYER HAS WON!", 0, 1, 27, 0);
			}
			else if(winner == 2) {
				f[f1].add_text("O", 1, 0, 3, 1);
				f[f2].add_text("O", 1, 0, 3, 1);
				f[f3].add_text("O", 1, 0, 3, 1);
				f[11].add_text("AI HAS WON!", 0, 1, 30, 0);
			}
			draw(6);
			ex = true;
			int lel;
			bool kkk = false;
			while(!kkk) {
				lel = getch();
				if(lel == '\n' || lel == ' ' || lel == KEY_F(2))
					kkk = true;
			}
			for(int i=0; i<c.n; i++)
				f[i].zero();
			draw(6);
			ex = true;
			for(int i=0; i<c.n; i++)
				f[i].zero();
			MainMenu();
		}
		for(int i=0, j=0; i<9; i++) {
			if(f[i].selected) {
				j++;
			}
			if(j >= 9) {
				f[11].add_text("DEAD END!", 0, 1, 30, 0);
			draw(6);
			ex = true;
			int lel;
			bool kkk = false;
			while(!kkk) {
				lel = getch();
				if(lel == '\n' || lel == ' ' || lel == KEY_F(2))
					kkk = true;
			}
			for(int i=0; i<c.n; i++)
				f[i].zero();
			MainMenu();
			}
		} 
		if((ch == '\n' || ch == ' ') && !f[select].selected) {
			//HARD BOT
			if(toe.level) {
				f[select].add_text("X", 7, 0, 3, 1);
				f[select].by = 1;
				f[11].add_text("(X) PLAYER VS (O) ai", 0, 1, 22, 0);
				f[select].selected = true;
				f[11].add_text("(O) playerVS (O) AI", 0, 1, 25, 0);
				draw(6);
				ai = select;
				for(int i=0; i<9; i++) {
					ai = rand() % (b - a+1) + a;
					if(!f[ai].selected)
						break;
				}
				if(!f[4].selected)
					ai = 4;
				else {
					f1 = 8;
					f2 = 5;
					f3 = 2;
					for(int i=0; i<3; i++) {
						if(f[f1].by == 1 && f[f2].by == 1 && !f[f3].by) {
							ai = f3;
						}
						if(f[f1].by == 1 && !f[f2].by && f[f3].by == 1) {
							ai = f2;
						}
						if(!f[f1].by && f[f2].by == 1 && f[f3].by == 1) {
							ai = f1;
						}
						f1--;
						f2--;
						f3--;
					}
					f1 = 8;
					f2 = 7;
					f3 = 6;
					for(int i=0; i<3; i++) {
						if(f[f1].by == 1 && f[f2].by == 1 && !f[f3].by) {
							ai = f3;
						}
						if(f[f1].by == 1 && !f[f2].by && f[f3].by == 1) {
							ai = f2;
						}
						if(!f[f1].by && f[f2].by == 1 && f[f3].by == 1) {
							ai = f1;
						}
						f1 -= 3;
						f2 -= 3;
						f3 -= 3;
					}
				}
				if(!f[ai].selected) {
					f[ai].add_text("O", 7, 0, 3, 1);
					f[ai].by = 2;
					f[11].add_text("(O) PLAYER VS (O) ai", 0, 1, 25, 0);
					f[ai].selected = true;
					draw(6);
				}
			}
		}
		if(ch == KEY_UP) {
			if(select < 8)
				select++;
		}
		if(ch ==KEY_DOWN) {
			if(select > 0)
				select--;
		}
		if(ch ==KEY_LEFT) {
			if(select >= 0)
				select += 3;
		}
		if(ch ==KEY_RIGHT) {
			if(select <= 8)
				select -= 3;
		}
		if(ch == KEY_F(2)) {
			ex = true;
			for(int i=0; i<c.n; i++)
					f[i].zero();
			MainMenu();
		}
		if(select > 8)
			select = 8;
		if(select < 0)
			select = 0;
		//Горизонтальные линии
	}
	
}

void ttt::PvP() {
	full();
	f[11].add_text("(X) PLAYER 1 VS (O) player 2", 0, 1, 22, 0);
	draw(6);
	keypad(stdscr, true);
	bool ex = false;
	bool one = false;
	int select = 8;
	halfdelay(1);
	while(!ex) {
		int ch = getch();
		move(f[select].ymin + 1, f[select].xmin + 3);
		if((ch == '\n' || ch == ' ') && !f[select].selected) {
			if(one)
				one = false;
			else
				one = true;
			if(one) {
				f[select].add_text("X", 7, 0, 3, 1);
				f[select].by = 1;
				f[11].add_text("(X) player 1 VS (O) PLAYER 2", 0, 1, 22, 0);
			}
			else {
				f[select].add_text("O", 7, 0, 3, 1);
				f[select].by = 2;
				f[11].add_text("(X) PLAYER 1 VS (O) player 2", 0, 1, 22, 0);
			}
			f[select].selected = true;
			draw(6);
		}
		if(ch == KEY_UP) {
			if(select < 8)
				select++;
		}
		if(ch ==KEY_DOWN) {
			if(select > 0)
				select--;
		}
		if(ch ==KEY_LEFT) {
			if(select >= 0)
				select += 3;
		}
		if(ch ==KEY_RIGHT) {
			if(select <= 8)
				select -= 3;
		}
		if(ch == KEY_F(2)) {
			ex = true;
			for(int i=0; i<c.n; i++)
					f[i].zero();
			MainMenu();
		}
		if(select > 8)
			select = 8;
		if(select < 0)
			select = 0;
		//Горизонтальные линии
		while(1) {
			if(winner)
				break;
			f1 = 0;
			f2 = 3;
			f3 = 6;
			for(int i=0; i<3; i++) {
				if(f[f1].by == 1 && f[f2].by == 1 && f[f3].by == 1) {
					winner = 1;
					if(winner)
						break;
					
				}
				if(f[f1].by == 2 && f[f2].by == 2 && f[f3].by == 2) {
					winner = 2;
					if(winner)
						break;
				}
				f1++;f2++;f3++;
			}
			//Вертикальные линии
			if(winner)
				break;
			f1 = -3;
			f2 = -2;
			f3 = -1;
			for(int i=0; i<3; i++) {
				f1 += 3; f2 += 3; f3 += 3;
				if(f[f1].by == 1 && f[f2].by == 1 && f[f3].by == 1) {
					winner = 1;
					break;
				}
				if(f[f1].by == 2 && f[f2].by == 2 && f[f3].by == 2) {
					winner = 2;
					break;
				}
			}
			//Диагональные линии
			if(winner)
				break;
			f1 = 0;
			f2 = 4;
			f3 = 8;
			if(f[f1].by == 1 && f[f2].by == 1 && f[f3].by == 1) {
				winner = 1;
			}
			if(f[f1].by == 2 && f[f2].by == 2 && f[f3].by == 2) {
				winner = 2;
			}
			if(winner)
				break;
			f1 = 2;
			f2 = 4;
			f3 = 6;
			if(f[f1].by == 1 && f[f2].by == 1 && f[f3].by == 1) {
				winner = 1;
				break;
			}
			if(f[f1].by == 2 && f[f2].by == 2 && f[f3].by == 2) {
				winner = 2;
				break;
			}
			break;
		}
		if(winner) {
			if(winner == 1) {
				f[f1].add_text("X", 1, 0, 3, 1);
				f[f2].add_text("X", 1, 0, 3, 1);
				f[f3].add_text("X", 1, 0, 3, 1);
				f[11].add_text("PLAYER 1 HAS WON!", 0, 1, 27, 0);
			}
			else if(winner == 2) {
				f[f1].add_text("O", 1, 0, 3, 1);
				f[f2].add_text("O", 1, 0, 3, 1);
				f[f3].add_text("O", 1, 0, 3, 1);
				f[11].add_text("PLAYER 2 HAS WON!", 0, 1, 27, 0);
			}
			draw(6);
			ex = true;
			int lel;
			bool kkk = false;
			while(!kkk) {
				lel = getch();
				if(lel == '\n' || lel == ' ' || lel == KEY_F(2))
					kkk = true;
			}
			for(int i=0; i<c.n; i++)
				f[i].zero();
			MainMenu();
		}
	}
}

void draw(int o = 6) { //Функция для вырисовывания экрана с выбранным цветом
	Graphics::background(o); //Вырисовывание фона
	for(int i=0; i<c.n; i++) //Цикл для вырисовывания каждой фигуры
		f[i].redraw(); //Метод для вырисовывания фигуры
}

int MainMenu() { //Метод для реализации меню
	ccolor(0, 0); //Установка черного цвета
	f[0].cube(c.x, 3); //Создание формы фигуры
	f[0].add_text("MAIN MENU ||   F2 - TO EXIT", 0, 1, f[0].xmax - 13, 0); //Добавления текста для фигуры 
	ccolor(0, 3); //Установка желтого цвета
	f[1].cube(10, 1); //Создание формы фигуры
	f[1].moving(3, 6); //Перемещение фигуры
	f[2].cube(10, 1); //Создание формы фигуры
	f[2].moving(3, 8); //Перемещение фигуры
	f[4].cube(10, 1); //Создание формы фигуры 
	f[4].moving(34, 17); //Перемещение фигуры
	f[1].add_text("Player VS Player", 3, 0); //Добавление текста
	f[2].add_text("Player VS AI", 3, 0); //Добавление текста
	f[4].add_text("|| RULES ||\n\n      In this game you should mark cubes in one lane by X or O for get win \
	\n      Ncмаилов, gpyппа KC-331 (c)\n\n\t\t\t\t      2016", 1, 0); //Добавление текста 
	draw(0); //Вырисовка экрана с черным фоном
	int bools = 1; //Переменная для определения выбранного пункта меню 
	keypad(stdscr, true); //Включение режима считывания дополнительных клавиш
	bool ex = false; //Переменная для выхода из while() 
	halfdelay(1); //Установка времени задержки 
	while(!ex) { //Цикл для считывания клавиш 
		int ch = getch(); //Считывание клавиши
		if(ch == '\n' || ch == ' ') //Считывание клавиши ENTER или пробел 
			ex = true; //Переменная для выхода из цикла
		for(int i=1; i<3; i++)  //Цикл для перерисовывания текста на фигуре 
			f[i].trecolor(3, 0); //Устанавливаем желтый текст
		f[bools].trecolor(0, 3); //Устанавливаем черный текст на желтом фоне
		draw(0); //Вырисовывание экрана с черным фоном
		if(ch == KEY_F(2)) { //Считывание клавиши "F2" для выхода
			return 0; //Выход из программы
		}
		if(ch == KEY_UP) //Считывание клавиши "стрелочка вверх"
			if(bools > 1)
				bools--; //Перемещение на пункт выше
		if(ch == KEY_DOWN)//Считывание клавиши "стрелочка вниз"
			if(bools < 2)
				bools++; //Перемещение на пункт ниже
	}
	if(bools == 1) { //Если выбран первый пункт
		ex = true; //Выход из цикла
		toe.PvP(); //Вызов метода битвы между игроками
	}
	else if(bools == 2) { //Если выбран второй пункт
		ex = true; //Выход из цикла
		toe.level = 1; //Установка уровни сложности ИИ
		toe.PvE(); //Вызов метода для битвы между игроком компьютером
	}
}                                                                                                                                            

int main() {
	srand(time(0)); //Случайные числа
	Graphics g; //Создание объекта класса Graphics
	noecho(); //Убрать вывод с клавиатуры на экран
	c.n = 15; //Устанавливаем максимальное кол-во объектов (фигур) используя класс Window 
	getmaxyx(stdscr, c.y, c.x); //Получаем координаты окна и сохраняет их в поля класса Window
	ccolor(0, 1); //Инициализируем систему управления цветов класса ColorController
	f = new Figures [c.n]; //Выделяем память под заранее созданный объект для фигур класса Figures 
	MainMenu(); //Вызываем метод реализации главного меню
}
