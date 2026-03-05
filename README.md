# baseconv

A lightweight CLI tool to convert numbers between binary, decimal and hexadecimal, written in C++.

## Usage
```bash
baseconv <value> --from <base> --to <base>
```

### Supported bases
- `dec` — Decimal (base 10)
- `hex` — Hexadecimal (base 16)
- `bin` — Binary (base 2)

### Examples
```bash
baseconv 255 --from dec --to hex     # FF
baseconv FF  --from hex --to bin     # 11111111
baseconv 11111111 --from bin --to dec # 255
```

## Build from source
```bash
cmake -B build -G Ninja
cmake --build build
./build/baseconv 255 --from dec --to hex
```
## License
MIT
