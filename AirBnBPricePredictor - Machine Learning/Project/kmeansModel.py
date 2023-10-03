import pandas as pd
from sklearn.neural_network import MLPRegressor
from sklearn.metrics import confusion_matrix, classification_report, r2_score
from sklearn.metrics import mean_squared_error
from sklearn.model_selection import train_test_split
from sklearn.decomposition import PCA
import numpy as np
from torch.utils.tensorboard import SummaryWriter
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error
from sklearn.metrics import r2_score
from sklearn.cluster import KMeans
from sklearn import datasets
from sklearn import metrics
import matplotlib.pyplot as plt

raw_data = house_data = pd.read_csv('nyc_2019_data.csv', low_memory=False)
column_names = []

for col in raw_data.columns:
    column_names.append(col)
# print(column_names)

# potential columns to use: neighbourhood_group, neighorbourhood, latitude, longitude, room_type, price, minimum_nights, number_of_reviews, reviews_per_month, availability_365
# size of whole dataset: 89895 row x 16 columns
raw_data = raw_data[['neighbourhood_group', 'neighbourhood', 'room_type', 'price', 'minimum_nights', 'number_of_reviews', 'availability_365']]
# raw_data = raw_data[['neighbourhood_group', 'neighbourhood', 'room_type', 'price', 'minimum_nights', 'number_of_reviews', 'reviews_per_month', 'availability_365']]
# raw_data = raw_data[['neighbourhood_group', 'neighbourhood', 'room_type', 'price', 'number_of_reviews', 'availability_365']]
print("num neighbourhood groups: " + str(raw_data['neighbourhood_group'].nunique()))
print("num neighbourhoods: " + str(raw_data['neighbourhood'].nunique()))

neighbourhood = pd.get_dummies(raw_data[['neighbourhood_group', 'neighbourhood', 'room_type']])
raw_data = raw_data.drop(columns=['neighbourhood_group', 'neighbourhood', 'room_type'])
raw_data = pd.concat([raw_data, neighbourhood],axis=1)



# Shows that the only null data after one hot encoding is the reviews_per_month column
for col in raw_data.columns:
    null_column = int(raw_data[col].isna().sum())
    if (null_column > 0):
        print(str(col) + " null: " + str(null_column))

# imputer = KNNImputer(n_neighbors=2)
# raw_data[:]= imputer.fit_transform(raw_data)

print("is null: " + str(raw_data.isnull().sum().sum()))

#y_data = raw_data['price']
#x_data = raw_data.drop(columns=['price'])

pca = PCA(n_components=25)
raw_data = pca.fit_transform(raw_data)

data_train, data_test = train_test_split(raw_data, test_size=0.2, random_state=4)

#data_train = data_train.to_numpy()
#data_test = data_test.to_numpy()

#Supervised Model

kmeans = KMeans(n_clusters = 10)
kmeans.fit(data_train)

pred_clusters = kmeans.predict(data_test)

print(pred_clusters)

labels = kmeans.labels_
print(metrics.silhouette_score(data_train, labels, metric='euclidean'))

distortions = []
K = range(1,16)
for k in K:
    kmeans = KMeans(n_clusters = k)
    kmeans.fit(data_train)
    distortions.append(kmeans.inertia_)

plt.figure(figsize=(16,8))
plt.plot(K, distortions, 'bx-')
plt.xlabel('k')
plt.ylabel('Distortion')
plt.title('The Elbow Method showing the optimal k')
plt.show()

kmeans = KMeans(n_clusters = 8)
kmeans.fit(data_train)
labels = kmeans.labels_
print(metrics.silhouette_score(data_train, labels, metric='euclidean'))

u_labels = np.unique(labels)
 
#plotting the results:
df = pca.fit_transform(data_train)
for i in u_labels:
    plt.scatter(df[labels == i , 0] , df[labels == i , 1] , label = i)
plt.legend()
plt.show()

# {i: raw_data[np.where(pred_clusters == i)] for i in range(kmeans.n_clusters)}