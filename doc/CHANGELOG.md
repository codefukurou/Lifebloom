# **lsystem** - Changelog
All notable changes to this project will be documented in this file.

## [0.1.3] Extended Grammars

### 2018-14-07 (2:00PM - UTC+10H)
- Created class `Expression` to handle mathematical expression processes. (Method `convertRPN` **unfinished**).
- Added properties for token functions and operators.
- Adjusted class `Token` to handle floating point values.

### 2018-14-07 (9:30PM - UTC+10H)
- Created class `Token` to handle tokens for mathematical expressions.
- Implemented tokenizer for mathematical expressions stored as strings.
- Started planning implementation of shunting yard algorithm for parametric grammar functionality.

## [0.1.2] Standardised Turtle Symbols

### 2018-10-07 (9:10PM - UTC+10H)

- Class `Turtle` is now abstract and is accompanied by two polymorphic classes `TurtleCartesian2D` and `TurtleCartesian3D` which are tuned to handle 2D and 3D instruction sets respectively (3D is currently not functional but will be resolved towards the end of `0.1.x` or at the start of `0.2.x`).
- The format for the new L-system interpreter is now finalised (an example can be found in `resource/test.json`). There will likely be tweaks to this as time continues.
- Work on `0.1.3` has commenced with the design of the construction rule interpreter for the extended grammars update.
- Condensed changelog format to a concise, non-specific format such as this entry, the old format was tedious to write and (mostly not worth the effort).

### 2018-10-07 (2:40AM - UTC+10H)

- Simplifications and improvements made to `turtle.hpp` to interface with a set of predetermined instructions. As such, custom functions can not be added to the class `Turtle` (there will be no need for custom functions with the implementation of extended grammars).
- `lsystem.hpp` is currently not functional as it relies on function calls removed from `turtle.hpp` (`lsystem.hpp` is planned to be functional at the end of `0.1.3` with the extended grammars implemented).

## [0.1.1] JSON Compatibility

### 2018-08-07 (5:50AM - UTC+10H)

- Sample L-systems to demonstrate the current functionality of the program have been added in `resources`.
- Added `doc/CHANGELOG.md`, `doc/ROADMAP.md` and `doc/USAGE.md` for improved documentation.
- Changed custom `.lsystem` file parser to a popular `.json` parser (rapidjson) for flexibility and expandability in the future.
- Restructured most of the existing code to fit the new parser.
- Updated `LICENSE.md` to be markdown friendly and added licenses to all source code files.