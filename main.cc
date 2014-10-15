#define ARGUMENT_COUNT 6

#include <iostream>
#include <iomanip>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <cstdint>
#include <ctime>
#include <mpi.h>
#include <sys/time.h>

using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::uint8_t;
using std::uint16_t;
using std::uint32_t;

long getTime (struct timeval time_begin, struct timeval time_end) {
  return (time_end.tv_sec*1000000 + time_end.tv_usec) -
    (time_begin.tv_sec*1000000 + time_begin.tv_usec);
}

int main(int argc, char **argv) {
  assert(argc == ARGUMENT_COUNT);
  int input_size = atoi(argv[1]);
  int a0 = atoi(argv[2]);
  int b0 = atoi(argv[3]);
  int p0 = atoi(argv[4]);
  int x0 = atoi(argv[5]);
  assert(input_size > 0);
  assert(a0 > 0);
  assert(b0 > 0);
  assert(p0 > 0);
  assert(x0 > 0);
  int rank;
  int process_count;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &process_count);

  struct timeval time_begin;
  if(rank == 0)
    gettimeofday(&time_begin, NULL);
  struct timeval time_end;
  long runtime = 0;
  if(rank == 0) {
    gettimeofday(&time_end, NULL);
    runtime += getTime(time_begin, time_end);
    printf("%d %d %ld \n", process_count, input_size, runtime);
  }
  MPI_Finalize();
  return 0;
}
