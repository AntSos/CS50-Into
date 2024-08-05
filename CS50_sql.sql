-- Songs
-- 1.
SELECT name
FROM songs;

--2
SELECT name
FROM songs
ORDER BY tempo ASC;

--3
SELECT name
FROM songs
ORDER BY duration_ms DESC
LIMIT 5;

--4
SELECT name
FROM songs
WHERE danceability > 0.75
AND energy > 0.75
AND valence > 0.75;

--5
SELECT AVG(energy)
FROM songs;

--6
SELECT name
FROM songs
WHERE artist_id =
(
    SELECT id
    FROM artists
    WHERE name = 'Post Malone'
);


--7.1
SELECT AVG(energy)
FROM songs
WHERE artist_id =
(
    SELECT id
    FROM artists
    WHERE name = 'Drake'
)

--7.2
SELECT AVG(energy)
FROM songs
JOIN artists ON songs.artist_id = artists.id
WHERE artists.name = 'Drake';

--8
SELECT name
FROM songs
WHERE name LIKE '%feat.%';


-- Movies
--1
SELECT title
FROM movies
WHERE year = 2008;

--2
SELECT birth
FROM people
WHERE name = 'Emma Stone';

--3
SELECT title
FROM movies
WHERE year >= 2018
ORDER BY title ASC;

--4
SELECT COUNT(movie_id)
FROM ratings
WHERE RATING = 10;

--5
SELECT title, year
FROM movies
WHERE title  LIKE 'Harry Potter%'
ORDER BY year ASC;

--6
SELECT AVG(rating)
FROM ratings
JOIN movies ON ratings.movie_id = movies.id
WHERE movies.year = 2012;

--7
SELECT movies.title,rating
FROM ratings
JOIN movies ON ratings.movie_id = movies.id
WHERE movies.year = 2010
ORDER BY rating DESC, movies.title ASC;

--8
SELECT name
FROM people
WHERE id IN
(
    SELECT person_id
    FROM stars
    WHERE movie_id = (

        SELECT id
        FROM movies
        WHERE title = 'Toy Story'
    )
);

--9
SELECT name
FROM people
WHERE id IN
(
    SELECT person_id
    FROM stars
    WHERE movie_id IN (

        SELECT id
        FROM movies
        WHERE year = 2004
    )
)
ORDER BY birth ASC;

--10
SELECT name
FROM people
WHERE id IN
(
    SELECT person_id
    FROM directors
    WHERE movie_id IN (

        SELECT movie_id
        FROM ratings
        WHERE rating >= 9.0

    )
);

--10.2
SELECT DISTINCT name
FROM people
JOIN directors ON directors.person_id = people.id
JOIN movies ON movies.id = directors.movie_id
JOIN ratings ON ratings.movie_id = movies.id
WHERE rating >= 9.0;

--11
SELECT title
FROM movies
JOIN ratings ON ratings.movie_id = movies.id
JOIN stars ON stars.movie_id = movies.id
JOIN people ON stars.person_id = people.id
WHERE people.name = 'Chadwick Boseman'
ORDER BY ratings.rating DESC
LIMIT 5;

--12
SELECT title
FROM movies
JOIN stars ON stars.movie_id = movies.id
JOIN people ON stars.person_id = people.id
WHERE people.name = 'Bradley Cooper'
AND title IN (
    SELECT title
    FROM movies
    JOIN stars ON stars.movie_id = movies.id
    JOIN people ON stars.person_id = people.id
    WHERE people.name = 'Jennifer Lawrence'

);

--13
SELECT DISTINCT name
FROM people
JOIN stars ON stars.person_id = people.id
JOIN movies ON movies.id = stars.movie_id
WHERE movies.id IN
(
    SELECT movies.id
    FROM movies
    JOIN stars ON stars.movie_id = movies.id
    JOIN people ON stars.person_id = people.id
    WHERE people.name = 'Kevin Bacon' AND people.birth = 1958)
AND people.name != 'Kevin Bacon';