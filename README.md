# cborr  
hello this is cborr, aka borr c, aka syborr, aka sybau  
please do not call it anything other than cborr or else you get the :onion:  
also please do not use anything other than c99 or else you get the :onion: aswell  


this project is licensed under the [WTFNMFPL](https://github.com/adversary-org/wtfnmf/tree/master)
```
    DO WHAT THE FUCK YOU WANT TO BUT IT'S NOT MY FAULT PUBLIC LICENSE
                    Version 1, October 2013

 Copyright (C) 2025 viylouu <viylouu@gmail.com>

 Everyone is permitted to copy and distribute verbatim or modified
 copies of this license document, and changing it is allowed as long
 as the name is changed.

   DO WHAT THE FUCK YOU WANT TO BUT IT'S NOT MY FAULT PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

  0. You just DO WHAT THE FUCK YOU WANT TO.

  1. Do not hold the author(s), creator(s), developer(s) or
     distributor(s) liable for anything that happens or goes wrong
     with your use of the work.
```

# usage
to use cborr, first make your repo or whatever  
if you make a repo, make a github submodule using cborr by doing `git submodule add https://github.com/viylouu/cborr`  
otherwise, clone the repo somewhere, and add the files into a cborr folder  

if you want to use the `build.sh` script provided for you, copy that into the root directory  
please copy the provided `compile_flags.txt` aswell, as that will allow for error handling in the ide  

# building
this project uses the tiny c compiler (aka. tcc) for test builds  
this means it builds very fast when needed (muy bueno)  
it also uses gcc for full builds  
this means it runs very fast when needed (muy bueno)  
you will need to have these in your path to run the build.sh  

## test builds
test builds use tcc, and are therefore less optimized, but a faster build  
you can do a test build like this:  
- run `./build.sh -t`  
this will build and run the src/main.c file  
it autoscans src, eng, and include for c files  

>
> just pointing out that test builds dont really have as must errors / warnings
>
  
if you want to test an example, see this:  
- run './build.sh EXAMPLE_NAME -t'  

## regular builds
regular builds use gcc, and are therefore more optimized, but a slower build  
you can do a regular build like this:  
- run `./build.sh`  
this will build and run the src/main.c file  
it autoscans src, eng, and include for c files  
  
if you want to build and example, see this:  
- run `./build.sh EXAMPLE_NAME`  

## windows builds
windows builds are simple  
same syntax, just add the -w flag! (only nesseccary for linux -> windows cross compilation)  
they do however force you to use gcc because silly windows :onion:  
