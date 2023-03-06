#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <ctime>


//пук хрюк

short call(std::string name);

class chessboard;

class piece;
void clean_matrix(chessboard *chessboard);
void steps_prediction(short from_let, short from_num, short PlayerSelector, chessboard *chessboard1, chessboard *chessboard2, chessboard *chessboard3, piece array[33], bool king_flag, short switch_piece, bool tracing);
void fill_matrix_piece(chessboard *chessboard1, chessboard *chessboard2, chessboard *chessboard3, piece array[], bool flag, bool flag1, bool flag2);
bool check_danger(std::string name, short from_let, short from_num, short PlayerSelector, chessboard *chessboard1, chessboard *chessboard2, chessboard *chessboard3, piece array[]);
class chessboard {
public:
/**вывод доски с фигурами в консоль*/
    void render_view() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        for (short i = 7; i > -1; --i) {
            SetConsoleTextAttribute(hConsole, 14);
            std::cout << i + 1 << "  ";
            for (short j = 0; j < 8; ++j) {
                if (matrix[j][i][0] == 'b') {
                    SetConsoleTextAttribute(hConsole, 1);
                }else {
                    SetConsoleTextAttribute(hConsole, 7);
                }
                std::cout << matrix[j][i][2] << "  ";
            }
            std::cout << "\n";
        }
        std::cout << "  ";
        for (int i = 0; i < 8; ++i) {
            SetConsoleTextAttribute(hConsole, 14);
            std::cout << " " << char(i + 65) << " ";
        }
        std::cout << "\n";
    }

    void render_predict() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        for (short i = 7; i > -1; --i) {
            SetConsoleTextAttribute(hConsole, 14);
            std::cout << i + 1 << "  ";
            for (short j = 0; j < 8; ++j) {
                if (matrix[j][i][0] == 'b') {
                    SetConsoleTextAttribute(hConsole, 1);
                }else {
                    SetConsoleTextAttribute(hConsole, 15);
                }
                if (matrix[j][i][1] == '$'){
                    SetConsoleTextAttribute(hConsole, 10);
                }else if (matrix[j][i][1] == 'X'){
                    SetConsoleTextAttribute(hConsole, 4);
                }
                std::cout << matrix[j][i][2] << "  ";
            }
            std::cout << "\n";
        }
        std::cout << "  ";
        for (int i = 0; i < 8; ++i) {
            SetConsoleTextAttribute(hConsole, 14);
            std::cout << " " << char(i + 65) << " ";
        }
        std::cout << "\n";
    }

/**vec - обозначение фигур на доске или их отсутствие*/
    void Set(std::string vec, short i, short j){
        matrix[i][j] = vec;
    }

    std::string Get(short i, short j){
        return matrix[i][j];
    }
private:
    std::string matrix[8][8];
};


class piece {
public:
    static void killer(short to_let, short to_num, chessboard *chessboard1, piece array[33]) {
        short second_piece = call(chessboard1->Get(to_let, to_num));
        array[second_piece].kill();
    }

    void mover(short from_let, short from_num, short to_let, short to_num, short *PlayerSelector, chessboard *chessboard1,
               piece array[33]) {
        short first_piece = call(chessboard1->Get(from_let, from_num));
        array[first_piece].set(to_let, to_num);
        this->moveCheck = true;
        *PlayerSelector *= -1;
        if (((short(name[0]) - 48) == 1) and (abs(from_num - to_num) == 2)) {
            array[32].revive(to_let, to_num - *PlayerSelector, array[call(chessboard1->Get(from_let, from_num))].name);
        } else array[32].kill();
    }

    bool get_move(){
        return this->moveCheck;
    }

    bool get_color() {
        return this->color;
    }

    void get(std::string *name) {
        *name = this->name;
    }

    void get(short *posLet, short *posNum) {
        *posLet = this->posLet;
        *posNum = this->posNum;
    }

    bool get_death() {
        return this->death;
    }

    bool get_pin() {
        return this->is_pinned;
    }

    void kill() {
        this->death = true;
    }

    void revive() {
        this->death = false;
    }

    void revive(short posLet, short posNum, std::string name) {
        this->posLet = posLet;
        this->posNum = posNum;
        this->name = name;
        this->death = false;
    }

    void set(std::string name) {
        this->name = name;
    }
    void set(short posLet, short posNum, std::string name, bool moveCheck, bool color, bool death, bool is_pinned) {
        this->posLet = posLet;
        this->posNum = posNum;
        this->name = name;
        this->moveCheck = moveCheck;
        this->color = color;
        this->death = death;
        this->is_pinned = is_pinned;
    }

    void set(short posLet, short posNum, std::string name, bool moveCheck, bool color) {
        this->posLet = posLet;
        this->posNum = posNum;
        this->name = name;
        this->moveCheck = moveCheck;
        this->color = color;
        this->death = false;
        this->is_pinned = false;
    }

    void set(short posLet, short posNum) {
        this->posLet = posLet;
        this->posNum = posNum;
    }

    void pin() {
        this->is_pinned = true;
    }

    void unpin(){
        this->is_pinned = false;
    }

private:
    bool color, moveCheck, death, is_pinned;
    short posLet, posNum;
    std::string name;
};

/** Памятка по name фигуры */
/*
 1st number:      2nd number:     3rd number:
 * 1 - pawn         0 - black       number of a piece
 * 2 - bishop       1 - white
 * 3 - knight
 * 4 - castle
 * 5 - queen
 * 6 - king
*/

/**заполнение фигур*/
void fill(piece array[], short i, short posLet, short posNum, std::string Name){
    bool color = short(Name[1]) - 48;
    array[i].set(posLet, posNum, Name, false, color);
}

/** на вход получаем имя фигуры, на выход - номер в массиве */
short call(std::string name){
    bool color = name[1] - 48;
    short piece_ord = name[2] - 48;
    short piece_number = -1;
    short switch_piece = name[0] - 48;
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

/**Вспомогательная функция для steps_prediction()
 * Используется для нанесения на предсказательные матрицы флагов (обозначающих: можно сходить, можно съесть)*/
 // к переработке?
void fill_cell(short PlayerSelector, chessboard *chessboard2, chessboard *chessboard3, piece array[33],
               short to_let, short to_num, short switcher, bool king_flag) {
    std::string name;
    if (king_flag) {
        name = chessboard2->Get(to_let, to_num);
    } else {
        name = chessboard3->Get(to_let, to_num);
    }
    if (switcher == 0) {
        name[1] = 'X';
    } else if (switcher == 1) {
        name[1] = '$';
    } else name[1] = 'O';
    if (king_flag) {
        chessboard2->Set(name, to_let, to_num);
    } else {
        chessboard3->Set(name, to_let, to_num);
    }
}

/**Вспомогательная функция для пешек для steps_prediction()*/
bool pawn_logic(short PlayerSelector, chessboard *chessboard1, short to_let, short to_num, bool *barrier, bool move_type, bool *switcher, bool *king_encounter){
    bool fill = false;
    if ((to_let < 8) and (to_num < 8) and (to_let > -1) and (to_num > -1)) {
        if (move_type) {
            //хождение вперёд
            if (chessboard1->Get(to_let,to_num) == "___") {
                fill = true;
                *switcher = true;
            } else *barrier = true;
        } else {
            //съедение
            if (short(chessboard1->Get(to_let, to_num)[1]) - 48 == -1 * PlayerSelector - 1
                or PlayerSelector == short(chessboard1->Get(to_let, to_num)[1]) - 48) {
                fill = true;
                *switcher = false;
                if (int(chessboard1->Get(to_let, to_num)[0]) - 48 == 6) {
                    *king_encounter = true;
                }
            }
        }
    }
    return fill;
}


bool pinner(bool *barrier, chessboard *chessboard1, piece array, short let, short num){
    bool flag = false;



    return flag;
}


/**Вспомогательная функция для фигур, которые ходят по прямой для steps_prediction()*/
bool beam_logic(short PlayerSelector, chessboard *chessboard1, short to_let, short to_num, bool *barrier, bool *switcher, bool *king_encounter, bool tracing, short *pinpiece) {
    bool fill = false;
    if ((to_let < 8) and (to_num < 8) and (to_let > -1) and (to_num > -1)) {
        if (chessboard1->Get(to_let, to_num) != "___") {
            if (short(chessboard1->Get(to_let, to_num)[1]) - 48 != -1 * PlayerSelector
                and PlayerSelector <= int(chessboard1->Get(to_let, to_num)[1]) - 48) {
                //съедение
                fill = true;
                *switcher = false;
                if (tracing) {
                    if (*pinpiece >= 0) {
                        *barrier = true;
                    } else {
                        if (int(chessboard1->Get(to_let, to_num)[0]) - 48 == 6) {
                            *king_encounter = true;
                            *barrier = true;
                        } else {
                            *pinpiece = call(chessboard1->Get(to_let, to_num));
                        }
                    }
                }
                else {
                    if (int(chessboard1->Get(to_let, to_num)[0]) - 48 == 6) {
                        *king_encounter = true;
                    }
                    *barrier = true;
                }
            }   else
                *barrier = true;
        } else {
            //хождение вперёд
            fill = true;
            *switcher = true;
        }
    } else *barrier = true;
    return fill;
}

/**Вспомогательная функция для короля для steps_prediction()*/
bool king_logic(std::string name, short PlayerSelector, chessboard *chessboard1,
                chessboard *chessboard2, chessboard *chessboard3, piece array[33], short to_let, short to_num, bool *switcher){
    bool fill = false;
    if (chessboard1->Get(to_let,to_num) != "___"){
        if ((short(chessboard1->Get(to_let,to_num)[1])-48 != -1 * PlayerSelector) and (PlayerSelector <= short(chessboard1->Get(to_let,to_num)[1])-48)){
            if (!check_danger(name,to_let,to_num, PlayerSelector, chessboard1, chessboard2, chessboard3, array)) {
                fill = true;
                *switcher = false;
            }
        }
    } else {
        if (!check_danger(name,to_let,to_num, PlayerSelector, chessboard1, chessboard2, chessboard3, array)) {
            fill = true;
            *switcher = true;
        }
    }
    return fill;
}

/**Проверка на то, находится ли данная клетка под ударом*/
//меня бесит стринговский name здесь, он вообще не нужен
bool check_danger(std::string name, short to_let, short to_num, short PlayerSelector, chessboard *chessboard1,
                  chessboard *chessboard2, chessboard *chessboard3, piece array[]) {
    bool danger = false;
    bool firstcolor = PlayerSelector == -1;
    short king_let, king_num;
    //name можно получить внутри, исходя из цвета, но я не умею работать со строками
    array[call(name)].get(&king_let, &king_num);
    /**перемещение короля*/
    if (!((king_let == to_let) and (king_num == to_num))){
        chessboard2->Set(chessboard2->Get(king_let,king_num),to_let,to_num);
        chessboard2->Set("___",king_let,king_num);
        chessboard1->Set("___",king_let,king_num);
        chessboard1->Set(name,to_let,to_num);

    }

    for (short i = 0; i < 32; ++i) {
        if (!array[i].get_death()){
            if (call(name) == i) continue;
            if ((array[i].get_color() != firstcolor)) {
                short num, let;
                std::string name1;
                array[i].get(&let, &num);
                array[i].get(&name1);
                short switch_piece = short(name1[0]) - 48;
                steps_prediction(let, num, PlayerSelector*-1, chessboard1, chessboard2,
                                 chessboard3, array, true, switch_piece, false);
            }
            if (chessboard2->Get(to_let,to_num)[1] == 'X'){
                danger = true;
                break;
            }
        }

    }
    clean_matrix(chessboard1);
    clean_matrix(chessboard2);
    fill_matrix_piece(chessboard1, chessboard2, chessboard3, array, true, false, false);

    return danger;
}

void add_check(bool *check1, bool *check2){
    if (*check1) {
        *check2 = true;
    } else
        *check1 = true;
}


//ОНО ПОЧТИ-ПОЧТИ РАБОТАЕТ
void king_tracing(short PlayerSelector, chessboard *chessboard1, chessboard *chessboard2, chessboard *chessboard3, piece array[33], bool *check1, bool *check2){
    bool firstcolor = PlayerSelector == -1;
    for (short i = 0; i < 30; ++i) {
        if (!*check2) {
            if (!array[i].get_death() and (array[i].get_color() != firstcolor)) {
                short num, let;
                std::string name1;
                array[i].get(&let, &num);
                array[i].get(&name1);
                short switch_piece = short(name1[0]) - 48;
                steps_prediction(let, num, PlayerSelector * -1, chessboard1, chessboard2,
                                 chessboard3, array, false, switch_piece, true);
                short pos_let, pos_num;
                array[30 + firstcolor].get(&pos_let, &pos_num);
                std::string king_name = chessboard2->Get(pos_let, pos_num);
                if (king_name[1] == 'X') {
                    std::string buffer_name;
                    buffer_name = king_name[0];
                    buffer_name += "_";
                    buffer_name += king_name[2];
                    chessboard2->Set(buffer_name, pos_let, pos_num);
                    std::string enemy_name = chessboard2->Get(let, num);
                    buffer_name = enemy_name[0];
                    buffer_name += "X";
                    buffer_name += enemy_name[2];
                    chessboard2->Set(buffer_name, let, num);
                    add_check(check1, check2);
                }
            }


        } else {
            clean_matrix(chessboard2);
            fill_matrix_piece(chessboard1, chessboard2, chessboard3, array, false, false, true);
            break;
        }
    }
    clean_matrix(chessboard3);
    fill_matrix_piece(chessboard1, chessboard2, chessboard3, array, false, true, false);
}


/**рендер возможных ходов*/
void steps_prediction(short from_let, short from_num, short PlayerSelector, chessboard *chessboard1, chessboard *chessboard2,
                      chessboard *chessboard3, piece array[33], bool king_flag, short switch_piece, bool tracing){
    short pinpiece = -1;
    bool switcher, king_encounter = false;
    switch (switch_piece) {
        case 1: {
            //на 1 вперёд
            bool barrier = false;
            short to_let = from_let;
            short to_num = from_num + (-1 * PlayerSelector);
            if (pawn_logic(PlayerSelector, chessboard1, to_let, to_num, &barrier, true, &switcher, &king_encounter)){
                fill_cell(PlayerSelector, chessboard2,  chessboard3, array, to_let, to_num, switcher, king_flag);
            }
            //на 2 вперёд
            if (!barrier and !array[call(chessboard1->Get(from_let, from_num))].get_move()) {
                to_let = from_let;
                to_num = from_num + (-2 * PlayerSelector);
                if (pawn_logic(PlayerSelector, chessboard1, to_let, to_num, &barrier, true, &switcher, &king_encounter)){
                    fill_cell(PlayerSelector, chessboard2,  chessboard3, array, to_let, to_num, switcher, king_flag);
                }
            }
            //диагональ вправо на 1
            to_let = from_let + 1;
            to_num = from_num + (-1 * PlayerSelector);
            if (pawn_logic(PlayerSelector, chessboard1, to_let, to_num, &barrier, false, &switcher, &king_encounter)){
                fill_cell(PlayerSelector, chessboard2,  chessboard3, array, to_let, to_num, switcher, king_flag);
            }
            if (king_encounter and tracing){
                fill_cell(PlayerSelector, chessboard2,  chessboard3, array, to_let, to_num, switcher, true);
            }
            //диагональ влево на 1
            to_let = from_let - 1;
            to_num = from_num + (-1 * PlayerSelector);
            if (pawn_logic(PlayerSelector, chessboard1, to_let, to_num, &barrier, false, &switcher, &king_encounter)){
                fill_cell(PlayerSelector, chessboard2,  chessboard3, array, to_let, to_num, switcher, king_flag);
            }
            if (king_encounter and tracing){
                fill_cell(PlayerSelector, chessboard2,  chessboard3, array, to_let, to_num, switcher, true);
            }
            break;
        }
        case 2: {
            short k = 0;
            bool barrier = false;
            while (k < 4) {
                short l = (k + 1) % 4;
                short to_let = from_let;
                short to_num = from_num;
                while (!barrier) {
                    to_let += k / 2 + !(k / 2) * -1;
                    to_num += l / 2 + !(l / 2) * -1;
                    if (beam_logic(PlayerSelector, chessboard1, to_let, to_num, &barrier, &switcher, &king_encounter, tracing, &pinpiece)){
                        fill_cell(PlayerSelector, chessboard2,  chessboard3, array, to_let, to_num, switcher, king_flag);
                    }
                }
                barrier = false;
                if (king_encounter and tracing) {
                    if (pinpiece < 0) {
                        to_let = from_let;
                        to_num = from_num;
                        while (!barrier) {
                            to_let += k / 2 + !(k / 2) * -1;
                            to_num += l / 2 + !(l / 2) * -1;
                            if (beam_logic(PlayerSelector, chessboard1, to_let, to_num, &barrier, &switcher,
                                           &king_encounter, tracing, &pinpiece)) {
                                fill_cell(PlayerSelector, chessboard2, chessboard3, array, to_let, to_num, switcher,
                                          true);
                            }
                        }
                    } else {
                        array[pinpiece].pin();
                    }
                    break;
                }
                k++;
            }
            break;
        }
        case 3: {
            bool barrier = false;
            short to_let = from_let - 2;
            short to_num = from_num - 1;

            short i = 0;
            while(i < 8){
                if ((to_let > -1) and (to_let < 8) and (to_num > -1) and (to_num < 8)) {
                    if (beam_logic(PlayerSelector, chessboard1, to_let, to_num, &barrier, &switcher, &king_encounter, tracing, &pinpiece)){
                        fill_cell(PlayerSelector, chessboard2,  chessboard3, array, to_let, to_num, switcher, king_flag);
                    }
                }
                if (king_encounter and tracing) {
                    fill_cell(PlayerSelector, chessboard2,  chessboard3, array, to_let, to_num, switcher, true);
                    break;
                }
                short j = (i + 2) % 8;
                /** даже не спрашивайте, как это работает*/
                to_let += (((i + 1) % 2) * (((i / 2) % 2) * 2) + (i % 2)) * (!(i/4) - (i/4));
                to_num += (((j + 1) % 2) * (((j / 2) % 2) * 2) + (j % 2)) * (!(j/4) - (j/4));
                i++;
            }
            break;
        }
        case 4: {
            short k = 0;
            bool barrier = false;
            while (k < 4) {
                short l = (k + 1) % 4;
                short to_let = from_let;
                short to_num = from_num;
                while (!barrier) {
                    to_let += (k / 2 + !(k / 2) * -1) * !(k % 2);
                    to_num += (l / 2 + !(l / 2) * -1) * !(l % 2);
                    if (beam_logic(PlayerSelector, chessboard1, to_let, to_num, &barrier, &switcher, &king_encounter, tracing, &pinpiece)){
                        fill_cell(PlayerSelector, chessboard2,  chessboard3, array, to_let, to_num, switcher, king_flag);
                    }
                }
                barrier = false;
                if (king_encounter and tracing) {
                    to_let = from_let;
                    to_num = from_num;
                    while (!barrier) {
                        to_let += (k / 2 + !(k / 2) * -1) * !(k % 2);
                        to_num += (l / 2 + !(l / 2) * -1) * !(l % 2);
                        if (beam_logic(PlayerSelector, chessboard1, to_let, to_num, &barrier, &switcher,
                                       &king_encounter,  tracing, &pinpiece)) {
                            fill_cell(PlayerSelector, chessboard2, chessboard3, array, to_let, to_num, switcher, true);
                        }
                    }
                    break;
                }
                k++;
            }
            break;
        }
        case 5: {
            short k = 0;
            bool barrier = false;
            while (k < 8) {
                short l = (k + 2) % 8;
                short to_let = from_let;
                short to_num = from_num;

                while (!barrier) {
                    to_let += (k / 4 + !(k / 4) * -1) * bool((k + 1) % 4);
                    to_num += (l / 4 + !(l / 4) * -1) * bool((l + 1) % 4);
                    if (beam_logic(PlayerSelector, chessboard1, to_let, to_num, &barrier, &switcher,
                                   &king_encounter, tracing, &pinpiece)) {
                        fill_cell(PlayerSelector, chessboard2, chessboard3, array, to_let, to_num, switcher,
                                  king_flag);
                    }
                }


                barrier = false;
                if (king_encounter and tracing) {
                    to_let = from_let;
                    to_num = from_num;
                    while (!barrier) {
                        to_let += (k / 4 + !(k / 4) * -1) * bool((k + 1) % 4);
                        to_num += (l / 4 + !(l / 4) * -1) * bool((l + 1) % 4);
                        if (beam_logic(PlayerSelector, chessboard1, to_let, to_num, &barrier, &switcher,
                                       &king_encounter, tracing, &pinpiece)) {
                            fill_cell(PlayerSelector, chessboard2, chessboard3, array, to_let, to_num, switcher, true);
                        }
                    }
                    break;
                }
                k++;
            }
            break;
        }
        case 6: {
            std::string name = chessboard1->Get(from_let,from_num);
            bool first_color = PlayerSelector == -1;
            short to_let = from_let - 1;
            short to_num = from_num - 1;
            short k = 0;
            /**данная проверка не позволяет логике двух королей зациклиться друг об друга*/
            if (!king_flag) {
                clean_matrix(chessboard2);
                fill_matrix_piece(chessboard1,chessboard2,chessboard3, array, false, false, true);
                /**проверка окружающих 8 клеток*/
                while (k < 8) {
                    if ((to_let > -1) and (to_let < 8) and (to_num > -1) and (to_num < 8)) {
                        if (king_logic(name, PlayerSelector, chessboard1, chessboard2, chessboard3, array, to_let, to_num, &switcher)) {
                            fill_cell(PlayerSelector, chessboard2,  chessboard3, array, to_let, to_num, switcher, king_flag);
                        }
                    }
                    bool yx = (k % 4) / 2;
                    int m;
                    (k / 4 ? m = -1 : m = 1);
                    to_num += m * !int(yx);
                    to_let += m * int(yx);
                    //chessboard3->render_predict();
                    k++;
                }

                /**рокировка:*/
                {
                    if (!array[call(name)].get_move()) {
                        to_let = from_let;
                        to_num = from_num;

                        /**рокировка вправо*/
                        bool barrier = false;
                        for (int i = from_let + 1; i < 7; ++i) {
                            if (chessboard1->Get(i, from_num) != "___") {
                                barrier = true;
                                break;
                            }
                        }

                        if (!barrier) {
                            bool danger = false;
                            for (int i = from_let + 1; i < 7; ++i) {
                                if (check_danger(name, i, from_num, PlayerSelector, chessboard1, chessboard2, chessboard3, array)) {
                                    danger = true;
                                    break;
                                }
                            }
                            if (!danger) {
                                if ((int(chessboard1->Get(7, from_num)[0]) - 48 == 4) and
                                    (!array[call(chessboard1->Get(7, from_num))].get_move())) {
                                    fill_cell(PlayerSelector, chessboard2, chessboard3, array, to_let + 2, to_num, 2, king_flag);
                                }
                            }
                        }

                        /**рокировка влево*/
                        barrier = false;
                        for (int i = from_let - 1; i > 0; --i) {
                            if (chessboard1->Get(i, from_num) != "___") {
                                barrier = true;
                                break;
                            }
                        }

                        if (!barrier) {
                            bool danger = false;
                            for (int i = from_let - 1; i > 0; --i) {
                                if (check_danger(name, i, from_num, PlayerSelector, chessboard1, chessboard2, chessboard3, array)) {
                                    danger = true;
                                    break;
                                }
                            }
                            if (!danger) {
                                if ((int(chessboard1->Get(0, from_num)[0]) - 48 == 4) and
                                    (!array[call(chessboard1->Get(0, from_num))].get_move())) {
                                    fill_cell(PlayerSelector, chessboard2, chessboard3, array, to_let - 2, to_num, 2, king_flag);
                                }
                            }
                        }
                    }

                }
            }
            break;
        }
        default: {
            break;
        }
    }
}

/**заполнение матрицы прочерками*/
void clean_matrix(chessboard *chessboard){
    for (short i = 0; i < 8; ++i) {
        for (short j = 0; j < 8; ++j) {
            chessboard->Set("___",i,j);
        }
    }
}

/**функция предназначена для сравнения cb2 и cb3, дабы выводилось только пересечение путей атакующей фигуры и защищающейся в условиях чека*/
void comparison(chessboard *chessboard2, chessboard *chessboard3){
    for (short i = 0; i < 8; ++i) {
        for (short j = 0; j < 8; ++j) {
            if (chessboard2->Get(i,j)[1] == '_') {
                std::string temp_name = chessboard2->Get(i,j);
                temp_name[1] = '_';
                chessboard3->Set(temp_name,i,j);
            }
        }
    }
}

/**размещение фигур на матрице(в зависимости от значений flag и flag1) */
void fill_matrix_piece(chessboard *chessboard1, chessboard *chessboard2, chessboard *chessboard3, piece array[], bool flag, bool flag1, bool flag2){
    for (short i = 0; i < 33; ++i) {
        short posLet, posNum;
        bool color;
        std::string name;
        color = array[i].get_color();
        array[i].get(&posLet, &posNum);
        array[i].get(&name);
        if (array[i].get_death() == 0){
            short switch_piece = short(name[0]) - 48;
            std::string piece_color;
            if (color){
                piece_color = "w";
            }else{
                piece_color = "b";
            }
            if (flag) chessboard1->Set(name,posLet, posNum);
            switch (switch_piece) {
                case 1:{
                    piece_color += "_P";
                    break;
                }
                case 2:{
                    piece_color += "_B";
                    break;
                }
                case 3:{
                    piece_color += "_N";
                    break;
                }
                case 4:{
                    piece_color += "_R";
                    break;
                }
                case 5:{
                    piece_color += "_Q";
                    break;
                }
                case 6:{
                    piece_color += "_K";
                    break;
                }

                default:{
                    break;
                }
            }
            if (i!=32) {
                if (flag1) chessboard3->Set(piece_color, posLet, posNum);
                //место для маркера скипа перезаполнения
                if (flag2) chessboard2->Set(piece_color, posLet, posNum);
            }
        }
    }
}


/**функция будет оценивать игру на наличие мата или пата*/
void game_state(){

}

std::string Get_filename(){
    time_t now = time(0);
    tm *ltm = localtime(&now);
    std::string nomber = "";
    int i = 0;
    while ((std::to_string(ltm->tm_mday))[i]!=NULL){
        i++;
    }
    std::string day = (i == 1?"0":"");
    i = 0;
    while ((std::to_string(1 + ltm->tm_mon))[i]!=NULL){
        i++;
    }
    std::string month = (i == 1?"0":"");
    nomber += day + std::to_string(ltm->tm_mday) + "_" + month + std::to_string(1 + ltm->tm_mon) + "_" + std::to_string(1900 + ltm->tm_year) + "_" + std::to_string(ltm->tm_hour) + "_" + std::to_string(ltm->tm_min);
    return nomber;
}

void find_file(std::string *array){
    WIN32_FIND_DATA FindFileData;
    HANDLE hf;
    hf=FindFirstFile("..\\saves\\*", &FindFileData);
    if (hf!=INVALID_HANDLE_VALUE){
        int i = 0;
        do{
            if (i>9){
                for (int j = 1; j < 10; ++j) {
                    array[j-1] = array[j];
                }
                array[9] = FindFileData.cFileName;
                i++;
            }else{
                array[i%10] = FindFileData.cFileName;
                i++;
            }
        }while (FindNextFile(hf,&FindFileData)!=0);
        FindClose(hf);
    }
}

int main(){


    // 1 d2 d4 d7 d5 c1 g5
    SetConsoleOutputCP(CP_UTF8);
    piece array[33];
    chessboard chessboard1; //подложная
    chessboard chessboard2; //предсказательная для короля
    chessboard chessboard3; //предсказательная
    short step = 0;
    short PlayerSelector = -1; //переменная, определяющая очерёдность хода, -1 - белые, 1 - чёрные
    bool check1 = false;
    bool check2 = false;
    bool check_mate = false;
    std::string name_enemy = "___";
    bool flag = false;
    do{
        std::cout << "Выберите режим\n";
        std::cout << "Для перехода в режим разработчика введите 0\n";
        std::cout << "Для перехода в классический режим введите 1\n";
        std::cout << "Для загрузки сохранения из файла введите 2\n";
        char switcher;
        std::cin >> switcher;
        switch (switcher) {
            case '1':{
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
                flag = true;
                break;
            }
            case '0':{

                for (short i = 0; i < 32; ++i) {
                    array[i].kill();
                }

                clean_matrix(&chessboard1);

                clean_matrix(&chessboard3);

                clean_matrix(&chessboard2);

                fill(array, 31, 4, 0, "611");
                fill(array, 30, 4, 7, "601");
                //fill(array, 28, 0, 1, "501");
                //fill(array, 8, 7, 1, "111");
                fill(array, 17, 0, 4, "202");
                fill(array, 29, 3, 0, "511");
                //fill(array, 24, 6, 0, "401");
                fill(array, 26, 0, 0, "411");
                flag = true;
                break;
            }
            case '2': {
                std::string filename, path = "..\\saves\\";
                std::cout << "Выберите файл из списка или введите 10 чтобы вписать свое имя файла\n";
                short switcher = NULL;
                std::string vector_filename [10];
                for (int i = 0; i < 10; ++i) {
                    vector_filename[i] = "";
                }
                find_file(vector_filename);
                int j = 0;
                for (int i = 9; i >= 0; --i) {
                    std::cout<< j << ". " << vector_filename[i] << std::endl;
                    j++;
                }
                std::cin >> switcher;
                if (switcher == 10){
                    std::cout << "Введите имя файла\n";
                    std::cin >> filename;
                    path+= filename + ".txt";
                }else{
                    if ((switcher >= 0) and (switcher <= 9)){
                        path += vector_filename[abs(switcher-9)];
                    }
                }

                std::ifstream file;
                //"..\\cmake-build-debug\\huis.txt"
                file.open(path);
                if (file.is_open()) {
                    std::cout << "Файл открыт\n";
                    std::string start="", end = "", line;
                    char buf = '$';
                    int i = 0;
                    while (!file.eof()) {
                        std::getline(file, line);
                        if (line[0] == buf){
                            (i == 0 ? start : end) = line;
                            if (i == 0) end = line;
                            i++;
                        }
                    }
                    file.close();
                    file.open(path,std::ios::in);
                    if (!file.is_open()){
                        std::cout <<"Файл повторно не открылся\n";
                        break;
                    }
                    bool flag1 = false;
                    short step1, step2;
                    while (!flag1){
                        std::cout << "Выберите ход с " << start[1] << " по " << end[1] << "\n";
                        std::cin >> step1;
                        if((step1>=int(start[1])-48) and (step1<=int(end[1])-48)){
                            flag1 = true;
                        }
                    }

                    std::string line1 = "$";
                    line1 += std::to_string(step1);
                    while (!file.eof()) {
                        std::getline(file, line);
                        if (line == line1) {
                            const char delim = ' ';
                            const char delim1 = '\n';
                            for (int i = 0; i <= 32; i++) {
                                std::string name;
                                bool color, moveCheck, death, is_pinned;
                                short posLet, posNum;
                                std::getline(file, line, delim);
                                name = line;
                                std::getline(file, line, delim);
                                posLet = int(line[0])- 48;
                                std::getline(file, line, delim);
                                posNum = int(line[0])- 48;
                                std::getline(file, line, delim);
                                death = int(line[0])- 48;
                                std::getline(file, line, delim);
                                is_pinned = int(line[0])- 48;
                                std::getline(file, line, delim);
                                moveCheck = int(line[0])- 48;
                                std::getline(file, line, delim1);
                                color = int(line[0])- 48;
                                array[i].set(posLet, posNum, name, moveCheck, color, death, is_pinned);
                            }
                        }
                    }
                    PlayerSelector = (step1 % 2? 1 : -1);
                    step = step1 - 1;
                    file.close();
                    flag = true;
                }else{
                    std::cout << "Файл не открылся\n";
                }

                break;
            }
            default:{
                break;
            }
        }
    }while (!flag);




    /*if (!switch_mod){

        for (short i = 0; i < 32; ++i) {
            array[i].kill();
        }

        clean_matrix(&chessboard1);

        clean_matrix(&chessboard3);

        clean_matrix(&chessboard2);

        fill_matrix_piece(&chessboard1, &chessboard2, &chessboard3, array, true, true, true);
        chessboard3.render_view();

        //Пофиксить баг с перестановкой фигуры 
        bool switcher = true;
        std::cout << "Выберите мод\n";
        std::cin>> switcher;
        if(switcher){
            //по-моему, оно вообще не работает
            bool add_new_piece = true;
            while (add_new_piece) {
                std::string name;
                short from_let, from_num;
                std::string from_pos;
                std::cout << "Введите код и координаты фигуры\n";
                std::cin >> name >> from_pos;
                int i = call(name);
                if (!array[i].get_death()) {
                    array[i].kill();
                    clean_matrix(&chessboard1);
                    clean_matrix(&chessboard3);
                    clean_matrix(&chessboard2);
                }
                if (from_pos == "-1") {
                    array[i].revive();
                } else {
                    from_let = from_pos[0] - 65;
                    from_num = from_pos[1] - 49;
                    if (from_let > 8) from_let -= 32;
                    fill(array, i, from_let, from_num, name);
                }

                fill_matrix_piece(&chessboard1, &chessboard2, &chessboard3, array, true, true, true);
                chessboard3.render_view();
                std::cout << "Хотите ли вы добавить новую фигуру?\n";
                std::cin >> add_new_piece;
            }
        }else{
            fill(array, 31, 4, 0, "611");
            fill(array, 30, 4, 7, "601");
            fill(array, 28, 0, 1, "501");
            //fill(array, 8, 7, 1, "111");
            fill(array, 29, 3, 0, "511");
            //fill(array, 24, 6, 0, "401");
            fill(array, 26, 0, 0, "411");
            fill_matrix_piece(&chessboard1, &chessboard2, &chessboard3, array, true, true, true);
            chessboard3.render_view();
        }
    } */

    fill_matrix_piece(&chessboard1, &chessboard2, &chessboard3, array, true, true, true);

    std::string path_saves = "..\\saves\\chess_game";
    path_saves += Get_filename() + ".txt";
    std::ofstream MyFile(path_saves);

    MyFile  << "$" << step << "\n" ;
    for (int i = 0; i<= 32; i++){
        std::string name;
        short posLet, posNum;
        array[i].get(&posLet,&posNum);
        array[i].get(&name);
        MyFile << name << " " << posLet << " " << posNum << " " << array[i].get_death() << " " ;
        MyFile << array[i].get_pin() << " " << array[i].get_move() << " " << array[i].get_color() << "\n";
    }
    MyFile << "\n";
    MyFile.close();
    std::string from_pos, to_pos;
    short from_let, from_num, to_let, to_num;

    //надо менять цикл с while на do while, игру изнутри остановить невозможно.
    while((from_pos != "-1") or !check_mate or (to_pos != "-1")){
        /**заполнение подложной матрицы*/
        clean_matrix(&chessboard1);
        /**заполнение игровой матрицы*/
        clean_matrix(&chessboard3);
        /**заполнение предсказательной матрицы*/
        clean_matrix(&chessboard2);

        /**размещение фигур*/
        fill_matrix_piece(&chessboard1, &chessboard2, &chessboard3, array, true, true, true);

        /**проверка на чеки*/
        king_tracing(PlayerSelector, &chessboard1, &chessboard2, &chessboard3, array, &check1, &check2);
        //chessboard2.render_predict();

        //game_state();

        std::cout << (PlayerSelector == -1 ? "Ход Белых\n" : "Ход Чёрных\n");

        //chessboard1.render_predict();
        chessboard3.render_view();
        short first_piece, second_piece;
        bool l = false;

        std::cin >> from_pos;
        if (from_pos == "-1") break;
        do {
            /**перезаполнение предсказательной матрицы*/
            clean_matrix(&chessboard3);
            clean_matrix(&chessboard2);
            check1 = false;
            check2 = false;

            /**переразмещение фигур на предсказательной матрице*/
            fill_matrix_piece(&chessboard1, &chessboard2, &chessboard3, array, false, true, true);

            king_tracing(PlayerSelector, &chessboard1, &chessboard2, &chessboard3, array, &check1, &check2);

            //chessboard2.render_predict();


            /**перевод координат*/
            from_let = from_pos[0] - 65;
            from_num = from_pos[1] - 49;
            if (from_let > 8) from_let -= 32;
            if ((-1 < from_let) and (-1 < from_num) and (from_let < 8) and (from_num < 8)) {
            if (!array[32].get_death()) {
                short temp_let, temp_num;
                std::string temp_name;
                array[32].get(&temp_let, &temp_num);
                array[32].get(&temp_name);
                if (chessboard1.Get(from_let, from_num)[0] == '1') {
                    chessboard1.Set(temp_name, temp_let, temp_num);
                } else {
                    chessboard1.Set("___", temp_let, temp_num);
                }
            }
            if (chessboard1.Get(from_let, from_num)[1] != '_') {

                bool FirstPieceColor = array[call(chessboard1.Get(from_let, from_num))].get_color();
                if ((int(FirstPieceColor) == -1 * PlayerSelector) or (PlayerSelector > int(FirstPieceColor))) {
                    short switch_piece = short(chessboard1.Get(from_let, from_num)[0]) - 48;
                    steps_prediction(from_let, from_num, PlayerSelector, &chessboard1, &chessboard2, &chessboard3,
                                     array, false, switch_piece, false);
                    if (check1 and (chessboard1.Get(from_let, from_num)[0] != '6')){

                        //std::cout << "cb3 render pre-comp\n";
                        //chessboard3.render_predict();
                        comparison(&chessboard2, &chessboard3);
                    }

                    chessboard2.render_predict();
                    //std::cout << "cb3 render post-comp\n";
                    chessboard3.render_predict();

                    /**перевод координат*/
                    std::cin >> to_pos;
                    if (to_pos == "-1") break;
                    to_let = to_pos[0] - 65;
                    to_num = to_pos[1] - 49;
                    if (to_let > 8)
                        to_let -= 32;

                    first_piece = call(chessboard1.Get(from_let, from_num));
                    if ((-1 < to_let) and (-1 < to_num) and (to_let < 8) and (to_num < 8)) {
                        if (chessboard3.Get(to_let, to_num)[1] != '_') {
                            if (chessboard3.Get(to_let, to_num)[1] == 'X') {
                                //съедение
                                second_piece = call(chessboard1.Get(to_let, to_num));
                                array[second_piece].kill();
                                array[first_piece].mover(from_let, from_num, to_let, to_num, &PlayerSelector,
                                                         &chessboard1, array);
                                step++;
                                l = true;
                            } else if (chessboard3.Get(to_let, to_num)[1] == 'O') {
                                //рокировка
                                array[first_piece].mover(from_let, from_num, to_let, to_num, &PlayerSelector,
                                                         &chessboard1, array);
                                std::string name_castle;
                                if (to_let / 4) {
                                    name_castle = chessboard1.Get(7, to_num);
                                    array[call(name_castle)].mover(7, from_num, 5, to_num, &PlayerSelector,
                                                                   &chessboard1, array);
                                } else {
                                    name_castle = chessboard1.Get(0, to_num);
                                    array[call(name_castle)].mover(0, from_num, 3, to_num, &PlayerSelector,
                                                                   &chessboard1, array);
                                }
                                PlayerSelector *= -1;
                                step++;
                                l = true;
                            } else {
                                array[first_piece].mover(from_let, from_num, to_let, to_num, &PlayerSelector,
                                                         &chessboard1, array);
                                step++;
                                l = true;
                            }
                        } else {
                            bool first_color = array[call(chessboard1.Get(from_let, from_num))].get_color();
                            if (int(chessboard1.Get(to_let, to_num)[1]) - 48 == first_color) {
                                from_pos = to_pos;
                            } else std::cout << "Попробуйте другой ход\n";
                        }
                    } else {
                        std::cout << "Выход за границы доски\n";
                    }

                } else {
                    std::cout << "Куда вне очереди\n";
                    l = true;
                }
            } else {
                std::cout << "Выберите фигуру\n";\
                l = true;
            }
        } else {
                std::cout << "Выход за границы доски\n";
                l = true;
            }

        }while (!l);
        MyFile.open(path_saves, std::ios::app);
        MyFile  << "$" << step << "\n" ;
        for (int i = 0; i<= 32; i++){
            std::string name;
            short posLet, posNum;
            array[i].get(&posLet,&posNum);
            array[i].get(&name);
            MyFile << name << " " << posLet << " " << posNum << " " << array[i].get_death() << " " ;
            MyFile << array[i].get_pin() << " " << array[i].get_move() << " " << array[i].get_color() << "\n";
        }
        MyFile << "\n";
        MyFile.close();
    }
    std::cout << "Легитимный выход из программы.";
    return 0;
}

//Надо провести рефакторинг кода
//1 d2 d4 g7 g6 a2 a4 f8 h6 e1 f2 f3 e8 f8 e2 e4 h6 c1 -1