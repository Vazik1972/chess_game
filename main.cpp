#include <iostream>
#include <string>
#include <Windows.h>

//пук


int call(std::string name);

class chessboard;

class piece;

class chessboard {
public:
//вывод доски с фигурами в консоль
    void render_view() {
        for (short i = 7; i > -1; --i) {
            std::cout << i + 1 << "  ";
            for (short j = 0; j < 8; ++j) {
                std::cout << matrix[j][i][0] << matrix[j][i][2] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "  ";
        for (int i = 0; i < 8; ++i) {
            std::cout << " " << char(i + 65) << " ";
        }
        std::cout << "\n";
    }

    void render_predict() {
        for (short i = 7; i > -1; --i) {
            std::cout << i + 1 << "  ";
            for (short j = 0; j < 8; ++j) {
                std::cout << matrix[j][i] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "  ";
        for (int i = 0; i < 8; ++i) {
            std::cout << "  " << char(i + 65) << " ";
        }
        std::cout << "\n";
    }

//vec - обозначение фигур на доске или их отсутствие
    void Set(std::string vec, int i, int j){
        matrix[i][j] = vec;
    }

    std::string Get(int i, int j){
        return matrix[i][j];
    }
private:
    std::string matrix[8][8];
};


class piece
{
public:
    void killer(short to_let, short to_num, chessboard *chessboard1, piece array[33]) {
        int second_piece = call(chessboard1->Get(to_let, to_num));
        array[second_piece].kill();
    }

    void mover(short from_let, short from_num, short to_let, short to_num, int *PlayerSelector, chessboard *chessboard1, piece array[33]){
        int first_piece = call(chessboard1->Get(from_let, from_num));
        array[first_piece].set(to_let, to_num);
        this->moveCheck = true;
        *PlayerSelector *= -1;
        if(((int(name[0]) - 48) == 1) and (abs(from_num - to_num) == 2)){
            array[32].revive(to_let, to_num - *PlayerSelector, array[call(chessboard1->Get(from_let, from_num))].name);
        }else array[32].kill();
    }


    //используется для определения клеток chessboard на которые фигура может сходить
    //на вход подаются координаты хода, на выходе выдается булево значение(может\не может)

    bool steps_permission(int from_let, int from_num, int to_let, int to_num, int PlayerSelector, chessboard *chessboard1, piece array[33]){
        int switch_piece = int(name[0]) - 48;
        bool switcher = false;
        switch (switch_piece) {
            case 1: {
                if (((to_num - from_num) == PlayerSelector * -1) and (abs(to_let - from_let) == 1)) {
                    if (chessboard1->Get(to_let, to_num)[1] != '_') {
                        int first_piece = call(chessboard1->Get(from_let, from_num));
                        int second_piece = call(chessboard1->Get(to_let, to_num));
                        if (array[first_piece].color != array[second_piece].color) {
                            switcher = true;
                        }
                    }
                } else {
                    if (moveCheck) {
                        if ((from_let == to_let) and (from_num - PlayerSelector == to_num)) {
                            if (chessboard1->Get(to_let, to_num)[1] == '_') {
                                switcher = true;
                            }
                        }
                    } else {
                        if ((from_let == to_let) and
                            ((from_num - PlayerSelector == to_num) or (from_num - 2 * PlayerSelector == to_num))) {
                            if (chessboard1->Get(to_let, to_num)[1] == '_') {
                                if (to_num - from_num == -2 * PlayerSelector)
                                {
                                    if (chessboard1->Get(to_let, to_num + PlayerSelector)[1] == '_') {
                                        switcher = true;
                                    }
                                } else {
                                    switcher = true;
                                }
                            }
                        }
                    }
                }


                break;
            }
            case 4: {

                break;
            }
            case 5: {

                break;
            }
            case 6: {

                break;
            }

            default: {
                switcher = true;
                break;
            }
        }
        return switcher;
    }

    bool get_color(){
        return this->color;
    }

    void get(std::string *name){
        *name = this->name;
    }

    void get(int *posLet, int *posNum){
        *posLet = this->posLet;
        *posNum = this->posNum;
    }

    bool get_death(){
        return this->death;
    }

    void kill(){
        this->death = true;
    }

    void revive(short posLet, short posNum, std::string name){
        this->posLet = posLet;
        this->posNum = posNum;
        this->name = name;
        this->death = false;
    }

    void set(std::string name){
        this->name = name;
    }

    void set(short posLet, short posNum, std::string name, bool moveCheck, bool color){
        this->posLet = posLet;
        this->posNum = posNum;
        this->name = name;
        this->moveCheck = moveCheck;
        this->color = color;
        this->death = false;
    }

    void set(short posLet, short posNum){
        this->posLet = posLet;
        this->posNum = posNum;
    }


private:
    bool color, moveCheck, death;
    short posLet, posNum;
    std::string name;
};

/*
 1st number:      2nd number:     3rd number:
 * 1 - pawn         0 - black       number of a piece
 * 2 - bishop       1 - white
 * 3 - knight
 * 4 - castle
 * 5 - queen
 * 6 - king
*/

class PlayerWhite {

};

class PlayerBlack {

};


bool check_danger(int from_let, int from_num, int PlayerSelector, chessboard *chessboard1, piece array[]) {
    bool danger = false;
    if ((from_let + 1 > -1) and (from_num + 1 < 8) and (from_num - 1 > -1)) {
        bool fircolor;
        int piece_type;
        fircolor = PlayerSelector == -1;
        int to_num = from_num - PlayerSelector;
        int to_let = from_let;
        if (((chessboard1->Get(to_num,to_let - 1)[1] != '_') or (chessboard1->Get(to_num,to_let + 1)[1] != '_')) and
            ((int(chessboard1->Get(to_num,to_let - 1)[1]) - 48 != fircolor) or
             (int(chessboard1->Get(to_num,to_let + 1)[1]) - 48 != fircolor))) {
            if ((int(chessboard1->Get(to_num,to_let - 1)[0]) - 48 == 1) or
                ((int(chessboard1->Get(to_num,to_let + 1)[0]) - 48 == 1))) {
                danger = true;
            } else {
                for (int i = 15; i < 32; ++i) {
                    std::string name;
                    array[i].get(&name);
                    if ((array[i].get_color() != fircolor)) {
                        int num, let;
                        array[i].get(&let, &num);
                        danger = array[i].steps_permission(let, num, from_let, from_num, PlayerSelector, chessboard1,
                                                          array);
                    }
                }
            }

        } else {
            for (int i = 15; i < 32; ++i) {
                std::string name;
                array[i].get(&name);
                if ((array[i].get_color() != fircolor)) {
                    int num, let;
                    array[i].get(&let, &num);
                    danger = array[i].steps_permission(let, num, from_let, from_num, PlayerSelector, chessboard1,
                                                      array);
                }
            }
        }
    }
}

//заполнение фигур
void fill(piece array[], int i, short posLet, short posNum, std::string Name){
    bool color = int(Name[1]) - 48;
    array[i].set(posLet, posNum, Name, false, color);
}

//на вход получаем имя фигуры, на выход - номер в массиве
int call(std::string name){
    bool color = name[1] - 48;
    int piece_ord = name[2] - 48;
    int piece_number = -1;
    int switch_piece = name[0] - 48;
    switch (switch_piece) {
        case 1:{
            piece_number = color * 8 + piece_ord - 1;
            break;
        }
        case 2: {
            piece_number = 15 + color * 2 + piece_ord;
            break;
        }
        case 3: {
            piece_number = 19 + color * 2 + piece_ord;
            break;
        }
        case 4: {
            piece_number = 23 + color * 2 + piece_ord;
            break;
        }
        case 5: {
            piece_number = 27 + color + piece_ord;
            break;
        }

        case 6: {
            piece_number = 29 + color + piece_ord;
            break;
        }
        default:{
            break;
        }
    }
    return piece_number;
}


void fill_cell(short from_let, short from_num, int PlayerSelector, chessboard *chessboard1, chessboard *chessboard3, piece array[33], int to_let, int to_num, bool switcher){
    if (array[call(chessboard1->Get(from_let,from_num))].steps_permission(from_let,from_num,to_let,to_num, PlayerSelector,chessboard1,array)){
        std::string name = chessboard3->Get(to_let,to_num);
        name[1] = (switcher?'$':'X');
        chessboard3->Set(name,to_let,to_num);
    }
}

//рендер возможных ходов
void steps_prediction(short from_let, short from_num, int PlayerSelector, chessboard *chessboard1, chessboard *chessboard3, piece array[33]){
    int switch_piece = int(chessboard1->Get(from_let,from_num)[0]) - 48;
    switch (switch_piece) {
        case 1: {
            //на 1 вперёд
            int to_let = from_let;
            int to_num = from_num + (-1 * PlayerSelector);

            fill_cell(from_let, from_num, PlayerSelector, chessboard1, chessboard3, array, to_let,
                           to_num,true);

            //на 2 вперёд
            to_let = from_let;
            to_num = from_num + (-2 * PlayerSelector);
            fill_cell(from_let, from_num, PlayerSelector, chessboard1, chessboard3, array, to_let,
                           to_num, true);

            //диагональ вправо на 1
            to_let = from_let + 1;
            to_num = from_num + (-1 * PlayerSelector);
            fill_cell(from_let, from_num, PlayerSelector, chessboard1,  chessboard3, array, to_let,
                           to_num, false);

            //диагональ влево на 1
            to_let = from_let - 1;
            to_num = from_num + (-1 * PlayerSelector);
            fill_cell(from_let, from_num, PlayerSelector, chessboard1, chessboard3, array, to_let,
                           to_num, false);

            break;
        }
        //нужно исправить "ghost"а
        case 2: {
            bool barrier = false;
            int to_let = from_let;
            int to_num = from_num;
            while (!barrier){
                to_let++;
                to_num++;
                if ((to_let < 8) and (to_num < 8)){
                    if(chessboard1->Get(to_let,to_num) != "___"){
                        if ((int(chessboard1->Get(to_let,to_num)[1])-48 == -1 * PlayerSelector)
                            or (PlayerSelector > int(chessboard1->Get(to_let,to_num)[1])-48)) {
                            barrier = true;
                        }else{
                            fill_cell(from_let, from_num, PlayerSelector, chessboard1,  chessboard3, array, to_let,
                                      to_num, false);
                            barrier = true;
                        }
                    }else{
                        fill_cell(from_let, from_num, PlayerSelector, chessboard1,  chessboard3, array, to_let,
                                  to_num, true);
                    }
                }else barrier = true;

            }

            barrier = false;
            to_let = from_let;
            to_num = from_num;
            while (!barrier){
                to_let--;
                to_num++;
                if ((to_let > -1) and (to_num < 8)){
                    if(chessboard1->Get(to_let,to_num) != "___"){
                        if ((int(chessboard1->Get(to_let,to_num)[1])-48 == -1 * PlayerSelector)
                            or (PlayerSelector > int(chessboard1->Get(to_let,to_num)[1])-48)) {
                            barrier = true;
                        }else{
                            fill_cell(from_let, from_num, PlayerSelector, chessboard1,  chessboard3, array, to_let,
                                      to_num, false);
                            barrier = true;
                        }
                    }else{
                        fill_cell(from_let, from_num, PlayerSelector, chessboard1,  chessboard3, array, to_let,
                                  to_num, true);
                    }
                }else barrier = true;

            }
            barrier = false;
            to_let = from_let;
            to_num = from_num;
            while (!barrier){
                to_let++;
                to_num--;
                if ((to_let < 8) and (to_num > -1)){
                    if(chessboard1->Get(to_let,to_num) != "___"){
                        if ((int(chessboard1->Get(to_let,to_num)[1])-48 == -1 * PlayerSelector)
                            or (PlayerSelector > int(chessboard1->Get(to_let,to_num)[1])-48)) {
                            barrier = true;
                        }else{
                            fill_cell(from_let, from_num, PlayerSelector, chessboard1,  chessboard3, array, to_let,
                                      to_num, false);
                            barrier = true;
                        }
                    }else{
                        fill_cell(from_let, from_num, PlayerSelector, chessboard1,  chessboard3, array, to_let,
                                  to_num, true);
                    }
                }else barrier = true;

            }
            barrier = false;
            to_let = from_let;
            to_num = from_num;
            while (!barrier){
                to_let--;
                to_num--;
                if ((to_let > -1) and (to_num > -1)){
                    if(chessboard1->Get(to_let,to_num) != "___"){
                        if ((int(chessboard1->Get(to_let,to_num)[1])-48 == -1 * PlayerSelector)
                            or (PlayerSelector > int(chessboard1->Get(to_let,to_num)[1])-48)) {
                            barrier = true;
                        }else{
                            fill_cell(from_let, from_num, PlayerSelector, chessboard1,  chessboard3, array, to_let,
                                      to_num, false);
                            barrier = true;
                        }
                    }else{
                        fill_cell(from_let, from_num, PlayerSelector, chessboard1,  chessboard3, array, to_let,
                                  to_num, true);
                    }
                }else barrier = true;

            }
            break;
        }
        case 3: {

            break;
        }
        case 4: {

            break;
        }
        case 5: {

            break;
        }
        case 6: {

            break;
        }

        default: {
            break;
        }
    }
}

int main(){
    SetConsoleOutputCP(CP_UTF8);
    piece array[33];
    {
        //пешечки-пушечки
        fill(array, 0, 0, 6, "101");
        fill(array, 1, 1, 6, "102");
        fill(array, 2, 2, 6, "103");
        fill(array, 3, 3, 6, "104");

        fill(array, 4, 4, 6, "105");
        fill(array, 5, 5, 6, "106");
        fill(array, 6, 6, 6, "107");
        fill(array, 7, 7, 6, "108");

        fill(array, 8, 0, 1, "111");
        fill(array, 9, 1, 1, "112");
        fill(array, 10, 2, 1, "113");
        fill(array, 11, 3, 1, "114");

        fill(array, 12, 4, 1, "115");
        fill(array, 13, 5, 1, "116");
        fill(array, 14, 6, 1, "117");
        fill(array, 15, 7, 1, "118");

        //слоники
        fill(array, 16, 2, 7, "201");
        fill(array, 17, 5, 7, "202");
        fill(array, 18, 2, 0, "211");
        fill(array, 19, 5, 0, "212");

        //коники
        fill(array, 20, 1, 7, "301");
        fill(array, 21, 6, 7, "302");
        fill(array, 22, 1, 0, "311");
        fill(array, 23, 6, 0, "312");

        //кастлы
        fill(array, 24, 0, 7, "401");
        fill(array, 25, 7, 7, "402");
        fill(array, 26, 0, 0, "411");
        fill(array, 27, 7, 0, "412");

        //знать
        fill(array, 28, 3, 7, "501");
        fill(array, 29, 3, 0, "511");
        fill(array, 30, 4, 7, "601");
        fill(array, 31, 4, 0, "611");

        //гост
        fill(array, 32, 0, 0, "uwu");
        array[32].kill();
    }

    chessboard chessboard1; //подложная
    chessboard chessboard3; //предсказательная

    std::string from_pos, to_pos;
    int PlayerSelector = -1; //переменная вокруг которой построенно определение кто сейчас ходит
    short from_let, from_num, to_let, to_num;

    while(from_pos != "-1"){

        //заполнение подложной матрицы
        for (short i = 0; i < 8; ++i) {
            for (short j = 0; j < 8; ++j) {
                chessboard1.Set("___",i,j);
            }
        }

        //заполнение предсказательной матрицы
        for (short i = 0; i < 8; ++i) {
            for (short j = 0; j < 8; ++j) {
                chessboard3.Set("___",i,j);
            }
        }

        //размещение фигур
        for (short i = 0; i < 33; ++i) {
            int posLet, posNum;
            bool color;
            std::string name;
            color = array[i].get_color();
            array[i].get(&posLet, &posNum);
            array[i].get(&name);
            if (array[i].get_death() == 0){
                int switch_piece = int(name[0]) - 48;
                std::string piece_color;
                if (color){
                    piece_color = "w";
                }else{
                    piece_color = "b";
                }
                chessboard1.Set(name,posLet, posNum);
                //избавляемся от chessdoard2
                switch (switch_piece) {
                    case 1:{
                        if (i!=32){
                            chessboard3.Set(piece_color + "_P",posLet, posNum);
                        }
                        break;
                    }
                    case 2:{
                        chessboard3.Set(piece_color + "_B",posLet, posNum);
                        break;
                    }
                    case 3:{
                        chessboard3.Set(piece_color + "_N",posLet, posNum);
                        break;
                    }
                    case 4:{
                        chessboard3.Set(piece_color + "_C",posLet, posNum);
                        break;
                    }
                    case 5:{
                        chessboard3.Set(piece_color + "_Q",posLet, posNum);
                        break;
                    }
                    case 6:{
                        chessboard3.Set(piece_color + "_K",posLet, posNum);
                        break;
                    }

                    default:{
                        chessboard3.Set(name,posLet, posNum);
                        break;
                    }
                }
            }
        }

        std::cout << (PlayerSelector == -1 ? "Ход Белых\n" : "Ход Чёрных\n");

        //chessboard1.render_predict();
        chessboard3.render_view();
        int first_piece, second_piece;
        //чтение и перевод координат
        int l = 0;
        std::cin >> from_pos;
        do{

            //перезаполнение предсказательной матрицы
            for (short i = 0; i < 8; ++i) {
                for (short j = 0; j < 8; ++j) {
                    chessboard3.Set("___",i,j);
                }
            }

            //переразмещение фигур на предсказательной матрице
            for (short i = 0; i < 33; ++i) {
                int posLet, posNum;
                bool color;
                std::string name;
                color = array[i].get_color();
                array[i].get(&posLet, &posNum);
                array[i].get(&name);
                if (array[i].get_death() == 0){
                    if(i != 32) {
                        int switch_piece = int(name[0]) - 48;
                        std::string piece_color;
                        if (color) {
                            piece_color = "w";
                        } else {
                            piece_color = "b";
                        }
                        switch (switch_piece) {
                            case 1: {
                                chessboard3.Set(piece_color + "_P", posLet, posNum);
                                break;
                            }
                            case 2: {
                                chessboard3.Set(piece_color + "_B", posLet, posNum);
                                break;
                            }
                            case 3: {
                                chessboard3.Set(piece_color + "_N", posLet, posNum);
                                break;
                            }
                            case 4: {
                                chessboard3.Set(piece_color + "_C", posLet, posNum);
                                break;
                            }
                            case 5: {
                                chessboard3.Set(piece_color + "_Q", posLet, posNum);
                                break;
                            }
                            case 6: {
                                chessboard3.Set(piece_color + "_K", posLet, posNum);
                                break;
                            }

                            default: {
                                break;
                            }
                        }
                    }
                }
            }

            from_let = from_pos[0] - 65;
            from_num = from_pos[1] - 49;
            if (from_let > 8) from_let -= 32;
            if (chessboard1.Get(from_let,from_num)[1] != '_'){
                bool FirstPieceColor = array[call(chessboard1.Get(from_let,from_num))].get_color();
                if((int(FirstPieceColor) == -1 * PlayerSelector) or (PlayerSelector > int(FirstPieceColor))) {
                    steps_prediction(from_let, from_num, PlayerSelector, &chessboard1, &chessboard3, array);
                    //глянуть после удаления chessboard2
                    chessboard3.render_predict();


                    std::cin >> to_pos;
                    to_let = to_pos[0] - 65;
                    to_num = to_pos[1] - 49;
                    if (to_let > 8)
                        to_let -= 32;
                    first_piece = call(chessboard1.Get(from_let,from_num));


                    if ((-1 < from_let < 8) and (-1 < from_num < 8) and (-1 < to_let < 8) and (-1 < to_num < 8)) {
                        if (chessboard3.Get(to_let, to_num)[1] != '_') {

                            if (chessboard3.Get(to_let, to_num)[1] == 'X') {
                                array[second_piece].killer(to_let, to_num, &chessboard1, array);
                                array[first_piece].mover(from_let, from_num, to_let, to_num, &PlayerSelector,
                                                           &chessboard1, array);
                                l = 1;
                            } else{
                                array[first_piece].mover(from_let, from_num, to_let, to_num, &PlayerSelector,
                                                         &chessboard1, array);
                                l = 1;
                            }
                        } else {
                            bool first_color = array[call(chessboard1.Get(from_let, from_num))].get_color();
                            if(int(chessboard1.Get(to_let, to_num)[1])-48 == first_color) {
                                from_pos = to_pos;
                            }else std::cout << "Попробуйте другой ход\n";
                        }
                    } else std::cout << "Выход за границы доски";

                }else{
                    std::cout << "Куда вне очереди\n";
                    l = 1;
                }
            }else{
                std::cout << "Выберите фигуру\n";\
                l = 1;
            }

        }while ( l != 1);

    }
    return 0;
}