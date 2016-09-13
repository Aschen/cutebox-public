# cutebox

Cutebox is a small backup tool written in C++11 with QT.  
The program is divided in two part, the server part and the client part.

The server who authenticate and store the data sended by the client. (Almost file backup)

The client who have a list of watched files and check every 30 sec if there is a modification.  
If a modification is identified, the client send the smallest amount of data that represent this modification.  
For each file, the client split the file in chunks and compute the corresponding hash. As it is very fast to identify modification in a file.  

This project has been developped in collaboration with [RG System](http://github.com/rgsystemes/) and it contains some copyrighted materials who are not present in this repository. 

## Server

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
