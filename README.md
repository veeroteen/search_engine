# search_engine
Programm that realize searching and ranking by requested words, in local text files. 

# About config.json
Config has 3 fields and an array with files path.

name - just name

version - just version

max responses - limit maxim count of responses per request

files - array of paths to files

# About request.json
Just array of requests

# About answer.json

Created after the program has run

Contains answer to all requsts per run

Answer to request contains result, that can be true or false, and docid with rank, if result was true. 

Instead of docid and rank, can be array with relevance name, that contains same thing but more than one.