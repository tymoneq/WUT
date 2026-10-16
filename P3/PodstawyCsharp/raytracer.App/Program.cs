namespace Raytracing;

class Program()
{
    public static void Main(string[] args)
    {
        //Image image = new Image(1920, 1080);
        //for (int i = 0; i < image.Width; i++)
        //{
        //    for (int j = 0; j < image.Height; j++)
        //    {
        //        float r = (float)i / image.Width;
        //        float g = (float)j / image.Height;
        //        float b = MathF.Sin(2 * MathF.PI * ((float)i * j / image.Width / image.Height));
        //        image[i, j] = new Vec3(r, g, b);
        //    }
        //}

        //Console.WriteLine(image);


        Scene world = new Scene();
        // Add a sky sphere
        world.Add(new Sphere(new Vec3(0, 0, 0), 1000.0f, new EmissiveMaterial(new Vec3(0.5f, 0.7f, 1.0f))));

        // Add a sphere
        world.Add(new Sphere(new Vec3(0, 0, -1), 0.5f, new EmissiveMaterial(new Vec3(1, 0, 0)))); 
        
        // Add a ground plane
        world.Add(new Plane(new Vec3(0, -0.5f, 0), new Vec3(0, 1, 0), new EmissiveMaterial(new Vec3(1, 1, 1))));

        Camera cam = new Camera();
        cam.Position = new Vec3(0, 0, 1);
        cam.Target = new Vec3(0, 0, -1);

        Image image = cam.Render(world);

        Console.Write(image.ToString());
    }
}
