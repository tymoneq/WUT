namespace Raytracing;


public abstract class Material
{
    public abstract bool Scatter(in Ray rIn, ref HitInfo hitInfo, out Vec3 attenuation, out Ray scattered);
    public virtual Vec3 Emit()
    {
        return new Vec3(0, 0, 0);
    }

}