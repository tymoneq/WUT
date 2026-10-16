namespace Raytracing;

class Plane : IHittable
{
    public Vec3 Point;
    public Vec3 Normal;


    public Plane(Vec3 point, Vec3 normal)
    {
        Point = point;
        Normal = normal.Normalized();
    }

    public bool Hit(Ray ray, float tMin, float tMax, out HitInfo hitInfo)
    {
        hitInfo = new HitInfo();

        float denom = Vec3.Dot(Normal, ray.Direction);
        if (MathF.Abs(denom) < 1e-6f)
        {
            return false;
        }

        float t = Vec3.Dot(Point - ray.Origin, Normal) / denom;
        if (t < tMin || tMax < t)
        {
            return false;
        }
        hitInfo.T = t;
        hitInfo.Position = ray.At(t);
        hitInfo.SetFaceNormal(ray, Normal);
        return true;
    }



}