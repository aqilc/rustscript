# rustscript

A very ambitious project, with the goal of making a combination systems language that tries to combine the main concepts from the languages Typescript and Rust. Aims to be the first systems language to have JSON as a first class citizen. Data types will be simple like C and other than slight ownership, will leave management to the user. Should be usable without types with powerful inference to an extent.

### Preliminary Syntax

This syntax is the current goal:

```rust
struct Datatype { // Syntax is similar to JS classes, but more concise and requires types.
	number: u32 = 0; // Optionals and defaults in-built.
	string: str; // Only stores length and capacity with extremely transparent and simple logic and easy conversion to C string.
	array: u32[]; // All arrays are variable size, contain the same things as strings.
	object: { [key: str]: str }; // or record<str, str>
	object2: {
		hi: str,
		[2]: bool // Unlike in Typescript, number keys are possible
	}; // { ... } type declarations are treated as records, not Structs. If you want to make a struct you have to define it with `struct x {}`.
	optional?: *Database; // Option types can only be pointers. Type recursion can only be done with pointers.
}

// Strings, objects and arrays will always be heap allocated unless they are never modified. They will not be available on the "systems" flavor of the language.

const obj = {
	prop: "lol"
}; // Defines a map or struct depending on if the indexing operator([]) is ever used on it.
// obj.prop and obj["prop"] will always do completely different things, and the second will always be slower.

// Alternative function syntaxes (last one is technically what happens internally anyways)
fn ez1() { 1 }
fn ez1() => 1;
const ez2 = () => 1;

fn main() {
	print("hi");
	Datatype {
		object2: {
			hi: false, // ERROR: Property "hi" expected to be of type str but is assigned to a boolean!
		} // ERROR: Property "2" needs to be defined!
	}; // ERROR: Need to define `string`, `array` and `object`!
	
	const d = Datatype {
		number: 4,
		string: "hi",
		array: [1, 0],
		object: {
			hi: "syntax inside of objects is just like structs"
		},
		object2: {
			hi: "i really want to finish this project for once",
			[2]: true
		}
	}

	print(d.number == 4, d.string.len == 2, d.array.len == 2, d.object.has("hi")); // All true.
	
	0
}
```

### Syntax TODO

- [ ] `fn main() => 0;`
	- [ ] Basic Tokenizing
	- [ ] Basic Code Generation and execution
		- [ ] Start working on custom Assembler library
- [ ] `fn main() => 1 + 1;`
	- [ ] Expression Parsing
		- [ ] Order of Operations
		- [ ] Unary Operators
		- [ ] Comma
- [ ] `fn main() { print("lol") }`
	- [ ] Function Calls
	- [ ] Linking to the C library / externally defined functions.

### Concepts

- Simple Ownership rules
	- `*` = Mutable pointer, `&` = Immutable Reference
		- Cannot take multiple `*`s of an object at once.
- Immutable strings
	- `"hi" + 2`
		- Checks if `2` has a `toString` trait and calls it if it does, then makes a new string with the combination of the two.
		- If string size is known at compile time, it will not be put with the data.

> Reusing a lot of code from `aqilc/jsc`
