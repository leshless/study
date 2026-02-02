package http

import (
	"net/http"
	api "swe3/file_analyzer/api/http"
	"swe3/file_analyzer/internal/domain"
	"swe3/library/go/xerrors"
)

func httpError(err error) api.Error {
	if err == nil {
		return api.Error{}
	}

	var message string
	if xerr, ok := err.(xerrors.Error); ok {
		message = xerr.Error()
	} else {
		message = domain.NewInternalError().Message()
	}

	return api.Error{
		Message: message,
	}
}

func httpStatus(err error) int {
	if err == nil {
		return http.StatusOK
	}

	var httpStatus int
	if xerr, ok := err.(xerrors.Error); ok {
		httpStatus = xerr.Code().HTTPStatus()
	} else {
		httpStatus = domain.NewInternalError().Code().HTTPStatus()
	}

	return httpStatus
}
