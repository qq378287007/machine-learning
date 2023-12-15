#include "utlis.h"

vector<double> readTxt(const string &file_data)
{
    vector<double> read_vec;
    ifstream infile;
    infile.open(file_data);
    assert(infile.is_open());
    double tmp;
    while (!infile.eof())
    {
        infile >> tmp;
        read_vec.push_back(tmp);
    }
    infile.close();
    return read_vec;
}

vector<vector<double>> getTrainData(int features_size, const vector<double> &read_vec)
{
    int n = features_size;
    unsigned int m = read_vec.size() / n;
    vector<vector<double>> train_data(m);
    int i = 0;
    for (vector<double> &vec : train_data)
    {
        for (int j = 0; j < n; j++)
            vec.push_back(read_vec[i + j]);
        i += n;
    }
    return train_data;
}

void showData(const vector<vector<double>> &data)
{
    int i = 0;
    for (const vector<double> &d : data)
    {
        cout << i << " | ";
        for (double num : d)
            cout << num << " ";
        cout << endl;
        i++;
    }
}

int random_unint(unsigned int max, unsigned int seed = 0)
{
    static default_random_engine e(seed);
    static uniform_int_distribution<int> u(0, max - 1);
    return u(e);
}

vector<int> generate_random(int sample_size, int batch_size)
{
    vector<int> gen_index(static_cast<unsigned int>(batch_size));
    for (int i = 0; i < batch_size; ++i)
        gen_index[i] = random_unint(static_cast<unsigned int>(sample_size), static_cast<unsigned int>(time(nullptr)));
    return gen_index;
}

void confusion_matrix(const vector<double> &y_true, const vector<double> &y_pred, double threshold)
{
    cout << "== The confusion Matrix == " << endl;
    vector<vector<double>> CM(2, vector<double>(2));
    for (int i = 0; i < y_true.size(); i++)
    {
        double predict = y_pred[i] > threshold ? 1.0 : 0.0;
        if (predict == 0 && y_true[i] == 0)
            CM[0][0] += 1;
        else if (predict == 1 && y_true[i] == 1)
            CM[1][1] += 1;
        else if (predict == 0 && y_true[i] == 1)
            CM[1][0] += 1;
        else if (predict == 1 && y_true[i] == 0)
            CM[0][1] += 1;
    }
    cout << "          | y_pred = 0 | y_pred = 1 | " << endl;
    for (int i = 0; i < 2; i++)
    {
        cout << "y_true = " << i << "|";
        for (int j = 0; j < 2; j++)
            cout << "      " << CM[i][j] << "     ";
        cout << "|" << endl;
    }
}