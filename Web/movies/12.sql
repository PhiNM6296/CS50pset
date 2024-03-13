SELECT title
FROM (
    SELECT movie_id
    FROM stars
    WHERE person_id = (SELECT id FROM people WHERE name ='Bradley Cooper')
) AS BC
JOIN (
    SELECT movie_id
    FROM stars
    WHERE person_id = (SELECT id FROM people WHERE name ='Jennifer Lawrence')
) AS JL ON BC.movie_id = JL.movie_id
JOIN movies ON BC.movie_id = movies.id;
