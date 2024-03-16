# Ideas that I might actually get to some day

- Expose a `Builder` trait that others can extend
  - This builder trait would allow JSX to be used in the language, like:

```rust
struct Field { name: string; content: string; }
struct Image { url: string; }
struct Embed implements Builder {
	children: (Field | Image)[];
	props: 
}

const embed = (
	<Embed title="title">
		<Field name="hi" content="i'm a field"/>
		<Image url="https://..."/>
	</Embed>
);
// equivalent to...
const embed = Embed {
	title: "title",
	children: [
		Field { name: "hi", content: "i'm a field" },
		Image { url: "https://..." }
	]
}
```

	- Definitely can be better named.
- 