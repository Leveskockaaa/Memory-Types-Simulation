# Second Programming Home Project

## Purpose of the program
With this program I wanted to simulate how the memory in the computers works.
But with different types like:
- Integer
- Character
- Float
- String

## How to use the program

Create a new Processor (core):
Processor cpu(cpu-core);

Create a new Memory where you can store the informations:
Memory memory;

Create a new hub for peripherals where you can connect your peripherals:
PeripheralHUB hub;

The peripherals can store std::vectors with the different types above.
The four options:
- std::vector<int> int-vector = {1, 2, 3, 4 };
- std::vector<char> char-vector = {'c' ,'h' ,'a' ,'r' };
- std::vector<float> float-vector = {3.0f, 3.1f, 3.14f }; 
- std::vector<std::string> string-vector = {"cpp", "ctor", "dtor", "goesbrr" };

You can add more types but those must have a form that you can write out to a file in characters and that back without lose any data.

Create a new Peripheral:
basePeripheral* int-peripheral = new Peripheral<int>(int-vector, "mouse", Int);
basePeripheral* char-peripheral = new Peripheral<char>(char_vector, "keyboard", Char);
basePeripheral* float-peripheral = new Peripheral<float>(float_vector, "camera", Float);
basePeripheral* string-peripheral = new Peripheral<std::string>(string_vector, "keyboard", String);

Create new memoryblock:
baseMemoryBlock* int-memory = new memoryBlock<int>(int_vector, Int);
baseMemoryBlock* char-memory = new memoryBlock<char>(char_vector, Char);
baseMemoryBlock* float-memory = new memoryBlock<float>(float_vector, Float);
baseMemoryBlock* string-memory = new memoryBlock<std::string>(string_vector, String);

Print out what is in a peripheral:
int-peripheral->print();
char-peripheral->print();
float-peripheral->print();
string-peripheral->print();

Print out what is in a memoryblock:
int-memory->print();
char-memory->print();
float-memory->print();
string-memory->print();

