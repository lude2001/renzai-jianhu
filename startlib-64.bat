@echo off
color 2f
echo ��ʼ�����������...
taskkill /f /t /im driver.exe
echo ��ʼ�رղ��ര��...
taskkill /FI "WINDOWTITLE eq fluffos"
title ����Ⱥ��֮�����˲�
echo ��ʼ����OS...
fluffos64\driver.exe config.hell
cmd