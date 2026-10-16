using System.IO.Compression;

namespace Raytracing;

public struct Vec3
{
    public float X { get; set; }
    public float Y { get; set; }
    public float Z { get; set; }

    public override string ToString()
    {
        return $"{X} {Y} {Z}";
    }

    public Vec3(float x, float y, float z)
    {
        X = x;
        Y = y;
        Z = z;
    }

    public static Vec3 operator -(Vec3 u) => new Vec3(-u.X, -u.Y, -u.Z);
    public static Vec3 operator +(Vec3 u, Vec3 v) => new Vec3(u.X + v.X, u.Y + v.Y, u.Z + v.Z);
    public static Vec3 operator -(Vec3 u, Vec3 v) => new Vec3(u.X - v.X, u.Y - v.Y, u.Z - v.Z);
    public static Vec3 operator *(float s, Vec3 u) => new Vec3(u.X * s, u.Y * s, u.Z * s);
    public static Vec3 operator /(Vec3 u, float s) => new Vec3(u.X / s, u.Y / s, u.Z / s);
    public static Vec3 operator *(Vec3 u, Vec3 v) => new Vec3(u.X * v.X, u.Y * v.Y, u.Z * v.Z);


    public float LengthSquared()
    {
        return X * X + Y * Y + Z * Z;
    }
    public float Length()
    {
        return MathF.Sqrt(LengthSquared());
    }

    public static float Dot(Vec3 v, Vec3 u)
    {
        return v.X * u.X + v.Y * u.Y + v.Z * u.Z;
    }

    public static Vec3 Cross(Vec3 v, Vec3 u)
    {
        return new Vec3(
            u.Y * v.Z - u.Z * v.Y,
            u.Z * v.X - u.X * v.Z,
            u.X * v.Y - u.Y * v.X
        );
    }

    public void Normalize()
    {
        float length = Length();
        if (length > 0)
        {
            X /= length;
            Y /= length;
            Z /= length;
        }
    }

    public Vec3 Normalized()
    {
        float length = Length();
        if (length > 0)
        {
            return new Vec3(X / length, Y / length, Z / length);
        }
        return this;
    }


};


