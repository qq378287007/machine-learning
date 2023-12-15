#include <memory>
#include "logistic_regression.h"
using namespace nlai;

int main(int argc, char **argv)
{
    cout << "Let's start" << endl;
    vector<double> read_vector = readTxt(argv[1]);
    vector<vector<double>> train_data = getTrainData(5, read_vector);
    showData(train_data);
    shared_ptr<LogisticRegression> lr(new LogisticRegression(4, 2));
    lr->fit(train_data, 32, 0.01, 100, 0.1);
    for (double w : lr->get_weights())
        cout << w << endl;

    cout << lr->get_bias() << endl;
    lr->getData(0, train_data, 32);
    vector<double> y_true = lr->get_y_data();
    vector<double> y_pred = lr->predict(lr->get_x_data());
    confusion_matrix(y_true, y_pred, 0.5);
    return 0;
}