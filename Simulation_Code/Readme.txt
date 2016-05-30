Useage of Simulation Mode in SGX Enhanced Application

Intel® Software Guard Extensions (Intel® SGX): 
          Intel® Software Guard Extensions (Intel® SGX) is an Intel technology for application developers who are seeking to protect select code and data from disclosure or modification. Intel SGX makes such protections possible through the use of enclaves, which are protected areas of execution. Application code can be put into an enclave by special instructions and software made available to developers via the Intel® SGX SDK. The Intel SGX SDK is a collection of APIs, libraries, documentation, sample source code, and tools that allows software developers to create and debug Intel SGX enabled applications in C/C++. 

Benefits of Intel SGX enclave:
          1. New Intel SGX instructions introduced with 6th Generation Intel® Core™ processor platforms.
          2. Relies on an Intel-provided driver and/or the OS for access to Intel SGX instructions and resource management.
          3. Executes within the context of its parent application, thereby benefiting from the full power of the Intel® processor.
          4. Reduces the trusted computing base of its parent application to the smallest possible footprint.
          5. Remains protected even when the BIOS, VMM, OS, and drivers are compromised, implying that an attacker with full execution control over the platform can be kept at bay.
          6. Benefits from memory protections that thwart memory bus snooping, memory tampering and “cold boot” attacks on images retained in RAM.
          7. Uses hardware-based mechanisms to respond to remote attestation challenges that validate its integrity.
          8. Can work in concert with other enclaves owned or trusted by the parent application.
          9. Can be developed using standard development tools, thereby reducing the learning curve impact on application developers.

Download the SDK from following path:
          https://software.intel.com/en-us/sgx-sdk

Software Requirements:
          1. Microsoft Windows* 7/ 8.1/10 64-bit version
          2. Microsoft Visual Studio* 2012 Professional/Ultimate Edition only
          3. Intel® Parallel Studio XE Professional Edition for Windows* Version 2013

Supported Languages:
          Enclave binding interface supported in C/C++ only

How to Use Simulation Mode in SGX Enhanced Application:
          Using the Simulation Libraries to run application enclaves in simulation mode (Intel® SGX hardware is not required). 

What is Simulation Libraries:
          The Intel® SGX Evaluation SDK provides simulation libraries to run application enclaves in simulation mode (Intel® SGX hardware is not required).
          There are an untrusted simulation library and a trusted simulation library. 
          The untrusted simulation library provides the functionality that the untrusted runtime library requires to manage an enclave linked with the trusted simulation library, including the simulation of the Intel® SGX instructions executed outside the enclave: ECREATE, EADD, EEXTEND, EINIT, EREMOVE, and ECREATE. 
          The trusted simulation library is primarily responsible for simulating the Intel® SGX instructions that can executed inside an enclave: EEXIT, EGETKEY, and EREPORT.

"The simulation mode works in the same way as the debug mode except the fact that true hardware is not exercised, instead the Intel® SGX instructions are simulated in software."

Create a Enclave and Application project using Microsoft Visual Studio* 2012 Professional/Ultimate Edition or Intel® Parallel Studio XE Professional Edition for Windows* Version 2013. 

Follow the below steps to developed an SGX Enhanced Application
          Step 1: Create Enclave Project
          Step 2: Define Enclave Interface
          Step 3: Import Enclave to Application
          Step 4: Implement Application and Enclave Functions
          Step 5: Compilation and Execution

Step 1: Create Enclave Project:
          You can use Microsoft* Visual Studio* Intel® Software Guard Extensions Wizard to create an enclave project. See Step by Step Enclave Creation for the detailed steps.

Step 2: Define Enclave Interface:
          Use an EDL file to define the enclave interface, which exposes a trusted interface

Step 3: Import Enclave to Application:
          To call the enclave interface in the application, import the enclave to the application using Microsoft* Visual Studio* Intel® Software Guard Extensions Add-in.
                    1. Right click the application project and select Intel® SGX Configuration -> Import Enclave. The Import Enclave dialog box opens.
                    2. Check the sample_enclave.edl box and press OK.

Step 4: Implement Application and Enclave Functions:
          Implement the application and enclave functions

Step 5: Compilation and Execution
          Now you can compile the application and enclave projects. After the compilation, set the working directory to the output directory and run the program.

Project Settings:
          This section introduces the following project settings:
                    1. Recommended Project Settings for an Enclave Project.
                    2. Recommended Project Settings for an Untrusted Application.
          To configure the project settings in Microsoft* Visual Studio*, right click the project name in Solu-tion Explorer and select Properties from the context menu.

1. Recommended Project Settings for an Enclave Project:
For an enclave, default project settings are recommended, with the following exceptions:
          C/C++->General->Additional Include Directories:
                    $(SGXSDKInstallPath)include;$(SGXSDKInstallPath)include\t-libc;$(SGXSDKInstallPath)include\stlport;

          Linker->General->Additional Library Directories:
                    $(SGXSDKInstallPath)bin\$(Platform)\$(Configuration)

          Linker->Input->Additional Dependencies:
                    HW Configuration: sgx_trts.lib; sgx_tservice.lib; sgx_tstdc.lib; sgx_tstdcxx.lib; sgx_tcrypto_opt.lib - This is not use for  Simulation mode. Used for DEBUG mode 
                    Simulation Configuration: sgx_trts.lib_sim; sgx_tservice_sim.lib; sgx_tstdc.lib; sgx_tstdcxx.lib; sgx_tcrypto.lib

          Linker->Input->Ignore All Default Libraries:Yes (/NODEFAULTLIB)

          Linker->Advanced->No Entry Point:Yes

          To sign the enclave during the build process, set a custom build step in the project settings:
                     Build Events->Post-Build Event->Command Line:
        "$(SGXSDKInstallPath)bin\win32\release\sgx_sign.exe" sign -key "$(Pro-jectDir)sample_enclave_private.pem" -enclave "$(OutDir)sample_enclave.dll" -out "$(OutDir)sample_enclave.signed.dll" -config "$(ProjectDir)sample_enclave.config.xml"

                     NOTE: The signing command line is a sample command. Change the command line based on the actual enclave name.
    
                      Build Events->Post-Build Event->Use In Build:Yes

2. Recommended Project Settings for an Untrusted Application:
Use the default project settings for an untrusted application, with the following additional settings:
          C/C++->General->Additional Include Directories: $(SGXSDKInstallPath)include;

          Linker->General->Additional Library Directories: $(SGXSDKInstallPath)bin\$(Plat-form)\$(Configuration)

          Linker->Input->Additional Dependencies:
                  HW Configuration: sgx_uae_service.lib; sgx_urts.lib - This is not use for Simulation mode. Used for DEBUG mode 
                  Simulation Configuration: sgx_uae_service_sim.lib; sgx_urts_sim.lib

Now we are able to run application enclaves in simulation mode (Intel® SGX hardware is not required) using Intel® SGX Evaluation SDK provides simulation libraries.
