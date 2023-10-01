// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <fstream>
#include <iostream>
#include <SFML/Audio.hpp>
#include <string>
#include <Windows.h>
using namespace std;


void initializeBoard(char board[][5], int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            board[i][j] = '-';
        }
    }
}

void printBoards(const char playerBoard[][5], const char computerBoard[][5], int size) {
    system("cls");  

    cout << "���� ����:\t\t\t\t\t\t���� ����������:" << endl;
    cout << "  ";
    for (int i = 0; i < size; ++i) {
        cout << i << " ";
    }
    cout << "\t\t\t\t\t\t  ";
    for (int i = 0; i < size; ++i) {
        cout << i << " ";
    }
    cout << endl;

    for (int i = 0; i < size; ++i) {
        cout << i << " ";
        for (int j = 0; j < size; ++j) {
            if (playerBoard[i][j] == 'X') {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); 
            }
            cout << playerBoard[i][j] << " ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);  
        }
        cout << "\t\t\t\t\t\t" << i << " ";
        for (int j = 0; j < size; ++j) {
            if (computerBoard[i][j] == 'X') {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);  
            }
            cout << computerBoard[i][j] << " ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);  
        }
        cout << endl;
    }
    cout << endl;
}

void placeShip(char board[][5], int size) {
    int row, col;
    cout << "������� ���������� ��� ���������� ������� (0-4): ";
    cin >> row >> col;

    if (row < 0 || row >= size || col < 0 || col >= size || board[row][col] == 'X') {
        cout << "������������ ����������. ��������� ����." << endl;
        placeShip(board, size);
    }
    else {
        board[row][col] = 'X';
    }
}

void computerPlaceShips(char board[][5], int size) {
    cout << "��������� ��������� �������:" << endl;
    for (int i = 0; i < size; ++i) {
        int row, col;
        row = rand() % size;
        col = rand() % size;

        while (board[row][col] == 'X') {
            row = rand() % size;
            col = rand() % size;
        }

        board[row][col] = 'X';
    }
}

void computerMove(char playerBoard[][5], int size) {
    int row, col;
    row = rand() % size;
    col = rand() % size;

    if (playerBoard[row][col] == 'X') {
        cout << "��������� ����� �� ������ �������!" << endl;
        playerBoard[row][col] = 'H'; 
    }
    else {
        cout << "��������� �����������." << endl;
        playerBoard[row][col] = 'M'; 
    }
}

bool isGameOver(const char board[][5], int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (board[i][j] == 'X') {
                return false; 
            }
        }
    }
    return true; 
}

void clearScreen() {
    system("cls");
}

int main() {
    srand(time(0));  
    setlocale(LC_ALL, "rus");
    char playerBoard[5][5];
    char computerBoard[5][5];

    initializeBoard(playerBoard, 5);
    initializeBoard(computerBoard, 5);
    sf::SoundBuffer sound;
    sound.loadFromFile("win.ogg");

    sf::Sound WinSound;
     WinSound.setBuffer(sound);
    char restart;
    do {
        clearScreen();

        cout << "���� ����������� ��������:" << endl;
        for (int i = 0; i < 5; ++i) {
            placeShip(playerBoard, 5);
        }

        clearScreen();

        cout << "��� ���:" << endl;

        computerPlaceShips(computerBoard, 5);

        while (!isGameOver(playerBoard, 5) && !isGameOver(computerBoard, 5)) {
            printBoards(playerBoard, computerBoard, 5);

            int row, col;
            cout << "������� ���������� �������� (0-4): ";
            cin >> row >> col;

            if (row < 0 || row >= 5 || col < 0 || col >= 5 || playerBoard[row][col] == 'H' || playerBoard[row][col] == 'M') {
                cout << "������������ ����������. ��������� ����." << endl;
            }
            else {
                if (computerBoard[row][col] == 'X') {
                    cout << "�� ������ �� ������� ����������!" << endl;
                    computerBoard[row][col] = 'H';  
                    WinSound.play();
                }
                else {
                    cout << "�� ������������." << endl;
                    computerBoard[row][col] = 'M'; 
                }

                cout << "��� ����������:" << endl;
                computerMove(playerBoard, 5);
            }
        }

        printBoards(playerBoard, computerBoard, 5);

        if (isGameOver(playerBoard, 5)) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);  
            cout << "�� ���������. ��������� �������" << endl;
        }
        else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);  
            cout << "�� ��������!" << endl;
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);  

        cout << "������ ������� ��� ���? (y/n): ";
        cin >> restart;
        if (restart == 'y' || restart == 'Y') {
            initializeBoard(playerBoard, 5);
            initializeBoard(computerBoard, 5);
        }
    } while (restart == 'y' || restart == 'Y');

   
}