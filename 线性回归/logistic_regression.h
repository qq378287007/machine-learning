#pragma once

#include "utlis.h"

namespace nlai
{
    class LogisticRegression
    {
        vector<double> weights;
        double bias;
        unsigned int features_size;
        vector<vector<double>> x_data;
        vector<double> y_data;
        unsigned int label_num;

    public:
        LogisticRegression() = default;
        ~LogisticRegression() = default;
        explicit LogisticRegression(unsigned int features_size, unsigned label_num);

        vector<double> logist(vector<vector<double>> x_data);
        double loss(vector<double> predict_y, vector<double> real_y, unsigned batch_size);
        vector<double> activation_func(vector<double> predict_y);
        void getData(int iter, vector<vector<double>> train_data, unsigned batch_size);
        void fit(vector<vector<double>> train_data, unsigned int batch_size, double error = 0.01, int max_iter = 100, float learning_rate = 0.001);
        vector<double> predict(vector<vector<double>> x_data);

        inline vector<double> get_weights() const { return weights; }
        inline double get_bias() const { return bias; }
        inline vector<vector<double>> get_x_data() const { return x_data; }
        inline vector<double> get_y_data() const { return y_data; }
    };
}
