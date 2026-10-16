namespace Raytracing;

class Sphere : IHittable
{
    public Vec3 Center;
    public float Radius;
    public Material Mat { get; set; }

    public Sphere(Vec3 center, float r, Material mat)
    {
        Center = center;
        Radius = r;
        Mat = mat;
    }

    public bool Hit(Ray ray, float tMin, float tMax, out HitInfo hitInfo)
    {
        hitInfo = new HitInfo();

        Vec3 oc = ray.Origin - Center;
        float a = ray.Direction.LengthSquared();
        float halfB = Vec3.Dot(oc, ray.Direction);
        float c = oc.LengthSquared() - Radius * Radius;

        float discriminant = halfB * halfB - a * c;

        if (discriminant < 0)
        {
            return false;
        }

        float sqrtd = MathF.Sqrt(discriminant);
        float root = (-halfB - sqrtd) / a;

        if (root < tMin || tMax < root)
        {
            root = (-halfB + sqrtd) / a;
            if (root < tMin || tMax < root)
            {
                return false;
            }
        }

        hitInfo.T = root;
        hitInfo.Position = ray.At(root);
        Vec3 outwardNormal = (hitInfo.Position - Center) / Radius;
        hitInfo.SetFaceNormal(ray, outwardNormal);
        hitInfo.Mat = Mat;

        return true;
    }

}
