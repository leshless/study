package domain

import time "time"

//go:generate go run github.com/leshless/golibrary/constructor_generator

// @PublicValueInstance
type Submission struct {
	ID           string
	WorkName     string
	StudentName  string
	File         []byte
	CreationTime time.Time
}
