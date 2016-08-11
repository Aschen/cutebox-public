# cutebox


## Server

 - Go to ```cutebox/cutebox/``` and run ```qmake && make```
 - Launch ```./cutebox srv```

## Client

 - Launch ```./cutebox cli```
 
### Client Usage

 - ```connect <host>``` : Connect the client to the server
 - ```login <email> <password>``` : Authenticate client
 - ```addfile <filepath>``` : Add a file to be watched
 - ```check``` : Force change detection
 - ```help``` : Display help
 - ```exit``` : Quit program

## Populate database

 - ```./cutebox seed```

## Tests

### ORM tests 

 - ```cd sql/tests/ && sh create_project.sh && qmake && make``` : Compile tests
 - ```./tests``` : Run tests
 
### Client tests

 - ```cd client/tests/ && sh create_project.sh && qmake && make``` : Compile tests
 - ```./tests``` : Run tests
