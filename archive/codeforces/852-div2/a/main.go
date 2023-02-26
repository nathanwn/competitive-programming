package main

import (
	"bufio"
	"fmt"
	"os"
)

// Copied from: https://cs.opensource.google/go/x/exp/+/master:constraints/constraints.go

// Signed is a constraint that permits any signed integer type.
// If future releases of Go add new predeclared signed integer types,
// this constraint will be modified to include them.
type Signed interface {
	~int | ~int8 | ~int16 | ~int32 | ~int64
}

// Unsigned is a constraint that permits any unsigned integer type.
// If future releases of Go add new predeclared unsigned integer types,
// this constraint will be modified to include them.
type Unsigned interface {
	~uint | ~uint8 | ~uint16 | ~uint32 | ~uint64 | ~uintptr
}

// Integer is a constraint that permits any integer type.
// If future releases of Go add new predeclared integer types,
// this constraint will be modified to include them.
type Integer interface {
	Signed | Unsigned
}

// Float is a constraint that permits any floating-point type.
// If future releases of Go add new predeclared floating-point types,
// this constraint will be modified to include them.
type Float interface {
	~float32 | ~float64
}

// Complex is a constraint that permits any complex numeric type.
// If future releases of Go add new predeclared complex numeric types,
// this constraint will be modified to include them.
type Complex interface {
	~complex64 | ~complex128
}

// Ordered is a constraint that permits any ordered type: any type
// that supports the operators < <= >= >.
// If future releases of Go add new ordered types,
// this constraint will be modified to include them.
type Ordered interface {
	Integer | Float | ~string
}

func ReadInt(in *bufio.Reader) (value int) {
	_, _ = fmt.Fscan(in, &value)
	return value
}

func ReadInt64(in *bufio.Reader) (value int64) {
	_, _ = fmt.Fscan(in, &value)
	return
}

func Println(out *bufio.Writer, a ...interface{}) { _, _ = fmt.Fprintln(out, a...) }

func Min[T Ordered](x, y T) T {
	if x < y {
		return x
	}
	return y
}

func main() {
	var (
		in  *bufio.Reader = bufio.NewReader(os.Stdin)
		out *bufio.Writer = bufio.NewWriter(os.Stdout)
	)

	defer func() {
		_ = out.Flush()
	}()

	T := ReadInt(in)
	for t := 0; t < T; t++ {
		Solve(in, out)
	}
}

// Solution starts here

func Solve(in *bufio.Reader, out *bufio.Writer) {
	p1 := ReadInt(in)
	p2 := ReadInt(in)
	n := ReadInt(in)
	m := ReadInt(in)

	var cost int64
	cost = 0

	// Buy x * (m + 1) potatoes.
	if p1*m < p2*(m+1) {
		cost += int64(n/(m+1)) * int64(p1) * int64(m)
	} else {
		cost += int64(n/(m+1)) * int64(p2) * int64(m+1)
	}

	// Buy the rest.
	if p1 < p2 {
		cost += int64(n%(m+1)) * int64(p1)
	} else {
		cost += int64(n%(m+1)) * int64(p2)
	}

	Println(out, cost)
}
