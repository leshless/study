package domain

import "time"

//go:generate go run github.com/leshless/golibrary/constructor_generator

// @PublicValueInstance
type Report struct {
	ID                   string
	WorkName             string
	SubmissionID         string
	OriginalityPercent   float64
	SimilarSubmissionIDs []string
	CreatedTime          time.Time
}
