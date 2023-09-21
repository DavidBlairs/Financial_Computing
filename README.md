# Financial Computing

This is my assignments for the "Financial Computing" module offered to masters students at Brunel University London. The course was comprised of two terms. The first term was to build up an understanding of the C programming language and introduct multi-threading using OpenMP. The second term involved more advanced C functionality as well as multi-processing using MPI. Below is a break down of the code created over the duration of this module:

## Assignment 1 

### Task 1: Word Count Utility

1. **Purpose**

   The C code `mywc.c` serves as a simple word count utility. It takes a filename as an argument, reads the file character by character, and counts the number of words in the file. It defines a word as a sequence of characters separated by spaces or newlines.

2. **Main Function**

   - `main(int argc, char** argv)`: The main function takes command-line arguments, where `argc` represents the number of arguments, and `argv` is an array of strings containing the program name and the filename to be processed.

3. **Functionality**

   - Argument Validation: It checks if the correct number of arguments (one filename) is provided. If not, it displays an error message.

   - File Handling: It attempts to open the specified file for reading. If the file cannot be opened, it displays an error message.

   - Word Count: It reads the file character by character, counting words based on spaces or newlines as separators. It uses a variable `lock` to avoid counting consecutive separators as multiple words.

   - Printing Result: It prints the number of words found in the file.

4. **Usage**

   To use the program, run it from the command line with the following format:

   ```
   mywc [filename]
   
   ```

   Replace `[filename]` with the name of the file you want to count words in.

### Task 2: Power Iteration Algorithm

This C code `matrix_*.c` implements the power iteration algorithm to find the largest eigenvalue of a matrix `A`. The purpose of this algorithm is to approximate the dominant eigenvalue and corresponding eigenvector of a given matrix. It does so by repeatedly multiplying the matrix `A` by a vector and normalizing the result until convergence.

#### Functions

- `double F(double z)`: This function computes a mathematical function of `z`.

- `double A_N(int N)`: The main function for performing the power iteration algorithm. It initializes matrices and vectors, populates the matrix `A`, and iteratively computes the dominant eigenvalue and eigenvector.

#### Algorithm Steps

1. Matrix Initialization: It initializes various matrices and vectors required for the algorithm.

2. Matrix Population: It populates the matrix `A` based on the function `F(z)`.

3. Vector Initialization: It sets an initial vector `x` for the power iteration.

4. Power Iteration Loop: It repeatedly performs the following steps until convergence (controlled by `e`):
   - Matrix-Vector Multiplication: Computes `y = Ax`.
   - 2-Norm Computation: Calculates the 2-norm of vector `y`.
   - Eigenvalue Approximation: Computes the eigenvalue approximation `lambda` as the dot product of `x` and `y`.
   - Vector Update: Sets `x` to be the normalized vector `y`.
   - Convergence Check: Computes the 2-norm of the difference between the current `x` and the previous `z` to determine convergence.

5. Results: It prints the results, including the number of iterations, the estimated dominant eigenvalue (`lambda`), and the duration of the algorithm.

6. Memory Cleanup: It frees the dynamically allocated memory.

#### Main Function

The `main` function takes user input for the number of iterations (`N`) and calls the `A_N` function to perform the power iteration algorithm.

#### Input Validation

The code includes input validation to ensure that `N` is a positive integer.

#### Parallelization

This code utilizes OpenMP for parallelization, potentially speeding up matrix operations on multi-core processors.

### Task 3: Numerical Integration with OpenMP

1. **Purpose**

   The C code `quadrature_*.c` performs numerical integration using the trapezoidal rule with OpenMP parallelization. It calculates the integral of the function `u(x) = exp(x) * sin(x)` over the interval `[1, 2]` for various values of the number of segments (`N`) and measures the execution time and error.

2. **Main Function**

   - `main()`: The main function carries out the numerical integration for different values of `N` and measures the execution time and error.

3. **Functionality**

   - Variable Setup: It initializes variables for error, calculated value (`total`), segment width (`h`), start time (`s_time`), end time (`e_time`), time duration (`time`), and expected value (`f_ex`), among others.

   - Iterating Over `N`: It iterates over a range of `N` values from 1 to 1024 (increasing in powers of 2).

   - Integration Calculation: For each `N`, it scales `N` to a larger value (`N_s`) to control the number of segments. It then calculates the width of segments (`h`) and performs numerical integration using the trapezoidal rule in parallel using OpenMP.

   - Time Measurement: It measures the execution time (`time`) for each integration calculation.

   - Error Calculation: It calculates the absolute error between the calculated integral (`total`) and the expected value (`f_ex`).

   - Result Printing: It prints the results, including the number of threads used, the scaled `N` value, the calculated integral, the error, and the duration for each `N`.

4. **Parallelization**

   The code utilizes OpenMP to parallelize the integration calculations, with the number of threads set to `NUM_THREADS`.

5. **Usage**

   The code is designed to be run as a standalone program, and it automatically performs the numerical integration for various values of `N`.

## Assignment 2

### Task 1: Parallel Matrix Computation and Performance Analysis

1. **Purpose**

   This C code `1_matrix_*.c` serves two main purposes:
   
   - It performs parallel matrix computation using OpenMP. Specifically, it calculates a matrix `A` with certain properties.
   
   - It analyzes the performance of the matrix computation in terms of execution times and speed-up for varying numbers of threads.

2. **Matrix Computation**

   - `double F(double z)`: This function computes a mathematical function of `z` used in the matrix computation.
   
   - `double A_N(int N)`: The main function for matrix computation. It initializes matrices and vectors, populates the matrix `A` in parallel, and measures the execution time.

   - Matrix Initialization: The code dynamically allocates memory for matrices and vectors and initializes variables for computation.
   
   - Parallel Matrix Population: It utilizes OpenMP parallelization to populate the matrix `A` based on a specific formula.

   - Execution Time Measurement: It measures the execution time of matrix computation and returns it.

3. **Performance Analysis**

   - `int populate_times(int N, double* times, double* speeds)`: This function analyzes the performance of matrix computation for different numbers of threads. It measures execution times and calculates speed-up values.

   - Main Function (`main()`): The main function iterates through different values of `N`, measures execution times, and computes speed-up values. It then prints the results in a tabular format.

   - Table Output: It generates a table showing execution times and speed-up for various `N` values and numbers of threads.

4. **Parallelization**

   The code uses OpenMP to parallelize the matrix computation and performance analysis, allowing it to utilize multiple threads for faster execution.

5. **Usage**

   The code is designed to be run as a standalone program. It automatically performs matrix computation and performance analysis for different `N` values and numbers of threads, generating a performance table.

### Task 2: Parallel Matrix Computation and Power Iteration with MPI

1. **Purpose**

   The C code `2_matrix_1.c` is designed to perform parallel matrix computation and power iteration using MPI (Message Passing Interface). The main goals of this code are as follows:
   
   - Calculate a matrix `A` with specific properties in parallel.
   
   - Perform power iteration to approximate the largest eigenvalue of `A` in parallel.
   
   - Measure and report the execution times for matrix setup and power iteration.

2. **Matrix Setup**

   - The matrix `A` is set up in parallel. Each process is responsible for computing a portion of the matrix.

   - `double F(double z)`: This function computes a mathematical function of `z` used in the matrix computation.

3. **Power Iteration**

   - The power iteration algorithm is parallelized using MPI. Each process participates in the computation.

   - `matVecMul()`: This function performs matrix-vector multiplication in parallel.

   - `calcNorm2()`: Calculates the 2-norm of a vector.

   - `dotProduct()`: Computes the dot product of two vectors.

   - `vecSub()`: Performs vector subtraction.

   - The power iteration loop continues until the convergence condition is met.

4. **MPI Initialization and Communication**

   - The code uses MPI for parallelism, initializing processes and facilitating communication between them.

   - `MPI_Init()`, `MPI_Comm_rank()`, and `MPI_Comm_size()` are used to set up the MPI environment.

   - `MPI_Bcast()` is used to broadcast the problem size `n` to all processes.

   - `MPI_Allgather()` is used for communication during matrix-vector multiplication.

5. **Usage**

   To run the program, provide the problem size `n` as a command-line argument:

   ```
   mpiexec -np [num_processes] ./program_name [n]
   
   ```

   Replace `[num_processes]` with the desired number of MPI processes and `[n]` with the problem size.







