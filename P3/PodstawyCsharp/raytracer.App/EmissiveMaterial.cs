namespace Raytracing;

public class EmissiveMaterial : Material
{
    public Vec3 Color { set; get; }
    public EmissiveMaterial(Vec3 color)
    {
        Color = color;
    }

    public override bool Scatter(in Ray rIn, ref HitInfo hitInfo, out Vec3 attenuation, out Ray scattered)
    {
        attenuation = new Vec3(0, 0, 0);
        scattered = new Ray();
        return false;
    }
    public override Vec3 Emit()
    {
        return Color;
    }


};