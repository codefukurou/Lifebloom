# **lsystem** - Changelog
All notable changes to this project will be documented in this file.

## [0.1.0] - 2018-08-07
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