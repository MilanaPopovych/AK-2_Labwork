#!/bin/bash

# якщо параметр N не передано, беремо 5
N=${1:-5}
OUTPUT_FILE="top_output.txt"

# текстовий зріз top, залишаємо лише перші N рядків
top -b -n 1 | head -n "$N" > "$OUTPUT_FILE"

echo "Результат top збережено в $OUTPUT_FILE (перші $N рядків):"
cat "$OUTPUT_FILE"
