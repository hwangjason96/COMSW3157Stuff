#!/bin/bash
#Always start with bin/bash

#echo prints stuff
echo "Hello World!"

#All variables in vim are globla
# $'_inText' will capture all of the escape sequences
text=$'To be or not to be, that is the question.\n Whether it is noble...\n'
#This syntax is called ANSI-C quoting

#$_Variable will call a variable.
printf '%s' "$text"
#printf '%s' "$_StringVar" will capture all of the escape sequences coupled with the above syntax for the string

#to get a parameter written from commandline, you need to use $n
# $0 = directory
# $1 = first word before the first space
# $2 = second word delimited by the empty space ...etc

#This retrieves the first variable given by the command line and,
inText=$1
#this would print it
echo $inText

#This prints how many arguments/parameters are passed through by the commandline
echo $#

#conditionals

#make sure there is a space between [ and the arguments inside
if [ $# -gt 0 ]; then
	echo "There is an argument here!"
fi

exit
