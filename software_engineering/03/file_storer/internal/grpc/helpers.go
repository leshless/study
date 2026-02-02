package grpc

import (
	"swe3/file_storer/internal/domain"
	"swe3/library/go/xerrors"

	"google.golang.org/grpc/status"
)

func grpcError(err error) error {
	if err == nil {
		return nil
	}

	if xerr, ok := err.(xerrors.Error); ok {
		return status.Error(xerr.Code().GRPCCode(), xerr.Message())
	}

	return status.Error(domain.NewInternalError().Code().GRPCCode(), err.Error())
}
