clear
load PPG_RAWDATA.mat;

% 1. �����ݼ��Ĳ����ʴ�1000Hz������100Hz
PPG_DATA_Resample=resample(PPG_RAWDATA,100,1000);

figure(1);
subplot(3,1,1);
plot(PPG_RAWDATA);
xlabel('ʱ��');
ylabel('��ֵ');
title('ԭʼ�ź�');
grid on;
subplot(3,1,2);
plot(PPG_DATA_Resample);
xlabel('ʱ��');
ylabel('��ֵ');
title('�������ź�');
grid on;

Fs = 100; % ����Ƶ��100Hz
N = 128; % ��������������100�����2���ݴ�
n = 0:N-1;
t = 0:1/Fs:1-1/Fs; % ʱ������
f = n*Fs/N; % Ƶ������

y = fft(PPG_DATA_Resample,N);
subplot(3,1,3);
plot(f,abs(y));
xlabel('Ƶ��');
ylabel('��ֵ');
title('�������źŸ���Ҷ�任');
grid on;

b = fir1(30,[0.5*2/100, 3*2/100]);
y2 = filtfilt(b,1,PPG_DATA_Resample);
figure(2);
subplot(2,1,1);
plot(y2);
xlabel('ʱ��');
ylabel('��ֵ');
title('�������źŴ�ͨ�˲�');
grid on;

y3 = fft(y2,N);
subplot(2,1,2);
plot(f,abs(y3));
xlabel('Ƶ��');
ylabel('��ֵ');
title('��ͨ�˲�����Ҷ�任');
grid on;

