
/** @file source_fusion.cpp
 * @brief The main function for the Sensor Fusion Project.
 */

// All C++ Headers
#include <iostream>
#include "../inc/sensor_fusion_common.hpp"
#include "../inc/sensor_fusion_implementation.hpp"
#include "../inc/fusion_algorithm.hpp"

#ifdef __cplusplus
extern "C" {
#endif

// All C Headers go here

#ifdef __cplusplus
}
#endif

void print_usage() {
//TODO: fill this

}

int main(int argc, char *argv[]) {

    SensorsList_t list;

    Sensor_t sensor = {.value=49, .time=make_time("12:00"), .name = "sens1"};
    Sensor_t sensor2 = {.value=54.7, .time=make_time("12:00"), .name = "sens2"};
    Sensor_t sensor3 = {.value=53.2, .time=make_time("12:00"), .name = "sens3"};
    Sensor_t sensor4 = {.value=54, .time=make_time("12:00"), .name = "sens4"};
    Sensor_t sensor5 = {.value=52.6, .time=make_time("12:00"), .name = "sens5"};
//    Sensor_t sensor6 = {.value=53.2, .time=make_time("12:00"), .name = "sens6"};
//    Sensor_t sensor7 = {.value=53.3, .time=make_time("12:00"), .name = "sens7"};
//    Sensor_t sensor8 = {.value=52.5, .time=make_time("12:00"), .name = "sens8"};


    list.push_back(sensor);
    list.push_back(sensor2);
    list.push_back(sensor3);
    list.push_back(sensor4);
    list.push_back(sensor5);
//    list.push_back(sensor6);
//    list.push_back(sensor7);
//    list.push_back(sensor8);

    double fused = perform_sensor_fusion(list, 0.85, 0.7);

    printf("%f", fused);



//    double x[5] = {0.8, 0.4, 0.86, 0.5, 0.95};
//    double x = {4.8, 3.4, 2.8, 1.5, 0.5};
//
//    double* contribution_rates = {0.8, 0.4, 0.86, 0.5, 0.95};
//    double* principal_components = {4.8, 3.4, 2.8, 1.5, 0.5};
//
//    int number_of_sensors = list.size();
//
//    int rates_to_be_deleted_indices[number_of_sensors];
//    int deleted_count = select_contribution_rate(rates_to_be_deleted_indices, contribution_rates, number_of_sensors, 0.85);
//
//    for (int i = 0; i < deleted_count; ++i) {
//        delete_element_from_double_array(principal_components, rates_to_be_deleted_indices[i]-i, number_of_sensors);
//        list.erase(list.begin()+rates_to_be_deleted_indices[i]-i);
//        number_of_sensors--;
//    }



//    double * res = get_degree_matrix(list);
//
//    printf("Printing Support Degree Matrix");
//    for (int i = 0; i < 9; ++i) {
//        count++;
//        printf("res: %f\n,", res[i]);
//    }
//
//    double ** vector = (double**) malloc(3*sizeof(double*));
//    double * values = (double*) malloc(3*sizeof(double));
//
//    get_eigenvalues_and_vectors(res, 3, values, vector);
//
//    for (int i = 0; i < 3; ++i) {
//            count++;
//            printf("%f\n,", values[i]);
//    }
//
//    printf("Printing Weights\n");
//
//    double inti[5] = {1.0, 1.0, 1.0, 1.0, 1.0};
//    double * coff = get_weight_coefficients(inti, 5);
//    for (int i = 0; i < 5; ++i) {
//        printf("weights: %f\n", coff[i]);
//    }
//
//
//    printf("The count is: %d", count);

//    setbuf(stdout, NULL);
//    printf("Program Name: %s\n", argv[0]);
//    printf("Number of arguments: %d\n", argc);
//    //TODO: ask user to provide column data in file
//
//    int ret = 0;
//
//    if (1 == argc) {
//        print_usage();
//        return 0;
//    } else if (2 == argc) {
//        /**
//         *         argv[1] is assumed to be a filename to open.
//         *         If only the file name is provided default values will be used:
//         *
//         *         sensos_stuck_interval default is: 10 minutes
//         *         fusion_interval_minutes default is: 2 minutes
//         */
//        ret = parse_file(argv[1]);
//        return ret;
//    } else if (3 == argc) {
//        /**
//         *         argv[2] is assumed to be a elapsed time to determine if a sensor is stuck.
//         *         argv[2] is validated to check if the values entered are digits.
//         *         argv[2] is validated if it is within range (0 to 59 minutes).
//         *         fusion_interval_minutes default value is used here: 2 minutes
//         */
//
//        if (0 == are_digits(argv[2])) {
//
//            int sensos_stuck_interval = validate_interval(argv[2]);
//
//            if (-1 != sensos_stuck_interval) {
//
//                ret = parse_file(argv[1], sensos_stuck_interval);
//                return ret;
//            }
//        }
//
//    } else if (4 == argc) {
//        /**
//         *         argv[2] is assumed to be a elapsed time (in minutes) to determine if a sensor is stuck
//         *         argv[3] is a tolerance range (in minutes) to fuse sensors within that range
//         *
//         *         argv[2] and argv[3] are validated to check if the values entered are digits
//         *         argv[2] and argv[3] are validated if it is within range (0 to 59 minutes).
//         */
//
//        if (0 == are_digits(argv[2]) && 0 == are_digits(argv[3])) {
//
//            int sensos_stuck_interval = validate_interval(argv[2]);
//            int fusion_interval = validate_interval(argv[3]);
//
//            if (-1 != fusion_interval && -1 != sensos_stuck_interval) {
//
//                ret = parse_file(argv[1], sensos_stuck_interval, fusion_interval);
//                return ret;
//            }
//        }
//    } else {
//
//        printf("Incorrect number of arguments\n");
//        print_usage();
//    }
    return 0;

}
