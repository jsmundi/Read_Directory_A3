# Read_Directory_A3
A program (in C) called readable.c targeted at the Linux platform that takes one or zero command line arguments. Argument, if present, is a pathname (relative or absolute). If no argument is present, the pathname of the present working directory is assumed (getcwd).

The proram traverses directories and their files recursively starting with the pathname, and lists every regualar file that is readable by the current process. No order is defined for the paths that are ouput. 

## Program Interface

```bash
./readable <pathname>
Where: <pathname> is an optional parameter that specifies a path in the directory system.
If no argument is present, then your program will operate on the current working directory.
```

## Running the Program (Unix)
- Open the directory where readable.c exists along with Makefile
- Open terminal and use make to compile 
```bash
make
```
- To run the program 
```bash
./readable <path>
```
- To clean
```bash
make clean
```

## Output
```bash
./redable /Start
/Users/../Read_Directory_A3/Start/file
/Users/../Read_Directory_A3/Start/anotherFile
/Users/../Read_Directory_A3/Start/AnotherDir/lastFile
```

## Folder Tree
```
.
├── Makefile
├── README.md
├── Start
│   ├── AnotherDir
│   │   └── lastFile
│   ├── anotherFile
│   └── file
└── readable.c
```

2 directories, 6 files

## Author
JT Mundi

