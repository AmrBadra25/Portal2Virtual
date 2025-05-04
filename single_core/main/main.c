#include "main.h"

int main() {

    // array to hold the output in L2 memory
    fixed_point_t output_r[DATA_SIZE];
    fixed_point_t output_i[DATA_SIZE];

    Statistics_S correct_stats = {0};
    Statistics_S wrong_stats = {0};
    // Initialize actuator structure
    Actuator_S actuator = {0};  // Initialize all fields to zero

    // Processing loop
    for (int i = 0; i < DATA_SIZE; i++) {  
        // Load input and expected output
        actuator.in_r = input_r[i];
        actuator.in_i = input_i[i];
        fixed_point_t exp_r = expected_r[i];
        fixed_point_t exp_i = expected_i[i];

        // Perform DPD operation
        actuator_func_single(&actuator);

        // Convert to double for analysis
        double in_r = fixed_to_double(actuator.in_r);
        double in_i = fixed_to_double(actuator.in_i);
        double exp_r_double = fixed_to_double(exp_r);
        double exp_i_double = fixed_to_double(exp_i);
        double out_r = fixed_to_double(actuator.out_r);
        double out_i = fixed_to_double(actuator.out_i);

        // Store results in output arrays
        output_r[i] = actuator.out_r;
        output_i[i] = actuator.out_i;

        // Check if output matches expected
        if (abs(exp_r - actuator.out_r) <= MARGIN && abs(exp_i - actuator.out_i) <= MARGIN) {
            //printf("Correct output\n");
            // Perform statistical analysis on correct outputs
            statistical_analysis(in_r, in_i, out_r, out_i, exp_r_double, exp_i_double, &correct_stats);
        } else {
            //printf("Wrong output\n");
            // Perform statistical analysis on wrong outputs
            statistical_analysis(in_r, in_i, out_r, out_i, exp_r_double, exp_i_double, &wrong_stats);
        }
    }
    print_analysis_report(&correct_stats, &wrong_stats);


    return 0;  // Return success
}

