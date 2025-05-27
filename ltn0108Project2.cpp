#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <cctype>
#include <stdio.h>
#include <cmath>
#include <unistd.h>
using namespace std;

enum menu{Match = 1, Display = 2, Giveup = 3, Exit = 4};
const int GRID_SIZE = 4;
void getName(){
    string name;
    cout << "Enter your name: ";
    getline(cin, name);

    //general checking loop
    while (true) {
        bool flag = true;
        // looping through the characters in the name
        for (int i = 0; i < name.size(); i++){
            // if your name isn't alphabet or space it is invalid 
            if (!isalpha(name[i]) && !isspace(name[i])){
                cout << "Your name can only have alphabets or spaces. Enter again." << endl;
                flag = false;
                break; // break the for loop 
            }
        }
        if (flag == true){
            for (int j = 0; j < name.size(); j++){ //first initial always capitalized
                if (j==0){
                    name[j] = toupper(name[j]);
                }
                else if ((j > 0) &&(isspace(name[j-1]))){ //second initial
                    name[j] = toupper(name[j]);
                }
            }
            cout << "Welcome " << name << "!" << endl;
            break;
        }
        else {
            cout << "Enter your name: ";
            getline(cin, name);
        
        }
    }
}

int getRandomIndex(){
    return rand() % GRID_SIZE + 0; 
}

void Shuffle(int cardsInfo[][GRID_SIZE]){
    for (int i = 0; i < 15; i++){
        //first card
        int x1 = getRandomIndex();
        int y1 = getRandomIndex();
        //second card
        int x2 = getRandomIndex();
        int y2 = getRandomIndex();

        int temp = cardsInfo[x1][y1];
        cardsInfo[x1][y1] = cardsInfo[x2][y2];
        cardsInfo[x2][y2] = temp;
    }
}

void initialize(int arrangement[][GRID_SIZE], int status[][GRID_SIZE]){
    //arrangement of the cards
    int card = 1;
    for (int i = 0; i < GRID_SIZE; i++){
        for (int j = 0; j < GRID_SIZE; j++){
            arrangement[i][j] = card;
            card++;
            if (card > 8){
                card = 1;
            }
        }
    }
    //Set the status to 0
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            status[i][j] = 0; // 0 means face down
        }
    }
    Shuffle(arrangement);
}

void showCards(int arrangement[][GRID_SIZE], int status[][GRID_SIZE], bool showReal = false){
    for (int i = 0; i < GRID_SIZE; i++){
        for (int j = 0; j < GRID_SIZE; j++){
            if (showReal == true){
                cout << arrangement[i][j] << " ";
            }
            else{
                if (status[i][j] == 1){
                    cout << arrangement[i][j] << " ";
                }
                else{
                    cout <<"* ";
                }
            }
        }
        cout << endl;
    }
}

bool allFaceUp(int status[][GRID_SIZE]){
    for (int i = 0; i < GRID_SIZE; i++){
        for (int j = 0; j < GRID_SIZE; j++){
            if (status[i][j] == 0){
                return false;
            }
        }
    }
    return true;
}

bool checkInputs(int x, int y, int status[][GRID_SIZE]){
    if ((x >=0) && (x < GRID_SIZE) && (y >= 0) && (y < GRID_SIZE)){
        if (status[x][y] == 0){
            return true;
        }
    }
    return false;
}

void match(int arrangement[][GRID_SIZE], int status[][GRID_SIZE], int points){
    showCards(arrangement,status);
    int x1,y1,x2,y2;

    //coordinate of the first card
    cout <<"What is the x coordinates of the first card? ";
    cin >> x1;
    cout <<"What is the y coordinates of the first card? ";
    cin >> y1;

    //coordinates of the second card
    cout << "What is the x coordinate of the second card? ";
    cin >> x2;
    cout <<"What is the y coordinates of the second card? ";
    cin >> y2;
    bool Firstcard = checkInputs(x1,y1,status);
    bool Secondcard = checkInputs(x2,y2,status);
    //checking the coordinates
    if (Firstcard == false || Secondcard == false){
        cout << "You enter the wrong coordinates" << endl;
        return;
    }
    //checking the status of the cards
    if (status[x1][y1] == 1 || status[x2][y2] == 1){
        cout <<"One or both cards are already face up. Please try again." << endl;
        return;
    }
    //checking if two cards are the same
    if (x1==x2 && y1 == y2){
        cout << "The coordinates of the two cards must be different. Please try again" << endl;
        return;
    }

    //extract card value
    int card1 = arrangement[x1][y1];
    int card2 = arrangement[x2][y2];
    if (card1 == card2){
        cout <<"Congratulations, it's a match!";
        status[x1][y1] = 1;
        status[x2][y2] = 1;
        points += 5;
    }
    else{
        cout << "No match!" << endl;
        status[x1][y1] = 1;
        status[x2][y2] = 1;
        showCards(arrangement,status);
        sleep(5);
        system("cls");
        status[x1][y1] = 0;
        status[x2][y2] = 0;
        points -= 1;
    }

}

void display(int arrangement[][GRID_SIZE], int status[][GRID_SIZE], int points){
    if (points < 10){
        cout << "Insufficient point! You need to have at least 10 points" << endl;
        return;
    }
    points -= 10;
    cout << "Your current points: " << points << endl;
    for (int i = 0; i < GRID_SIZE; i++){
        for (int j = 0; j < GRID_SIZE; j++){
            if (status[i][j] == 1){
                 continue;
            }
            int cardvalue = arrangement[i][j];
            for (int x = 0; x < GRID_SIZE; x++){
                for (int y = 0; y < GRID_SIZE; y++){
                    if ((x == i && y == j) || status[x][y] == 1){
                        continue;
                    }

                    if (arrangement[x][y] == cardvalue){
                        status[i][j] = 1;
                        status[x][y] = 1;
                        cout << "Identical pair found!" << endl;
                        showCards(arrangement, status);
                        return;
                    }
                }
            }
        }
    }
}
int main() {
    //Project detail
    cout << "Computer Science and Engineering" << endl;
    cout << "CSCE 1030 - Computer Science I" << endl;
    cout << "Jack Ngo ltn0108 LongNgo2@my.unt.edu" << endl;
    int arrangement[GRID_SIZE][GRID_SIZE];
    int status[GRID_SIZE][GRID_SIZE];
    int points = 50;
    int selection;
    bool gamecmd = true;
    char playagain;
    srand(time(0));
    // Initialize the game
    initialize(arrangement, status);
    //get name
    getName();
    if (points > 0){
        while (gamecmd == true){
            cout << "1. MATCH" << endl;
            cout << "2. DISPLAY" << endl;
            cout << "3. GIVEUP" << endl;
            cout << "4. EXIT" << endl;
            cout << "Enter your choice: ";
            cin >> selection;
            if (selection > 4){
                cout << "Wrong option!" << endl;
                cout << "Enter your choice: "; 
                cin >> selection; 
            }
            else{
                switch(selection){
                    case Match: {
                        match(arrangement, status, points);
                        
                        if (allFaceUp(status)){
                            cout << "Congratulation! You won the game!" << endl;
                            cout << "Do you want to play again? (y/n) ";
                            
                            cin >> playagain;
                            if (tolower(playagain) == 'y'){
                                initialize(arrangement, status);
                                points = 50;
                            }
                            else{
                                cout << "Thank you for playing! Goodbye" << endl;
                                gamecmd = false;
                            }
                        }
                        break;
                    }

                    case Display: {
                        display(arrangement,status,points);
                        break;
                    }

                    case Giveup: {
                        showCards(arrangement,status,true);
                        cout << "Do you want to play again? (y/n)";
                        cin >> playagain;
                        if (tolower(playagain) == 'y'){
                            initialize(arrangement,status);
                            points = 50;
                        }
                        else{
                            cout <<"Thank you for playing! Goodbye!" << endl;
                            gamecmd = false;
                        }
                        break;
                    }

                    case Exit: {
                        cout << "Thank you for playing! Goodbye!" << endl;
                        gamecmd = false;
                        break;
                    }

                    default: {
                        cout << "You entered the wrong choice! Try again" << endl;
                        break;
                    }
                }
            }
        }
    }
    else{
        cout << "Your points fall below 0! Thank you for playing!" << endl;
    }
    return 0;
}

