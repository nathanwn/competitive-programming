package main

// Usage: use heap.<Operation>(heapObject) where heap is imported from "container/heap"

type Heap struct {
	data []interface{}
	less func(interface{}, interface{}) bool
}

func (h *Heap) Len() int {
	return len(h.data)
}

func (h *Heap) Less(i, j int) bool {
	return h.less(h.data[i], h.data[j])
}

func (h *Heap) Swap(i, j int) {
	h.data[i], h.data[j] = h.data[j], h.data[i]
}

func (h *Heap) Push(x interface{}) {
	h.data = append(h.data, x)
}

func (h *Heap) Pop() interface{} {
	old := h.data
	n := len(old)
	x := old[n-1]
	h.data = old[0 : n-1]
	return x
}

func (h *Heap) Peek() interface{} {
	return h.data[0]
}

func NewHeap(less func(interface{}, interface{}) bool) *Heap {
	return &Heap{data: []interface{}{}, less: less}
}
