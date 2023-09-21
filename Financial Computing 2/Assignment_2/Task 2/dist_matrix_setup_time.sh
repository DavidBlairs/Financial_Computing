#f N and M
N_VALUES=(256 512 1024 2048 4096)
M_VALUES=(1 2 4 8)

# Initialize the results arrays
declare -A results

# Iterate over the values of N and M
for N in "${N_VALUES[@]}"; do
  for M in "${M_VALUES[@]}"; do
    echo "Running program for N=$N and M=$M"

    # Generate host string
    HOSTS=""
    for (( i=1; i<=$M; i++ ))
    do
      HOSTS+="heron$i,"
    done
    HOSTS=${HOSTS%?} # To remove the trailing comma

    echo "mpirun -H $HOSTS ./2_matrix_1 $N"

    output=$(mpirun -H $HOSTS ./2_matrix_8 $N)
    matrix_setup_time=$(echo "$output" | awk '/Matrix Setup Time:/ {print $4}')
    results["$N,$M"]=$matrix_setup_time
    echo ""
  done
done

# Print the results table
printf "%10s" "N/M"
for M in "${M_VALUES[@]}"; do
  printf "%12s" "$M"
done
echo ""

for N in "${N_VALUES[@]}"; do
  printf "%10s" "$N"
  for M in "${M_VALUES[@]}"; do
    time=${results["$N,$M"]}
    printf "%12s" "$time"
  done
  echo ""
  if [[ ${results["$N,1"]} ]]; then
    printf "%10s" "Speedup:"
    for M in "${M_VALUES[@]}"; do
      if [[ $M -eq 1 ]]; then
        speedup=0.0
      else
        time=${results["$N,$M"]}
        baseline_time=${results["$N,1"]}
        speedup=$(awk "BEGIN {printf \"%.6f\", $baseline_time - $time}")
      fi
      printf "%12s" "$speedup"
    done
    echo ""
  fi
done