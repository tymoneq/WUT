using System.ComponentModel;

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

public sealed record class Station
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

    private void AddStation(string? stationID, string? stationName)
    {
        if (stationID == null)
            return;

        if (_Station.ContainsKey(stationID))
            return;

        if (stationName == null)
            return;

        var station = new Station { StationId = stationID, StationName = stationName };
        _Station.Add(stationID, station);
    }

    private void AddBikeTrip(string rideID, BikeTrip trip)
    {
        if (_BikeTrip.ContainsKey(rideID))
        {
            Console.WriteLine("ID already exist");
            return;
        }
        _BikeTrip.Add(rideID, trip);
    }

    public void ParseNewRecord(string ? line)
    {
        throw new NotImplementedException();
    }


}