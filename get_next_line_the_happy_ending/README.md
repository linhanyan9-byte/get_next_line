*This project has been created as part of the 42 curriculum by halin*

# Description
## goal
* Build a get program that can repeatedly read the text file pointed to by the file descriptor, one line at a time.
## brief overview
* Repeated calls (e.g., using a loop) to get_next_line() function will let
you read the text file pointed to by the file descriptor, one line at a time.
* The function will return the line that was read.
* If there is nothing left to read or if an error occurs, it will return NULL.

# Instruction
* The project is compiled alongside a `main.c` test file. You must define the `BUFFER_SIZE` macro at compile time using the `-D` flag.

## compilation
**Standard compilation:**
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```
## installation
please use git clone to get the files.


but you are not gonna get it anyway, (cause it is 42 innernet). So I am not gonna put the link.

## execution
* Run the compiled program (passing a file path if your `main.c` reads from `argv[1]`):
```bash
./a.out test.txt
```

# resources
* Linux Manual Pages 
* Norminette
## ai usage
AI assistance was used for:
1. Understanding concepts
2. Debugging
3. Discuss about edge cases

# explaination of the algorithm for the project
* I use a transporter which is like a truck thats gonna get the food from supermarket(file you opened) and store it to your house(storage).
* The signals of operation change are two, one is the new line sign and the other is the end of file sign. 
    * for the '\n', the stopping is the "strlen" reaching the char and then truncating is following up. 
    * for the end of file, the 
