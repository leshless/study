package filestorer

import (
	"context"
	"swe3/file_analyzer/internal/domain"
	"swe3/file_analyzer/internal/telemetry"
	filestorerapi "swe3/file_storer/api/grpc"

	"github.com/leshless/golibrary/xslices"
)

//go:generate go run github.com/leshless/golibrary/constructor_generator

type Adapter interface {
	ListWorkSubmissions(ctx context.Context, workName string) ([]domain.Submission, error)
}

var _ Adapter = (*adapter)(nil)

// @PublicPointerInstance
type adapter struct {
	logger telemetry.Logger
	client filestorerapi.SubmissionsClient
}

func (a *adapter) ListWorkSubmissions(ctx context.Context, workName string) ([]domain.Submission, error) {
	req := &filestorerapi.ListWorkSubmissionsRequest{
		WorkName: workName,
	}

	res, err := a.client.ListWorkSubmissions(ctx, req)
	if err != nil {
		a.logger.Error("failed to list work submissions grpc", telemetry.Error(err))
		return nil, domain.NewInternalError()
	}

	if len(res.GetSubmissions()) == 0 {
		return nil, domain.NewSubmissionNotFoundError()
	}

	return xslices.Map(res.GetSubmissions(), func(grpcSubmission *filestorerapi.Submission) domain.Submission {
		return domain.NewSubmission(
			grpcSubmission.ID,
			grpcSubmission.WorkName,
			grpcSubmission.StudentName,
			grpcSubmission.File,
			grpcSubmission.CreationTime.AsTime(),
		)
	}), nil
}
