namespace Raytracing;

public struct HitInfo
{
    public Vec3 Position;
    public Vec3 Normal;
    public float T;
    public bool FrontFace;
    public Material Mat;


    public void SetFaceNormal(Ray r, Vec3 outwardNormal)
    {
        FrontFace = Vec3.Dot(r.Direction, outwardNormal) < 0;
        Normal = FrontFace ? outwardNormal : -outwardNormal;
    }
};