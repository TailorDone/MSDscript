# MSDscript 
## Table of Contents
+ [Description](#about)
+ [Getting Started](#start)
+ [User Guide](#user)
+ [API Documentation](#API)

## Description: <a name = "about"></a>
<p>
  <ul>
    <li><b>What is MSDscript:</b> MSDscript is an interpreter built upon a C++ foundation that allows for the parsing and interpreting of mathematical expressions. This includes: </li>
    <ul>
      <li>Numerical Expressions</li>
      <li>Variable Expressions</li>
      <li>Boolean Expressions</li>
      <li>Addition Expressions</li>
      <li>Multiplication Expressions</li>
      <li>Let Expressions</li>
      <li>If/Else Expressions</li>
      <li>Equivalence Expressions</li>
      <li>Function Expressions</li>
      <li>Call Expressions</li>
    </ul>
    <li><b>How it's meant to be used:</b> MSDscript can be built and ran as a stand alone script. Users may input an expression via the command line which will be parsed and interpretted. MSDscript can also be used as an embedded language.</li>
  </ul>
 </p>
 
 ## Getting Started: <a name = "start"></a>
 <p>
    Via the command line, navigate into the directory where the MSDscript package is located. Run the following commands:<br>
    <ul>
    <li><i>cmake .</i> <br>Generates a Makefile in the current directory</li>
    <li><i>make</i> <br>Installs the MSDscript executable and MSDscriptLib library</li>
    <li>The program can be ran from the command line in the directory where the executable is located by running the following command: <i>./MSDscript</i></li>
    <li>The program can also be ran as a library using libMSDlibrary.a via the commandline and the following command:<br><i>$ c++ -o project_name your_project.cpp libMSDlibrary.a</i></li>    
  </ul>
</p>

## User Guide: <a name = "user"></a>
<p>
MSDscript can parse user input and interpret a variety of expressions.
<ul>
      <li>Numerical Expressions</li>
        <ul>
          <li>Format:</li>
            <ul>
              <li> Numbers in MSDscript may be positive or negative. MSDscript is not capable of parsing numbers that may include decimals, commas, division symbols, or spaces</li>
            </ul>
          <li>Examples:</li>
            <ul>
              <li>-5</li>
              <li>100000</li>
              <li>0</li>
           </ul>
          <li>Errors:</li>
          <ul>
            <li>5,000</li>
            <li>3.14159</li>
            <li>1 000 000</li>
            <li>1/4</li>
          </ul>
        </ul>
      <li>Variable Expressions</li>
        <ul>
          <li>Format:</li>
            <ul>
              <li> Variables in MSDscript consist of an unbroken string of upper or lowercase letters and containing no numerical representations or spaces </li>
            </ul>
          <li>Examples:</li>
            <ul>
              <li>x</li>
              <li>VAR</li>
              <li>hello</li>
           </ul>
          <li>Errors:</li>
          <ul>
            <li>h3ll0</li>
            <li>h e l l o</li>
          </ul>
        </ul>
      <li>Boolean Expressions</li>
         <ul>
          <li>Format:</li>
            <ul>
              <li> Boolean expressions can be interpreted using MSDscript by using _true or _false </li>
            </ul>
          <li>Examples:</li>
            <ul>
              <li>_true</li>
              <li>_false</li>
           </ul>
          <li>Errors:</li>
          <ul>
            <li>true</li>
            <li>false</li>
            <li>yes</li>
            <li>no</li>
          </ul>
        </ul>
      <li>Addition Expressions</li>
         <ul>
          <li>Format:</li>
            <ul>
              <li> Addition expressions can be interpreted using MSDscript by using the + operator. MSDscript is not capable of parsing or interpreting the - operator used as subtraction </li>
            </ul>
          <li>Examples:</li>
            <ul>
              <li>2 + -3</li>
              <li>(2 + (-3))</li>
           </ul>
          <li>Errors:</li>
          <ul>
            <li>2 - 3</li>
          </ul>
        </ul>
      <li>Multiplication Expressions</li>
         <ul>
          <li>Format:</li>
            <ul>
              <li> Multiplication expressions can be interpreted using MSDscript by using the * operator. MSDscript is not capable of parsing or interpreting the / operator </li>
            </ul>
          <li>Examples:</li>
            <ul>
              <li> 2 * -3 </li>
              <li> (1 * 0)</li>
           </ul>
          <li>Errors:</li>
          <ul>
            <li>2 / 3</li>
          </ul>
        </ul>
      <li>Let Expressions</li> 
          <ul>
          <li>Format:</li>
            <ul>
              <li> MSDscript can interpret Let Expressions in the following format _let (variable) = (expression) _in (expression) </li>
            </ul>
          <li>Examples:</li>
            <ul>
              <li> _let x = 5 _in x + 2 </li>
           </ul>
          <li>Errors:</li>
          <ul>
             <li> let x = 5 _in x + 2 </li>
             <li> _let x = 5 in x + 2 </li>
             <li> _let x 5 _in x + 2 </li>
          </ul>
        </ul>
      <li>If/Else Expressions</li>
         <ul>
          <li>Format:</li>
            <ul>
              <li> MSDscript can interpret If/Else Expressions in the following format _if (boolean) _then (expression) _else (expression). MSDscript will return the _if expression if the boolean is true and the _else expression if the boolean is false. </li>
            </ul>
          <li>Examples:</li>
            <ul>
              <li> _if _false _then 5 _else 3 </li>
              <li> _if 6 == 6 _then 5 _else 3 </li>
              <li> _if 6 == 1 _then 5 _else 3 </li>
           </ul>
          <li>Errors:</li>
          <ul>
            <li> _if 2 _then 5 _else 3 </li>
            <li> if _true _then 5 _else 3 </li>
            <li> _if _true then 5 _else 3 </li>
            <li> _if _true _then 5 else 3 </li>
          </ul>
        </ul>
      <li>Equivalence Expressions</li>
        <ul>
          <li>Format:</li>
            <ul>
              <li> MSDscript can interpret equivalence statements using == and return a boolean. MSDscript cannot interpret equivalence statments involving variables </li>
            </ul>
          <li>Examples:</li>
            <ul>
              <li> 6 == 6</li>
              <li> _true == _true </li>
              <li> 1 == 2 </li>
           </ul>
          <li>Errors:</li>
          <ul>
            <li> 6 = 6 </li>
            <li> x == y </li>
          </ul>
        </ul>
      <li>Function Expressions</li>
        <ul>
          <li>Format:</li>
            <ul>
              <li> MSDscript can interpret Functions in the following format _fun (variable) (expression)  </li>
            </ul>
          <li>Examples:</li>
            <ul>
              <li> _fun (x) x * 2</li>
           </ul>
          <li>Errors:</li>
          <ul>
          </ul>
        </ul>
      <li>Call Expressions</li>
        <ul>
          <li>
        </ul>
    </ul>
</p>
<p>
  MSDscript can run the following arguments via the command line:
  <ul>
    <li><b>--help</b>
      <ul>
        <li> 'help' will show the user which arguments MSDscript can run</li>
        <li>Example:</li>
          <ul>
            <li>./MSDscript --help (return)
            <br>Allowed Arguments: --help, --interp, --print, --pretty-print, --test, --step</li>
          </ul>
      </ul>
    <li><b>--print</b>
      <ul>
        <li>'print' will print an expression without spaces and with parenthesis around the expression</li>
        <li>Example:</li>
          <ul>
            <li>./MSDscript --print (return) 2 + 2 (ctrl+d)
            <br> (2+2)</li>
          </ul>
      </ul>
    <li><b>--pretty-print</b>
      <ul>
        <li>'pretty-print' will print an expression avoiding unnecessary parenthesis assuming that operators associating to the right </li>
        <li>Examples:</li>
          <ul>
            <li>./MSDscript --pretty-print (return) (6*2) (ctrl+d)
            <br> 6 * 2 </li>
            <li> ./MSDscript --pretty-print (return) (6*2)+5 (ctrl+d)
            <br> 6 * 2 + 5 </li>
            <li> ./MSDscript --pretty-print (return) (6*2)*5 (ctrl+d)
            <br> (6 * 2) * 5 </li>
          </ul>
        <li>Potential Error:</li>
          <ul>
            <li> ./MSDscript --interp (return) _let x = y in x+5 (ctrl+d)
            <br> _in expected </li>
          </ul>
      </ul>
      <li><b>--interp</b></li>
      <ul>
        <li>'interp' will return the value of an expression if possible </li>
        <li>Examples:</li>
           <ul>
            <li> ./MSDscript --interp (return) (6*2)+5 (ctrl+d)
            <br> 17 </li>
            <li> ./MSDscript --interp (return) _let x = 3 _in x+5 (ctrl+d)
            <br> 8 </li>
            <li> ./MSDscript --interp (return) 7 == 7 (ctrl+d)
            <br> _true </li>
          </ul>
        <li>Potential Error:</li>
          <ul>
            <li> ./MSDscript --interp (return) _let x = y _in x+5 (ctrl+d)
            <br> free variable: y </li>
          </ul>
    </ul>
    <li><b>--step</b></li>
    <ul>
        <li>'step' works the same as interp but will prevent segmentation faults for recursive calls </li>
    </ul>
    <li><b>--test</b></li>
    <ul>
        <li>'test' will run catch tests found within the code to make sure the program is working as intended </li>
    </ul>
  </ul>
  <b>Note: Command-line programs depend on an input on end of file, so use 'ctrl+d' as opposed to 'return' when finished entering an expression and to begin the program</b>
</p>

## API Documentation <a name = "API"></a>
<p>
  <ul>
    <li></li>
 </ul>
</p>
