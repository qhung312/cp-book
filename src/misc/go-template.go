package main

import (
	"fmt"
	"bufio"
	"os"
	"strconv"
)

var (
	scanner = bufio.NewScanner(os.Stdin)
	// writer = bufio.NewWriter(os.Stdout)
)

func next() string { scanner.Scan(); return scanner.Text() }
func nextInt() int { n, _ := strconv.Atoi(next()); return n }
func nextLong() int64 { n, _ := strconv.ParseInt(next(), 10, 64); return n }
func nextFLoat() float32 { n, _ := strconv.ParseFloat(next(), 32); return float32(n) }
func nextDouble() float64 { n, _ := strconv.ParseFloat(next(), 64); return n }

func main() {
	scanner.Split(bufio.ScanWords)
}

