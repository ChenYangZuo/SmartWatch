clear
load PPG_RAWDATA.mat;

% 1. 将数据集的采样率从1000Hz降低至100Hz
PPG_DATA_Resample=resample(PPG_RAWDATA,100,1000);

figure(1);
subplot(3,1,1);
plot(PPG_RAWDATA);
xlabel('时间');
ylabel('幅值');
title('原始信号');
grid on;
subplot(3,1,2);
plot(PPG_DATA_Resample);
xlabel('时间');
ylabel('幅值');
title('降采样信号');
grid on;

Fs = 100; % 采样频率100Hz
N = 128; % 采样点数，距离100最近的2的幂次
n = 0:N-1;
t = 0:1/Fs:1-1/Fs; % 时间序列
f = n*Fs/N; % 频率序列

y = fft(PPG_DATA_Resample,N);
subplot(3,1,3);
plot(f,abs(y));
xlabel('频率');
ylabel('幅值');
title('降采样信号傅里叶变换');
grid on;

b = fir1(30,[0.5*2/100, 3*2/100]);
y2 = filtfilt(b,1,PPG_DATA_Resample);
figure(2);
subplot(2,1,1);
plot(y2);
xlabel('时间');
ylabel('幅值');
title('降采样信号带通滤波');
grid on;

y3 = fft(y2,N);
subplot(2,1,2);
plot(f,abs(y3));
xlabel('频率');
ylabel('幅值');
title('带通滤波后傅里叶变换');
grid on;

