// All C++ Headers
#include "../inc/sf_common.hpp"

#ifdef __cplusplus
extern "C" {
#endif

// All C Headers go here

#ifdef __cplusplus
}
#endif

/**
 *  Adds the second float vector to the first one.
 * @param dest The vector that will be added to.
 * @param src The vector that will be used to add.
 * @param vector_size the size of the vectors.
 */
//float* vector_add(float* dest, float* src, int vector_size){
//    for (int i = 0; i < vector_size; ++i) {
//        dest[i] += src[i];
//    }
//}
/**
 *  Multiplies a vector by a float scalar value.
 * @param vector The vector that will be multiplied.
 * @param vector_size the size of the vectors.
 * @param scalar the scalar that will be used to multiply of the vectors.
 */
float* vector_scalar_multiply(float *vector,
                              int vector_size,
                              float scalar)
{
    for (int i = 0; i < vector_size; ++i)
    {
        vector[i] *= scalar;
    }
    return vector;
}

//float** get_degree_matrix(float* values){
//
//}

//float* get_eignvalues(float** degree_matrix){
//
//}
//
//float** get_eignvectors(float** degree_matrix){
//
//}
//
//float* get_principal_components(float* eignvalues, float** eignvectors){
//
//}

float* get_contribution_rates(float *eignvalues,
                              int number_of_sensors)
{
    float *contribution_rates = (float*) malloc(number_of_sensors
                                                * sizeof(float));
    float eignvalue_sum = 0.0;
    for (int i = 0; i < number_of_sensors; ++i)
    {
        eignvalue_sum += eignvalues[i];
    }
    for (int i = 0; i < number_of_sensors; ++i)
    {
        contribution_rates[i] = eignvalues[i] / eignvalue_sum;
    }
    return contribution_rates;
}

float* get_cumulative_contributions(float *contribution_rates,
                                    int number_of_sensors)
{
    float *cumulative_contributions = (float*) malloc(number_of_sensors
                                                      * sizeof(float));
    for (int i = 0; i < number_of_sensors; ++i)
    {
        cumulative_contributions[i] = 0.0;
        for (int j = 0; j <= i; ++j)
        {
            cumulative_contributions[i] += contribution_rates[j];
        }
    }
    return cumulative_contributions;
}

float* get_integrated_support_score(float **principal_components,
                                    float *contribution_rates,
                                    int number_of_sensors)
{
    float *integrated_scores = (float*) malloc(number_of_sensors
                                               * sizeof(float));
    for (int i = 0; i < number_of_sensors; ++i)
    {
        float *score = vector_scalar_multiply(principal_components[i],
                                              number_of_sensors,
                                              contribution_rates[i]);
//        vector_add(integrated_scores, score, number_of_sensors);
    }
    return integrated_scores;
}

//float* get_weight_coefficients(float* integrated_scores){
//
//}
//
//float get_fused_output(float* sensor_values, float* weight_coefficients){
//
//}
