@echo off
setlocal enabledelayedexpansion

:: Указываем путь к исполняемому файлу и тестовой папке
set EXE=.\invert.exe
set TEST_DIR=.\test-data

:: Список тестов
set TESTS=matrix1 matrix2 matrix3 matrix4 matrix5

:: Запуск тестов
for %%T in (%TESTS%) do (
    echo Running test: %%T
    %EXE% "%TEST_DIR%\%%T.txt" > "%TEST_DIR%\%%T_out.txt"
    
    :: Сравниваем результаты
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
