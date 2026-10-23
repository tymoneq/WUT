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

}