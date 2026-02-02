package domain

import "time"

//go:generate go run github.com/leshless/golibrary/constructor_generator

// @PublicValueInstance
type Submission struct {
	ID          string
	WorkName    string
	StudentName string
	ObjectID    string
	CreatedTime time.Time
}
