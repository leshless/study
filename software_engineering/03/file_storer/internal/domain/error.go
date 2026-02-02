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
CodeInvalidArgument
file too large
Uploaded file is too large
*/
type FileIsTooLargeError struct{}

/*
CodeNotFound
submission not found
Submission not found
*/
type SubmissionNotFoundError struct{}
