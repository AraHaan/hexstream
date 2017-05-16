# hexstream
Hexstream class for converting data to hex simply in C++.

## Plans

I plan to eventually when all things are said and done to hopefully try to get this added to the ISO C++ standard library.

## Reasons for this

Sometimes you just want to place a file in an C / C++ array to embed the file's data in an prebuilt binary to make something like an portable installer for something.

With this it should help make this simple. 

## Issues

if you know how I feel, I feel the need for absolutely no buffers (or pointers) allocated with ``new`` just to ``read`` an file's contents to it. After all it is hard to remember to ``delete[]`` them causing an resource leak itself.

There is has to be a better way than that by now. Even if I somehow have to hack something to do it (Overload the read function somehow) to take in an std::string or an std::wstring.

However doing that, I would have to find the implementation to the ``read`` method itself.

*But even hacking the standard library for this has consequences that is not advised. As such I recommend adding or propose such ammendments to the affected standard library classes.*
