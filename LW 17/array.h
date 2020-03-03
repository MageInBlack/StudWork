#pragma once
#include <iostream>
#include <locale.h>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <ctime>

void input_keyboard(double** array,const int& lines,const int& columns);
int input_file_old(double** array,const int& lines,const int& columns);
int input_file_old_binary(double** array,const int& lines,const int& columns);
int input_file(double** array,const int& lines,const int& columns);
int input_file_binary(double** array,const int& lines,const int& columns);
void input_random(double** array,const int& lines,const int& columns);
void input_formula(double** array,const int& lines,const int& columns);

void output_file_old(double** array,const int& lines,const int& columns);
void output_file_old_binary(double** array,const int& lines,const int& columns);
void output_file(double** array,const int& lines,const int& columns);
void output_file_binary(double** array,const int& lines,const int& columns);

void work_array();
