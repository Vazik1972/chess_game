#include <iostream>
#include <string>
#include <Windows.h>



//теперь я проверяю


class piece;
int call(std::string name);

class chessboard{
public:

    void render(){
        if (matrix[1][1].length() == 2){
            for (int i = 7; i > -1; --i) {
                std::cout << i+1 << "  ";
                for (int j = 0; j < 8; ++j) {
                    std::cout << matrix[j][i] << " ";
                }
                std::cout << "\n";
            }
            std::cout << "  ";
            for (int i = 0; i < 8; ++i) {
                std::cout << " " << char(i + 65) << " ";
            }
            std::cout << "\n";
        }else{
            for (int i = 7; i > -1; --i) {
                std::cout << i+1 << "  ";
                for (int j = 0; j < 8; ++j) {
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

    }

    void Set(std::string vec, int i, int j){
        matrix[i][j] = vec;
    }

    std::string Get(int i, int j){
        return matrix[i][j];
    }
private:
    int len = 8, shir = 8;
    std::string matrix[8][8];
};


class piece
{

public:
    piece(int posLet, int posNum, std::string name){
        this->posNum = posNum;
        this->posLet = posLet;
        this->name = name;
    }

    piece(){

    }
//Вань
//давай будем комментить логические блоки
//а то я вообще не ориентируюсь
//ок

//пока не починил
//хавать не работает((

    void movement(int from_let, int from_num, int to_let, int to_num, int *PlayerSel, chessboard *chessboard1, piece array[32]) {
        int switch_piece = int(name[0]) - 48;
        bool color = int(chessboard1->Get(from_let, from_num)[1]) - 48;
        switch (switch_piece) {
            case 1: {
                if (*PlayerSel * from_num > *PlayerSel * to_num) {
                    if (((to_num - from_num) == *PlayerSel * -1) and
                        ((to_let - from_let == 1) or (to_let - from_let == -1))) {
                        if (chessboard1->Get(to_let, to_num)[1] != '_') {
                            int first_piece = call(chessboard1->Get(from_let, from_num));
                            int second_piece = call(chessboard1->Get(to_let, to_num));
                            if (array[first_piece].color != array[second_piece].color) {
                                this->moveCheck = 1;
                                array[first_piece].set(to_let, to_num);
                                array[second_piece].kill();
                                *PlayerSel *= -1;
                            } else {
                                std::cout << "Попробуйте другой ход\n";
                            }

                        } else {
                            std::cout << "Попробуйте другой ход\n";
                        }

                        //eat
                    } else {
                        if (moveCheck) {
                            if (color) {
                                if ((from_let == to_let) and (from_num + 1 == to_num)) {
                                    if (chessboard1->Get(to_let, to_num)[1] == '_') {
                                        int first_piece = call(chessboard1->Get(from_let, from_num));
                                        array[first_piece].set(to_let, to_num);
                                        chessboard1->Set("___", from_let, from_num);
                                        *PlayerSel *= -1;
                                    } else {
                                        std::cout << "Попробуйте другой ход\n";
                                    }
                                }
                            } else {
                                if ((from_let == to_let) and (from_num - 1 == to_num)) {
                                    if (chessboard1->Get(to_let, to_num)[1] == '_') {
                                        int first_piece = call(chessboard1->Get(from_let, from_num));
                                        array[first_piece].set(to_let, to_num);
                                        chessboard1->Set("___", from_let, from_num);
                                        *PlayerSel *= -1;
                                    } else {
                                        std::cout << "Попробуйте другой ход\n";
                                    }
                                }
                            }
                        } else {
                            if (color) {
                                if ((from_let == to_let) and ((from_num + 1 == to_num) or (from_num + 2 == to_num))) {
                                    if (chessboard1->Get(to_let, to_num)[1] == '_') {
                                        if (to_num - from_num == 2) {
                                            if (chessboard1->Get(to_let, to_num - 1)[1] == '_') {
                                                this->moveCheck = 1;
                                                int first_piece = call(chessboard1->Get(from_let, from_num));
                                                array[first_piece].set(to_let, to_num);
                                                chessboard1->Set("___", from_let, from_num);
                                                *PlayerSel *= -1;
                                            } else {
                                                std::cout << "Не перепрыгиваем\n";
                                            }
                                        } else {
                                            this->moveCheck = 1;
                                            int first_piece = call(chessboard1->Get(from_let, from_num));
                                            array[first_piece].set(to_let, to_num);
                                            chessboard1->Set("___", from_let, from_num);
                                            *PlayerSel *= -1;
                                        }

                                    } else {
                                        std::cout << "Попробуйте другой ход\n";
                                    }
                                }
                            } else {
                                if ((from_let == to_let) and ((from_num - 1 == to_num) or (from_num - 2 == to_num))) {
                                    if (chessboard1->Get(to_let, to_num)[1] == '_') {
                                        if (to_num - from_num == -2) {
                                            if (chessboard1->Get(to_let, to_num + 1)[1] == '_') {
                                                this->moveCheck = 1;
                                                int first_piece = call(chessboard1->Get(from_let, from_num));
                                                array[first_piece].set(to_let, to_num);
                                                chessboard1->Set("___", from_let, from_num);
                                                *PlayerSel *= -1;
                                            } else {
                                                std::cout << "Не перепрыгиваем\n";
                                            }
                                        } else {
                                            this->moveCheck = 1;
                                            int first_piece = call(chessboard1->Get(from_let, from_num));
                                            array[first_piece].set(to_let, to_num);
                                            chessboard1->Set("___", from_let, from_num);
                                            *PlayerSel *= -1;
                                        }
                                    } else {
                                        std::cout << "Попробуйте другой ход\n";

                                    }
                                }
                            }
                        }
                    }

                } else {
                    std::cout << "Попробуйте другой ход\n";
                }

                break;
            }
            case 2: {
                this->moveCheck = 1;
                int first_piece = call(chessboard1->Get(from_let, from_num));
                array[first_piece].set(to_let, to_num);
                chessboard1->Set("___", from_let, from_num);
                *PlayerSel *= -1;
                break;
            }
            case 3: {
                this->moveCheck = 1;
                int first_piece = call(chessboard1->Get(from_let, from_num));
                array[first_piece].set(to_let, to_num);
                chessboard1->Set("___", from_let, from_num);
                *PlayerSel *= -1;
                break;
            }
            case 4: {
                this->moveCheck = 1;
                int first_piece = call(chessboard1->Get(from_let, from_num));
                array[first_piece].set(to_let, to_num);
                chessboard1->Set("___", from_let, from_num);
                *PlayerSel *= -1;
                break;
            }
            case 5: {
                this->moveCheck = 1;
                int first_piece = call(chessboard1->Get(from_let, from_num));
                array[first_piece].set(to_let, to_num);
                chessboard1->Set("___", from_let, from_num);
                *PlayerSel *= -1;
                break;
            }
            case 6: {
                this->moveCheck = 1;
                int first_piece = call(chessboard1->Get(from_let, from_num));
                array[first_piece].set(to_let, to_num);
                chessboard1->Set("___", from_let, from_num);
                *PlayerSel *= -1;
                break;
            }

            default: {
                std::cout << "Попробуйте другой ход\n";
                break;
            }
        }
    }

    bool steps_prediction(int from_let, int from_num, int to_let, int to_num, int PlayerSel, chessboard *chessboard1, piece array[32]){
        int switch_piece = int(name[0]) - 48;
        bool switcher = 0;
        bool color = int(chessboard1->Get(from_let, from_num)[1]) - 48;
        switch (switch_piece) {
            case 1: {
                if (((to_num - from_num) == PlayerSel * -1) and
                    ((to_let - from_let == 1) or (to_let - from_let == -1))) {
                    if (chessboard1->Get(to_let, to_num)[1] != '_') {
                        int first_piece = call(chessboard1->Get(from_let, from_num));
                        int second_piece = call(chessboard1->Get(to_let, to_num));
                        if (array[first_piece].color != array[second_piece].color) {
                            switcher = 1;
                        }

                    }

                } else {
                    if (moveCheck) {
                        if (color) {
                            if ((from_let == to_let) and (from_num + 1 == to_num)) {
                                if (chessboard1->Get(to_let, to_num)[1] == '_') {
                                    switcher = 1;
                                }
                            }
                        } else {
                            if ((from_let == to_let) and (from_num - 1 == to_num)) {
                                if (chessboard1->Get(to_let, to_num)[1] == '_') {
                                    switcher = 1;
                                }
                            }
                        }
                    } else {
                        if (color) {
                            if ((from_let == to_let) and ((from_num + 1 == to_num) or (from_num + 2 == to_num))) {
                                if (chessboard1->Get(to_let, to_num)[1] == '_') {
                                    if (to_num - from_num == 2) {
                                        if (chessboard1->Get(to_let, to_num - 1)[1] == '_') {
                                            switcher = 1;
                                        }
                                    } else {
                                        switcher = 1;
                                    }

                                }
                            }
                        } else {
                            if ((from_let == to_let) and ((from_num - 1 == to_num) or (from_num - 2 == to_num))) {
                                if (chessboard1->Get(to_let, to_num)[1] == '_') {
                                    if (to_num - from_num == -2) {
                                        if (chessboard1->Get(to_let, to_num + 1)[1] == '_') {
                                            switcher = 1;
                                        }
                                    } else {
                                        switcher = 1;
                                    }
                                }
                            }
                        }
                    }
                }


                break;
            }
            case 2: {

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
        return switcher;
    }

    void check_eat_ability(){

    }

    void get(bool *color){
        *color = this->color;
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
        this->death = 1;
    }

    void set(int posLet, int posNum, std::string name, bool moveCheck, bool color){
        this->posLet = posLet;
        this->posNum = posNum;
        this->name = name;
        this->moveCheck = moveCheck;
        this->color = color;
        this->death = 0;
    }

    void set(int posLet, int posNum){
        this->posLet = posLet;
        this->posNum = posNum;
    }


private:
    bool color, moveCheck, death;
    short posLet, posNum, type;
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


void foo(piece array[], int i, int Let, int Num, std::string Name){
    bool color = int(Name[1]) - 48;
    array[i].set(Let, Num, Name, 0, color);
}

int call(std::string name){
    bool color = name[1] - 48;
    short piece_ord = name[2] - 48;
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

void predict(int from_let, int from_num, int PlayerSel, chessboard *chessboard1, chessboard *chessboard2, chessboard *chesboard3, piece array[32]){
    int switch_piece = int(chessboard1->Get(from_let,from_num)[0]) - 48;
    bool color = int(chessboard1->Get(from_let, from_num)[1]) - 48;
    switch (switch_piece) {
        case 1: {
                int tolet = from_let;
                int tonum = from_num + (-1 * PlayerSel);
                if (array[call(chessboard1->Get(from_let,from_num))].steps_prediction(from_let,from_num,tolet,tonum, PlayerSel,chessboard1,array)){
                    std::string name2 = chessboard2->Get(tolet,tonum), name3 = "___";
                    name3[0] = name2[0];
                    name3[1] = '$';
                    name3[2] = name2[1];
                    chesboard3->Set(name3,tolet,tonum);
                }
                tolet = from_let;
                tonum = from_num + (-2 * PlayerSel);
                if (array[call(chessboard1->Get(from_let,from_num))].steps_prediction(from_let,from_num,tolet,tonum, PlayerSel,chessboard1,array)){
                    std::string name2 = chessboard2->Get(tolet,tonum), name3 = "___";
                    name3[0] = name2[0];
                    name3[1] = '$';
                    name3[2] = name2[1];
                    chesboard3->Set(name3,tolet,tonum);
                }
                tolet = from_let + 1;
                tonum = from_num + (-1 * PlayerSel);
                if (array[call(chessboard1->Get(from_let,from_num))].steps_prediction(from_let,from_num,tolet,tonum, PlayerSel,chessboard1,array)){
                    std::string name2 = chessboard2->Get(tolet,tonum), name3 = "___";
                    name3[0] = name2[0];
                    name3[1] = '$';
                    name3[2] = name2[1];
                    chesboard3->Set(name3,tolet,tonum);
                }
                tolet = from_let -1;
                tonum = from_num + (-1 * PlayerSel);
                if (array[call(chessboard1->Get(from_let,from_num))].steps_prediction(from_let,from_num,tolet,tonum, PlayerSel,chessboard1,array)){
                    std::string name2 = chessboard2->Get(tolet,tonum), name3 = "___";
                    name3[0] = name2[0];
                    name3[1] = '$';
                    name3[2] = name2[1];
                    chesboard3->Set(name3,tolet,tonum);
                }

            break;
        }
        case 2: {

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
    piece array[32];
    {
        //пешечки-пушечки
        foo(&array[0], 0, 0, 6, "101");
        foo(&array[0], 1, 1, 6, "102");
        foo(&array[0], 2, 2, 6, "103");
        foo(&array[0], 3, 3, 6, "104");

        foo(&array[0], 4, 4, 6, "105");
        foo(&array[0], 5, 5, 6, "106");
        foo(&array[0], 6, 6, 6, "107");
        foo(&array[0], 7, 7, 6, "108");

        foo(&array[0], 8, 0, 1, "111");
        foo(&array[0], 9, 1, 1, "112");
        foo(&array[0], 10, 2, 1, "113");
        foo(&array[0], 11, 3, 1, "114");

        foo(&array[0], 12, 4, 1, "115");
        foo(&array[0], 13, 5, 1, "116");
        foo(&array[0], 14, 6, 1, "117");
        foo(&array[0], 15, 7, 1, "118");

        //слоники
        foo(&array[0], 16, 2, 7, "201");
        foo(&array[0], 17, 5, 7, "202");
        foo(&array[0], 18, 2, 0, "211");
        foo(&array[0], 19, 5, 0, "212");

        //коники
        foo(&array[0], 20, 1, 7, "301");
        foo(&array[0], 21, 6, 7, "302");
        foo(&array[0], 22, 1, 0, "311");
        foo(&array[0], 23, 6, 0, "312");

        //кастлы
        foo(&array[0], 24, 0, 7, "401");
        foo(&array[0], 25, 7, 7, "402");
        foo(&array[0], 26, 0, 0, "411");
        foo(&array[0], 27, 7, 0, "412");

        //знать
        foo(&array[0], 28, 3, 7, "501");
        foo(&array[0], 29, 3, 0, "511");
        foo(&array[0], 30, 4, 7, "601");
        foo(&array[0], 31, 4, 0, "611");
    }

    chessboard chessboard1;
    chessboard chessboard2;
    chessboard chessboard3;



    int x, y, PlayerSel = -1;
    std::string from_pos, to_pos;
    int from_let, from_num, to_let, to_num;

    while(from_let != -1){
        //заполнение выводной матрицы
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                chessboard2.Set("__",i,j);
            }
        }

        //заполнение подложной матрицы
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                chessboard1.Set("___",i,j);
            }
        }

        //заполнение предсказательной матрицы
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                chessboard3.Set("___",i,j);
            }
        }

        //размещение фигур
        for (int i = 0; i < 32; ++i) {
            int x, y;
            bool color;
            std::string name;
            array[i].get(&color);
            array[i].get(&x, &y);
            array[i].get(&name);
            if (array[i].get_death() == 0){
                int switch_piece = int(name[0]) - 48;
                switch (switch_piece) {
                    case 1:{
                        std::string piece_type = "P";
                        std::string piece_color;
                        if (color){
                            piece_color = "w";
                        }else{
                            piece_color = "b";
                        }

                        chessboard3.Set(piece_color + "_" + piece_type,x,y);
                        chessboard2.Set(piece_color + piece_type,x,y);
                        chessboard1.Set(name,x,y);
                        break;
                    }
                    case 2:{
                        std::string piece_type = "B";
                        std::string piece_color;
                        if (color){
                            piece_color = "w";
                        }else{
                            piece_color = "b";
                        }
                        chessboard3.Set(piece_color + "_" + piece_type,x,y);
                        chessboard2.Set(piece_color + piece_type,x,y);
                        chessboard1.Set(name,x,y);
                        break;
                    }
                    case 3:{
                        std::string piece_type = "N";
                        std::string piece_color;
                        if (color){
                            piece_color = "w";
                        }else{
                            piece_color = "b";
                        }
                        chessboard3.Set(piece_color + "_" + piece_type,x,y);
                        chessboard2.Set(piece_color + piece_type,x,y);
                        chessboard1.Set(name,x,y);
                        break;
                    }
                    case 4:{
                        std::string piece_type = "C";
                        std::string piece_color;
                        if (color){
                            piece_color = "w";
                        }else{
                            piece_color = "b";
                        }
                        chessboard3.Set(piece_color + "_" + piece_type,x,y);
                        chessboard2.Set(piece_color + piece_type,x,y);
                        chessboard1.Set(name,x,y);
                        break;
                    }
                    case 5:{
                        std::string piece_type = "Q";
                        std::string piece_color;
                        if (color){
                            piece_color = "w";
                        }else{
                            piece_color = "b";
                        }
                        chessboard3.Set(piece_color + "_" + piece_type,x,y);
                        chessboard2.Set(piece_color + piece_type,x,y);
                        chessboard1.Set(name,x,y);
                        break;
                    }
                    case 6:{
                        std::string piece_type = "K";
                        std::string piece_color;
                        if (color){
                            piece_color = "w";
                        }else{
                            piece_color = "b";
                        }
                        chessboard3.Set(piece_color + "_" + piece_type,x,y);
                        chessboard2.Set(piece_color + piece_type,x,y);
                        chessboard1.Set(name,x,y);
                        break;
                    }

                    default:{
                        chessboard3.Set(name,x,y);
                        chessboard2.Set(name,x,y);
                        chessboard1.Set(name,x,y);
                        break;
                    }
                }
            }


        }

        if (PlayerSel == -1){
            std::cout << "Ход Белых\n";
        } else {
            std::cout << "Ход Чёрных\n";
        }
        //chessboard1.render();
        chessboard2.render();
        int first_piece, second_piece;
        //чтение и перевод координат
        int l = 0;
        std::cin >> from_pos;
        do{
            from_let = from_pos[0] - 65;
            from_num = from_pos[1] - 49;
            if (from_let > 8)
                from_let -= 32;
            if (chessboard1.Get(from_let,from_num)[1] != '_'){
                int fir_color = array[call(chessboard1.Get(from_let,from_num))].get_color();
                if((int(fir_color) == -1 * PlayerSel) or (PlayerSel > int(fir_color))) {
                    predict(from_let, from_num, PlayerSel, &chessboard1, &chessboard2, &chessboard3, array);
                    chessboard3.render();
                    //заполнение предсказательной матрицы
                    for (int i = 0; i < 8; ++i) {
                        for (int j = 0; j < 8; ++j) {
                            chessboard3.Set("___",i,j);
                        }
                    }
                    //размещение фигур
                    for (int i = 0; i < 32; ++i) {
                        int x, y;
                        bool color;
                        std::string name;
                        array[i].get(&color);
                        array[i].get(&x, &y);
                        array[i].get(&name);
                        if (array[i].get_death() == 0){
                            int switch_piece = int(name[0]) - 48;
                            switch (switch_piece) {
                                case 1:{
                                    std::string piece_type = "P";
                                    std::string piece_color;
                                    if (color){
                                        piece_color = "w";
                                    }else{
                                        piece_color = "b";
                                    }

                                    chessboard3.Set(piece_color + "_" + piece_type,x,y);
                                    chessboard2.Set(piece_color + piece_type,x,y);
                                    chessboard1.Set(name,x,y);
                                    break;
                                }
                                case 2:{
                                    std::string piece_type = "B";
                                    std::string piece_color;
                                    if (color){
                                        piece_color = "w";
                                    }else{
                                        piece_color = "b";
                                    }
                                    chessboard3.Set(piece_color + "_" + piece_type,x,y);
                                    chessboard2.Set(piece_color + piece_type,x,y);
                                    chessboard1.Set(name,x,y);
                                    break;
                                }
                                case 3:{
                                    std::string piece_type = "N";
                                    std::string piece_color;
                                    if (color){
                                        piece_color = "w";
                                    }else{
                                        piece_color = "b";
                                    }
                                    chessboard3.Set(piece_color + "_" + piece_type,x,y);
                                    chessboard2.Set(piece_color + piece_type,x,y);
                                    chessboard1.Set(name,x,y);
                                    break;
                                }
                                case 4:{
                                    std::string piece_type = "C";
                                    std::string piece_color;
                                    if (color){
                                        piece_color = "w";
                                    }else{
                                        piece_color = "b";
                                    }
                                    chessboard3.Set(piece_color + "_" + piece_type,x,y);
                                    chessboard2.Set(piece_color + piece_type,x,y);
                                    chessboard1.Set(name,x,y);
                                    break;
                                }
                                case 5:{
                                    std::string piece_type = "Q";
                                    std::string piece_color;
                                    if (color){
                                        piece_color = "w";
                                    }else{
                                        piece_color = "b";
                                    }
                                    chessboard3.Set(piece_color + "_" + piece_type,x,y);
                                    chessboard2.Set(piece_color + piece_type,x,y);
                                    chessboard1.Set(name,x,y);
                                    break;
                                }
                                case 6:{
                                    std::string piece_type = "K";
                                    std::string piece_color;
                                    if (color){
                                        piece_color = "w";
                                    }else{
                                        piece_color = "b";
                                    }
                                    chessboard3.Set(piece_color + "_" + piece_type,x,y);
                                    chessboard2.Set(piece_color + piece_type,x,y);
                                    chessboard1.Set(name,x,y);
                                    break;
                                }

                                default:{
                                    chessboard3.Set(name,x,y);
                                    chessboard2.Set(name,x,y);
                                    chessboard1.Set(name,x,y);
                                    break;
                                }
                            }
                        }


                    }

                    std::cin >> to_pos;
                    to_let = to_pos[0] - 65;
                    to_num = to_pos[1] - 49;
                    if (to_let > 8)
                        to_let -= 32;
                    if (chessboard1.Get(to_let, to_num)[1] != '_'){
                        int sec_color = array[call(chessboard1.Get(to_let,to_num))].get_color();
                        if (fir_color != sec_color) {
                            first_piece = call(chessboard1.Get(from_let,from_num));
                            if ((-1 < from_let < 8) and (-1 < from_num < 8) and (-1 < to_let < 8) and (-1 < to_num < 8)) {
                                array[first_piece].movement(from_let, from_num, to_let, to_num, &PlayerSel, &chessboard1, array);
                                l=1;
                            } else
                                std::cout << "Выход за границы доски";
                        }else{
                            from_pos = to_pos;
                        }
                    }else{
                        first_piece = call(chessboard1.Get(from_let,from_num));
                        if ((-1 < from_let < 8) and (-1 < from_num < 8) and (-1 < to_let < 8) and (-1 < to_num < 8)) {
                            array[first_piece].movement(from_let, from_num, to_let, to_num, &PlayerSel, &chessboard1, array);
                            l=1;
                        } else
                            std::cout << "Выход за границы доски";
                    }

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
