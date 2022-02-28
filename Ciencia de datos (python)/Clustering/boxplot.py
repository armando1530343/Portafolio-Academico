import matplotlib.pyplot as plt
import numpy as np
import math

kmeans = [0.73,0.56,0.96,0.43,0.15,0.62,0.55,1.0,0.48,0.99,0.63,0.54,0.04,-0.1,0.94,0.93,0.95,1.0,0.98,0.89,1.0,0.84,0.95,0.97,0.88]
average = [0.99,0.8,0.93,0.36,0.02,0.56,0.51,1.0,0.47,0.99,0.5,0.63,0.02,0.02,0.77,0.38,0.98,0.87,0.81,0.89,1.0,0.8,0.75,0.88,0.76]
single = [0.81,0.76,0.15,0.01,0.01,0.56,0.01,1.0,0.0,0.54,0.0,1.0,1.0,1.0,0.31,0.0,0.0,1.0,0.89,0.9,1.0,0.78,0.76,0.66,0.41]
complete = [0.93,0.72,0.87,0.29,0.03,0.57,0.51,0.0,0.39,0.98,0.5,0.54,0.02,0.0,0.63,0.52,0.66,0.87,0.79,0.8,1.0,0.79,0.77,0.8,0.78]



##all_data = [np.random.normal(12,23,23) for std in range(1, 7)]
all_data = [kmeans, average, single, complete]
fig, ax = plt.subplots(figsize=(9, 4))

# rectangular box plot
bplot1 = ax.boxplot(all_data,
                         vert=True,   # vertical box aligmnent
                         patch_artist=True)   # fill with color


ax.set_xticklabels( ['Kmeans', 'Average Linkage', 'Single Linkage', 'Complete Linkage'] )
ax.set_ylabel('Adjusted Rand Score')

plt.show()