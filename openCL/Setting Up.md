# Set up OpenCl Environment with Visual Studio 2022 

This readme file summarizes the steps to create a new Visual Studio project for using OpenCL with the AMD APP SDK.

- Visual Studio
- AMD APP SDK 

## Steps

1. Open Visual Studio and select "Create a new project".
2. Select an "Empty Project" and click "Next".
3. Enter a project name, a location, and a solution name, then click "Create".
4. If you have existing files for the project, put them in the solution directory and add them to the project by right-clicking on the appropriate folder in Solution Explorer and selecting "Add" -> "Existing Item".
5. Open the project properties by right-clicking on the project name and selecting "Properties".
6. Apply the properties to all configurations by selecting "All Configurations" and "Active(Win32)".
7. Under Configuration Properties -> VC++ Directories, add C:\AMD APP SDK\3.0\include to the Include Directories and C:\AMD APP SDK\3.0\lib\x86 to the Library Directories.
8. Under Configuration Properties -> Linker -> Input, add OpenCL.lib to the Additional Dependencies.
9. Click Apply and OK.
10. To compile and run the code, make sure "x86" is selected and click on the button.
