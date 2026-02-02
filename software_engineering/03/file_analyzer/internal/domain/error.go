package domain

//go:generate go run swe3/library/go/xerrors/generator

/*
CodeUnknown
unknown
Unknown error
*/
type UnknownError struct{}

/*
CodeInternal
internal
Internal error
*/
type InternalError struct{}

/*
CodeInvalidArgument
invalid argument
Invalid argument
*/
type InvalidArgumentError struct{}

/*
CodeUnimplemented
unimplemented
This feature is not implemented yet
*/
type UnimplementedError struct{}

/*
CodeNotFound
submission not found
Submission with requested paremeters not found
*/
type SubmissionNotFoundError struct{}
