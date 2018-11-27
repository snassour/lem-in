# lem-in
Find your way into an anthill

## Quick Description
Lem-in finds the fastest way to move all the ants from an entry point to and exit.<br />
Its default behaviour is to read from the standard input. However, you can use the flag <code>--read</code><br/>
in order to read from a file.<br />

Input format :
First line is the number of ants.<br />
First block is the map coordinates : point_name coord_x coord_y<br />
In the first block, the start and the end are specified using the ##start and ##end commands.<br />
Second block is the map links : point_name_a-point_name_b<br />

```
12
##start
a 1 2
b 3 4
c 5 6
##end
d 7 8
e 9 10
a-b
b-c
c-d
```
Its default behaviour is to write the output on the standard output. However, you can use the flag <code>--write</code><br/>
in order to write in a file.<br />

## Run it
<code>make ; make clean;</code><br />
<code>./lem-in [OPTIONAL [--help] [-c] [--path] [--read [INPUT_FILE]] [--write [OUTPUT_FILE]] ]</code><br />

## PDF Link <a href="https://github.com/snassour/lem-in/blob/master/lem-in.fr.pdf">lem-in</a>
