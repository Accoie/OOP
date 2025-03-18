@echo off
setlocal
chcp 1251 > nul

set program=.\BasicVector.exe

:: Тест 1
echo Тест 1: Ввод: 1.0 2 3.659512
echo 1.0 2 3.659512 | %program% > output.txt
set /p output=<output.txt
if "%output%"=="3.220 4.220 5.879 " (
    echo Тест 1 пройден!
) else (
    echo Тест 1 не пройден. Ожидалось: 3.220 4.220 5.879, Получено: %output%
)

:: Тест 2
echo Тест 2: Ввод: 4 16 -30 10
echo 4 16 -30 10 | %program% > output.txt
set /p output=<output.txt
if "%output%"=="-20.000 14.000 20.000 26.000 " (
    echo Тест 2 пройден!
) else (
    echo Тест 2 не пройден. Ожидалось: -20.000 14.000 20.000 26.000, Получено: %output%
)

:: Тест 3
echo Тест 3: Ввод: -1.0004000 -703 -3.659512 -11
echo -1.0004000 -703 -3.659512 -11 | %program% > output.txt
set /p output=<output.txt
if "%output%"=="-703.000 -11.000 -3.660 -1.000 " (
    echo Тест 3 пройден!
) else (
    echo Тест 3 не пройден. Ожидалось: -703.000 -11.000 -3.660 -1.000, Получено: %output%
)

:: Тест 4
echo Тест 4: Ввод: - 2 3
echo - 2 3 | %program% > output.txt
set /p output=<output.txt
if "%output%"=="ERROR" (
    echo Тест 4 пройден!
) else (
    echo Тест 4 не пройден. Ожидалось: ERROR, Получено: %output%
)

pause

:: Удаление временных файлов
del output.txt

endlocal