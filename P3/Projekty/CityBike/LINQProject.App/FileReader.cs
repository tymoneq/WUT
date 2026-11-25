namespace LINQProject.APP;

public class ReadAndParseFile
{
    public ReadAndParseFile(string? filePath)
    {
        ArgumentNullException.ThrowIfNull(filePath);

        using var sr = new StreamReader(filePath);
        // to do parsing file

    }


}