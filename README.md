# FileHide Minifilter Driver 
FileHide is a minifiter driver that allows you to hide your files or directories 

Tested on Windows 10 21H2 and 22H2

# Usage:
modify the TARGET_FILE(file/directory name only) and TARGET_FOLDER(parent directory  of the file to hide)  in 'main.h' 



# How it works 
programs like explorer use functions like NtQueryDirectoryFile to obtain information about directories and their contents 

the corresponding sent IRP is IRP_MJ_DIRECTORY_CONTROL with MinorFunction of IRP_MN_QUERY 

we register both pre and post filters for IRP_MJ_DIRECTORY_CONTROL 

the pre filter is responsible to filter out uninteresting directory controls by returning FLT_PREOP_SUCCESS_NO_CALLBACK 

the post filter , which is invoked only for the directory controls with minor function code of query , is responsible for parsing the query results buffer and removing our file 

again , to reduce overhead the post filter will do it's work only if the reequest is targeted at our file's target directory 
***************************
# Demo


  
