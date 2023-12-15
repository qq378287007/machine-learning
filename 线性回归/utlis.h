#pragma once

#include <cassert>
#include <vector>
#include <cmath>
#include <fstream>
#include <iostream>
// #include <windows.h>
// #include <unistd.h>
#include <algorithm>
#include <random>
#include <ctime>
using namespace std;

vector<double> readTxt(const string &file_data);
vector<vector<double>> getTrainData(int features_size, const vector<double> &read_vec);
void showData(const vector<vector<double>> &data);
int random_unint(unsigned int batch_size, unsigned int seed);
vector<int> generate_random(int sample_size, int batch_size);
void confusion_matrix(const vector<double> &y_true, const vector<double> &y_pred, double threshold);
