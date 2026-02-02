package http

import (
	"context"
	"encoding/json"
	"io"
	api "swe3/file_storer/api/http"
	"swe3/file_storer/internal/domain"
	"swe3/file_storer/internal/logic"
	"swe3/file_storer/internal/telemetry"
)

//go:generate go run github.com/leshless/golibrary/constructor_generator

// @PublicPointerInstance
type handler struct {
	logger                  telemetry.Logger
	createSubmissionUsecase logic.CreateSubmissionUsecase
}

var _ api.StrictServerInterface = (*handler)(nil)

const (
	maxMultipartSize = 16 * (1 << 20) // 16 MB
	maxFileSize      = maxMultipartSize
)

func (h *handler) CreateSubmission(ctx context.Context, reqObject api.CreateSubmissionRequestObject) (api.CreateSubmissionResponseObject, error) {
	form, err := reqObject.Body.ReadForm(maxMultipartSize)
	if err != nil {
		return api.CreateSubmissiondefaultJSONResponse{
			Body:       httpError(err),
			StatusCode: httpStatus(err),
		}, nil
	}
	defer form.RemoveAll()

	requestValues := form.Value["request"]
	if len(requestValues) == 0 {
		err := domain.NewInvalidArgumentError()
		return api.CreateSubmissiondefaultJSONResponse{
			Body:       httpError(err),
			StatusCode: httpStatus(err),
		}, nil
	}

	var req api.CreateSubmissionRequest
	if err := json.Unmarshal([]byte(requestValues[0]), &req); err != nil {
		err := domain.NewInvalidArgumentError()
		return api.CreateSubmissiondefaultJSONResponse{
			Body:       httpError(err),
			StatusCode: httpStatus(err),
		}, nil
	}

	fileHeaders := form.File["file"]
	if len(fileHeaders) == 0 {
		err := domain.NewInvalidArgumentError()
		return api.CreateSubmissiondefaultJSONResponse{
			Body:       httpError(err),
			StatusCode: httpStatus(err),
		}, nil
	}

	file, err := fileHeaders[0].Open()
	if err != nil {
		return api.CreateSubmissiondefaultJSONResponse{
			Body:       httpError(err),
			StatusCode: httpStatus(err),
		}, nil
	}
	defer file.Close()

	data, err := io.ReadAll(file)
	if err != nil {
		return api.CreateSubmissiondefaultJSONResponse{
			Body:       httpError(err),
			StatusCode: httpStatus(err),
		}, nil
	}

	if len(data) > maxFileSize {
		err := domain.NewFileIsTooLargeError()
		return api.CreateSubmissiondefaultJSONResponse{
			Body:       httpError(err),
			StatusCode: httpStatus(err),
		}, nil
	}

	args := logic.NewCreateSubmissionArgs(reqObject.WorkName, req.StudentName, data)

	res, err := h.createSubmissionUsecase.Execute(ctx, args)
	if err != nil {
		return api.CreateSubmissiondefaultJSONResponse{
			Body:       httpError(err),
			StatusCode: httpStatus(err),
		}, nil
	}

	return api.CreateSubmission200JSONResponse{
		SubmissionId: res.SubmissionID,
	}, nil
}
