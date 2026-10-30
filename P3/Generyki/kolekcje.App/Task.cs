using System.Globalization;

namespace Task2;

public readonly record struct Reading(string Sensor, double Value, DateTime At);
public record class Data(
    double HighestValue,                        // highest recorded value across all sensors
    double LowestTemp,                          // lowest recorded temperature
    string MostReadings,                        // name of the sensor with most readings
    TimeSpan TotalDuration,                     // difference between first and last recorded reading
    IList<string> UniqueSensors,                // list of all sensor names without duplicates
    IList<(string, double)> AverageReadings,    // average reading per sensor
    IList<(string, TimeSpan)> LargestGaps,      // a largest timespan between two consecutive readings (time order) per sensor
    IList<(Reading, Reading)> SignChanges       // two consecutive readings (time order) having two differnet signs (first < second) 
);

public class SensorLog
{
    private readonly List<Reading> _readings = new();
    public void Add(Reading r) { _readings.Add(r); }
    public IReadOnlyList<Reading> All => _readings;

    public SensorLog LoadFromCsv(string path)
    {
        bool first = true;
        foreach (var line in File.ReadLines(path))
        {
            if (first) { first = false; continue; } // assuming header            
            if (string.IsNullOrWhiteSpace(line))
            {
                continue;
            }
            var parts = line.Split(',');
            Add(new Reading(parts[0].Trim(), double.Parse(parts[1], CultureInfo.InvariantCulture), DateTime.Parse(parts[2], CultureInfo.InvariantCulture)));
        }
        return this;
    }
}

// =============================================================
// TODO 1
// =============================================================

public static class T1
{
    public static IEnumerable<Reading> InRange(IEnumerable<Reading> source, double min, double max)
    {
        foreach (Reading read in source)
        {
            if (read.Value >= min && read.Value <= max)
            {
                yield return read;
            }
        }
    }
}

// =============================================================
// TODO 2 
// =============================================================

public static class T2
{
    public static IEnumerable<Reading> Repeat(string sensor, double value, int count, DateTime start)
    {
        if (count <= 0)
        {
            yield break;
        }
        DateTime currentTime = start;
        for (int i = 0; i < count; i++)
        {
            yield return new Reading(sensor, value, currentTime);
            currentTime = currentTime.AddMinutes(2);
            value += 0.2;
        }
    }
}

// =============================================================
// TODO 3
// =============================================================

public class ReadingBySensorThenValue : Comparer<Reading>
{
    public override int Compare(Reading x, Reading y)
    {
        int result = x.Sensor.CompareTo(y.Sensor);
        if (result < 0)
        {
            return -1;
        }
        else if (result > 0)
        {
            return 1;
        }
        if (x.Value > y.Value)
        {
            return -1;
        }
        else if (x.Value < y.Value)
        {
            return 1;
        }
        if (x.At < y.At)
        {
            return -1;
        }
        else if (x.At > y.At)
        {
            return 1;
        }


        return 0;
    }
}

// =============================================================
// TODO 4 
// =============================================================

public static class T4
{
    public static Data Summarize(IEnumerable<Reading> source)
    {
        var ReadingList = source.ToList();
        var groupedBySensor = source.GroupBy(r => r.Sensor).ToList();

        double highestValue = source.Max(r => r.Value);
        double lowestTemp = source.Min(r => r.Value);

        string mostReadings = groupedBySensor.OrderByDescending(g => g.Count()).First().Key;

        var minTime = source.Min(r => r.At);
        var maxTime = source.Max(r => r.At);
        TimeSpan totalDuration = maxTime - minTime;

        IList<string> uniqueSensors = groupedBySensor.Select(g => g.Key).ToList();
        IList<(string, double)> avgReading = groupedBySensor.Select(g => (g.Key, g.Average(r => r.Value))).ToList();
        IList<(string, TimeSpan)> largestGaps = groupedBySensor.Select(
            g =>
            {
                var sorted = g.OrderBy(r => r.At).ToList();
                TimeSpan maxGap = sorted.Count > 1 ? sorted.Zip(sorted.Skip(1), (prev, next) => next.At - prev.At).Max() : TimeSpan.Zero;

                return (g.Key, maxGap);

            }
        ).ToList();

        var chronologicallySorted = source.OrderBy(r => r.At).ToList();
        IList<(Reading, Reading)> signChanges = chronologicallySorted.Zip(chronologicallySorted.Skip(1), (first, second) => (first, second)
            ).Where(pair => Math.Sign(pair.first.Value) != Math.Sign(pair.second.Value) && pair.first.Value < pair.second.Value).ToList();
        return new Data(
                    HighestValue: highestValue,
                    LowestTemp: lowestTemp,
                    MostReadings: mostReadings,
                    TotalDuration: totalDuration,
                    UniqueSensors: uniqueSensors,
                    AverageReadings: avgReading,
                    LargestGaps: largestGaps,
                    SignChanges: signChanges
                );


    }
}

// =============================================================
// TODO 5 
// =============================================================

public static class T5
{
    public static string Classify(IReadOnlyList<Reading> readings)
    {
        return readings switch
        {
            [] => "empty",
            [_] => "single",
            [{ Value: var v1 }, { Value: var v2 }] when v1 < v2 => "pair-asc",
            [{ Value: var v1 }, { Value: var v2 }] when v1 > v2 => "pair-desc",
            [{ Value: var v1 }, { Value: var v2 }] when v1 == v2 => "pair-eq",
            [{ Value: > 100 }, ..] => "starts-high",
            [.., { Value: < 0 }] => "ends-low",

            _ => "other"
        };
    }
}
