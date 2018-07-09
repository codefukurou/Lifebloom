# **lsystem** - Development Roadmap
## [0.1] Classical L-systems

The first and most fundamental feature of this project is to implement the classical two dimensional, turtle graphics driven, implementation of the L-system. This type of L-system is the most common but can still has a lot of flexibility in it's development. This major patch should aim to create an effective interface for the classical L-system, while keeping in mind it's capabilities for expansion.

### [0.1.0] Baseline Functionality - ⭕️ 

The program (running OpenGL) should be able to generate a standard L-system from an axiom, a list of rules and a list of functions given by the user in some form. Unlike most simple L-system generators, the user must have the ability to modify the initial state of the turtle and be able to modify the turtle state through token functions. The turtle must be able to be capable of processing and drawing colours using a HSL colour space. 

<!-- Give more information on L-systems. -->

### [0.1.1] JSON Compatibility - ⭕️ 

To be as accessible as possible to users without using a GUI, L-system configuration files should use the `.json` format style. This will also help as the scope of the project becomes larger (the format is easily expandable and flexible in its implementation). The exact format and rules of the `.json` will probably not be finalised until much later in the patch cycle, so at this point the only main requirement is that the **[0.1.0]** functionality is maintained and compatible with the `.json` implementation. For convenience, a pre-established `.json` parser will be used ([RapidJSON](https://github.com/Tencent/rapidjson)), and a small sub-parser will be written to help **RapidJSON** interface with the L-system components.

### [0.1.2] Standardised Turtle Symbols - ❗️

To make this program as accessible as possible (particularly to those that already are familiar with L-systems), symbols that the turtle is capable of interpreting should be static. The symbols that are to be used are as follows:

| Symbol        | Function                                       |
|:-------------:|------------------------------------------------|
| F($\alpha$)   | Move forward by $\alpha$ and draw a line       |
| f($\alpha$)   | Move forward by $\alpha$ and don't draw a line |
| +($\alpha$)   | Turn left by $\alpha$ degrees                  |
| -($\alpha$)   | Turn right by $\alpha$ degrees                 |
| ^($\alpha$)   | Pitch up by $\alpha$ degrees                   |
| &($\alpha$)   | Pitch down by $\alpha$ degrees                 |
| <($\alpha$)   | Roll left by $\alpha$ degrees                  |
| >($\alpha$)   | Roll right by $\alpha$ degrees                 |
| \|            | Turn around.                                   |
| $             | Rotate the turtle to the vertical              |
| [             | Start a branch                                 |
| ]             | Complete a branch                              |
| !($\alpha$)   | Decrement the segment diameter by $\alpha$     |
| `($\alpha$)   | Increment colour index by %\alpha%             |

There will likely be more functions as this project evolves but these turtle functions form a decent basis. 

### [0.1.3] Extended Grammars - ❌

L-systems are capable of a number of advanced grammars that can introduce new layers of complexity. Each of the new grammars described below should be implemented into the program and configuration files:

#### Stochastic Grammars

Using stochastic grammars, each of the symbols in a grammar can be given a number of different production rules that have their own probability of occurring. For example, the deterministic production rule,

$$
\mathbb{0} \rightarrow \mathbb{1[0]0}
$$

could become,

$$
\mathbb{0\{0.5\}} \rightarrow \mathbb{1[0]0}
$$
$$
\mathbb{0\{0.5\}} \rightarrow \mathbb{0[0]1}
$$

where $\mathbb{0} has a 50% chance to become $\mathbb{1[0]0}$ and a 50% chance to become $\mathbb{0[0]1}$ upon production.


#### Context Sensitive Grammars

Coming soon...

#### Stochastic Grammars

Coming soon...

<!-- 
### [0.1.4] Dynamic Variables - ❌
### [0.1.5] Advanced Rendering - ❌
### [0.1.6] SVG Exportation - ❌
### [0.1.7] Polylines - ❌
### [0.1.8] Animation - ❌ -->

### [0.1.x] Documentation - ❌

Although not necessarily convenient to those that wish to understand and contribute to the project. Documentation for this major patch will not be released until the end of the patch cycle (this won't be the same for every patch cycle). While I am establishing this repository and adjusting to the development of a potentially long term project like this, I need time to decide exactly how documentation of this project should be executed. In the mean time, I will do my best to comment the code well.