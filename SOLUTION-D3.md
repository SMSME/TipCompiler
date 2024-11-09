We created 4 new files in src/semantic/types/concrete. These were TipBoolean.h, TipBoolean.cpp, TipArray.h, and TipArray.cpp. At first, we implemented TipBoolean because we thought it would be a good idea to figure out what exactly we needed to do for a new type before tackling TipArray, which we believed to be harder. To fully implement TipBoolean, we modified TipCons.cpp

- Testing : modified substituter to aid tests, didn't modify TypeHelper to aid tests.
- Testing: we achieved high code coverage by running the commands and checking what hadn't been covered and writing tests for each thing that wasn't covered.
- Array: mention the alternatives we thought of and how it took us a while to figure it out. 
