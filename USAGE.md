# Introduction

With the uncertainty that comes with data from multi-sensory systems, the sensor fusion algorithm reduces and tries to eliminate the incorrect data. Since amongst the multiple sensory data received at different time intervals, only a single value is needed at a particular time.

The software takes input data from an csv file, the file is provided in the following format:

| Time | SensorName | Value
| ------ | ------ | ------ |
| 10:45 |sens1| 10.5

**Note: The order of the columns should exactly match the above format for correct parsing.**

The following time formats are both accepted by the program  `10:45` or `10.45`.
 
A sensor fusion algorithm is executed for each group of sensors received synchronously (at the same time). The software will determine if there are sensors that are stuck, or if there are invalid date to be ignored.

# Usage

```sh
SourceFusion.exe filename contribution_p tolerance stuck_interval fusion_interval
```

  **filename**              : The name of the file with the input values. (required).
  **contribution_p**        : The p parameter used in contribution rate selection (default = 85%).
  **tolerance**             : The tolerance ratio used in fault tolerance elimination process (default = 70%).
  **stuck_interval**        : The minimum interval where if a sensor doesn't change value it's considered stuck. (default = 10)
  **fusion_interval**       : The maximum interval where sensor values are fused. (default = 2).
  
  
Example:

To execute a command that will parse the file input.csv with:
 contributon_p = 49%
 Tolerance = 60%
 Stuck interval = 25 minutes
 Fusion interval = 4 minutes
 
 You need to navigate to the bin folder and run the following command:
 
```sh
cd bin;
./FusedOutput input.csv 49 25 4
```
To use your own .csv file, put it in the data directory and replace the file name in the command above
  
# Installation

Installation instructions can be found in [INSTALL.md](https://github.com/aminabukoash/sourcefusion/blob/master/INSTALL.md) 

# Run Tests
Navigate into the created bin directory and execute the test binaries

```sh
cd bin;
./TESTS
```

# Print Usage

User can run the below command to know the details about input parameters. (you have to be in the bin directory)

```
./FusedOutput
```

# Output File Generation

The output file will be generated after executing the sensor fusion software.

*/data/fused_outputs.csv* will contain the fused output.

*/data/sensors_with_incorrect_data.txt* will contain sensors with incorrect data.


