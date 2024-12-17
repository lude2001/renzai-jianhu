@echo off
color 2f
echo 开始结束残余进程...
taskkill /f /t /im driver.exe
echo 开始关闭残余窗口...
taskkill /FI "WINDOWTITLE eq fluffos"
title 武林群侠之天龙八部
echo 开始启动OS...
fluffos64\driver.exe config.hell
cmd