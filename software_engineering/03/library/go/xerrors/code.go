package xerrors

import (
	"net/http"

	"github.com/leshless/golibrary/xmaps"
	"google.golang.org/grpc/codes"
)

type Code uint8

const (
	CodeOK Code = iota
	CodeUnknown
	CodeInternal
	CodeInvalidArgument
	CodeDeadlineExceeded
	CodeNotFound
	CodeAlreadyExists
	CodeResourceExhausted
	CodeFailedPrecondition
	CodeUnauthenticated
	CodePermissionDenied
	CodeUnimplemented
)

var codeToString = map[Code]string{
	CodeOK:                 "OK",
	CodeUnknown:            "UNKNOWN",
	CodeInternal:           "INTERNAL",
	CodeInvalidArgument:    "INVALID_ARGUMENT",
	CodeDeadlineExceeded:   "DEADLINE_EXCEEDED",
	CodeNotFound:           "NOT_FOUND",
	CodeAlreadyExists:      "ALREADY_EXISTS",
	CodeResourceExhausted:  "RESOURCE_EXHAUSTED",
	CodeFailedPrecondition: "FAILED_PRECONDITION",
	CodeUnauthenticated:    "UNAUTHENTICATED",
	CodePermissionDenied:   "PERMISSION_DENIED",
	CodeUnimplemented:      "UNIMPLEMENTED",
}

func (c Code) String() string {
	if str, ok := codeToString[c]; ok {
		return str
	}

	return codeToString[CodeUnknown]
}

var codeToHTTPStatus = map[Code]int{
	CodeOK:                 http.StatusOK,
	CodeUnknown:            http.StatusInternalServerError,
	CodeInternal:           http.StatusInternalServerError,
	CodeInvalidArgument:    http.StatusBadRequest,
	CodeDeadlineExceeded:   http.StatusRequestTimeout,
	CodeNotFound:           http.StatusNotFound,
	CodeAlreadyExists:      http.StatusConflict,
	CodeResourceExhausted:  http.StatusPreconditionFailed,
	CodeFailedPrecondition: http.StatusPreconditionFailed,
	CodeUnauthenticated:    http.StatusUnauthorized,
	CodePermissionDenied:   http.StatusForbidden,
	CodeUnimplemented:      http.StatusNotImplemented,
}

func (c Code) HTTPStatus() int {
	if httpStatus, ok := codeToHTTPStatus[c]; ok {
		return httpStatus
	}

	return codeToHTTPStatus[CodeUnknown]
}

var codeToGRPCCode = map[Code]codes.Code{
	CodeOK:                 codes.OK,
	CodeUnknown:            codes.Unknown,
	CodeInternal:           codes.Internal,
	CodeInvalidArgument:    codes.InvalidArgument,
	CodeDeadlineExceeded:   codes.DeadlineExceeded,
	CodeNotFound:           codes.NotFound,
	CodeAlreadyExists:      codes.AlreadyExists,
	CodeResourceExhausted:  codes.ResourceExhausted,
	CodeFailedPrecondition: codes.FailedPrecondition,
	CodeUnauthenticated:    codes.Unauthenticated,
	CodePermissionDenied:   codes.PermissionDenied,
	CodeUnimplemented:      codes.Unimplemented,
}

var codeFromGRPCCode = xmaps.Reverse(codeToGRPCCode)

func (c Code) GRPCCode() codes.Code {
	if grpcCode, ok := codeToGRPCCode[c]; ok {
		return grpcCode
	}

	return codeToGRPCCode[CodeUnknown]
}

func CodeFromGRPC(grpcCode codes.Code) Code {
	if code, ok := codeFromGRPCCode[grpcCode]; ok {
		return code
	}

	return codeFromGRPCCode[codes.Unknown]
}
