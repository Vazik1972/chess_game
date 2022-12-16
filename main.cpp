#include <iostream>
#include <string>
#include <Windows.h>

//пук


short call(std::string name);

class chessboard;

class piece;
void fill_matrix(chessboard *chessboard1);
void steps_prediction(short from_let, short from_num, short PlayerSelector, chessboard *chessboard1, chessboard *chessboard2, chessboard *chessboard3, piece array[33], bool king_flag);
void fill_matrix_piece(chessboard *chessboard1, chessboard *chessboard2, chessboard *chessboard3, piece array[], bool flag, bool flag1);
bool check_danger(std::string name, short from_let, short from_num, short PlayerSelector, chessboard *chessboard1, chessboard *chessboard2, chessboard *chessboard3, piece array[]);
class chessboard {
public:
/**вывод доски с фигурами в консоль*/
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

    void set(short posLet, short posNum, std::string name, bool moveCheck, bool color) {
        this->posLet = posLet;
        this->posNum = posNum;
        this->name = name;
        this->moveCheck = moveCheck;
        this->color = color;
        this->death = false;
    }

    void set(short posLet, short posNum) {
        this->posLet = posLet;
        this->posNum = posNum;
    }


private:
    bool color, moveCheck, death;
    short posLet, posNum;
    std::string name;
};



class PlayerWhite {

};

class PlayerBlack {

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
void fill_cell(short from_let, short from_num, short PlayerSelector, chessboard *chessboard1, chessboard *chessboard2,
               chessboard *chessboard3, piece array[33], short to_let, short to_num, short switcher, bool king_flag) {
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
void pawn_logic(short from_let, short from_num, short PlayerSelector, chessboard *chessboard1,chessboard *chessboard2,
                chessboard *chessboard3, piece array[33], short to_let, short to_num, bool *barrier, bool king_flag, bool move_type){
    if ((to_let < 8) and (to_num < 8) and (to_let > -1) and (to_num > -1)) {
        if (move_type) {
            //хождение вперёд
            if (chessboard1->Get(to_let,to_num) == "___") {
                fill_cell(from_let, from_num, PlayerSelector, chessboard1, chessboard2,  chessboard3, array, to_let,
                          to_num, true, king_flag);
            } else *barrier = true;
        } else {
            //съедение
            if (short(chessboard1->Get(to_let, to_num)[1]) - 48 == -1 * PlayerSelector - 1
                or PlayerSelector == short(chessboard1->Get(to_let, to_num)[1]) - 48) {
                fill_cell(from_let, from_num, PlayerSelector, chessboard1, chessboard2,  chessboard3, array, to_let,
                          to_num, false, king_flag);
            }
        }
    }
}

/**Вспомогательная функция для фигур, которые ходят по прямой для steps_prediction()*/
void beam_logic(short from_let, short from_num, short PlayerSelector, chessboard *chessboard1,chessboard *chessboard2,
                  chessboard *chessboard3, piece array[33], short to_let, short to_num, bool *barrier, bool king_flag){
    if ((to_let < 8) and (to_num < 8) and (to_let > -1) and (to_num > -1)) {
        if(chessboard1->Get(to_let,to_num) != "___"){
            if (int(chessboard1->Get(to_let, to_num)[1]) - 48 != -1 * PlayerSelector
                and PlayerSelector <= int(chessboard1->Get(to_let, to_num)[1]) - 48) {
                fill_cell(from_let, from_num, PlayerSelector, chessboard1, chessboard2,  chessboard3, array, to_let,
                          to_num, false, king_flag);
            }
            *barrier = true;
        }else{
            fill_cell(from_let, from_num, PlayerSelector, chessboard1, chessboard2,  chessboard3, array, to_let,
                      to_num, true, king_flag);
        }
    }else *barrier = true;
}

/**Вспомогательная функция для короля для steps_prediction()*/
void king_logic(std::string name,short from_let, short from_num, short PlayerSelector, chessboard *chessboard1,chessboard *chessboard2, chessboard *chessboard3, piece array[33], short to_let, short to_num, bool king_flag){
    if(chessboard1->Get(to_let,to_num) != "___"){
        if ((short(chessboard1->Get(to_let,to_num)[1])-48 != -1 * PlayerSelector) and (PlayerSelector <= short(chessboard1->Get(to_let,to_num)[1])-48)){
            if (!check_danger(name,to_let,to_num,PlayerSelector,chessboard1,chessboard2,chessboard3, array)){
                fill_cell(from_let, from_num, PlayerSelector, chessboard1,chessboard2, chessboard3, array, to_let,
                          to_num, false, king_flag);
            }
        }
    }else{
        if (!check_danger(name,to_let,to_num,PlayerSelector,chessboard1,chessboard2,chessboard3, array)){
            fill_cell(from_let, from_num, PlayerSelector, chessboard1,chessboard2, chessboard3, array, to_let,
                      to_num, true, king_flag);
        }
    }
}



/**проход по всем фигурам и поиск той, которая сможет съесть фигуру на данной клетке */
void running_through_the_piece(std::string name, bool fircolor, bool *danger, short from_let, short from_num, short PlayerSelector, chessboard *chessboard1,chessboard *chessboard2, chessboard *chessboard3, piece array[33]){
    short king_let, king_num;
    array[call(name)].get(&king_let, &king_num);
    if ((king_let != from_let) and (king_num !=from_num)){
        chessboard2->Set(chessboard2->Get(king_let,king_num),from_let,from_num);
        chessboard2->Set("___",king_let,king_num);
        chessboard1->Set(name,from_let,from_num);
        chessboard1->Set("___",king_let,king_num);
    }

    for (short i = 0; i < 32; ++i) {
        if (!array[i].get_death()){
            if (call(name) == i) continue;
            std::string name1;
            array[i].get(&name1);
            if ((array[i].get_color() != fircolor)) {
                short num, let;
                array[i].get(&let, &num);
                steps_prediction(let, num, PlayerSelector*-1, chessboard1, chessboard2, chessboard3, array, true);
            }
            if (chessboard2->Get(from_let,from_num)[1] == 'X'){
                *danger = true;
                break;
            }
        }

    }
    fill_matrix(chessboard1);
    fill_matrix(chessboard2);
    fill_matrix_piece(chessboard1, chessboard2, chessboard3, array, true, false);
}


/**Проверка на то, находится ли данная клетка под ударом*/
//Я перестал понимать, как функция работает
bool check_danger(std::string name, short from_let, short from_num, short PlayerSelector, chessboard *chessboard1, chessboard *chessboard2, chessboard *chessboard3, piece array[]) {
    bool danger = false;
    bool firstcolor = PlayerSelector == -1;
    short to_num = from_num - PlayerSelector;
    short to_let = from_let;
    running_through_the_piece(name, firstcolor, &danger, from_let, from_num, PlayerSelector, chessboard1,
                              chessboard2, chessboard3, array);
    return danger;
}


void king_tracing(short from_let, short from_num, short PlayerSelector, chessboard *chessboard1, chessboard *chessboard2, chessboard *chessboard3, piece array[33], bool king_flag){
    short switch_piece = 1;
    while (switch_piece < 7) {
        steps_prediction(from_let, from_num, PlayerSelector, chessboard1, chessboard2, chessboard3, array, king_flag);
        /**заброшено на время переработки steps_prediction*/
        switch_piece++;
    }
}

/**рендер возможных ходов*/
void steps_prediction(short from_let, short from_num, short PlayerSelector, chessboard *chessboard1, chessboard *chessboard2, chessboard *chessboard3, piece array[33], bool king_flag){
    //вынести отсюда свитч_пис наружу, чтобы можно было вызывать логику отдельной фигуры вне зависимости от того, какая фигура ходит
    short switch_piece = short(chessboard1->Get(from_let,from_num)[0]) - 48;
    switch (switch_piece) {
        case 1: {
            //на 1 вперёд
            bool barrier = false;
            short to_let = from_let;
            short to_num = from_num + (-1 * PlayerSelector);
            pawn_logic(from_let, from_num, PlayerSelector, chessboard1, chessboard2, chessboard3,
                           array, to_let, to_num, &barrier, king_flag, true);
            //на 2 вперёд
            if (!barrier and !array[call(chessboard1->Get(from_let, from_num))].get_move()) {
                to_let = from_let;
                to_num = from_num + (-2 * PlayerSelector);
                pawn_logic(from_let, from_num, PlayerSelector, chessboard1, chessboard2, chessboard3,
                               array, to_let, to_num, &barrier, king_flag, true);
            }
            //диагональ вправо на 1
            to_let = from_let + 1;
            to_num = from_num + (-1 * PlayerSelector);
            pawn_logic(from_let, from_num, PlayerSelector, chessboard1, chessboard2, chessboard3,
                           array, to_let, to_num, &barrier, king_flag, false);

            //диагональ влево на 1
            to_let = from_let - 1;
            to_num = from_num + (-1 * PlayerSelector);
            pawn_logic(from_let, from_num, PlayerSelector, chessboard1, chessboard2, chessboard3,
                           array, to_let, to_num, &barrier, king_flag, false);
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
                    beam_logic(from_let, from_num, PlayerSelector, chessboard1, chessboard2, chessboard3,
                                 array, to_let, to_num, &barrier, king_flag);
                }
                barrier = false;
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
                    beam_logic( from_let, from_num, PlayerSelector, chessboard1,chessboard2, chessboard3, array, to_let, to_num, &barrier, king_flag);

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
                    beam_logic(from_let, from_num, PlayerSelector, chessboard1, chessboard2, chessboard3,
                                 array, to_let, to_num, &barrier, king_flag);
                }
                barrier = false;
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
                    beam_logic(from_let, from_num, PlayerSelector, chessboard1, chessboard2, chessboard3,
                                 array, to_let, to_num, &barrier, king_flag);
                }
                barrier = false;
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
            if (!king_flag) {
                while (k < 8) {
                    if ((to_let > -1) and (to_let < 8) and (to_num > -1) and (to_num < 8)) {
                        king_logic(name, from_let, from_num, PlayerSelector, chessboard1, chessboard2, chessboard3,
                                   array, to_let, to_num, king_flag);
                    }
                    bool yx = (k % 4) / 2;
                    int m;
                    (k / 4 ? m = -1 : m = 1);
                    to_num += m * !int(yx);
                    to_let += m * int(yx);
                    k++;
                }

                if (!array[call(name)].get_move()){
                    to_let = from_let;
                    to_num = from_num;
                    bool barrier = false;
                    for (int i = from_let + 1; i < 7; ++i) {
                        if (chessboard1->Get(i,from_num) != "___"){
                            barrier = true;
                            break;
                        }
                    }
                    if (!barrier){
                        bool danger = false;
                        for (int i = from_let + 1; i < 7; ++i) {
                            if (check_danger(name, i, from_num, PlayerSelector, chessboard1, chessboard2, chessboard3, array)){
                                danger = true;
                                break;
                            }
                        }
                        if (!danger){
                            if ((int(chessboard1->Get(7,from_num)[0])-48 == 4) and
                                (!array[call(chessboard1->Get(7,from_num))].get_move())){
                                fill_cell(from_let, from_num, PlayerSelector, chessboard1, chessboard2, chessboard3, array, to_let+2,
                                          to_num, 2, king_flag);
                            }
                        }
                    }


                    barrier = false;
                    for (int i = from_let - 1; i > 0; --i) {
                        if (chessboard1->Get(i,from_num) != "___"){
                            barrier = true;
                            break;
                        }
                    }
                    if (!barrier){
                        bool danger = false;
                        for (int i = from_let - 1; i > 0; --i) {
                            if (check_danger(name, i, from_num, PlayerSelector, chessboard1, chessboard2, chessboard3, array)){
                                danger = true;
                                break;
                            }
                        }
                        if (!danger){
                            if ((int(chessboard1->Get(0,from_num)[0])-48 == 4) and
                                (!array[call(chessboard1->Get(0,from_num))].get_move())){
                                fill_cell(from_let, from_num, PlayerSelector, chessboard1, chessboard2, chessboard3, array, to_let-2,
                                          to_num, 2, king_flag);
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
void fill_matrix(chessboard *chessboard1){
    for (short i = 0; i < 8; ++i) {
        for (short j = 0; j < 8; ++j) {
            chessboard1->Set("___",i,j);
        }
    }
}

/**размещение фигур на матрице(в зависимости от значений flag и flag1) */
void fill_matrix_piece(chessboard *chessboard1, chessboard *chessboard2, chessboard *chessboard3, piece array[], bool flag, bool flag1){
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
                    piece_color += "_C";
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
                chessboard2->Set(piece_color, posLet, posNum);
            }
        }
    }
}

bool switch_check(std::string name, bool check){

    return true;
}

int main(){
    SetConsoleOutputCP(CP_UTF8);
    bool switch_mod = true;
    std::cout << "Выберите режим\n";
    std::cin >> switch_mod;
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
    chessboard chessboard2; //предсказательная для короля
    chessboard chessboard3; //предсказательная
    short PlayerSelector = -1; //переменная вокруг которой построенно определение кто сейчас ходит
    bool check = false;
    bool check_mate = false;
    std::string name_enemy = "___";
    if (!switch_mod){

        for (short i = 0; i < 32; ++i) {
            array[i].kill();
        }

        fill_matrix(&chessboard1);

        fill_matrix(&chessboard3);

        fill_matrix(&chessboard2);

        fill_matrix_piece(&chessboard1, &chessboard2, &chessboard3, array, true, true);
        chessboard3.render_view();

        /** Пофиксить баг с перестановкой фигуры */
        bool switcher = true;
        std::cout << "Выберите мод\n";
        std::cin>> switcher;
        if(switcher){
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
                    fill_matrix(&chessboard1);
                    fill_matrix(&chessboard3);
                    fill_matrix(&chessboard2);
                }
                if (from_pos == "-1") {
                    array[i].revive();
                } else {
                    from_let = from_pos[0] - 65;
                    from_num = from_pos[1] - 49;
                    if (from_let > 8) from_let -= 32;
                    fill(array, i, from_let, from_num, name);
                }

                fill_matrix_piece(&chessboard1, &chessboard2, &chessboard3, array, true, true);
                chessboard3.render_view();
                std::cout << "Хотите ли вы добавить новую фигуру?\n";
                std::cin >> add_new_piece;
            }
        }else{
            fill(array, 31, 4, 0, "611");
            fill(array, 7, 3, 6, "108");
            fill(array, 8, 4, 3, "111");
            fill(array, 9, 1, 1, "112");
            fill(array, 22, 1, 0, "311");
            fill(array, 23, 6, 0, "312");
            fill(array, 30, 4, 7, "601");
            fill(array, 28, 0, 4, "501");
            fill(array, 29, 3, 0, "511");
            fill(array, 24, 0, 7, "401");
            fill(array, 25, 7, 7, "402");
            fill(array, 26, 0, 0, "411");
            fill(array, 27, 7, 0, "412");
            fill_matrix_piece(&chessboard1, &chessboard2, &chessboard3, array, true, true);
            chessboard3.render_view();
        }
    }

    std::string from_pos, to_pos;

    short from_let, from_num, to_let, to_num;

    while((from_pos != "-1") or !check_mate){

        /**заполнение подложной матрицы*/
        fill_matrix(&chessboard1);
        /**заполнение предсказательной матрицы*/
        fill_matrix(&chessboard3);
        /**заполнение предсказательной матрицы для короля*/
        fill_matrix(&chessboard2);

        /**размещение фигур*/
        fill_matrix_piece(&chessboard1, &chessboard2, &chessboard3, array, true, true);

        std::cout << (PlayerSelector == -1 ? "Ход Белых\n" : "Ход Чёрных\n");

        //chessboard1.render_predict();
        chessboard3.render_view();
        short first_piece, second_piece;
        bool l = false;
        /*
        if (check){
            std::cout<< "шах\n";
            std::string king_name;
            (PlayerSelector == -1 ? king_name = "611" : king_name = "601");

        }*/
        std::cin >> from_pos;
        from_let = from_pos[0] - 65;
        from_num = from_pos[1] - 49;
        if (from_let > 8) from_let -= 32;

        do{
            /**перезаполнение предсказательной матрицы*/
            fill_matrix(&chessboard3);

            /**переразмещение фигур на предсказательной матрице*/
            fill_matrix_piece(&chessboard1, &chessboard2, &chessboard3, array, false, true);


            /**перевод координат*/
            from_let = from_pos[0] - 65;
            from_num = from_pos[1] - 49;
            if (from_let > 8) from_let -= 32;

            if (!array[32].get_death()) {
                short temp_let, temp_num;
                std::string temp_name;
                array[32].get(&temp_let,&temp_num);
                array[32].get(&temp_name);
                if (chessboard1.Get(from_let,from_num)[0] == '1') {
                    chessboard1.Set(temp_name, temp_let, temp_num);
                } else {
                    chessboard1.Set("___", temp_let, temp_num);
                }
            }

            if (chessboard1.Get(from_let,from_num)[1] != '_'){
                bool FirstPieceColor = array[call(chessboard1.Get(from_let,from_num))].get_color();
                if((int(FirstPieceColor) == -1 * PlayerSelector) or (PlayerSelector > int(FirstPieceColor))) {

                    steps_prediction(from_let, from_num, PlayerSelector, &chessboard1, &chessboard2, &chessboard3, array, false);

                    //chessboard2.render_predict();
                    chessboard3.render_predict();

                    /**перевод координат*/
                    std::cin >> to_pos;
                    to_let = to_pos[0] - 65;
                    to_num = to_pos[1] - 49;
                    if (to_let > 8)
                        to_let -= 32;

                    first_piece = call(chessboard1.Get(from_let,from_num));
                    std::string name_enemy_king = "___";
                    if ((-1 < from_let < 8) and (-1 < from_num < 8) and (-1 < to_let < 8) and (-1 < to_num < 8)) {
                        if (chessboard3.Get(to_let, to_num)[1] != '_') {

                            if (chessboard3.Get(to_let, to_num)[1] == 'X') {
                                array[second_piece].killer(to_let, to_num, &chessboard1, array);
                                array[first_piece].mover(from_let, from_num, to_let, to_num, &PlayerSelector,
                                                         &chessboard1, array);
                                (PlayerSelector == -1 ? name_enemy_king = "611" : name_enemy_king = "601");
                                short king_let, king_num;
                                array[call(name_enemy_king)].get(&king_let, &king_num);
                                if (check_danger(name_enemy_king,king_let, king_num,PlayerSelector,&chessboard1,&chessboard2,&chessboard3,array)){
                                    check = true;
                                    name_enemy = chessboard1.Get(from_let,from_num);
                                }
                                l = true;
                            } else if (chessboard3.Get(to_let, to_num)[1] == 'O'){
                                array[first_piece].mover(from_let, from_num, to_let, to_num, &PlayerSelector,
                                                         &chessboard1, array);
                                std::string name_castle;
                                if (to_let/4){
                                    name_castle = chessboard1.Get(7,to_num);
                                    array[call(name_castle)].mover(7, from_num, 5, to_num, &PlayerSelector,
                                                                                 &chessboard1, array);
                                }else{
                                    name_castle = chessboard1.Get(0,to_num);
                                    array[call(name_castle)].mover(0, from_num, 3, to_num, &PlayerSelector,
                                                                                 &chessboard1, array);
                                }
                                PlayerSelector *= -1;
                                (PlayerSelector == -1 ? name_enemy_king = "611" : name_enemy_king = "601");
                                short king_let, king_num;
                                array[call(name_enemy_king)].get(&king_let, &king_num);
                                if (check_danger(name_enemy_king,king_let, king_num,PlayerSelector,&chessboard1,&chessboard2,&chessboard3,array)){
                                    check = true;
                                    name_enemy = name_castle;
                                }

                                l = true;
                            }else{
                                array[first_piece].mover(from_let, from_num, to_let, to_num, &PlayerSelector,
                                                         &chessboard1, array);
                                (PlayerSelector == -1 ? name_enemy_king = "611" : name_enemy_king = "601");
                                short king_let, king_num;
                                array[call(name_enemy_king)].get(&king_let, &king_num);
                                if (check_danger(name_enemy_king,king_let, king_num,PlayerSelector,&chessboard1,&chessboard2,&chessboard3,array)){
                                    check = true;
                                    name_enemy = chessboard1.Get(from_let,from_num);
                                }
                                l = true;
                            }


                        } else {
                            bool first_color = array[call(chessboard1.Get(from_let, from_num))].get_color();
                            if (int(chessboard1.Get(to_let, to_num)[1])-48 == first_color) {
                                from_pos = to_pos;
                            }else std::cout << "Попробуйте другой ход\n";
                        }
                    } else std::cout << "Выход за границы доски";

                }else{
                    std::cout << "Куда вне очереди\n";
                    l = true;
                }
            }else{
                std::cout << "Выберите фигуру\n";\
                l = true;
            }

        }while (!l);

    }

    return 0;
}
//Надо провести рефакторинг кода
//d2 d4 g7 g6 a2 a4 f8 h6 e1 f2 f3 e8 f8 e2 e4 h6