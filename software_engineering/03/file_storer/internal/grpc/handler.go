package grpc

import (
	"context"
	api "swe3/file_storer/api/grpc"
	"swe3/file_storer/internal/logic"
	"swe3/file_storer/internal/telemetry"

	"google.golang.org/protobuf/types/known/timestamppb"
)

//go:generate go run github.com/leshless/golibrary/constructor_generator

// @PublicPointerInstance
type submissionsHandler struct {
	api.UnimplementedSubmissionsServer

	logger                     telemetry.Logger
	listWorkSubmissionsUsecase logic.ListWorkSubmissionsUsecase
}

var _ api.SubmissionsServer = (*submissionsHandler)(nil)

func (h *submissionsHandler) ListWorkSubmissions(ctx context.Context, req *api.ListWorkSubmissionsRequest) (*api.ListWorkSubmissionsResponse, error) {
	args := logic.NewListWorkSubmissionsArgs(req.GetWorkName())

	res, err := h.listWorkSubmissionsUsecase.Execute(ctx, args)
	if err != nil {
		h.logger.Error("failed to list work submissions")
		return nil, grpcError(err)
	}

	var apiSubmissions []*api.Submission
	for i, submission := range res.Submissions {
		apiSubmission := &api.Submission{
			ID:           submission.ID,
			WorkName:     submission.WorkName,
			StudentName:  submission.StudentName,
			CreationTime: timestamppb.New(submission.CreatedTime),
			File:         res.Files[i],
		}
		apiSubmissions = append(apiSubmissions, apiSubmission)
	}

	return &api.ListWorkSubmissionsResponse{
		Submissions: apiSubmissions,
	}, nil
}
