fs = 1000;
N = 1024;
n = 0:N-1;
t = n/fs;
f = n*fs/N;

x = sin(2*pi*50*t)+sin(2*pi*200*t);
b = fir1(28, [125*2/1000 300*2/1000]);
y = filter(b,1,x);

subplot(3,1,1);
plot(t,x);
axis([0,0.2,-2,2]);
title('ԭʼ����');
xlabel('ʱ��');
ylabel('��ֵ');
grid on;

subplot(3,1,2);
plot(t,y);
axis([0,0.2,-2,2]);
title('MATLAB�˲�����');
xlabel('ʱ��');
ylabel('��ֵ');
grid on;

subplot(3,1,3);
d = importdata('fir.txt');
plot(t,d);
axis([0,0.2,-2,2]);
title('STM32�˲�����');
xlabel('ʱ��');
ylabel('��ֵ');
grid on;