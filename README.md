# FileHide Minifilter Driver 
FileHide is a minifiter driver that allows you to hide your files or directories 

Tested on Windows 10 21H2 and 22H2

# Usage:
modify the TARGET_FILE(file/directory name only) and TARGET_FOLDER(parent directory  of the file to hide)  in 'main.h' 



# How it works 
programs like explorer use functions like NtQueryDirectoryFile to obtain information about directories and their contents 

the corresponding sent IRP is IRP_MJ_DIRECTORY_CONTROL with MinorFunction of IRP_MN_QUERY 

we register both pre and post filters for IRP_MJ_DIRECTORY_CONTROL 

the pre filter is responsible to reduce overhead by filtering out uninteresting directory controls and returning FLT_PREOP_SUCCESS_NO_CALLBACK 

the post filter , which is invoked only for directory queries we care about , is responsibble for parsing the query results buffer structure and removing the file we wish to hide 

***************************
# Demo
before loading our FileHide

![FileHide_Before](https://github.com/0mWindyBug/FileHide/assets/139051196/d9861966-f4a2-46b6-b869-1a77a5d9660a)

after loading FileHide

![FileHide_After](https://github.com/0mWindyBug/FileHide/assets/139051196/974240d2-a923-415b-8c02-174741dcbe7e)


  
