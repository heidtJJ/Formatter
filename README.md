# Formatter
This is C program that formats a text so that it fits nicely into a given number of columns. The text formatter must right-justify an input text file so the right margins are aligned in a straight line. The number of columns or width is specified as part of the input.
<h3>A sample input file</h3>

Here is T.S. Eliot's poem <i><a href="hollow.txt">Hollow Men</a></i> in free form.

<hr>

<h3>Compilation and run</h3>
The makefile is included.
<pre>
	./formatter hollow.txt hollow-20.txt 20 
	./formatter hollow.txt hollow-40.txt 40
	./formatter hollow.txt hollow-50.txt 50
</pre>
The resulting output files are as follows: 
<a href="hollow-30.txt">30-line</a>,
<a href="hollow-40.txt">40-line</a>,
<a href="hollow-50.txt">50-line</a> formats.
<br>
