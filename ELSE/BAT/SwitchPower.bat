    @echo off
setlocal

rem 设定两个电源计划的 GUID
set "plan1=381b4222-f694-41f0-9685-ff5bb260df2e"
set "plan2=d827ad51-0111-49d1-bd1b-93d099bc317a"

rem 获取当前的电源计划
for /f "tokens=2 delims=: " %%i in ('powercfg /GETACTIVESCHEME') do set "current_plan=%%i"

rem 判断当前计划是哪个，并切换到另一个计划
if "%current_plan%"=="%plan1%" (
    echo 当前计划为第一个计划，切换到第二个计划...
    powercfg /S %plan2%
) else (
    echo 当前计划为第二个计划，切换到第一个计划...
    powercfg /S %plan1%
)

rem 显示切换后的电源计划
echo 切换后的电源计划：
powercfg /L

echo 电源计划已切换。
