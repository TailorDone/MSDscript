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
    <li> Expression Precedence </li>
        <ul>
            <li>Multiplication Expression</li>
            <li>Addition Expression</li>
            <li> Equivalence Expression </li>
            <li> Let Expressions, If/Else Expression, Function Expressions, Call Expressions</li>
        </ul>
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
            <li>Subtraction will result in the following error: "Invalid input for an expression"</li>
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
            <li>Division will result in the following error: "Invalid input for an expression"</li>
          </ul>
        </ul>
      <li>Let Expressions</li> 
          <ul>
          <li>Format:</li>
            <ul>
              <li> MSDscript can interpret Let Expressions in the following format _let (variable) = (expression) _in (expression) </li>
              <li> _let (variable) = (expression) assigns a variable to an expression. This assigned expression is then substituted into the expression found after _in.</li>
            </ul>
          <li>Examples:</li>
            <ul>
              <li> _let x = 5 _in x + 2 </li>
           </ul>
          <li>Errors:</li>
          <ul>
             <li> let x = 5 _in x + 2 </li>
             <li> A _ must precede let or the following error will occur: "Invalid input for an expression" or "_let expected" if used as an inner expression
             <li> _let x = 5 in x + 2 </li>
             <li> A _ must precede in or the following error will occur: "_in expected"</li>
             <li> _let x 5 _in x + 2 </li>
            <li> A = must follow the variable for proper assignment in or the following error will occur: "equal expected"</li>
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
              <li> This will result in leading to the else branch and will return 3 after interpretation</li>
              <li> _if 6 == 6 _then 5 _else 3 </li>
              <li> This will result in leading to the if branch and will return 5 after interpretation</li>
              <li> _if 6 == _true _then 5 _else 3 </li>
              <li> Comparing a number to a boolean will always result in _false, which would be the _else branch, and will return a 3 after interpretation</li>
           </ul>
          <li>Errors:</li>
          <ul>
            <li> _if 2 _then 5 _else 3 </li>
            <li> A boolean expression must be after the _if. A non-boolean after _if will result in the error: "Test expression is not a boolean"
            <li> if _true _then 5 _else 3 </li>
            <li> A _ must precede if or the following error will occur: "Invalid input for an expression" or "_in expected" if used as an inner expression
            <li> _if _true then 5 _else 3 </li>
            <li> A _ must precede then or the following error will occur: "_then expected"</li>
            <li> _if _true _then 5 else 3 </li>
            <li> A _ must precede else or the following error will occur: "_else expected"</li>
          </ul>
        </ul>
      <li>Equivalence Expressions</li>
        <ul>
          <li>Format:</li>
            <ul>
              <li> MSDscript can interpret equivalence statements using == and return a boolean. The == operation can work on any kinds of values, and is allowed to compare a boolean to a number, but only a number expression can be equivalent with a number expression, and only a boolean expression can be equivalent to a number expression. MSDscript can interpret equivalence statments involving variables if the variable have been assigned a value. </li>
            </ul>
          <li>Examples:</li>
            <ul>
              <li> 6 == 6</li>
              <li> This example compares a number to a number and would interp to _true </li>
              <li> _true == _false </li>
              <li> This example compares a boolean to a boolean and would interp to _false </li>
              <li> 1 == _true </li>
              <li> This example compares a number to a boolean, which will always interp to _false </li>
              <li> _let x = 5 _in x == x </li>
              <li> This example will interp to _true </li>
           </ul>
          <li>Errors:</li>
          <ul>
            <li> 6 = 6 </li>
            <li> This will result in the following error: "2nd equal sign expected"</li>
            <li> x == y </li>
            <li> Since x and y have not been defined at this point, this will result in the following error: "free variable: x"</li>
          </ul>
        </ul>
      <li>Function Expressions</li>
        <ul>
          <li>Format:</li>
            <ul>
              <li> MSDscript can interpret Functions in the following format _fun ((variable)) (expression)  </li>
            </ul>
          <li>Examples:</li>
            <ul>
              <li> _fun (x) x * 2</li>
              <li> This is similar to f(x) = x*2 </li>
           </ul>
          <li>Errors:</li>
          <ul>
            <li> fun (x) x * 2</li>
            <li> _ must precede fun and will result in the following error: "Invalid input for an expression" </li>
            <li> _fun x x * 2</li>
            <li> the variable argument after _fun must be surrounded by parenthesis and will result in the following error: "Invalid input for an expression"</li>
          </ul>
        </ul>
      <li>Call Expressions</li>
        <ul>
          <li> MSDscript can use call expressions in conjunction with function expressions to pass a value into a function.</li>
           <li>Examples:</li>
            <ul>
              <li> (_fun (x) x * 2)(3)</li>
              <li> This will pass 3 in for x and result in 6 after interpretation </li>
           </ul>
          <li>Errors:</li>
          <ul>
            <li> (_fun (x) x * 2)3 </li>
            <li>A call value must be placed within parenthesis after a function expression and will result in the following error: "Invalid input for an expression"</li>
          </ul>
        </ul>
    </ul>
</p>

  ### Comandline Arguments:
  <p>
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

### MSDscript Grammar
  ```
  〈expr〉     = 〈comparg〉
                  | 〈comparg〉==〈expr〉
              
  〈comparg〉  = 〈addend〉
                  | 〈addend〉+〈comparg〉
              
  〈addend〉   = 〈multicand〉
                  | 〈multicand〉*〈addend〉
              
  〈multicand〉= 〈inner〉
                  | 〈multicand〉(〈expr〉)
              
  〈inner〉    = 〈number〉| (〈expr〉) |〈variable〉
                  | _let〈variable〉=〈expr〉_in〈expr〉
                  | _true | _false
                  | _if〈expr〉_then〈expr〉_else〈expr〉
                  | _fun (〈variable〉)〈expr〉
  ```

## API Documentation <a name = "API"></a>

<p>
MSDscript Files

<ul>
<b>Core</b>
<li>`cmdline.cpp, cmdline.hpp` - Contains methods necessary for command line arguments for the terminal</li>
<li>`cont.cpp, cont.hpp` - Contains methods necessary for continuations within step mode interpretation</li>
<li>`env.cpp, env.hpp` - Contains methods necessary for quick referencing of variables without creating new expressions</li>
<li>`expr.cpp, expr.hpp` - Contains methods for expressions</li>
<li>`parse.cpp, parse.hpp` - Contains methods necessary for parsing an input or string</li>
<li>`step.cpp, step.hpp` - Contains methods necessary for step interpretation which prevents seg faults in large recursive expressions</li>
<li>`val.cpp, val.hpp` - Contains methods necessary for values</li>
</ul>

<ul>
<b>Helper</b>
<li>`main.cpp` - Runs the commandline code. Can be used for testing with editing the scheme. </li>
<li>`pointer.h` - Allows for  the switching between shared and regular pointers.</li>
</ul>

<ul>
<b>Tests</b>
<li>`catch.h` - Used to run the tests found through various cpp codes.</li>
</ul>

<ul>
<b>Expr Functions</b>
<li>  `equals(PTR(Expr)a)` </li>
<ul>
<li>Returns a boolean to determine if two expressions are equivalent.</li>
</ul>
<li> `PTR(Val) interp(PTR(Env) env)`</li>
<ul>
<li>Returns a PTR(Val) which represents the interpreted expression</li>
</ul>
<li> `void print(std::ostream& output)`</li>
<ul>
<li>Returns void. Used to print an expression to an output stream.</li>
</ul>
<li> `void pretty_print(std::ostream& output)`</li>
<ul>
<li>Returns void. Used to print an expression avoiding unnecessary parenthesis assuming that operators are associating to the right to an output stream.</li>
</ul>
<li> `void step_interp()`</li>
<ul>
<li>Returns void. Used to interpret recursive expressions without causing a segmentation fault.</li>
</ul>
</ul>

<ul>
<b>Expr Subtypes</b>
<li> `NumExpr` - Represents numeric expressions</li>
<li> `AddExpr` - Represents addition expressions</li>
<li> `MultExpr` - Represents a multiplication expression</li>
<li> `VarExpr` - Represents a variable expression</li>
<li> `LetExpr` - Represents a let expression</li>
<li> `BoolExpr` - Represents a boolean expression</li>
<li> `IfExpr` - Represents an else/if expression</li>
<li> `EqExpr` - Represents an equivalence expression</li>
<li> `FunExpr` - Represents a function expression </li>
<li> `CallExpr` - Represents a call to a function expression</li>
</ul>

<ul>
<b>Val Functions</b>
<li>`equals(PTR(Val) v)` </li>
<ul>
<li>Returns a boolean to determine if two values are equivalent.</li>
</ul>
<li>`PTR(Val) add_to(PTR(Val) rhs)`</li>
<ul>
<li>Returns a PTR(Val) of the addition result of the calling value to the parameter value.</li>
</ul>
<li>`mult_to(PTR(Val) rhs)`</li>
<ul>
<li>Returns a PTR(Val) of the multiplication result of the calling value to the parameter value.</li>
</ul>
<li>`print(std::ostream& outstream)`</li>
<ul>
<li>Returns void. Used to print a value to an output stream.</li>
</ul>
<li>`is_true()`</li>
<ul>
<li>Returns a boolean whether the calling value is _true.</li>
</ul>
</ul>

<ul>
<b>Val Subtypes</b>
<li>`NumVal` - Represents a number value</li>
<li>`BoolVal` - Represents a boolean value</li>
<li>`FunVal` - Represents a function value</li>
</ul>

<ul>
<b>Parsing Expressions</b>
<br> MSDscript can parse expressions by utilizing the `parse()` function.
<li> `PTR(Expr) parse(std::istream &in)` takes an input stream and will return `PTR(Expr)` which is a pointer to an expression. This function is used in the command line to parse user input into an expression.</li>
<li> `PTR(Expr) parse_str(std::istream &in)` takes a string and will return `PTR(Expr)` which is a pointer to an expression.</li>
</ul>

<ul>
<b>Interpretting Expressions</b>
<br> MSDscript can interpret expressions by utilizing the `interp()` function.
<li> `interp_by_steps(PTR(Expr) e)` takes an expression and returns `PTR(Val)` which is the interpreted value</li>
</ul>


