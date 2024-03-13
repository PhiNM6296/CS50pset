SELECT AVG(rating) AS avg_rating_2012
FROM ratings JOIN movies ON movie_id = id
WHERE year = 2012;
