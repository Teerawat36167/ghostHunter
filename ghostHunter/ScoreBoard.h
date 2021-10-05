#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <utility>
#include <algorithm>
#include <string.h>
#include <vector>
#include <iostream>
using namespace std;

inline void gotoxy(int x, int y) {//go to x,y
    COORD c = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

inline void ScoreBoard(string PlayerName,unsigned int PlayerScore) 
{
    FILE* fp;
    char temp[255];
    unsigned int score[6];
    string name[6];
    vector<pair<unsigned int, string>> userScore;
    fp = fopen("./score.txt", "r");
    for (int i = 0; i < 5; i++)
    {
        fscanf(fp, "%s", &temp);
        name[i] = temp;
        fscanf(fp, "%d", &score[i]);
        userScore.push_back(make_pair(score[i], name[i]));
    }
    name[5] = PlayerName;
    score[5] = PlayerScore;
    userScore.push_back(make_pair(score[5], name[5]));
    sort(userScore.begin(), userScore.end());
    fclose(fp);
    fopen("./score.txt", "w");
    for (int i = 5; i >= 1; i--)
    {
        strcpy(temp, userScore[i].second.c_str());
        fprintf(fp, "%s %d\n", temp, userScore[i].first);
    }
    fclose(fp);
}
inline void scoreUI() {
    FILE* fp;
    char temp[255];
    unsigned int score[5];
    string name[5];
    fp = fopen("./score.txt", "r");
    for (int i = 0; i < 5; i++)
    {
        fscanf(fp, "%s", &temp);
        name[i] = temp;
        fscanf(fp, "%d", &score[i]);
    }
    fclose(fp);
    printf("+_______________________________________________________\n");
    printf("|                                                       \n");
    printf("|                                                       \n");
    printf("|           xxxxx  xxxx  xxxxx  xxxx   xxxxx            \n");
    printf("|           x      x     x   x  x   x  x                \n");
    printf("|           xxxxx  x     x   x  xxxx   xxxxx            \n");
    printf("|               x  x     x   x  x x    x                \n");
    printf("|               x  x     x   x  x  x   x                \n");
    printf("|           xxxxx  xxxx  xxxxx  x   x  xxxxx            \n");
    printf("|                                                       \n");
    printf("|                                                       \n");
    printf("|                                                       \n");
    printf("|                                                       \n");
    printf("|                                                       \n");
    printf("|                                                       \n");
    printf("|                                                       \n");
    printf("|                                                       \n");
    printf("|                                                       \n");
    printf("|                                                       \n");
    printf("|                                                       \n");
    printf("|                                                       \n");
    printf("|                                                       \n");
    printf("|                                                       \n");
    printf("|                                                       \n");
    printf("|                                                       \n");
    printf("|                                                       \n");
    printf("|                                                       \n");
    printf("|                                                       \n");
    gotoxy(18, 10);
    cout << name[0];
    gotoxy(33, 10);
    cout << score[0];
    gotoxy(18, 13);
    cout << name[1];
    gotoxy(33, 13);
    cout << score[1];
    gotoxy(18, 16);
    cout << name[2];
    gotoxy(33, 16);
    cout << score[2];
    gotoxy(18, 19);
    cout << name[3];
    gotoxy(33, 19);
    cout << score[3];
    gotoxy(18, 22);
    cout << name[4];
    gotoxy(33, 22);
    cout << score[4];
    _getch(); //keyboard check
}