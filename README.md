## SCCompiler

Simplified C Compiler

### Usages
```bash
scc input.c [-ast ast_path.html] [-ir ir_path.txt] [-o] out.asm
```

### Goals
- [ ] Scanner
- [ ] Parser
- [ ] Generator
- [ ] Type check
- [ ] Optimization

### Semantic Analytics
- [ ] Algebraic operation: `&, |, +, -, *, /, %, <<, >>, <, >, <=, >=, ==, !=, &&, ||, ^`
- [ ] Selection statement: `if, if-else, switch`
- [ ] Iteration statement: `while, do-while, for`
- [ ] Jump statement: `goto`
- [ ] Function call & function definition
- [ ] Variable initialization & definition
- [ ] Conditional expression: ` ? : `
- [ ] Array initialization & operation
- [ ] Enum
- [ ] String literal
- [ ] Struct
- [ ] Type cast: `(int) a`
- [ ] Pointer
- [ ] Type quailifier: `const volatile`
- [ ] `sizeof(exp)`