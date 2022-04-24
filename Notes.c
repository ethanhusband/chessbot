/*
    Acknowledge that if these notes seem obfuscated, it is because they are primarily for the developer to refer to, 
    as many of these concepts were unlearned prior to the project like C++, neural networks and machine learning.

*/

/* 

C++

    C KNOWLEDGE IS ASSUMED HERE - SKIP THIS SECTION IF YOURE NOT A DEV, THE APPROACH WILL STILL MAKE SENSE
    Most C programs are also valid in C++, it is essentially an extension of C

    C++ uses <iostream> instead of <stdio.h>

    A good convention is that function and class names use PascalCase while variables use underscores (e.g. variable_x) 

    C++ has an explicit 'string' type unlike C 

    The main function in C++ optionally has arguments, it just needs to be named "main" really 

    Classes are instantiated in the following way:
    class MyClass {
        // Constructor Method
        public: MyClass() {
            // Instantiation
        }
    }

    To compile a C++ program, execute: g++ MyProgram.cpp -o MyProgram
    (The -o flag lets you name the resulting executable file MyProgram)

    Hello World:
    #include <iostream>
    using namespace std;
    
    int main() {
    cout << "Hello, world!";
    return 0;
    }

    Standard library names still must be enclosed in <> and user libraries must still be enclosed in ""

    The line "using namespace std;" allows us allows the usage of standard library objects without prepending the std:: identifier.
    If this line is omitted, the cout in hello world (or any other standard library object) must be replaced with std::cout

    INPUT AND OUTPUT

    To utilise input and output, we need to #include <iostream>

    To output anything we need std::cout which stands for 'characters out'. We then use the insertion operator << to
    add a set of characters to our output
    Example: std::cout << "Hello world"

    Note that multiple insertions can be used in the same statement, for example
    std::cout << "Codecademy is " << 10 << " years old.";

    Note that std::cout does not automatically append a \n at the end of each statement
    We can either append a \n to our string or add << std::end1 at the end of our insertion

    To access input, we use std::cin
    Furthermore to assign it to a string variable x we would use std::cin >> x

    Example of using input and output together:
        int age;  // the variable to hold the input value
        std::cout << "Enter your age: ";  // asks the user for age
        std::cin >> age;  // get user input and store it in variable name
        std::cout << "You are " << age << " years old.";  // print the user's age

    VARIABLES

    Mostly the same as C. Constant variables have a 'const' before they are defined

    TYPES

    5 basic C++ data types are int, double, char, string, bool (true/false not 0/1)

    Note to use strings you need to #include <string>. The string type is then references with std::string
    Strings can be indexed and have a .length() method

    OPERATORS

    All operators are the same. Do not that the bitshift operator is the same as the std::cin and std::cout insertion operator (idk how)
    Bitwise operators should be researched if needed

    POINTERS

    A reference is created by adding an & between the type and variable name, as opposed to * in C

    Refertences however have a few caveats, they can be called references and:
        References must be initialized: there is no such thing as an empty reference.
        References cannot be reassigned: reassigning an existing reference variable will produce unexpected results.

    The memory address of a variable can always be accessed by placing an & in front of the variable name

    Pointer variables are however declared in the same way as C
    Pointers are dereferenced in the same way as C

    Note: instead of NULL as the default null pointer reference, C++ uses the keyword nullptr instead

    MEMORY ALLOCATION

    For general array instantiation, we can use the new keyword

    C++ also has the malloc and realloc functions available for dynamic size updating

    CONTROL FLOW

    Conditionals are exactly the same as C
    Switch statements are the same (require breaks)
    
    C++ implements for-each loops, with the same syntax as Java:
        int fibonacci[5] = {0, 1, 1, 2, 3};
        for (int number : fibonacci) {
        std::cout << number;
        }

    Using the keyword 'auto' in a for-each loop in place of the type will let C++ deduce the type

    Calling random numbers with rand() and srand(int seed) is the same as C

    FUNCTIONS

    C++ allows for default (and therefore, optional) parameters to be passed through
    It also enables function overloading, so you can have functions with the same name
    
    To incorporate command line arguments, simply add the normal C parameters to the main function
    Note that if a command line argument intends to contain double quotes, it must be escaped first like /"

    CLASSES

    To create classes we use the class keyword
    Each class must end with a semi-colon, and in general has the following boiler plate
        class ExampleClass {

        };
    The class obviously contains attributes and methods

    The class is seperated into its public and private sections, such that all public members come after a public: keyword

    Class methods can be declared outside of the class, and sometimes need to be in header files
    They are simply preceded by the namespace that is the classname:
        void School::banner() {
            std::cout << name << " is " << age << " years old.\n";
        }

    Classes essentially replace typedef in C++

    By default, all class members are private. So there is a private: keyword, but it is often redundant

    C++ classes also include the 'protected' modifier so inherited classes can access superclass members

    Constructors can be called like so: ClassName varName(constructor arguments)

    A problem is run into when a constructor attempts to initialise const variables
    C++ implements a member initialisation list to get around this:
        public:
            Book() 
                : title("Diary"), pages(100) {}    // Member initializer list
    Where title and pages are const members

    Note any code can be placed in the constructor body after the member initialisation

    Each class also has a Destructor, denoted by ~ClassName() {}
    which is implicitly called whenever the object is destroyed or deleted

    To declare a class as extending another superclass, we use the notation
    class Dog: public Animal

    Suppose we have a superclass constructor 
        public:
            Animal(std::string new_gender, int new_age)
                : gender(new_gender), age(new_age) {}
            };
    Then we can call this in a subclass in our member initialiser list like so
        public:
            // Call base class constructor
            Dog(std::string new_gender, int new_age, std::string new_breed)
                : Animal(new_gender, new_age), breed(new_breed) {}

    VECTORS

    C++ has a vector type that is included via #include <vector>
    Unlike arrays, vectors can dynamically grow and shrink in size, they are like python lists (ideal for decision tree)
    Declared like:
        std::vector<char> alphabet;

    To add a new element to the end of the vector, use the .push_back method
    In turn the end of a vector can be removed with the .pop_back method (note this has no return value)

    Other methods include .front() and .back(), which can be used to access the last and first elements of a vector

    .size() gives vector length
    .empty() indicates if it is empty

    Vectors can be iterated through using for-each loops

    STACKS AND QUEUES

    C++ has built in stack and queue data structures under #include <stack>, #include <queue>
    Declared like so:
        std::stack<int> plates;
        std::queue<int> line;

    The stack has methods:
        - .push()
        - .pop()
        - .top()
        - .size()
        - .empty()

    Queue has methods:
        - .push()
        - .pop()
        - .front()
        - .back()
        - .size()
        - .empty()

    SETS

    C++ also has sets and unordered sets available as a type

    They are declared like so:
        std::unordered_set<int> primes;

    Set operations:
        - .add()
        - .erase()
        - .count() (check the amount of times an element is in a set)
        - .size()
        - .empty()

    Note that unordered sets are generally faster than ordered sets

    HASH MAP

    In C++, a hash map is a data structure that stores a collection of elements formed by a combination of a key value and a mapped value. 
    Each key value acts as a unique identifier for the element, while the mapped value is the content associated with this key. 
    This is often referred to as a key-value pair.

    There are two types <map> and <unordered_map>

    To declare a hashmap we need to state the type of the keys and the values:
        std::unordered_map<std::string, int> country_codes;
    You can also initialise this to have key-value pairs already, like:
        std::unordered_map<std::string, int> country_codes( 
            {{"India", 91}, 
            {"Italy", 39}});

    Hash map methods:
        - .insert({key, value})
        - .erase(key)
        - .count(key)
        - .at(key)
            This is useful for checking maps since indexing a key that does not exist will add it to the map
        - .size()
        - .empty()

    When using a for-each loop on a map, with an individual key-value pair you can do .first() and .second() to access the key and value

    Like with sets, unordered maps are faster

NEURAL NETWORKS

    How do brains recognise numbers? 
    It happens effortlessly even with pixels in different places when shown images of the same number.
    The brain resolves that they are logically equal despite being visually distinct.
    How could a program possibly recognise numbers?

    It can do so by implementing a neural network

    Variants of neural networks:
        - Convolutional neural networks
        - Long short-term memory networks
        For the moment we will just consider the 'vanilla' basic neural network
    
    Neural networks are obviously inspired by the brain, but what are neurons and how are they linked together

    For the moment, define
    * NEURON - a container that holds a number between 0 and 1

    Example:
    Starts with a 28 x 28 pixel image
    Consider the color of each pixel to have a value from 0 to 1 corresponding to how its greyscale value (how black/white it is)
    Now we have 28 x 28 = 784 neurons from an image
    * The number inside a neuron is called its ACTIVATION
    So these 784 neurons make up our first 'layer' of the neural network.
    Then our last layer of the neural network has 10 neurons, corresponding to each digit it could potentially recognise
    The numbers in these 10 neurons in the last layer, correspond to how much our system thinks each digit is what was given
        There are layers in between called HIDDEN LAYERS
        The way the network works is that activations in one layer determine the activations in the next
        In our hypothetical neural network, a 28x28 image of a number is the first layer
        This causes some specific combination of activations to be present in the second, third, nth layer
        This causes finally for a combination to be present in the last layer which tells us the number probabilities
        The brightest neuron in the last layer represents the number the system thinks it was given
    What are the hidden layers doing?
        To continue with our example, when we identify numbers, we recognise its constituent parts
        For example, 9 has a loop and a line, 8 has two loops, 4 has 4 lines
        If an individual layer had the job of identifying loops and lines, we could break this problem down
            Then recognising a loop can be broken into subproblems, like recognising the edges that compose it
        The goal is that we have a layer that recognises loop and line subcomponents, then after a layer that recognises loops and lines
        This is analogous to how the brain recognises anything, like speech breaking down into syllables, words breaking into letters etc
    Suppose all we want is a network that can recognise some particular pixel pattern, for the meanwhile
        For example, lets say we want to recognise an edge in a region of the image
        Lets assign a weight to each one of the connections from the first layer to our single neuron 'outcome' layer
        Then take all of the activations in the first layer, and compute their weighted sum
        This computes the activation of our outcome
        Suppose we made the weights of all of the pixels 0, except for some of the pixels near our region
        If you really wanted to pick up whether there was a "square" here, you would have negative weights on pixels surrounding
        This way the sum is largest when middle pixels of the region are bright, and surrounding ones are dark, better identifying an edge
        The problem usually is, computing a weighted sum like this for the next layer could come out with any value, not just 0 to 1
        However, for the network we need values to be some number from 0 to 1
        So a common thing to do is to pump our weighted some into some function that squishes the real number line to 0 to 1
        A function that does this is the sigmoid function sigma(x) = 1/(1+e^-x)
        So the activation of our 'outcome' neuron is sigma(weighted sum)

    Perhaps you dont want a neuron to activate if its weighted sum is greater than 0
    Maybe you want it to be greater than say 10, to induce a sort of BIAS against this neuron
    Then in that case it would have an activation calculated sigma(weighted sum - 10)

    But consider how much instruction we have to give to a larger second layer, a bias for each one
        We would have 784 * 16 weights, + 16 biases per layer connection
        And all of that is just a connection between two layers

    So learning refers to getting the computer to figure out the correct weights and biases

    Before continuing though, notice how cumbersome it is to write out the sigma(sum)

    As a result, we write out each activation in a given layer as a vector (with the size of the layer)
    Then we write out each weight as a matrix, where: 
        - Each row corresponds to the weights each neuron has to a single neuron in the next layer
        - (In turn, each column corresponds to the weight of one neuron relative to each of those in the next layer)
        - There matrix should therefore have <current layer size> columns, <next layer size> rows
    
    Then our sigma(weighted sum) is equivalent to sigma([weight matrix] * [activation vector] + [bias vector]) 
        Written as a^(n+1) = sigma(Wa^(n)+b)
    The result is another [activation matrix]

    This makes the code a lot faster, since many libraries optimise matrix multiplication

    We can see now that it could be more accurate to think of the neurons as a function,
    one that takes layer0size inputs and outputs a number from 0 to 1

    Composing all these functions, the entire network can be viewed as one function

    Relatively few modern networks actually use the sigmoid function anymore
    An easier to train function is one called ReLU(a) = max(0, a)
        Has an interesting biological motivation from how neurons are either activated or not

HOW NEURAL NETWORKS LEARN

    Our example goal is still handwritten digit recognition - the 'hello world' of neural networks
    
    To recall our example, a 24x24 image determines the activations of 784 neurons on an input layer
    Each activation in the following layers is determined by a weighted sum of every activation in the previous layer, plus bias
    This is then passed through a sigmoid or ReLU function which scales the weighted sum between 0 and 1
    In sum, with 2 hidden layers of size 16, an input layer of size 784 and output layer of size 10, 
        the network has around 13000 weights and biases which might be adjusted
    The motivation for our structure was that hopefully the second layer picks up on edges,
    The third layer picks up shapes
    The final layer recognises a number

    What we want is an algorithm which provides numbers, and their actual value,
    and the network can adjust its 13000 variables depending on how correct it was (training)

    Ultimately machine learning is just finding the minimum of some given function, by adjusting its 13000 variables.

    To start things off, the weights and biasses are initialised totally randomly
    The network will initially perform horribly
    What must be done is that you define a 'cost' function, which compares the output layer and desired output layer
        More specifically, you add up the squares of the differences for each value, and this is the cost of the training example
    In turn, the layer the number on the cost function, the worst the network has performed

    Then what you can do is take an 'average cost' over tens of thousands of training example,
    getting a more justified measure of how good or bad the network is

    Now we can see how we are just trying to minimise a function, that is, the cost function, and can adjust 13000 variables
        in order to do so

    How we can minimise each time? Consider a function with a single input
        If we can figure out the slope at our given random point, we can figure out which direction to move in to minimise
        I.e. shift to the left if slope is positive, shift to the right if negative
        A caveat is that there is no gaurantee that a local minimum you land in will be the absolute minimum
        Also note if you make your step sizes proportional to the slope, then you go slower when flattening out

    For a function with two inputs, the problem is to ask which (x, y) direction to step in order to decrease
    Taking the negative of nablaF gives you the direction

    So in general, the process for computationally finding the minimum is
        Compute nabla of function at this random point
        Take a step in the -nablaF direction
        Repeat
    
    If you organise the 13000 weights into one vector, then we want to move in direction of the negative cost function gradient 
    at this 13000 weight 'point'
    Remember that the cost function represents an average over all of the training data

    A network 'learning' always means minimising a cost function

    This network will simply learn the patterns itself, we never actually told it what it was looking for.
    It learns purely based on what the output was compared against to create the cost function

    Wrapping up, the network still doesnt actually recognise patterns by the second layer, shapes by the third etc
    The patterns it recognises make no sense to us
    And in fact, if we show it a nonsense image, it will say that it is some particular number with certainty
    That is since we always provided certain comparisons
    
    What we have introduced so far is an outdated type of neural network, a 'multilayer perceptron'
    More advanced modern variants are better at the job, but this was necessary to introduce as a foundation to the idea

BACKPROPAGATION

    Backpropagation is an algorithm for computing the gradient we need to revise our weights and biases

    The derivative cost function for a set of weight values tells us how sensitive the cost function is to changes in each weight

    We said before that the cost function takes the average of multiple examples, but for now consider just one example, a 2.
    What effect should this one example have on how the weights and biases are adjusted
    Untrained, our cost function will have a high output, output activations will be quite random

    What we need is the output activation for the 2 neuron to be higher next time, and all others closer to 0
    This output activation for neuron 2 is a product of a few variables:
        - b bias in calculation of 2 (should be increased)
        - w_i every weight involved in calculation of 2 (should be increased in proportion to activation_i)
        - activations of the previous layer (should be modified)
    *Note that increasing the weights connected to neurons in the previous layer with a high activation havr a greater efect
    on the activation of the output neuron than increasing the weights for those in the previous layer with low activations

    The other way to increase the activity of the output 2 neuron is to increase a_i for all positive weights
    and decrease a_i for all negative weights
    However, we also want every non-2 neuron to be less active, and each of these has its own set of weights
    So what is done is that the desired previous a_i value for every output neuron is added together to give what it should be
    This is where the idea of propagating backwards comes in
    
    Note that as soon as we do this process for one layer, we can recursively do it for all layers

    If we trained this network, it will obviously eventually realise that every image is a two
    However, if we average out the desired w_i values for each training example, we get a network that coordinates a larger task
    This averaged amount is equivalent to the negative gradient of the cost function! (or a good approximation, at least)

    Since a large amount of training data will take too long for a computer to average out,
    We often break it into smaller amounts of examples for each backprop step to occur

    This technique is referred to as stochastic gradient descent

    It is worth noting that for all kinds of neural networks, a lot of training data is needed.

    NOTE: The 'softmax' function is often used over the sigmoid function

BACKPROPAGATION CALCULUS

    https://drive.google.com/file/d/1ehuLY3Gx08icoJ-sh7ymuomiF0kRCJyx/view?usp=sharing
    

RECURSIVE DATA STRUCTURES

    Consider a piece of data with various fields:
        School {
            classes
            students
            teachers
            dilfs
        }

    Then ask, what if this 'object' or 'structure' of data contained an instance of itself
        School {
            classes
            students
            School
        }
        Perhaps this would relate to a sister school once instantiates, but as for an abstract representation, it is entirely
        the case that this object is nesting a copy of itself, in a recursive manner

    Naturally, theres no reason this cant extend to an object containing multiple instances of itself
        School {
            classes
            students
            School[]
        }
        Where one object school somewhat recursively contains an array of schools, identical to itself

    The example that this idea relevantly extends to is that an object "tree" can have some contained set of 'branches'
    But then these branches within the scope of themselves can also be perceived as their own 'tree'
    So we can safely say that a given tree has the structure
    Tree {
        Color
        Shape
        Tree[]
    }

    

MINIMAX TREE

    A minimax tree has the exact same structure as described directly above.
    It is a data structure that 'contains' multiple instances of itself
    However, it also contains a "cost" value.
        This cost value is often based on something that needs to be evaluated, like, who is winning in a given chess position

    How this "cost" will be evaluated will have a number of factors that are to be resolved later,
    but for now just assume that each board can be perfectly evaluated as "winning or losing" for a certain player (say, white)
    We also need to know whose turn it is given a board, so we can add that to our data structure

    Then our minimax tree has the following structure
    MiniMax Tree {
        board
        cost
        turn
        MiniMax Tree[] (called, options vector)
    }

    Now we have a single minimax tree structure that contains the game board you currently have (called BOARD 1)
    Then, what we can do is generate every possible move that could be made given this board and whose turn it is.
        All called BOARD2a, BOARD2b, ..., BOARD2n
    Then for each of these boards generated, we have a board, whose cost we can evaluate, and we know whose turn it will be.
        Hence, we can create another Minimax Tree structure out of this board (containing an empty array of other minimax trees, for the moment)
    
    So we see our BOARD 1 is a Minimax Tree structure with:
    a board
    a cost
    a value indicating whose turn it is
    an array of minimax trees (which have BOARD2a, BOARD2b, ..., BOARD2n)

    But also, each of BOARD2a, BOARD2b, ..., BOARD2n are Minimax Trees, which we can do the exact same thing with
    So what we end up with is a "root" board, then branches with all its possible moves, 
    then for each possible move, there are branches with all those possible moves and so on

    So how do we decide which move to choose?

    What we do is the following:
        Pick the first possible move for our root board (BOARD1)
        For that possible move we picked, the result of that move is another board
        Pick the first possible move for that board
        ...
        Continue until there are no possible moves on a given set of 
        For each Minimax Tree that is in the same options vector, compare the costs of each board
        If the cost was designed such that a higher cost means a "better" board for white,
            then for the Minimax Tree which this options array is apart of, if it is blacks turn
            assign it the lowest cost, if it whites turn assign it the highest cost.
        Continue this until we reach the root, in which case for the root Minimax Tree object, 
            if it is whites turn we play the move in the options array which propagated the highest cost,
            if it was blacks turn we play the move that propagated the lowest cost.
        This way we play with the assumption that each player plays the best move possible, such that we choose the best option
            while assuming the worst case, therefore optimising the choice we make about which move to play

        Obviously this cant be down to the bottom of a tree of all chess boards, so we will stop at a particular depth
        (a depth chosen such that it completes in some desired amount of time)

        This is how Minimax Trees are employed so the computer can choose the best move to play (from a Game Theory perspective)


BRINGING IT TOGETHER

    Ultimately, the program employs a neural network self-learning board evaluation mechanism in amalgamation
    with the the minimax tree paradigm (utilising other techniques like Alpha-Beta pruning 
    to and the neural network growing more accurate over time to shrink the tree size and therefore run faster)
    written in C++ in order to play the best chess move with a given board and player turn.
    



REFERENCES

https://www.cs.tau.ac.il/~wolf/papers/deepchess.pdf

https://ccrl.chessdom.com/ccrl/4040/games.html



*/
