//Класс для хранения условий и методов для, название расшифровывается,
//как tic-tac-toe (Крестики-Нолики, на английском)

class ttt {
public:
	int f1; //Свойство для условий 1
	int f2; //Свойство для условий 1
	int f3; //Свойство для условий 1
	int winner = 0; //Свойство для определения победителя
	int level = 0; //Свойство для определения силы компьютера
	void full(); 
	void PvP();
	void PvE();
}toe;