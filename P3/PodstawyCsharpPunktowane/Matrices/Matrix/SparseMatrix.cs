namespace Matrices.Matrix;

public class SparseMatrix : Matrix
{
    private Dictionary<(int, int), float> _data;

    public override float this[int row, int col]
    {
        get
        {
            if (!ValidIndices(row, col))
            {
                throw new ArgumentException("Index out of range");
            }
            return _data.GetValueOrDefault((row, col), 0.0f);
        }

        set
        {
            if (!ValidIndices(row, col))
            {
                throw new ArgumentException("Index out of range");
            }
            if (value == 0.0f)
            {
                _data.Remove((row, col));
                return;
            }

            _data[(row, col)] = value;
        }
    }



    public SparseMatrix(int row, int col) : base(row, col)
    {
        _data = new Dictionary<(int, int), float>();
    }
}