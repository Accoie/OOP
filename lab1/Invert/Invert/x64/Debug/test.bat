@echo off
setlocal enabledelayedexpansion

:: ��������� ���� � ������������ ����� � �������� �����
set EXE=.\invert.exe
set TEST_DIR=.\test-data

:: ������ ������
set TESTS=matrix1 matrix2 matrix3 matrix4 matrix5

:: ������ ������
for %%T in (%TESTS%) do (
    echo Running test: %%T
    %EXE% "%TEST_DIR%\%%T.txt" > "%TEST_DIR%\%%T_out.txt"
    
    :: ���������� ����������
    fc /w "%TEST_DIR%\%%T_out.txt" "%TEST_DIR%\%%T_expected.txt" > nul
    if errorlevel 1 (
        echo Test %%T: FAILED
    ) else (
        echo Test %%T: PASSED
    )
)

echo All tests completed.
pause
exit /b
