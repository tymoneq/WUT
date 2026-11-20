using System.Text.Json;
using System.Text.Json.Serialization;
using tasks.Databases;

namespace tasks;

/// <summary>
/// Here you should implement various database query methods for the IMovieDatabase interface.
/// </summary>
public static class DatabaseQueries
{
    public static void RunQueries(this IMovieDatabase movieDatabase)
    {
        movieDatabase.ActorsFromFantasyMovies();
        movieDatabase.LongestMovieByGenre();
        movieDatabase.HighRatedMoviesWithCast();
        movieDatabase.DistinctRolesCountPerActor();
        movieDatabase.RecentMoviesWithAverageRating();
        movieDatabase.AverageRatingByGenre();
        movieDatabase.ActorsWhoNeverPlayedInThriller();
        movieDatabase.Top3MoviesByRatingCount();
        movieDatabase.MoviesWithoutRatings();
        movieDatabase.MostVersatileActors();
    }

    public static void ActorsFromFantasyMovies(this IMovieDatabase movieDatabase)
    {
        var movies = movieDatabase.Movies;
        var actors = movieDatabase.Actors;
        var ratings = movieDatabase.Ratings;
        var casts = movieDatabase.Casts;

        var queryResult = casts
            .Join(movies.Where(m => m.Genre == Genre.Fantasy),
                cast => cast.MovieId,
                movie => movie.Id,
                (cast, movie) => cast.ActorId)
            .Distinct()
            .Join(actors,
                actorId => actorId,
                actor => actor.Id,
                (actorId, actor) => actor)
            .ToList();

        Console.WriteLine("Actors From Fantasy Movies");
        DisplayQueryResults(queryResult);
        Console.WriteLine();
    }

    public static void LongestMovieByGenre(this IMovieDatabase movieDatabase)
    {
        var movies = movieDatabase.Movies;
        var actors = movieDatabase.Actors;
        var ratings = movieDatabase.Ratings;
        var casts = movieDatabase.Casts;

        var queryResult = movies.GroupBy(m => m.Genre).Select(group => new
        {
            Genre = group.Key,
            Movie = group.MaxBy(movie => movie.DurationMinutes)
        }).ToList();

        Console.WriteLine("Longest Movie By Genre");
        DisplayQueryResults(queryResult);
        Console.WriteLine();
    }

    public static void HighRatedMoviesWithCast(this IMovieDatabase movieDatabase)
    {
        var movies = movieDatabase.Movies;
        var actors = movieDatabase.Actors;
        var ratings = movieDatabase.Ratings;
        var casts = movieDatabase.Casts;

        var queryResult = ratings.GroupBy(r => r.MovieId)
        .Select(g => new
        {
            MovieId = g.Key,
            Average = g.Average(r => r.Score)

        }).Where(g => g.Average > 8).
        Join(movies, rating => rating.MovieId, movie => movie.Id, (rating, movie) => new
        {
            Movie = movie,
            rating.Average

        }).GroupJoin(casts, movie => movie.Movie.Id, cast => cast.MovieId, (movie, movieCasts) => new
        {
            movie.Movie,
            CastIds = movieCasts.Select(c => c.ActorId),
            movie.Average
        }).Select(
            x => new
            {
                x.Movie,
                x.Average,
                Cast = x.CastIds.Join(actors, actorId => actorId,
                          actor => actor.Id, (actorId, actor) => actor).ToList()
            }
        ).ToList();
        Console.WriteLine("High Rated Movies With Cast");
        DisplayQueryResults(queryResult);
        Console.WriteLine();
    }

    public static void DistinctRolesCountPerActor(this IMovieDatabase movieDatabase)
    {
        var movies = movieDatabase.Movies;
        var actors = movieDatabase.Actors;
        var ratings = movieDatabase.Ratings;
        var casts = movieDatabase.Casts;

        var queryResult = new object();

        Console.WriteLine("Distinct Roles Count Per Actor");
        DisplayQueryResults(queryResult);
        Console.WriteLine();
    }

    public static void RecentMoviesWithAverageRating(this IMovieDatabase movieDatabase)
    {
        var movies = movieDatabase.Movies;
        var actors = movieDatabase.Actors;
        var ratings = movieDatabase.Ratings;
        var casts = movieDatabase.Casts;

        var queryResult = new object();

        Console.WriteLine("Recent Movies With Average Rating");
        DisplayQueryResults(queryResult);
        Console.WriteLine();
    }

    public static void AverageRatingByGenre(this IMovieDatabase movieDatabase)
    {
        var movies = movieDatabase.Movies;
        var actors = movieDatabase.Actors;
        var ratings = movieDatabase.Ratings;
        var casts = movieDatabase.Casts;

        var queryResult = new object();

        Console.WriteLine("Average Rating By Genre");
        DisplayQueryResults(queryResult);
        Console.WriteLine();
    }

    public static void ActorsWhoNeverPlayedInThriller(this IMovieDatabase movieDatabase)
    {
        var movies = movieDatabase.Movies;
        var actors = movieDatabase.Actors;
        var ratings = movieDatabase.Ratings;
        var casts = movieDatabase.Casts;

        var queryResult = new object();

        Console.WriteLine("Actors Who Never Played In Thriller");
        DisplayQueryResults(queryResult);
        Console.WriteLine();
    }

    public static void Top3MoviesByRatingCount(this IMovieDatabase movieDatabase)
    {
        var movies = movieDatabase.Movies;
        var actors = movieDatabase.Actors;
        var ratings = movieDatabase.Ratings;
        var casts = movieDatabase.Casts;

        var queryResult = new object();

        Console.WriteLine("Top 3 Movies By Rating Count");
        DisplayQueryResults(queryResult);
        Console.WriteLine();
    }

    public static void MoviesWithoutRatings(this IMovieDatabase movieDatabase)
    {
        var movies = movieDatabase.Movies;
        var actors = movieDatabase.Actors;
        var ratings = movieDatabase.Ratings;
        var casts = movieDatabase.Casts;

        var queryResult = new object();

        Console.WriteLine("Movies Without Ratings");
        DisplayQueryResults(queryResult);
        Console.WriteLine();
    }

    public static void MostVersatileActors(this IMovieDatabase movieDatabase)
    {
        var movies = movieDatabase.Movies;
        var actors = movieDatabase.Actors;
        var ratings = movieDatabase.Ratings;
        var casts = movieDatabase.Casts;

        var queryResult = new object();

        Console.WriteLine("Most Versatile Actors");
        DisplayQueryResults(queryResult);
        Console.WriteLine();
    }

    public static void DisplayQueryResults<T>(T query)
    {
        var options = new JsonSerializerOptions
        {
            WriteIndented = true
        };

        options.Converters.Add(new JsonStringEnumConverter());

        var json = JsonSerializer.Serialize(query, options);

        Console.WriteLine(json);
    }
}