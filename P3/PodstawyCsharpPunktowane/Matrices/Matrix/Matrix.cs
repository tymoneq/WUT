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

}