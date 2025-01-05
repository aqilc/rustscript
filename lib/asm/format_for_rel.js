import { mkdirSync, existsSync, readFileSync as read, writeFileSync as write } from 'fs';
import { $ } from "bun";


if(!existsSync('./release'))
  mkdirSync('./release');

const hfile = read("asm_x64.h", "utf8");
const cfile = read("asm_x64.c", "utf8");

const cut1 = hfile.lastIndexOf("\n", hfile.indexOf("x64Table"));
const cut2 = hfile.indexOf("};", cut1) + 3;
const write_cfile = cfile.replace("// INSERT TABLE HERE", hfile.slice(cut1, cut2));

write("release/asm_x64.h", hfile.slice(0, cut1) + hfile.slice(cut2));
write("release/asm_x64.c", write_cfile);

console.log("Release files written to ./release");

