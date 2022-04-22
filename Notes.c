/* 

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

MACHINE LEARNING

    

    
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
    in order to play the best chess move with a given board and player turn

*/