# ft_containers_WIP
## Implementation of C++ STL containers
* Vector
* Stack
* Map
* Set (bonus)

## Run container tests:
* Pass one or more container names to "test_container":
```bash
./test_container <container1> <container2> ...
```

## Dockerfile usage for leaks testing:
```bash
docker build -t ft_containers .
docker run -it ft_containers bash
make <container_name>; valgrind ./ft_<container_name>
```
## Speed testing
```bash
cd speed
./compile_speed_test.sh
time ./ft_speed <seed>
time ./std_speed <seed>
```
"seed" must be a positive integer and is used to generate random values
