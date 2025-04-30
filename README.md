# 2025-SP-101-hw2-ykydh

## How to Run the Program

1. Open a terminal and **navigate to the root directory** of the project:  
   `2025-SP-101-hw2-ykydh`

2. **Compile the program** by running:  
   ```bash
   make
   ```

3. **Change to the build directory**:  
   ```bash
   cd build
   ```

4. **Run the executable**:  
   ```bash
   ./Files
   ```

---

## Notes

- To **clean up build files**, run:
  ```bash
  make clean
  ```
  from the root directory.

- After launching `./Files`, you can type:
  ```
  help
  ```
  to view a help.

- Available Commands and Its parameters
  
  cd: cd <subdirectory or ../>
  
  ls: ls for normal listing or ls -l for details
  
  pwd: pwd for displaying current directory's path
  
  mkdir: mkdir <name> to make a new directory
  
  rm: rm <filename> to remove a file
  
  mv: mv <path from the root> to move a file or directory
  Ex:Move main.cpp from Root/User/Downloads to Root/User/Docs mv main.cpp User/Docs
  nano: nano <filename> to create or edit a file
  
  rmdir: rmdir <directoryname> to remove a directory
  
  exit: exit to stop running this program
  
