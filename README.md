<p align="center">
<h1 align="center"> Brainfreeze </h1>

<h3 align="center">A brainfu*k compiler written in C.</h3>
</p>
<p align="center">
<img align="center" width="30%" src="https://raw.githubusercontent.com/GnikDroy/brainfreeze/master/images/brainfreeze.png">
</p>



## Requirements
- as (The GNU assembler)
- ld (The GNU linker)


## Meeting the Requirements


**The project uses CMake to compile the project**

Make sure that the requirements are met.

### Linux

I think most systems come with as and ld if you have gcc installed.
A more concrete way to meet the requirements will be added soon.

`sudo apt-get update`

`sudo apt-get install cmake build-essential`


## How to compile

Clone this github repository, and make a folder named 'build' inside the project root folder.

`git clone https://github.com/GnikDroy/brainfreeze`

`mkdir build`

Then, we can compile the compiler here.

`cd build`

`cmake ..`

`make`

This will create a new folder named  `bin` inside the build folder.

The compiled compiler should be inside. 


## Running

After compiling the compiler, we can compile other bf source files! ;)

`cd bin`

`./brainfreeze -h`

Notice that there are some examples in the `examples` directory. You can use them for testing. I have made sure to use open source code or given proper credits to the owners of the code.


## Creating the documentation

The project uses Doxygen for managing its documentation.

If you wish to read the documentation, install doxygen.

`sudo apt-get install doxygen-gui`

You might also need to install `graphviz` for visualizing the relations.

`sudo apt-get install graphviz`


You can create the docs by running `doxygen` inside the root folder.

All the documentation will be created under the `docs` folder.


## Optimization

Currently this compiler does not implement any sort of optimizations. It may be added in the future.

I used the project image from <a href="https://pixabay.com/vectors/brain-icon-human-background-idea-1710293/">here</a>.
