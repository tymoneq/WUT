namespace Raytracing;

public class Camera
{
    private float _aspectRatio = 16.0f / 9.0f;
    private int _imageWidth = 1280;
    private Vec3 _position = new Vec3(0, 0, 0);
    private Vec3 _target = new Vec3(0, 0, -1);
    private float _fov = 90.0f;

    private int _imageHeight;
    private Vec3 _pixelDu;
    private Vec3 _pixelDv;
    private Vec3 _viewportCorner;


    public float AspectRatio
    {
        get => _aspectRatio;
        set
        {
            _aspectRatio = value;
            Recalculate();
        }
    }
    public int ImageWidth
    {
        get => _imageWidth;
        set
        {
            _imageWidth = value;
            Recalculate();
        }
    }
    public Vec3 Position
    {
        get => _position;
        set
        {
            _position = value;
            Recalculate();
        }
    }
    public Vec3 Target
    {
        get => _target;
        set
        {
            _target = value;
            Recalculate();
        }
    }
    public float Fov
    {
        get => _fov;
        set
        {
            _fov = value;
            Recalculate();
        }
    }

    public Camera()
    {
        Recalculate();
    }

    private void Recalculate()
    {
        _imageHeight = (int)(ImageWidth / AspectRatio);

        if (_imageHeight < 1) 
        {
            _imageHeight = 1;
        }

        float theta = Fov * MathF.PI / 180.0f;
        float h = MathF.Tan(theta / 2.0f);
        float distanceToViewport = (Position - Target).Length();
        float viewportHeight = 2.0f * h * distanceToViewport;
        float viewportWidth = viewportHeight * AspectRatio;

        Vec3 w = (Position - Target).Normalized();
        Vec3 u = Vec3.Cross(new Vec3(0, 1, 0), w).Normalized();
        Vec3 v = Vec3.Cross(w, u);

        Vec3 viewportU = viewportWidth * u;
        Vec3 viewportV = viewportHeight * -v;

        _pixelDu = viewportU / ImageWidth;
        _pixelDv = viewportV / _imageHeight;

        Vec3 viewportUpperLeft = Position - (distanceToViewport * w) - viewportU / 2.0f - viewportV / 2.0f;
        _viewportCorner = viewportUpperLeft + 0.5f * (_pixelDu + _pixelDv);




    }

}