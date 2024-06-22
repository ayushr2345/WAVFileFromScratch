# WAVFileFromScratch
A project for creating WAV file using C++. 
<br>
The type of wave, frequency, amplitude and the duration 
is taken as input from the user and a WAV file is generated 
using those parameters. By default it produces a wave with 
frequency of 440 Hz (A note) for 5 seconds and amplitude of 0.5.
<br>
Supported waves:
* Sine wave
* Square wave
* Triangle wave
* Sawtooth wave

<br>

This project took inspration from 
[Akash Murthy's youtube channel](https://www.youtube.com/watch?v=qqjvB_VxMRM&list=PLrs18WYDlpOKi-R7YqpIPPqMSL8Tvmsd4&index=5)
and additional functionalities with types of waves have been added.

## Compilation
### To compile project using CMake:
* Create a folder named build: ``` mkdir build ```
* Change directory to build folder: ``` cd build ```
* Run command: ``` cmake build ..```
* Run command: ``` make ```
* Execute the binary named WAVFileFromScratch: ``` ./WAVFileFromScratch ```


### To compile project using Visual Studio
* Open the ``` WAVFileFromScratch.sln ``` file in Visual Studio
* Goto ``` Build -> Build WAVFileFromScratch ```
* After the build is complete, click on the green arrow to execute the binary 


### To compile project using CMake in Visual Studio
* Open Visual Studio
* Click on ``` File -> Open -> CMake ``` and select the CMakeLists.txt
* Change the target to ``` WAVFileFromScratch.exe ```
* Click on the green arrow to start the build and execution
