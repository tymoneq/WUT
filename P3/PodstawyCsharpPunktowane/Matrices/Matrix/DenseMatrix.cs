namespace Matrices.Matrix;

public class DenseMatrix : Matrix
{
    public override float this[int row, int col]
    {
        get
        {
            if (!ValidIndices(row, col))
            {
                throw new ArgumentException("Index out of range");
            }
            return _data[row, col];
        }

        set
        {
            if (!ValidIndices(row, col))
            {
                throw new ArgumentException("Index out of range");
            }
            _data[row, col] = value;
        }
    }


    private float[,] _data;

    public DenseMatrix(int row, int col) : base(row, col)
    {
        _data = new float[row, col];
    }

    public override void Identity()
    {
        if (Rows != Columns)
        {
            throw new InvalidOperationException("Matrix is not a square matrix");
        }
        for (int row = 0; row < Rows; row++)
            for (int col = 0; col < Columns; col++)
            {
                if (row == col)
                {
                    this[row, col] = 1.0f;
                }
                else this[row, col] = 0.0f;
            }

    }
    public override Matrix Transpose()
    {
        Matrix result = new DenseMatrix(Columns, Rows);

        for (int row = 0; row < Rows; row++)
            for (int col = 0; col < Columns; col++)
            {
                result[col, row] = this[row, col];
            }

        return result;
    }

    public override float Norm()
    {
        float res = 0.0f;

        for (int row = 0; row < Rows; row++)
            for (int col = 0; col < Columns; col++)
                res += this[row, col] * this[row, col];

        res = MathF.Sqrt(res);


        return res;
    }

    protected override Matrix GetInstance(int row, int col)
    {
        DenseMatrix res = new DenseMatrix(row, col);
        return res;
    }
}

