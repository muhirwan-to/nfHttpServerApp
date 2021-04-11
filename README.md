### Requirements
 - Boost library version 1.70.0 or above
 - CMake 3.20
 - Tortoise svn 1.12.2.28653
 
 ### Compile Error
 -- Boost
 - follow this step `https://stackoverflow.com/questions/13042561/fatal-error-lnk1104-cannot-open-file-libboost-system-vc110-mt-gd-1-51-lib`

 -- Unresolved opencv
 - On Saturday, I can run the project normally
 - On Sunday, whalaa ... there's unresolved symbol on opencv :(
 - ... 
 
 ### How to Build
 - run `make_all.bat` to get external
 - run `\prj\nfhs.sln`