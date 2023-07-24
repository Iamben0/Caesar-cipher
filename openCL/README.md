# Set up OpenCL Environment with Visual Studio 2022 

This readme file summarizes the steps to create a new Visual Studio project for using OpenCL with the AMD APP SDK.

## Prerequisites

Before proceeding with the setup, ensure you have the following installed:

- Visual Studio
- AMD APP SDK 3.0

## Steps

1. **Create a New Visual Studio Project:**
   - Open Visual Studio and select "Create a new project".
   - Choose "Empty Project" and click "Next".
   - Enter a project name, a location, and a solution name, then click "Create".

2. **Add Existing Files (Optional):**
   - If you have existing files for the project, place them in the solution directory.
   - Add them to the project by right-clicking on the appropriate folder in Solution Explorer and selecting "Add" -> "Existing Item".

3. **Open Project Properties:**
   - Right-click on the project name in Solution Explorer and select "Properties".

4. **Configure for All Configurations (Win32):**
   - At the top of the Property Pages window, ensure "All Configurations" and "Active(Win32)" are selected.

5. **Include Directories:**
   - Under Configuration Properties -> VC++ Directories, add `C:\AMD APP SDK\3.0\include` to the Include Directories.

6. **Library Directories:**
   - Under Configuration Properties -> VC++ Directories, add `C:\AMD APP SDK\3.0\lib\x86` to the Library Directories.

7. **Additional Dependencies:**
   - Under Configuration Properties -> Linker -> Input, add `OpenCL.lib` to the Additional Dependencies.

8. **Apply Changes:**
   - Click "Apply" and then "OK" to save the changes.

9. **Compile and Run:**
   - To compile and run the code, make sure "x86" is selected as the active platform.
   - Click on the "Start" button or press `F5`.

## Conclusion

Following these steps, you should now have a working Visual Studio project set up to use OpenCL with the AMD APP SDK. You can start developing OpenCL applications and take advantage of GPU acceleration for parallel computing tasks.
