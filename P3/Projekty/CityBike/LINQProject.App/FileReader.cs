namespace LINQProject.APP;

public class ReadAndParseFile
{

    Database _database;

    public ReadAndParseFile(string? filePath)
    {
        _database = new Database();
        ArgumentNullException.ThrowIfNull(filePath);

        using var sr = new StreamReader(filePath);

        while (sr.ReadLine() is { } line)
        {
            ParseLine(line);
        }
    }

    private void ParseLine(string? line)
    {
        if (line == null)
            return;

        var splitLine = line.Split(",");
        _database.ParseNewRecord(splitLine);

    }


}