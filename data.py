import numpy as np
import matplotlib.pyplot as plt

data_inter = np.loadtxt("data_inter.txt")
data_real = np.loadtxt("data_real.txt")
plt.plot(data_inter[:,0], data_inter[:,1])
plt.plot(data_real[:,0], data_real[:,1])
plt.show()