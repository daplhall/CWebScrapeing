# (WIP) A simple webscraper for C
![#f03c15](https://placehold.co/15x15/f03c15/f03c15.png) The project is currently WIP, and as such the README and program is not finished.  

The goal of this project is just to write a scraper in C for the enjoyment of writing a web scraper in C (it would be better to do in python). I want it to be able to scrape html and APIs, then upload them to a postgres database. This pipeline needs to be simple and extendable.
# Prerequisites
The program needs [`libcurl`](https://github.com/curl/curl), [`libxml2`](https://github.com/GNOME/libxml2) and googles [`Robotstxt`](https://github.com/google/robotstxt)

# Licensing
My own code is licensed under MIT, however `robottxt` is under apache. The build setup just clones the `robottxt` repo, and links it statically. Do with that what you will.


# Todo
1. Finish `robottxt` integration, to do ethical scraping.
2  Utilize [Curl impersonate](https://github.com/lexiforest/curl-impersonate) so the scraper can mask it 
self as a browser (is a bit paradoxical to 1)
3. write "user" callback for writing to postgres db, which i can spin up with docker.
4. This is a maybe: Further test better ways if importing `robottxt` as it uses the a decrepit cmake version.

# TODO today
1. Refactor the code!
2. write tests
3. begin on url parser.
4. Be done with robottxt

# CLangd
Currently integrated into config presets, should be a user preset
```
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1
```
