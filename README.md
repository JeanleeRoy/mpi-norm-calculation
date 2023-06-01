# Norm computing with MPI

## Dependencies

For this project we need the `mpic++` wrapper compiler. You can install it with:

```
sudo apt install openmpi-bin
```
## Compiles 

```
mpic++ <mpi_code.cpp>
```

## Run 

```
mpirun [-np <N_CORES>] ./a.out
```

## Profiling

Here we are using [valgrind](https://valgrind.org/)

```
valgrind --leak-check=yes ./a.out
```