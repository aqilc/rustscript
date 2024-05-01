# Reference

This holds the main language reference. Most people that know Typescript should be able to learn this quickly.

## Variables

```rust
let a = 1
let b: number = 1
const c = "hello"
```

## Primitives

```typescript
let a: u32[] = [1, 2, 4];
let b: bool = false;
let c: *bool = &b;
```

## Logic

```rust
if hi < 10 {
	return
}
if hi < 10 return // equivalent

for i in array {}
for i of array {}
for i in obj {}

for i to 10 {}
for i from 0 to 10 {}
for i = 0; i < 10; i ++ {} // equivalent to above

while cond =>;
while cond {}
```

## Types

```typescript
type A = number
type B<T> = T
type C = { x: number, y: number }
type D = struct { x: number, y: number }
type E = `number` // matches all number strings, only accepts concrete input
```

## Functions

```rust
// Two main ways to declare functions
fn hello() { return "world"; }
fn hello() => "world"

fn add(a, b) => a + b
fn add(a: number, b: number) => a + b // Overload
fn add(a: u32, b: u32) => a + b

add("hello", "world") // calls add(a, b)
add(1, 2) // calls add(a: number, b: number)
add(1u32, 2u32) // calls add(a: u32, b: u32)

fib(10) // Functions can be used before they're declared
fn fib(n) {
	if n <= 1 {
		return n
	}
	return fib(n - 1) + fib(n - 2)
}

const anon = fn() => 2

fn rest(a, b, ...rest) => rest
fn rest(a, b, ...rest: number[]) => rest

rest("a", "b", "c", "d", "e") // ["c", "d", "e"]
rest(1, 2, 3, 4, 5) // [3, 4, 5]

fn func2({ hi: alias }: { hi: string } = { hi: "default" }) => alias

fn template<T>(a: T): T => a
fn templaterest<T>(a, b, ...rest: T[]): T => rest[0]

```

### Arrow Functions

```javascript
const func = () => 1;
func()
```

## Structs

Use different terminology since they're different from Javascript Classes. You cannot use indexing operators (`[]`) on structs.

```rust
struct Point {
	// order packed into memory is arbitrary
	x: number = 3;
	y?: *Point, // the only self reference allowed is through pointers
	#z: number = 2 // private member
	[1 + 2]: string // number keys

	// All methods return self by default unless specified.
	method1() { return this.x; }
	static method2() => Point {}
	method3 => this.y
	#method4() => this.#z; // private method
	method5() {} // returns self

	method6: number => this.y // Types are allowed for getters. No overloads allowed for them though.
	
	// most methods will probably get inlined anyways, but this will 100% inline
	inline method7() => this.method1() + this.method3 + this.method6
}

// Struct attributes (TBD)
struct rgb is Ordered, Packed { r: u8, g, b; }

let point = Point { y: &point, [3]: "hello!" }
let color = rgb { 10, 20, 30 }
point.method5()..method7
```

> Note: , or ; are allowed to separate members, but you can put them on new lines without either.

## Objects

Behave mostly like JavaScript Objects

```typescript
let hi = {
	"full": "json" + " supported",
	[1 + 2]: "number keys supported",
}

type someobj = {
	hi: number
}
type someobj2 = object
type someobj3 = object<number, string>
```
