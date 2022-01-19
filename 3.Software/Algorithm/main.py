import json
from matplotlib import pyplot as plt
import numpy as np
from scipy import signal

filename = "D:\\Project\\SmartWatch\\Algorithm\\PPG_DATA\\1.json"

data = open(filename)
strJson = json.load(data)

# 读入原始数据
data_PPG = np.asarray(strJson["data_PPG"])
plt.subplot(3, 1, 1)
plt.plot(data_PPG)

# FFT分析
# data_PPG_fft = np.fft.fft(data_PPG)
# plt.plot(data_PPG_fft[0:10])

# 低通滤波器
b, a = signal.butter(4, 2*3/1000, 'low')
filtedData = signal.filtfilt(b, a, data_PPG)
plt.plot(filtedData)

# 重采样减少数据
data_filtedData_resample = signal.resample(filtedData,int(np.size(filtedData)/50))
plt.subplot(3, 1, 2)
plt.plot(data_filtedData_resample)

# 重采样后滤波
b, a = signal.butter(4, 2*3/20, 'low')
filtedResampleData = signal.filtfilt(b, a, data_filtedData_resample)
plt.plot(filtedResampleData)


# 寻找波峰
data_peak = signal.find_peaks(filtedResampleData, distance=3)
plt.subplot(3, 1, 3)
plt.plot(filtedResampleData)
for i in range(len(data_peak[0])):
    plt.plot(data_peak[0][i], filtedResampleData[data_peak[0][i]],'*',markersize=10)


plt.savefig("1.png", dpi=600)
plt.show()