namespace LINQProject.APP;

public enum BikeType : byte
{
    UNKNOWN = 0,
    electric_bike,
    classic_bike,
};

public enum MemberType : byte
{
    member,
    casual,
}

public sealed class Station
{
    public required string StationId;
    public required string StationName;
}

public sealed record class BikeTrip
{
    public required string RideID { get; init; }
    public required BikeType RideableType { get; init; }
    public required DateTime StartedAt { get; init; }
    public required DateTime EndedAt { get; init; }
    public string? StartStationID { get; init; }
    public string? EndStationID { get; init; }
    public double StartLatitude { get; init; }
    public double StartLongitude { get; init; }
    public double? EndLatitude { get; init; }
    public double? EndLongitude { get; init; }

    public required MemberType Member { get; init; }
}


public sealed class Database
{
    private readonly Dictionary<string, Station> _Station = [];
    private readonly Dictionary<string, BikeTrip> _BikeTrip = [];


}