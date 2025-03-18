@echo off
setlocal
chcp 1251 > nul

set program=.\BasicVector.exe

:: ���� 1
echo ���� 1: ����: 1.0 2 3.659512
echo 1.0 2 3.659512 | %program% > output.txt
set /p output=<output.txt
if "%output%"=="3.220 4.220 5.879 " (
    echo ���� 1 �������!
) else (
    echo ���� 1 �� �������. ���������: 3.220 4.220 5.879, ��������: %output%
)

:: ���� 2
echo ���� 2: ����: 4 16 -30 10
echo 4 16 -30 10 | %program% > output.txt
set /p output=<output.txt
if "%output%"=="-20.000 14.000 20.000 26.000 " (
    echo ���� 2 �������!
) else (
    echo ���� 2 �� �������. ���������: -20.000 14.000 20.000 26.000, ��������: %output%
)

:: ���� 3
echo ���� 3: ����: -1.0004000 -703 -3.659512 -11
echo -1.0004000 -703 -3.659512 -11 | %program% > output.txt
set /p output=<output.txt
if "%output%"=="-703.000 -11.000 -3.660 -1.000 " (
    echo ���� 3 �������!
) else (
    echo ���� 3 �� �������. ���������: -703.000 -11.000 -3.660 -1.000, ��������: %output%
)

:: ���� 4
echo ���� 4: ����: - 2 3
echo - 2 3 | %program% > output.txt
set /p output=<output.txt
if "%output%"=="ERROR" (
    echo ���� 4 �������!
) else (
    echo ���� 4 �� �������. ���������: ERROR, ��������: %output%
)

pause

:: �������� ��������� ������
del output.txt

endlocal