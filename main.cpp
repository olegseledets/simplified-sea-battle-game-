#include <iostream>

const unsigned int FIELDSIZE = 10;

bool fillDeck(int start, int end, int position, char flag, bool field[FIELDSIZE][FIELDSIZE]){
  if (flag == 'v') {
    for ( ; start <= end; ++start) {
      if (field[start][position] == true) {
        std::cout << "\nТут уже находится корабль\n";
        return false;
      }
      field[start][position] = true;
    }
  } else {
    for ( ; start <= end; ++start) {
      if (field[position][start] == true) {
        std::cout << "\nТут уже находится корабль\n";
        return false;
      }
      field[position][start] = true;
    }
  }
  return true;
}

// Заполнить многопалубники
bool checkLineDeck(int x_s, int y_s, int x_e, int y_e, bool field[FIELDSIZE][FIELDSIZE], int maxSize){
  if (x_s == x_e) { //вертикальные
    if (y_s > y_e)
      std::swap(y_s, y_e); 
    return ((y_e - y_s) == (maxSize - 1)) ? fillDeck(y_s, y_e, x_s, 'v', field) : false;
  } else { //горизонтальные
    if (x_s > x_e)
      std::swap(x_s, x_e); 
    return ((x_e - x_s) == (maxSize - 1)) ? fillDeck(x_s, x_e, y_s, 'h', field) : false;
  }
  return false;
}

void showField(bool field[FIELDSIZE][FIELDSIZE]) {
  for (int i = 0 ; i < FIELDSIZE; ++i) {
    for (int j = 0; j < FIELDSIZE; ++j) {
      std::cout << (field[i][j] ? "■\t" : ".\t");
    }
    std::cout << std::endl;
  }
}

bool checkCorrectLine(int x_s, int y_s, int x_e, int y_e) {
  return (x_s == x_e || y_s == y_e);
}

bool checkCorrectCoordOne(int x, int y) {
  return ((x >= 0 || x <= 9) || (y >= 0 || y <= 9));
}

bool checkCorrectCoordLot(int x_s, int y_s, int x_e, int y_e, bool field[FIELDSIZE][FIELDSIZE], int maxSize) {
  if (!checkCorrectCoordOne(x_s, y_s) || !checkCorrectCoordOne(x_e, y_e)) { 
    std::cout << "Не верные координаты!\n";
    return false;
  } else if (x_s == x_e && y_s == y_e) {  // для НЕ однопалубных координаты не могут совпасть
    std::cout << "Координаты совпали!\n";
    return false;
  } else if (!checkCorrectLine(x_s, y_s, x_e, y_e) || !checkLineDeck(x_s, y_s, x_e, y_e, field, maxSize)) {
    std::cout << "Не верные координаты!\n";
    return false;
  }
  return true;
}

int inputCoord(std::string text) {
  int coord;
  std::cout << text;
  std::cin >> coord;
  return coord;
}

void arrangeShips(int ship, std::string nameShip, int LineSize, bool field[FIELDSIZE][FIELDSIZE]){
  int coordX_start, coordY_start, coordX_end, coordY_end;
  for ( ; ship > 0 ; --ship) {
    std::cout << "Размещение "+nameShip+", осталось: " << ship << std::endl;
    do {
      std::cout << "-------------\n";
      coordX_start = inputCoord("X start: ");
      coordY_start = inputCoord("Y start: ");
      coordX_end = inputCoord("X end: ");
      coordY_end = inputCoord("Y end: ");
    }
    while (!checkCorrectCoordLot(coordX_start, coordY_start, coordX_end, coordY_end, field, LineSize));
    showField(field);
  }
}

void fillingField(bool field[FIELDSIZE][FIELDSIZE]) {
  int coordX_start = 0, coordY_start = 0;
  int coordX_end = 0, coordY_end = 0;
  int singleDeck = 4, doubleDeck = 3, threeDeck = 2, fourDeck = 1; 

  for ( ; singleDeck > 0 ; --singleDeck) {
    std::cout << "Размещение однопалубных, осталось: " << singleDeck << std::endl;
    do {
      coordX_start = inputCoord("X: ");
      coordY_start = inputCoord("Y: ");
    }
    while (checkCorrectCoordOne(coordX_start, coordY_start) && field[coordY_start][coordX_start]);
    field[coordY_start][coordX_start] = true;
    showField(field);
  }
  arrangeShips(doubleDeck, "двухпалубных", 2, field);
  arrangeShips(threeDeck, "трехпалубных", 3, field);
  arrangeShips(fourDeck, "четырехпалубных", 4, field);
}

int playerAttack(bool field[FIELDSIZE][FIELDSIZE], char emptyField[FIELDSIZE][FIELDSIZE]){
  int x = 0, y = 0;
  x = inputCoord("X: ");
  y = inputCoord("Y: ");
  if (field[y][x]){
    std::cout << "baBoom!!!\n";
    field[y][x] = false;
    emptyField[y][x] = 'X';
    return 1;
  } else {
    std::cout << "Wisk :(\n";
    if (emptyField[y][x] == '.' || emptyField[y][x] == 'O'){
      emptyField[y][x] = 'O';
    }
    return 0;
  }
}

void showEmptyField(char emptyField[FIELDSIZE][FIELDSIZE]) {
  for(int i = 0 ; i < FIELDSIZE; ++i) {
    for (int j = 0 ; j < FIELDSIZE ; ++j) {
      std::cout << emptyField[i][j] << '\t';
    }
    std::cout << std::endl;
  }
}

void fillEmptyField(char emptyField[FIELDSIZE][FIELDSIZE]) {
  for(int i = 0 ; i < FIELDSIZE; ++i) 
    for (int j = 0 ; j < FIELDSIZE ; ++j) 
      emptyField[i][j] = '.';
}

int battle(bool yourField[FIELDSIZE][FIELDSIZE], bool opponentField[FIELDSIZE][FIELDSIZE]) {
  int countShipFirst = 4, countShipSecond = 4;
  char emptyYourField[FIELDSIZE][FIELDSIZE] = {' '};
  fillEmptyField(emptyYourField);
  char emptyOpponentsField[FIELDSIZE][FIELDSIZE] = {' '};
  fillEmptyField(emptyOpponentsField);
  while(true) {
    std::cout << "countShipFirst = " << countShipFirst << "\tcountShipSecond = " << countShipSecond << std::endl;
    std::cout << "\n-------------\nХод игрока 1\n";
    countShipSecond = countShipSecond - playerAttack(opponentField, emptyOpponentsField);
    std::cout << "\n Корабли игрока 1\n";
    showField(yourField);
    std::cout << "\n Поле игрока 2\n";
    showEmptyField(emptyOpponentsField);
    if (countShipSecond == 0)
      return 1;
    std::cout << "\n-------------\nХод игрока 2\n";
    countShipFirst = countShipFirst - playerAttack(yourField, emptyYourField);
    std::cout << "\n Корабли игрока 2\n";
    showField(opponentField);
    std::cout << "\n Поле игрока 1\n";
    showEmptyField(emptyYourField);
    if (countShipFirst == 0)
      return 2;
  }
}

int main() {
  bool yourPlayingField[FIELDSIZE][FIELDSIZE] = {false};
  bool opponentsPlayingField[FIELDSIZE][FIELDSIZE] = {false}; 
  std::cout << "\nИгрок 1 размещает корабли\n";
  fillingField(yourPlayingField);
  std::cout << "\nИгрок 2 размещает корабли\n";
  fillingField(opponentsPlayingField);
  int winPlayer = battle(yourPlayingField, opponentsPlayingField);
  std::cout << "\n\nПобедил игрок " << winPlayer << "!!!\n"; 
}

/*
Требуется реализовать упрощённую игру в Морской бой. Игровое поле размером 10 на 10 клеток. Участвует двое игроков. В арсенале каждого из них: 4 маленьких кораблика размером в одну клетку, 3 небольших корабля размером в две клетки, 2 средних корабля размером в три клетки и один большой корабль размером в четыре клетки. Для простоты, клетки поля пронумерованы по вертикали от 0 до 9, и по горизонтали также от 0 до 9. Мы не будем использовать классические наименования клеток, такие как B4, C6, а просто два индекса. Вначале игроки по очереди расставляют корабли, начиная с самых маленьких и заканчивая большими. Маленькие корабли в одну клетку расставляются с помощью указания лишь одной клетки-точки на поле, к примеру 2,1. Корабли размерностью от двух клеток и выше, расставляются с помощью координат их начала и конца, к примеру: 0,1 - 0,3. Корабли могут быть установлены только строго вертикально, или горизонтально. Установка корабля по диагонали — недопустимо, в случае которого об этом тоже надо сообщить пользователю. Если корабль не может быть размещён на заданных клетках из-за того, что он столкнётся с другим кораблём (окажется на его клетках) или выйдет за пределы поля вообще, то игроку должно быть сделано предупреждение, после которого он должен переставить корабль на новые валидные координаты. Замечу, в нашем упрощённом варианте игры, мы не будем обсчитывать соприкосновения кораблей друг с другом, а потому корабли вполне можно будет размещать друг к другу вплотную — борт к борту. После того как все корабли были расставлены начинается игра. Игроки по очереди атакуют друг друга, называя координаты выстрела. После выстрела, в консоль выводится информация о его результате: попал или мимо. Если выстрел успешен, клетка, на которой был корабль (или его фрагмент) затирается и становится пустой. Игра заканчивается тогда, когда все корабли одной из сторон будут полностью уничтожены. Как только это произойдёт в консоль выводится информация с номером игрока, который победил.
*/