Deliverable 4: Code Generation
=========

## Methodology
Our implementation was done from the easiest to hardest so we could get a grasp on the IR builder and explore before we
implemented the arrays and for-loops.

While writing the code-generation methods, we didn't initially write _actual_ system tests, but instead opted for small
tests that we manually built and checked.

The methodology was like this:
1. Comment out code generation in the node and write base case
2. Build and test for basic functionality e.g.: 

``` 
cd bin
./cleancov.sh
./build.sh --asm --do [file_name] // For checking assembly
./build.sh [file_name] for running the file and checking values
```

3. Writing system tests to check for edge cases and adding more functionality to our methods
4. Adding tests that overlapped


This process was continually repeated until we believed we had working functionality for all cases, but arrays and
for-loops took particularly long due to error injections and checking failing tests.






# Tricky Parts
Similar to before, the main tricky parts were the arrays and for-loops, but also testing.

#### Arrays 
In terms of arrays, we had boundary checks to consider. For example:
```
var a, b, c, d;
a = [ -1 of 5]; // This should error!
b = [0 of 5]; // This one should work!

a = [4 of 3];

c = a[-1]; // These BOTH should error
d = a[999999]; 
```
The main concerns were that the index had to be in bounds (i.e. 0 <= i < #arr) and the size of an Array-Of also had to 
be positive or 0. These were both difficult since we had to inject errors into the methods, meaning that we created 
additional code blocks to jump to which made our code quite lengthy and a bit convoluted. 

Additionally, because we needed
to allocate room on the heap for the arrays, we had to consider the size of array which was an llvm value. This means we
had to do some conversions back and forth and had variables that represented the same thing but in different forms. However,
when we attempted to write a test that created an array via a function, we realized using constant ints and a typical
for-loop would not work. This led us to use a phi-node to fill up the array instead.

#### For-Loops
For both for-loops our main difficulty was dealing with the iterator value and using it. For example:
```
var x, y, z;

y = [1, 2, 3];

for (x : 0 .. 2){
    z = z + x; // How would we retrieve this value?
}

for (x : y){
    z = z + x; // Similar problem
}

```
We ended up looping through the entry block for the same variable declared in the for-loop itself. Additionally, because
the same variable was declared twice, a 1 was appended onto the variable name so it had to be split and matched so that
it could be utilized. E.g.:
```
var x; --> produces x

for (x: 0 .. 2) {}; --> produces x1

// Code gen pseudo
for var in entry block:
    if iterate_var == var.split():
        take this variable and use it
```
After this, we also considered a backwards iteration in a for-range. Though this wasn't the most difficult (since it was
similar to us just creating jumps), it made the code lengthy as we weren't really experienced with llvm. Ultimately we 
really just needed to check the bounds of our variables, add checks to see if it was a valid decrement, and then proceed
as usual or error if it wasn't smaller --> larger (positive increment) or larger --> smaller (negative increment).
```
var a, b;
for (a : 10 .. 5 by -1) {
    b = b + a;
}
```
#### Testing
The main difficulty in testing was checking for failing tests. As mentioned before, our arrays and for-loops could fail
if certain conditions weren't met. Of course if you write a test that will produce one of these errors, then the test 
will fail, but we weren't sure how to handle these since there was nothing really similar to a try-catch in TIP. Though
ultimately after finding a helpful Piazza post, we altered our loop for our testing folder to check for files that ended 
in "_F". Here we reversed the typical loop, checking if test designated with the F (for fail) was passing when it wasn't
meant to.
```
// Modified run.sh
if [[ $i == *"_F.tip" ]]; then
    # test optimized program for tests expected to fail
    initialize_test
    ${TIPC} $i
    ${TIPCLANG} -w $i.bc ${RTLIB}/tip_rtlib.bc -o $base

    ./${base} &>/dev/null
    exit_code=${?}
    # Test is passing when it should fail
    if [ ${exit_code} -eq 0 ]; then
      echo -n "Test failure for : "
      echo $i ...
```


## Design Changes
The design considerations were ultimately based on our coding (or lack thereof) capabilities/familiarity with llvm. The main considerations were, again,
the loops and the arrays.

#### Arrays
The main consideration for the array was the size and this created two designs:

1. In the length function we figure out the array type.\
This first idea was to retrieve the array and 
then determine what type of array it was, and then either somehow grab the size from the elements (if it was an Array Of)
or just count the number of elements inside of it (traditional array). 
   - There were multiple iterations of this attempt, but ultimately we could not figure it out.
2. Place the size of the array into the array itself.\
We ended up googling how the size is typically stored, and found at that oftentimes the size was stored within the array
itself, leading us to store the size in the first element and building the rest of the array.
   - This lead to some alterations in indexing as we had to essentially shift all the values over, but ended up not 
   being too difficult to implement

#### For-Loops
We recognize that the for-loops are most likely over-engineered, however we weren't really sure how otherwise to
implement all the functionality. There was an attempt at simplification, but that was not very fruitful.