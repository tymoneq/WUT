using System.Text;

namespace Matrices.Matrix;


public abstract class Matrix
{
    public int Rows { get; }
    public int Columns { get; }

    public abstract float this[int row, int col] { get; set; }

    public Matrix(int row, int col)
    {
        if (row <= 0 || col <= 0)
            throw new ArgumentException("Row and Column count must be greater than zero");
        Rows = row;
        Columns = col;
    }

    public override string ToString()
    {
        StringBuilder sb = new StringBuilder();

        for (int row = 0; row < Rows; row++)
        {
            for (int col = 0; col < Columns; col++)
            {
                sb.AppendFormat($"{this[row, col]}");
            }
            if (row <= Rows - 1)
            {
                sb.AppendFormat("\n");
            }
        }
        return sb.ToString();
    }
    protected bool ValidIndices(int row, int col)
    {
        return row >= 0 && row < Rows && col >= 0 && col < Columns;
    }

    public abstract void Identity();
    public abstract Matrix Transpose();
    public abstract float Norm();

    protected abstract Matrix GetInstance(int row, int col);

    public static Matrix operator +(Matrix A, Matrix B)
    {
        if (!SameSize(A, B))
        {
            throw new ArgumentException("Wrong Matrix Sizes");
        }

        Matrix C = A.GetInstance(A.Rows, A.Columns);
        for (int row = 0; row < A.Rows; row++)
            for (int col = 0; col < A.Columns; col++)
                C[row, col] = A[row, col] + B[row, col];

        return C;
    }

    public static Matrix operator -(Matrix A, Matrix B)
    {
        if (!SameSize(A, B))
        {
            throw new ArgumentException("Wrong Matrix Sizes");
        }

        Matrix C = A.GetInstance(A.Rows, A.Columns);
        for (int row = 0; row < A.Rows; row++)
            for (int col = 0; col < A.Columns; col++)
                C[row, col] = A[row, col] - B[row, col];

        return C;
    }
    public static Matrix operator *(float scalar, Matrix A)
    {
        Matrix C = A.GetInstance(A.Rows, A.Columns);
        for (int row = 0; row < A.Rows; row++)
            for (int col = 0; col < A.Columns; col++)
                C[row, col] = A[row, col] * scalar;

        return C;
    }

    public static Matrix operator *(Matrix A, Matrix B)
    {
        if (A.Columns != B.Rows)
        {
            throw new ArgumentException("Wrong Matrix Sizes");
        }

        Matrix C = A.GetInstance(A.Rows, B.Columns);
        for (int row = 0; row < C.Rows; row++)
        {
            for (int col = 0; col < C.Columns; col++)
            {
                for (int i = 0; i < A.Columns; i++)
                {
                    C[row, col] += A[row, i] * B[i, col];
                }
            }
        }

        return C;
    }


    private static bool SameSize(Matrix a, Matrix b)
    {
        return a.Rows == b.Rows && a.Columns == b.Columns;
    }
}