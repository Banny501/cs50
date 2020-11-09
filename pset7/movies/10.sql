SELECT name FROM directors JOIN ratings ON directors.movie_id = ratings.movie_id JOIN people ON people.id = directors.person_id WHERE rating >= 9 GROUP BY id;
