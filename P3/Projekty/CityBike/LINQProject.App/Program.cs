namespace LINQProject.APP;

class Program
{
    static void Main(string[] argv)
    {

        if (argv == null || argv.Length == 0)
        {
            throw new Exception("[X] Error no file to read data from");
        }

        var ParseFile = new ReadAndParseFile(argv[0]);

    }

}