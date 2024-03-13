WITH Bosma_movies AS(
    SELECT title, id
    FROM movies
    WHERE id IN (
        SELECT movie_id FROM stars WHERE person_id = (
            SELECT id FROM people WHERE name = 'Chadwick Boseman'
        )
    )
)
SELECT title
FROM Bosma_movies JOIN ratings ON movie_id = id
ORDER BY rating DESC LIMIT 5;
