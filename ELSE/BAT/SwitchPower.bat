    @echo off
setlocal

rem �趨������Դ�ƻ��� GUID
set "plan1=381b4222-f694-41f0-9685-ff5bb260df2e"
set "plan2=d827ad51-0111-49d1-bd1b-93d099bc317a"

rem ��ȡ��ǰ�ĵ�Դ�ƻ�
for /f "tokens=2 delims=: " %%i in ('powercfg /GETACTIVESCHEME') do set "current_plan=%%i"

rem �жϵ�ǰ�ƻ����ĸ������л�����һ���ƻ�
if "%current_plan%"=="%plan1%" (
    echo ��ǰ�ƻ�Ϊ��һ���ƻ����л����ڶ����ƻ�...
    powercfg /S %plan2%
) else (
    echo ��ǰ�ƻ�Ϊ�ڶ����ƻ����л�����һ���ƻ�...
    powercfg /S %plan1%
)

rem ��ʾ�л���ĵ�Դ�ƻ�
echo �л���ĵ�Դ�ƻ���
powercfg /L

echo ��Դ�ƻ����л���
