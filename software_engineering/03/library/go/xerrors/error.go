package xerrors

// Error is a general for logic and provider levels produced errors
// Code() is a special grpc-like code which affects logic
// Message() is a public error text which is accessible by users
type Error interface {
	Code() Code
	Error() string
	Message() string
}
