# ft_containers_WIP
## Implementation of c++ STL containers
* Vector
* Stack
* Map
* Set (bonus)

## Run container tests:
* Pass one or more container names to "test_container":
** ./test_container <container1> <container2> ...

## Dockerfile usage for leaks testing:
* docker build -t ft_containers .
* docker run -it ft_containers bash
* then: "make <container_name>" and run executables with valgrind