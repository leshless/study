package http

import (
	"context"
	api "swe3/file_analyzer/api/http"
	"swe3/file_analyzer/internal/domain"
	"swe3/file_analyzer/internal/logic"
	"swe3/file_analyzer/internal/telemetry"

	"github.com/leshless/golibrary/xslices"
)

//go:generate go run github.com/leshless/golibrary/constructor_generator

// @PublicPointerInstance
type handler struct {
	logger              telemetry.Logger
	createReportUsecase logic.CreateReportUsecase
	listReportsUsecase  logic.ListReportsUsecase
}

var _ api.StrictServerInterface = (*handler)(nil)

func (h *handler) CreateReport(ctx context.Context, req api.CreateReportRequestObject) (api.CreateReportResponseObject, error) {
	args := logic.NewCreateReportArgs(
		req.WorkName,
		req.SubmissionID,
	)

	res, err := h.createReportUsecase.Execute(ctx, args)
	if err != nil {
		h.logger.Error("failed to create report")
		return &api.CreateReportdefaultJSONResponse{
			Body:       httpError(err),
			StatusCode: httpStatus(err),
		}, nil
	}

	return &api.CreateReport200JSONResponse{
		Report: api.Report{
			Id:                   res.Report.ID,
			SubmissionId:         res.Report.SubmissionID,
			OriginalityPercent:   float32(res.Report.OriginalityPercent),
			SimilarSubmissionIds: res.Report.SimilarSubmissionIDs,
			CreationTime:         res.Report.CreatedTime,
		},
	}, nil
}

func (h *handler) ListReports(ctx context.Context, req api.ListReportsRequestObject) (api.ListReportsResponseObject, error) {
	args := logic.NewListReportsArgs(req.WorkName)

	res, err := h.listReportsUsecase.Execute(ctx, args)
	if err != nil {
		h.logger.Error("failed to list reports")
		return &api.ListReportsdefaultJSONResponse{
			Body:       httpError(err),
			StatusCode: httpStatus(err),
		}, nil
	}

	httpReports := xslices.Map(res.Reports, func(report domain.Report) api.Report {
		return api.Report{
			Id:                   report.ID,
			SubmissionId:         report.SubmissionID,
			OriginalityPercent:   float32(report.OriginalityPercent),
			SimilarSubmissionIds: report.SimilarSubmissionIDs,
			CreationTime:         report.CreatedTime,
		}
	})

	return &api.ListReports200JSONResponse{
		Reports: &httpReports,
	}, nil
}
