# Version

<p align="justify">This application generates c-style preprocessor definitions for the current date and time and stores them in the specified file. Generated definitions are customizable by the formatting options described below. Date is set to the current number of days since January 01, 2000. Time is set to the current number of seconds since midnight divided by two.</p>

**WARNING:** Existing contents of the file will be destroyed.

### Input
```bash
$ Version [Format] [Filename]
```

### Output
* 0 - No errors occurred
* 1 - No filename was passed
* 2 - File could not be opened

### Format
* 0x - Output as hex (e.g. 0xD, 0xT)
* D  - Current date
* T  - Current time

### Default
```bash
$ Version BUILD=D REVISION=T [Filename]
```

### Author
* Email: <dave@krutsko.net>
* Home: [dave.krutsko.net](http://dave.krutsko.net)
* GitHub: [github.com/dkrutsko](https://github.com/dkrutsko)