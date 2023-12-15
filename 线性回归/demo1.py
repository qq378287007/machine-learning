from sklearn.datasets import load_breast_cancer
boston = load_breast_cancer()
X=boston.data
y=boston.target
print(X.shape)
print(y.shape)

from sklearn.model_selection  import train_test_split
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.7)

from sklearn import preprocessing
standard_X = preprocessing.StandardScaler()
X_train = standard_X.fit_transform(X_train)
X_test = standard_X.transform(X_test)

standard_y = preprocessing.StandardScaler()
y_train = standard_y.fit_transform(y_train.reshape(-1,1))
y_test = standard_y.transform(y_test.reshape(-1,1))

from sklearn.linear_model import ElasticNet
ElasticNet_clf = ElasticNet(alpha=0.1, l1_ratio=0.71)
ElasticNet_clf.fit(X_train, y_train.ravel())
ElasticNet_clf_score = ElasticNet_clf.score(X_test, y_test.ravel())
print('lasso模型得分：', ElasticNet_clf_score)
print(ElasticNet_clf.coef_)
print(ElasticNet_clf.intercept_)
print(ElasticNet_clf.n_iter_)
