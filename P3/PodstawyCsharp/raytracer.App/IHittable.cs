namespace Raytracing;


public interface IHittable
{
    public bool Hit(Ray ray, float tMin, float tMax, out HitInfo hitInfo);
}