#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

const int SIZE = 3;

typedef double Matrix[SIZE][SIZE];

bool readMatrix(std::istream& input, Matrix& matrix) 
{
    std::string line;
    for (int i = 0; i < SIZE; ++i) 
    {
        if (!std::getline(input, line))
        {
            std::cout << "Invalid matrix format" << std::endl;
            return false;
        }
        std::istringstream iss(line);
        for (int j = 0; j < SIZE; ++j)
        {
            if (!(iss >> matrix[i][j])) 
            {
                std::cout << "Invalid matrix" << std::endl;
                return false;
            }
        }
        if (!iss.eof()) 
        {
            std::cout << "Invalid matrix format" << std::endl;
            return false;
        }
    }
    return true;
}

double determinant(Matrix& matrix) // форматирование
{
    return matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
        matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
        matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
}

void adjugate(Matrix& matrix, Matrix& adj)
{
    adj[0][0] = matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1];
    adj[0][1] = -(matrix[0][1] * matrix[2][2] - matrix[0][2] * matrix[2][1]);
    adj[0][2] = matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1];
    adj[1][0] = -(matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]);
    adj[1][1] = matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0];
    adj[1][2] = -(matrix[0][0] * matrix[1][2] - matrix[0][2] * matrix[1][0]);
    adj[2][0] = matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0];
    adj[2][1] = -(matrix[0][0] * matrix[2][1] - matrix[0][1] * matrix[2][0]);
    adj[2][2] = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

void invertMatrix(Matrix& matrix) 
{
    double det = determinant(matrix);
    if (det == 0) 
    {
        std::cout << "Non-invertible" << std::endl;
        return;
    }
    Matrix adj;
    adjugate(matrix, adj);

    for (int i = 0; i < SIZE; ++i) 
    {
        for (int j = 0; j < SIZE; ++j) 
        {
            std::cout << std::fixed << std::setprecision(3) << (adj[i][j] / det);
            if (j < SIZE - 1) 
            {
                std::cout << "\t";
            }
        }
        std::cout << std::endl;
    }
}

int main(int argc, char* argv[]) 
{
    Matrix matrix;
    if (argc == 2) 
    {
        if (std::string(argv[1]) == "-h") \
        {
            std::cout << "Usage: invert.exe [matrix_file]" << std::endl;
            return 0;
        }
        std::ifstream file(argv[1]);
        if (!file) 
        {
            std::cout << "File is not found" << std::endl;
            return 1;
        }
        if (!readMatrix(file, matrix)) 
        {
            return 1;
        }
        
    }
    else 
    {
        if (!readMatrix(std::cin, matrix))
        {
            return 1;
        }
    }
    invertMatrix(matrix);
    return 0;
}
// тест кейс 2 строки 2 колонки