# OpenGMocker
## What is OpenGMocker?
OpenGMocker is a tool for generating gmock files from C++ interfaces. It consists of two parts:
* A simple command line tool - This is the core of OpenGMocker which can be used completely in isolation
* A Visual Studio 2022 extension - This currently provides a very barebones interface to the command line tool within Visual Studio. The plan is to gradually add more features to this and to make it more visually appealing.
  
It's currently a Windows-only tool, but the core tool could easily be built for other operating systems.

## How do I get it?
See releases here. (TODO: Add a link to releases)

## How do I use it?
* Command line tool - Simply pass OpenGMocker an input file and an output file at the command line like so:
  
  `OpenGMocker.exe ITestInterface.h MockTestInterface.h`
  
  OpenGMocker currently only supports mocking of one file at a time and the file in question is expected to contain a single interface e.g.
  ```
  #ifndef ITESTINTERFACE_H
  #define ITESTINTERFACE_H
  
  class ITestInterface
  {
  public:
    virtual ~ITestInterface() = default;
    [[nodiscard]] virtual int GetValue() const = 0;
  };
  
  #endif
  ```
  Multiple interfaces per file may be supported at some point, but because this isn't how I would normally use this tool that isn't a priority at the moment.
* Visual Studio Extension - With the extension installed, in the tools menu you will see the option to run OpenGMocker. A rather unattractive pop-up will show up letting you select the input and output files to run the OpenGMocker tool with. For the moment you will have to manually add the generated mock file to your Visual Studio project. This process will be automated at a later date; again it's a case of this not being important for my current use case.

## Contributing
Bug reports, feature suggestions and pull requests are all very much welcome! I'll be continually supporting this tool because I'll be using it daily.
