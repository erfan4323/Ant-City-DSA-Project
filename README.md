# Ant-City-DSA-Project
A project for DSA


In the city of ants, every ant's body structure is defined by a string of English letters, equivalent to human DNA. For example, one ant may be identified by the string "abcd," although another ant may be represented by the string "x." The ant city contains two types of ants: queen ants and worker ants. During a reproductive cycle, if substrings from a worker and the queen ant share the same prefix, offspring with those substrings are born. For instance, suppose the worker ant has the string "xyzy" and the queen ant has "yzxx," the offspring will be "yz" and two "y."

All newly born ants form a queue to enter the city, with no particular pattern. In this queue, there are also some outsider ants trying to enter the city. These outsider ants seem different any of the ant children, and their unique strings make them obviously noticed.

The city's gatekeeper is in responsibility for blocking outsider ants out and organizing and protecting their children. However, the gatekeeper has a barriers because to the endless number of ants generated throughout a reproductive cycle, making it impractical to write all ant names, which could take up a significant amount of space.

You have to:

Identify and erase outsider ants from the entry queue, utilizing lists of worker and queen ants.
Efficiently store the order of entry for ant offspring in a file, allowing you to reassemble the ant child queue using worker and queen lists.

Delivery requirements:

In this project, you must be able to provide two programs: Encoder and Decoder.

The Encoder program ought to read worker and queen ants from the "txt.parents" file and the entry queue from standard input. After eliminating the outsider ants from the queue, it should keep the ideal order of ant children entry into the city in a file labeled "order."

The Decoder program should be able to decode the "order" file using the "txt.parents" file and print all offspring in the correct order to the standard output.

In the simplest instance, the entire queue can be put in the "order" file. However, keep in mind that the primary goal of this project is to shrink the size of the "order" file while simultaneously making sure the programs run correctly.

Input and output:

The "txt.parents" file provides the number of queen and worker ants first, then their strings. In different lines, queen ants come first. The total amount of ants does not surpass 100.
In standard input, the first line decides the queue length, and each following line contains the string of each ant.
The "order" file can be in any format, and its contents are not critical to the project evaluation.
In standard output (Decoder), print the ants one at a time on separate lines, in the order they were entered.

parents.txt:
1 2
bcde
bbb
abcd
Encoder’s standard input:
b
bc
x
b
bcd
x
b
bcde
b
Decoder’s standard output:
b
bc
b
bcd
b
b 
