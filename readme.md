# rustscript

A very ambitious project, with the goal of making a combination systems language that tries to combine the main concepts from the languages Typescript and Rust. Aims to be the first systems language to have JSON as a first class citizen.

### Preliminary Syntax

This syntax is the current goal:

```rust
struct Datatype {
	number: u32 = 0; // Optionals and defaults in-built.
	string: str; // Only stores length and capacity with extremely transparent and simple logic and easy conversion to C string.
	array: u32[]; // All arrays are variable size, contain the same things as strings.
	object: { [key: str]: str }; // or record<str>
	object2: {
		hi: str,
		[2]: bool // All keys are automatically converted to strings.
	}; // { ... } type declarations are treated as records, not Structs. If you want to make a struct you have to define it with `struct x {}`.
	optional?: *u32; // Option types can only be pointers.
}

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
			"2": true
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
