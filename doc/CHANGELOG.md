# **lsystem** - Changelog
All notable changes to this project will be documented in this file.

## [0.1.2] - 2018-10-07
### Added

- `enum` for direction vector indices (`HEAD`, `LEFT`, `UP`).
- `map<char,double> Turtle::m_defaults` for default function arguments.
- `Turtle::constructFunctionMap()` to define functions for symbols and their defaults.

### Changed

- `Turtle::m_state` is now a custom `struct State` with members `position`, `direction`, `diameter` and `color` instead of a `map<string,double>`.
- `Turtle::generateDrawList(string word)` is now called `Turtle::processWord(const string& word)` 
- `map<char,vector<function<void()>>> Turtle::m_fmap` renamed and retyped to `map<char,function<void(double)>> Turtle::m_functions`
- 

### Removed

- `Turtle::addFunction(char c, string label, double param)` (turtle functions are now predetermined).
- `Turtle::initState()` - Soon to be done with `struct State` constructor
- `Turtle::setState()` - Soon to be done with `struct State` constructor
- 

### Notes

- `lsystem.hpp` is currently not functional (it relies on function calls removed from `turtle.hpp`)

## [0.1.1] - 2018-08-07
### Added

* Sample L-systems (see `resources/*.json`)
* `CHANGELOG.md` to track changes and progress.
* `ROADMAP.md` to plan new feature.
* `USAGE.md` to explain how to use the program (currently uncompleted on the basis that the `.json` interface will likely change dramatically in the near future).

### Changed

* Changed custom `.lsystem` file parser to a popular `.json` parser (rapidjson) for flexibility and expandability in the future.
* Restructured most of the existing code to fit the new parser.
* General cleaning and optimization.
* Updated `LICENSE.md` to be markdown friendly.
* Added licenses to all source code files.

### Removed

* A number of old (unnecessary) classes were removed (or replaced).
* Old `.lsystem` files that are now incompatible.