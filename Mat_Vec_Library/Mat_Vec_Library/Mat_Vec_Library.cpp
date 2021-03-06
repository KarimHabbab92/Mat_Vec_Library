#include "iostream"
#include "framework.h"
#include "Mat_Vec_Library.h"
#include "pch.h"

using namespace std;

// Constructor for Any Matrix
Matrix::Matrix(unsigned rowSize, unsigned colSize, float initial) {
    m_rowSize = rowSize;
    m_colSize = colSize;
    m_matrix.resize(rowSize);
    static int m=0, k=0, l=0, e=0, t=0;
    for (unsigned i = 0; i < m_matrix.size(); i++)
    {
        m_matrix[i].resize(colSize, initial);
    }
}

// Addition of Two Matrices
Matrix Matrix::operator+(Matrix& B) {
    Matrix sum(m_colSize, m_rowSize, 0.0);
    unsigned i, j;
    for (i = 0; i < m_rowSize; i++)
    {
        for (j = 0; j < m_colSize; j++)
        {
            sum(i, j) = this->m_matrix[i][j] + B(i, j);
        }
    }
    return sum;
}

// Subtraction of Two Matrices
Matrix Matrix::operator-(Matrix& B) {
    Matrix diff(m_colSize, m_rowSize, 0.0);
    unsigned i, j;
    for (i = 0; i < m_rowSize; i++)
    {
        for (j = 0; j < m_colSize; j++)
        {
            diff(i, j) = this->m_matrix[i][j] - B(i, j);
        }
    }

    return diff;
}
// Multiplication of Two Matrices
Matrix Matrix::operator*(Matrix& B) {
    Matrix multip(m_rowSize, B.getCols(), 0.0);
    if (m_colSize == B.getRows())
    {
        unsigned i, j, k;
        double temp = 0.0;
        for (i = 0; i < m_rowSize; i++)
        {
            for (j = 0; j < B.getCols(); j++)
            {
                temp = 0.0;
                for (k = 0; k < m_colSize; k++)
                {
                    temp += m_matrix[i][k] * B(k, j);
                }
                multip(i, j) = temp;
                //cout << multip(i,j) << " ";
            }
            //cout << endl;
        }
        return multip;
    }
    else
    {
        return "Error";
    }
}
// Scalar Addition
Matrix Matrix::operator+(float scalar) {
    Matrix result(m_rowSize, m_colSize, 0.0);
    unsigned i, j;
    for (i = 0; i < m_rowSize; i++)
    {
        for (j = 0; j < m_colSize; j++)
        {
            result(i, j) = this->m_matrix[i][j] + scalar;
        }
    }
    return result;
}

// Scalar Subraction
Matrix Matrix::operator-(float scalar) {
    Matrix result(m_rowSize, m_colSize, 0.0);
    unsigned i, j;
    for (i = 0; i < m_rowSize; i++)
    {
        for (j = 0; j < m_colSize; j++)
        {
            result(i, j) = this->m_matrix[i][j] - scalar;
        }
    }
    return result;
}

// Scalar Multiplication
Matrix Matrix::operator*(float scalar) {
    Matrix result(m_rowSize, m_colSize, 0.0);
    unsigned i, j;
    for (i = 0; i < m_rowSize; i++)
    {
        for (j = 0; j < m_colSize; j++)
        {
            result(i, j) = this->m_matrix[i][j] * scalar;
        }
    }
    return result;
}

// Scalar Division
Matrix Matrix::operator/(float scalar) {
    Matrix result(m_rowSize, m_colSize, 0.0);
    unsigned i, j;
    for (i = 0; i < m_rowSize; i++)
    {
        for (j = 0; j < m_colSize; j++)
        {
            result(i, j) = this->m_matrix[i][j] / scalar;
        }
    }
    return result;
}
// Returns value of given location when asked in the form A(x,y)
double& Matrix::operator()(const unsigned& rowNo, const unsigned& colNo)
{
    return this->m_matrix[rowNo][colNo];
}

// No brainer - returns row #
unsigned Matrix::getRows() const
{
    return this->m_rowSize;
}

// returns col #
unsigned Matrix::getCols() const
{
    return this->m_colSize;
}

// Take any given matrices transpose and returns another matrix
Matrix Matrix::transpose()
{
    Matrix Transpose(m_colSize, m_rowSize, 0.0);
    for (unsigned i = 0; i < m_colSize; i++)
    {
        for (unsigned j = 0; j < m_rowSize; j++) {
            Transpose(i, j) = this->m_matrix[j][i];
        }
    }
    return Transpose;
}

// Prints the matrix 
void Matrix::print() const
{
    cout << "Matrix: " << endl;
    for (unsigned i = 0; i < Matrix::m_rowSize; i++) {
        for (unsigned j = 0; j < Matrix::m_colSize; j++) {
            cout << "[" << Matrix::m_matrix[i][j] << "] ";
        }
        cout << endl;
    }
}
// Returns 3 values
//First: Eigen Vector
//Second: Eigen Value
//Third: Flag
tuple <Matrix, double, int> Matrix::powerIter(unsigned rowNum, double tolerance) {
    // Picks a classic X vector
    Matrix X(rowNum, 1, 1.0);
    // Initiates X vector with values 1,2,3,4
    for (unsigned i = 1; i <= rowNum; i++) {
        X(i - 1, 0) = i;
    }
    int errorCode = 0;
    double difference = 1.0; // Initiall value greater than tolerance
    unsigned j = 0;
    unsigned location;
    // Defined to find the value between last two eigen values
    vector<double> eigen;
    double eigenvalue = 0.0;
    eigen.push_back(0.0);

    while (abs(difference) > tolerance) // breaks out when reached tolerance
    {
        j++;
        // Normalize X vector with infinite norm
        for (int i = 0; i < rowNum; ++i)
        {
            eigenvalue = X(0, 0);
            if (abs(X(i, 0)) >= abs(eigenvalue))
            {
                // Take the value of the infinite norm as your eigenvalue
                eigenvalue = X(i, 0);
                location = i;
            }
        }
        if (j >= 5e5) {
            cout << "Oops, that was a nasty complex number wasn't it?" << endl;
            cout << "ERROR! Returning code black, code black!";
            errorCode = -1;
            return make_tuple(X, 0.0, errorCode);
        }
        eigen.push_back(eigenvalue);
        difference = eigen[j] - eigen[j - 1];
        // Normalize X vector with its infinite norm
        X = X / eigenvalue;

        // Multiply The matrix with X vector
        X = (*this) * X;
    }

    // Take the X vector and what you've found is an eigenvector!
    X = X / eigenvalue;
    return make_tuple(X, eigenvalue, errorCode);
}

Matrix Matrix::deflation(Matrix& X, double& eigenvalue)
{
    // Deflation formula exactly applied
    double denominator = eigenvalue / (X.transpose() * X)(0, 0);
    Matrix Xtrans = X.transpose();
    Matrix RHS = (X * Xtrans);
    Matrix RHS2 = RHS * denominator;
    Matrix A2 = *this - RHS2;
    return A2;
}

//Matrix * Vector function:
void Matrix::matrix_x_vector(int y[m], int x[k][l], int A[e][t])
{
    if (l != m)
    {
        throw "colmuns of Matrix Are NOT equal to vector's Rows";

        return ;
    }
    else
    {
        int i, j; // i = row; j = column;
        printf("\nResulted Matrix of [M]*[V]\n");
        // Load up A[][]
        for (i = 0; i < m_rowSize; i++)
        {
            for (j = 0; j < m_colSize; j++)
            {
                A[j][0] += x[j][i] * y[i];
                //printf("%4i", A[j][0]);
            }
            printf("\n");
        }
        
    }
}
//Vector*Matrix Function
void Matrix::vector_x_matrix(int y[m], int x[k][l], int A[e][t])
{
    if (k != m)
    {
        throw "colmuns of vector  Are NOT equal to Matrix's Rows";

        return;
    }
    else
    {
        int i, j; // i = row; j = column;
        printf("\nResulted Matrix of [M]*[V]\n");
        // Load up A[][]
        for (i = 0; i < m; i++)
        {
    
             A[j][0] += y[i]* x[j][i];
             //printf("%4i", A[j][0]);
            
            printf("\n");
        }

    }
}

void vectorClass::push(float data, int index)
{

    // if index is equal to capacity then this 
    // function is same as push defined above 
    if (index == capacity)
        push(data);
    else
        arr[index] = data;
}

int vectorClass::get(int index)
{

   // if index is within the range 
    if (index < current)
        return arr[index];
}