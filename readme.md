# rustscript

A very ambitious project, with the goal of making a combination systems language that tries to combine the main concepts from the languages Typescript and Rust. Aims to be the first systems language to have JSON as a first class citizen. Data types will be simple like C and other than slight ownership, will leave management to the user. Should be usable without types with powerful inference to an extent.

### Preliminary Syntax

This syntax is the current goal:

```rust
struct Datatype { // Syntax is similar to JS classes, but more concise and requires types.
	number: u32 = 0; // Optionals and defaults in-built.
	string: string; // Only stores length and capacity with extremely transparent and simple logic and easy conversion to C string.
	array: u32[]; // All arrays are variable size, contain the same things as strings.
	object: { [key: string]: string }; // or record<string, string>
	object2: {
		hi: string,
		[2]: bool // Unlike in Typescript, number keys are possible
	}; // { ... } type declarations are treated as records, not Structs. If you want to make a struct you have to define it with `struct x {}`.
	optional?: *Database; // Option types can only be pointers. Type recursion can only be done with pointers.

	// Struct methods
	print() => print("hello ${this.string}")
	static hi() => "something"
}

// Strings, objects and arrays will always be heap allocated unless they are never modified. They will not be available on the "systems" flavor of the language.

const obj = {
	prop: "lol"
}; // Defines a map or struct depending on if the indexing operator([]) is ever used on it.
// obj.prop and obj["prop"] will always do completely different things, and the second will always be slower.


Datatype {
	object2: {
		hi: false, // ERROR: Property "hi" expected to be of type string but is assigned to a boolean!
	} // ERROR: Property "2" needs to be defined!
}; // ERROR: Need to define `string`, `array` and `object`!
	
const d = Datatype {
	number: 4,
	string: "world",
	array: [1, 0],
	object: {
		hi: "syntax inside of objects is just like structs"
	},
	object2: {
		hi: "i really want to finish this project for once",
		[2]: true
	}
}

d.print(); // "hello world"
print(d.number == 4, d.string.len == 2, d.array.len == 2, "hi" in d.object); // All true.


// ? in front of any type creates an option type, would take no extra memory for pointers.
const res: ?u32 = [3, 3, 4].find(a => a == 3)
if res {
	// Inside this if statement, res's type automatically resolves to u32 and the option type/data is discarded.
	print("hoorah we found ${res}")
}
print("we can also unwrap types with ? like this: ${res?}")

// Alternative function syntaxes (last one is technically what happens internally anyways)
fn ez1() { 1 }
fn ez1() => 1;
const ez2 = () => 1;
```

### Syntax TODO

- [x] `return 0;`
	- [x] Basic Tokenizing
	- [x] Basic AST generation
	- [x] Basic Code Generation and execution
  	- [x] x86 Code Generation
    	- [x] AST Iteration
    	- [x] Statement -> Assembly
		- [x] Custom Assembler library
  		- [x] Assemble Basic instructions like `push rax`
  		- [x] Prefixes
  		- [x] Hints
  		- [ ] Vector EXtension Instructions
    		- [ ] EVEX
- [ ] `return 1 + 1;`
	- [x] Expression Parsing
		- [ ] Order of Operations
		- [ ] Unary Operators
		- [ ] Comma
  - [ ] x86 Code Generation
    - [ ] Expression iteration and emitting appropriate instructions
- [ ] `print("lol");`
	- [ ] Function Calls
	- [ ] Linking to the C library / externally defined functions.
- [ ] `fn main() { return 0; } return main();`
	- [ ] Function Calls
	- [ ] Linking to the C library / externally defined functions.

### Concepts

- Simple Ownership rules
	- `*` = Mutable pointer, `&` = Immutable Reference
		- Cannot take multiple `*`s of an object at once.
- "number" type
  - Will start off as an i64, but will be changed to a double depending on operands. Similar to how JS numbers work.
- Immutable strings
	- `"hi" + 2`
		- Checks if `2` has a `toString` trait and calls it if it does, then makes a new string with the combination of the two.
		- If string size is known at compile time, it will not be put with the data.

### Execution

- JIT
- Assembly output -> `nasm` -> Linking with C STDLIB -> Binary

> Reusing a lot of code from `aqilc/jsc`
