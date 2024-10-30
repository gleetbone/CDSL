# Agent

This data structure implements the basis for a class of instances that represent an action (function) to be executed, along with its input parameters and result (if any).
These classes are similar to what are called closures or continuations in other languages.
Understanding how this class is used requires the study of an example, such as the one in the Test/Agent directory. 
Agents can be used for a variety of purposes, including holding actions that may be invoked by user interaction (as from a GUI menu item selection), or to hold a task for a worker thread.

This data structure class provides two functions that allow all agents to be invoked and disposed in the same way.

### Protocols Supported

none
