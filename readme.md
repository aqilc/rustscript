# rush



### Goals

- Simple and easy to use syntax
- Everything should be typed
- As much type inference as possible
- Explicit type conversions
- JSON as a first class citizen
- Ease of typing and rapid prototyping
- Compile to .exe, importing types and metadata from .exe.
- As compatible with C as possible

### Preliminary Syntax

This syntax is the current goal:

```typescript
class Datatype { // Syntax is similar to JS classes, but more concise and requires types when there are no default values.
	number: number = 0; // Optionals and defaults in-built.
	string: string; // Only stores length and capacity with extremely transparent and simple logic and easy conversion to C string.
	array: number[]; // All arrays are variable size, contain the same things as strings.
	object: { [key: string]: string }; // or record<string, string>
	object2: {
		hi: string,
		[2]: bool // Unlike in Typescript, number keys are possible
	}; // { ... } type declarations are treated as records, not Structs. If you want to make a struct you have to define it with `struct x {}`.
	optional?: Database;

	// Class methods
	print() => print("hello ${this.string}")
	static hi() => "something"
}

// Strings, objects and arrays will always be heap allocated unless they are never modified. They will not be available on the "systems" flavor of the language.

const obj = {
	prop: "lol"
};

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
		hi: "syntax is the same as js"
	},
	object2: {
		hi: "i really want to finish this project for once",
		[2]: true
	}
}

d.print(); // "hello world"
print(d.number == 4, d.string.len == 2, d.array.len == 2, "hi" in d.object); // All true.


// ? in front of any type creates an option type, would take no extra memory for pointers.
const res: ?number = [3, 3, 4].find(a => a == 3)
if res {
	// Inside this if statement, res's type automatically resolves to number and the option type/data is discarded.
	print("hoorah we found ${res}")
}
print("we can also unwrap types with ? like this: ${res?}")

// Alternative function syntaxes (last one is technically what happens internally anyways)
fn ez1() { return 1 }
fn ez1() => 1;
const ez1 = () => 1;

fn func1(str: string) { return str; }
fn func3(reg: Regex) => reg.exec("hi")

func1("hi")
func1 "hi"
func3 /rand\w+/g
```

### Concepts

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
