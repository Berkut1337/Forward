﻿#include <iostream>
#include <locale.h>
#define N 6 //Количество кусочно-линейных зависимостей 

using namespace std;

float Сalc_M(float V, float M, float M_arr[], float V_arr[]) //Функция для вычисления M
{
    for (int i = 0; i < N; i++)
    {
        if (V > V_arr[i] && V < V_arr[i + 1])
        {
            float k = (M_arr[i + 1] - M_arr[i]) / (V_arr[i + 1] - V_arr[i]);
            float b = M_arr[i] - k * V_arr[i];
            float M = k * V + b;
            return M;
        }
    }
}


int main()
{
    setlocale(LC_ALL, "Rus"); 

    float I = 10; //Момент инерции двигателя
    float a; //Ускорение двигателя
    float Vh; //Скорость нагрева двигателя 
    float Hm = 0.01; //Коэффициент зависимости скорости нагрева от крутящего момента
    float Hv = 0.0001; //Коэффициент зависимости скорости нагрева от скорости вращения коленвала
    float Vc; //Скорость охлаждения двигателя
    float C = 0.1; //Коэффициент зависимости скорости охлаждения от температуры двигателя и окружающей среды
    float Tc; //Температура окружающей среды
    float Tp = 110; //Температура перегрева
    int seconds = 0; //Время до перегрева
    float M_arr[N] = { 20,75,100,105,75,0 }; //Кусочно-линейная зависимость крутящего момента M
    float V_arr[N] = { 0,75,150,200,250,300 }; //Кусочно-линейная зависимость скорости вращения коленвала V
    float M = M_arr[0]; //Момент инерции двигателя
    float V = V_arr[0]; //Скорость вращения двигателя

    cout << "Tемпература среды = ";
    cin >> Tc;
    float Td = Tc; //Температура двигателя

    while (Td < Tp) //Вычисления времени до перегрева
    {

        a = M / I; //Вычисление ускорения
        V = V + a; //Вычисление скорости
        M = Сalc_M(V, M, M_arr, V_arr); //Вычисление M
        Vh = M * Hm + pow(V, 2) * Hv; //Вычисление скорости нагрева двигателя
        Vc = abs(C * (Tc - Td)); //Вычисление скорости охлаждения двигателя
        Td = Td + Vh - Vc; //Вычисление температуры двигателя
        seconds++; //Время работы двигателя

        if (seconds > 10000)
        {
            cout << "Скорей всего двигатель никогда не нагреется" << "\n";
            return 0;
        }
    }
    cout << "Время до нагрева = " << seconds << " секунд";
    return 0;
}