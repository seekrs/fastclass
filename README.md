
# fastclass

A C program destined to make C++ classes faster following the orthodox canonical class form.

## How to install

Clone the repo and use ```make``` :  
Will compile fastclass in current directory  
```make install``` :
Will compile fastclass in ```/nfs/homes/${USER}/.local/bin/```  
## How to use

The format for using fastclass is : ```class [-FLAGS] [FILES] ...```

* ```-f``` will insert the 42Header in all classes created using NAME and MAIL defines.
* ```-p``` will insert std::cout output for the constructors and destructors.
* ```-h``` will prints this help.

## How to uninstall
```make fclean``` will delete the class file located in ```/nfs/homes/${USER}/.local/bin/``` 




