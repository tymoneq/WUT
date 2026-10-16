using System.Text;

namespace Raytracing;

public class Image
{
    private Vec3[,] Pixels;
    public int Width { get; private set; }
    public int Height { get; private set; }

    public Image(int width, int height)
    {
        Width = width;
        Height = height;
        Pixels = new Vec3[width, height];
    }

    public Vec3 this[int x, int y]
    {
        get
        {
            return Pixels[x, y];
        }
        set
        {
            Pixels[x, y] = value;
        }
    }

    public override string ToString()
    {
        StringBuilder result = new StringBuilder();
        result.AppendLine("P3");
        result.AppendLine($"{Width} {Height}");
        result.AppendLine("255");

        for (int h = 0; h < Height; h++)
        {
            for (int w = 0; w < Width; w++)
            {
                var color = this[w, h];
                int r = Math.Clamp((int)(color.X * 255.99), 0, 255);
                int g = Math.Clamp((int)(color.Y * 255.99), 0, 255);
                int b = Math.Clamp((int)(color.Z * 255.99), 0, 255);
                result.AppendLine($"{r} {g} {b}");
            }
        }

        return result.ToString();
    }

};