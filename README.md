## SpideR

***NOTE: A lot of functionality is still missing. This will be rectified eventually.***  

***WINDOWS PORT HAS JUST BEEN ADDED, 
IT IS THEREFORE HIGHLY DOUBTFUL THAT IT WILL WORK***

A web crawler engine that gathers data, sorts it and outputs it to file.  
The goal is for it to be fully customizable and extensible, with possibilities for scripting the behaviour of the spiders.  

Requirements:  
libcurl and the c++ wrapper curlpp.  
See: https://curl.haxx.se/libcurl/ and http://www.curlpp.org/ for downloads.  
For arch-linux, curl is to be found in the core repos, while libcurlpp can be found in the AUR.  

Installation:
Compile it. For linux there is a makefile that should work.  

Settings:  
Settings are set through the Settings.json file.  
The settings currently available are:  
textspeed : int - Does nothing atm.  
depth : int - Determines how far it should follow links that are found. Default is 1.  
debug : bool - Setting this to 1 sets the verbose flag for the connection. But this ends up in the parsing..  
type : unchanged|small|firstcapital|fullcapital - Format of the words stored.  

Use:  
At the moment there are only 3 commands: help, connect and quit.  
Connect url - Attempts to connect to the specified site and gather words and url based on the settings set.  
Example:
```
connect www.google.com
```
Output goes to **output.txt**. 